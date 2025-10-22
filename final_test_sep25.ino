#include <EnableInterrupt.h>
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

// motor driver pins
const int EN1_PIN = 9;
const int IN1_PIN = 8;
const int IN2_PIN = 7;
const int IN3_PIN = 10;
const int IN4_PIN = 12;
const int EN2_PIN = 11;


// the final values that we have read
// to be used by our sketch outside of the RC code
// 16 bit integer: 0…65535
uint16_t rc_values[RC_NUM_CHANNELS];
// keeps track of the time that the pulses start
uint32_t rc_start[RC_NUM_CHANNELS];
// holds the values for each channel until they can be copied into rc_values[]
// volatile because it can be updated from the interrupt service routines at any time
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

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

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }

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

  pinMode(9, OUTPUT); //en1
  pinMode(8, OUTPUT); //in1
  pinMode(7, OUTPUT); //in2

  pinMode(11, OUTPUT); //en2
  pinMode(10, OUTPUT); //in3
  pinMode(12, OUTPUT); //in4

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
  if (rc_values[RC_CH1] > 1700) 
    forward(map(rc_values[RC_CH1], 1700, 2300, 0, 255));
  if (rc_values[RC_CH1] < 1300) 
    reverse(map(rc_values[RC_CH1], 600, 1300, 0, 255));
  if ((rc_values[RC_CH1] < 1700) && (rc_values[RC_CH1] > 1300)) 
    stop();

// robot moving right and left using Hobby RC controller
  if (rc_values[RC_CH2] > 1700) 
    right(map(rc_values[RC_CH2], 1700, 2500, 0, 255));
  if (rc_values[RC_CH2] < 1300) 
    left (map(rc_values[RC_CH2], 600, 1300, 0, 255));

}

void forward(int value) {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(EN1_PIN, value);

  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(EN2_PIN, value);   
}

void reverse(int value) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(EN1_PIN, value);

  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(EN2_PIN, value);            
}

void right(int value) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(EN1_PIN, value);

  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(EN2_PIN, value);      
}

void left(int value) {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(EN1_PIN, value);

  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(EN2_PIN, value);            
}


void stop(){
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}