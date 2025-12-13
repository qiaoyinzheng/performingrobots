#include <EnableInterrupt.h>
#include <Servo.h>
// include library

// preprocessor macro tells the compiler to do a text substitution before compiling 
#define SERIAL_PORT_SPEED 9600
#define RC_NUM_CHANNELS  4

// access the specific channels in arrays
#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

// pin usage
// radio pins
// define the pins that the signals are connected to
#define RC_CH1_PIN  6
#define RC_CH2_PIN  5
#define RC_CH3_PIN  4
#define RC_CH4_PIN  3

// the final values that we have read
// to be used by our sketch outside of the RC code
// 16 bit integer: 0…65535
uint16_t rc_values[RC_NUM_CHANNELS];
// keeps track of the time that the pulses start
uint32_t rc_start[RC_NUM_CHANNELS];
// holds the values for each channel until they can be copied into rc_values[]
// volatile because it can be updated from the interrupt service routines at any time
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

// motor driver pins
const int LEFT_MOTOR_EN = 9;
const int LEFT_MOTOR_INA = 8;
const int LEFT_MOTOR_INB = 7;

const int RIGHT_MOTOR_EN = 11;
const int RIGHT_MOTOR_INA = 10;
const int RIGHT_MOTOR_INB = 12;

// const int EN1_PIN = 9;
// const int IN1_PIN = 8;
// const int IN2_PIN = 7;
// const int IN3_PIN = 10;
// const int IN4_PIN = 12;
// const int EN2_PIN = 11;

int currentSpeedLeftMotor = 0;
int currentSpeedRightMotor = 0;
int desiredSpeedLeftMotor = 0;
int desiredSpeedRightMotor = 0;
int stepSize;


Servo LeftArm;
Servo RightArm;

const int LeftArmPin  = 18; // M5 = 18  (Left hand)
const int RightArmPin = 16; // M4 = 16  (Right hand)


void rc_read_values() {
  // simply copies the volatile rc_shared[] values into the rc_values[] array
  // disable interrupts to ensure that the interrupts do not trigger and alter the memory as we’re trying to read it
  noInterrupts();
  // memcpy(destination, source, number of bytes to copy)
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  // checking HIGH: beginning of pulse (e.g. we are on the leading edge of the pulse)
  if (digitalRead(input_pin) == HIGH) {
    // store time which pulse is start for later comparison
    rc_start[channel] = micros();
  // if LOW: end of pulse
  } else {
    // compare the current micros() to the value that we previously stored in rc_start[]
    // result = the position of our transmitter stick
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_PIN); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_PIN); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_PIN); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_PIN); }

void setup() {
  // opening a serial port so we can look at the RC values after we’ve read them
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_PIN, INPUT); //side wheel
  pinMode(RC_CH2_PIN, INPUT); //trigger
  pinMode(RC_CH3_PIN, INPUT); //side knob
  pinMode(RC_CH4_PIN, INPUT); //bottom button

  // calc_ch1 function will be called any time that pin’s value changes from high<>low
  enableInterrupt(RC_CH1_PIN, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_PIN, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_PIN, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_PIN, calc_ch4, CHANGE);


  pinMode(LEFT_MOTOR_EN, OUTPUT);
  pinMode(LEFT_MOTOR_INA, OUTPUT);
  pinMode(LEFT_MOTOR_INB, OUTPUT);

  pinMode(RIGHT_MOTOR_EN, OUTPUT);
  pinMode(RIGHT_MOTOR_INA, OUTPUT);
  pinMode(RIGHT_MOTOR_INB, OUTPUT);

  setupServoMotors();
}

void loop() {
  // prints out the values for viewing on the serial monitor
  rc_read_values();

  Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
  Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
  Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
  Serial.print("CH4:"); Serial.println(rc_values[RC_CH4]);

  delay(200);

// 1500 neural 1000-2000
// robot moving forward and in reverse using Hobby RC controller
// map(x, inMin, inMax, outMin, outMax) linearly remaps x from one range into another
// we flip the front size of the robot, so it's forward when rc_value is big
  if (rc_values[RC_CH1] > 1700) {
    reverse(map(rc_values[RC_CH1], 1700, 2300, 0, 255));
    // reverse(map(rc_values[RC_CH1], 600, 1300, 0, 255));
  } else if (rc_values[RC_CH1] < 1300) {
    forward(map(rc_values[RC_CH1], 600, 1300, 0, 255));
    // forward(map(rc_values[RC_CH1], 1700, 2300, 0, 255));

  } else if ((rc_values[RC_CH1] < 1550) && (rc_values[RC_CH1] > 1450)) 
    stop();

// robot moving right and left using Hobby RC controller
  if (rc_values[RC_CH2] > 1700) 
    rightTurn(map(rc_values[RC_CH2], 1700, 2500, 0, 255));
  if (rc_values[RC_CH2] < 1300) 
    leftTurn(map(rc_values[RC_CH2], 600, 1300, 0, 255));

  // movingArms();
  // delay(600);
  }


void forward(int mySpeed) {
  Serial.print("\tforward speed = ");
  Serial.print(mySpeed);
  Serial.println();
  stepSize = 20;
  leftMotorForward(mySpeed);
  rightMotorForward(mySpeed);
  // digitalWrite(LEFT_MOTOR_INA, HIGH);
  // digitalWrite(LEFT_MOTOR_INB, LOW);
  // analogWrite(LEFT_MOTOR_EN, mySpeed);

  // digitalWrite(RIGHT_MOTOR_INA, HIGH);
  // digitalWrite(RIGHT_MOTOR_INB, LOW);
  // analogWrite(RIGHT_MOTOR_EN, mySpeed);   
}

void leftMotorForward(int mySpeed) {
  digitalWrite(LEFT_MOTOR_INA, LOW);
  digitalWrite(LEFT_MOTOR_INB, HIGH);

  desiredSpeedLeftMotor = mySpeed;
  // currentSpeedLeftMotor = mySpeed; // this would cause immediate change
  // Serial.print("\tdesiredSpeedLeftMotor = ");
  // Serial.print(desiredSpeedLeftMotor);
  // Serial.println();
  updateLeftMotor();
}

void rightMotorForward(int mySpeed) {
  digitalWrite(RIGHT_MOTOR_INA, LOW);
  digitalWrite(RIGHT_MOTOR_INB, HIGH);
  desiredSpeedRightMotor = mySpeed;
  // currentSpeedRightMotor = mySpeed; // this would cause immediate change
  updateRightMotor();
}

void updateLeftMotor() {
  if (desiredSpeedLeftMotor > currentSpeedLeftMotor) {
    currentSpeedLeftMotor += stepSize;

  } else if (desiredSpeedLeftMotor < currentSpeedLeftMotor) {
    currentSpeedLeftMotor -= stepSize;
  }

  currentSpeedLeftMotor = constrain(currentSpeedLeftMotor, 0, 255);

  Serial.print("currentSpeedLeftMotor = ");
  Serial.print(currentSpeedLeftMotor);

  Serial.print("\tdesiredSpeedLeftMotor = ");
  Serial.print(desiredSpeedLeftMotor);
  // Serial.println("");
  analogWrite(LEFT_MOTOR_EN, currentSpeedLeftMotor);
}

void updateRightMotor() {
  if (desiredSpeedRightMotor > currentSpeedRightMotor) {
    currentSpeedRightMotor += stepSize;

  } else if (desiredSpeedRightMotor < currentSpeedRightMotor) {
    currentSpeedRightMotor -= stepSize;
  }

  currentSpeedRightMotor = constrain(currentSpeedRightMotor, 0, 255);

  Serial.print("\tcurrentSpeedRightMotor = ");
  Serial.print(currentSpeedRightMotor);
  Serial.print("\tdesiredSpeedRightMotor = ");
  Serial.print(desiredSpeedRightMotor);
  Serial.println("");

  analogWrite(RIGHT_MOTOR_EN, currentSpeedRightMotor);
}

void reverse(int mySpeed) {
  Serial.print("\treverse speed = ");
  Serial.print(mySpeed);
  Serial.println();

  stepSize = 20; 
  
  digitalWrite(LEFT_MOTOR_INA, HIGH);
  digitalWrite(LEFT_MOTOR_INB, LOW);

  digitalWrite(RIGHT_MOTOR_INA, HIGH);
  digitalWrite(RIGHT_MOTOR_INB, LOW);

  desiredSpeedLeftMotor  = mySpeed;
  desiredSpeedRightMotor = mySpeed;

  updateLeftMotor();
  updateRightMotor();           
}

void rightTurn(int mySpeed) {
  Serial.print("\tright turn speed = ");
  Serial.print(mySpeed);
  Serial.println();

  stepSize = 20;

  // Left wheel forward
  digitalWrite(LEFT_MOTOR_INA, LOW);
  digitalWrite(LEFT_MOTOR_INB, HIGH);

  // Right wheel backward
  digitalWrite(RIGHT_MOTOR_INA, HIGH);
  digitalWrite(RIGHT_MOTOR_INB, LOW);

  desiredSpeedLeftMotor  = mySpeed;
  desiredSpeedRightMotor = mySpeed;

  updateLeftMotor();
  updateRightMotor();
}

void leftTurn(int mySpeed) {
  Serial.print("\tleft turn speed = ");
  Serial.print(mySpeed);
  Serial.println();

  stepSize = 20;

  // Left wheel backward
  digitalWrite(LEFT_MOTOR_INA, HIGH);
  digitalWrite(LEFT_MOTOR_INB, LOW);

  // Right wheel forward
  digitalWrite(RIGHT_MOTOR_INA, LOW);
  digitalWrite(RIGHT_MOTOR_INB, HIGH);

  desiredSpeedLeftMotor  = mySpeed;
  desiredSpeedRightMotor = mySpeed;

  updateLeftMotor();
  updateRightMotor();
}



void stop(){
  if (currentSpeedLeftMotor == 0 && currentSpeedRightMotor == 0) {
    return;
  }

  stepSize = 5;

  desiredSpeedLeftMotor = 0;
  desiredSpeedRightMotor = 0;
  updateLeftMotor();
  updateRightMotor();
}


void setupServoMotors() {
  // Set up the arms
  LeftArm.attach(LeftArmPin);
  RightArm.attach(RightArmPin);

  // resting position
  int leftAngle = 0;
  int rightAngle = 0;
  LeftArm.write(leftAngle);
  RightArm.write(rightAngle);
}

// moving arms function to be called when needed
void movingArms() {
  for (int i = 0; i < 3; i++) {  // repeat the sequence
    // Move arms to 120/40
    LeftArm.write(120);
    RightArm.write(120);
    delay(500);

    // Move arms to 80/0
    LeftArm.write(0);
    RightArm.write(80);
    delay(500);

    // Repeat the same two poses
    LeftArm.write(0);
    RightArm.write(0);
    delay(500);

    LeftArm.write(20);
    RightArm.write(20);
    // delay(500);
  }
}
