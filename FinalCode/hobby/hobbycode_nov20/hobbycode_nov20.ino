#include <EnableInterrupt.h>
    
    #define SERIAL_PORT_SPEED 9600
    #define RC_NUM_CHANNELS  4
    
    #define RC_CH1  0
    #define RC_CH2  1
    #define RC_CH3  2
    #define RC_CH4  3

    // pin usage
    // radio pins
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


// --- Add these variables for smoothing motor transitions ---
float currentSpeedA = 0;
float currentSpeedB = 0;
int targetSpeedA = 0;
int targetSpeedB = 0;

// Adjust this value between 0.0 and 1.0. 
// A smaller value means a smoother, slower transition.
const float LERP_FACTOR = 0.1; 

const float TURN_FACTOR = 1.5;

    
    uint16_t rc_values[RC_NUM_CHANNELS];
    uint32_t rc_start[RC_NUM_CHANNELS];
    volatile uint16_t rc_shared[RC_NUM_CHANNELS];
    
    void rc_read_values() {
      noInterrupts();
      memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
      interrupts();
    }
    
    void calc_input(uint8_t channel, uint8_t input_pin) {
      if (digitalRead(input_pin) == HIGH) {
        rc_start[channel] = micros();
      } else {
        uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
        rc_shared[channel] = rc_compare;
      }
    }
    
    void calc_ch1() {
      calc_input(RC_CH1, RC_CH1_PIN);
    }
    void calc_ch2() {
      calc_input(RC_CH2, RC_CH2_PIN);
    }
    void calc_ch3() {
      calc_input(RC_CH3, RC_CH3_PIN);
    }
    void calc_ch4() {
      calc_input(RC_CH4, RC_CH4_PIN);
    }
    
    void setup() {
      Serial.begin(SERIAL_PORT_SPEED);
    
      pinMode(RC_CH1_PIN, INPUT); //side wheel
      pinMode(RC_CH2_PIN, INPUT); //trigger
      pinMode(RC_CH3_PIN, INPUT); //side knob
      pinMode(RC_CH4_PIN, INPUT); //bottom button
    
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
  rc_read_values();

  // --- Check the state of each controller channel ---
  bool isMovingForward = rc_values[RC_CH2] > 1600;
  bool isMovingReverse = rc_values[RC_CH2] < 1500;
  bool isTurningRight = rc_values[RC_CH1] > 1600;
  bool isTurningLeft = rc_values[RC_CH1] < 1300;

  // --- Map controller values to speed ---
  int throttleSpeed = 0;
  if (isMovingForward) {
    throttleSpeed = map(rc_values[RC_CH2], 1600, 2300, 50, 255);
  } else if (isMovingReverse) {
    throttleSpeed = map(rc_values[RC_CH2], 1500, 600, 50, 255);
  }

  int steerSpeed = 0;
  if (isTurningRight) {
    steerSpeed = map(rc_values[RC_CH1], 1600, 2300, 50, 255);
  } else if (isTurningLeft) {
    steerSpeed = map(rc_values[RC_CH1], 1300, 600, 50, 255);
  }

  // --- Main Control Logic ---
  // The logic checks for combined movements first.
  if (isMovingForward && isTurningRight) {
    forwardRight(throttleSpeed);
  } else if (isMovingForward && isTurningLeft) {
    forwardLeft(throttleSpeed);
  } else if (isMovingReverse && isTurningRight) {
    reverseRight(throttleSpeed);
  } else if (isMovingReverse && isTurningLeft) {
    reverseLeft(throttleSpeed);
  } else if (isMovingForward) {
    forward(throttleSpeed); // Straight forward
  } else if (isMovingReverse) {
    reverse(throttleSpeed); // Straight reverse
  } else if (isTurningRight) {
    right(steerSpeed);      // Turn on the spot
  } else if (isTurningLeft) {
    left(steerSpeed);       // Turn on the spot
  } else {
    stop();                 // All controls are neutral
  }
  
  // This function smoothly applies the speed changes
  updateMotorSpeeds();
  delay(20);
} 

    
void forward(int value) {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  targetSpeedA = value;
  targetSpeedB = value;
}

void reverse(int value) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);

  // Trim adjustment to keep straight in reverse
  targetSpeedA = value;           // Left motor
  targetSpeedB = value;   // Right motor slightly reduced   * 0.92; 
}

void left(int value) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  targetSpeedA = value;
  targetSpeedB = value;
}

void right(int value) {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  targetSpeedA = value;
  targetSpeedB = value;
}

void forwardRight(int speed) {
  // Both motors forward
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  
  // Slow down the right motor to turn right
  targetSpeedA = speed; 
  targetSpeedB = speed * TURN_FACTOR;
}

void forwardLeft(int speed) {
  // Both motors forward
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);

  // Slow down the left motor to turn left
  targetSpeedA = speed * TURN_FACTOR;
  targetSpeedB = speed;
}

void reverseRight(int speed) {
  // Both motors in reverse
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);

  // Slow down the right motor to turn right
  targetSpeedA = speed;
  targetSpeedB = speed * TURN_FACTOR;
}

void reverseLeft(int speed) {
  // Both motors in reverse
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);

  // Slow down the left motor to turn left
  targetSpeedA = speed * TURN_FACTOR;
  targetSpeedB = speed;
}

void stop() {

  targetSpeedA = 0;
  targetSpeedB = 0;
}

void updateMotorSpeeds() {
  // Linearly interpolate the current speed towards the target speed
  currentSpeedA += (targetSpeedA - currentSpeedA) * LERP_FACTOR;
  currentSpeedB += (targetSpeedB - currentSpeedB) * LERP_FACTOR;

  // Apply the calculated smoothed speed to the motor driver
  analogWrite(EN1_PIN, (int)currentSpeedA);
  analogWrite(EN2_PIN, (int)currentSpeedB);
}