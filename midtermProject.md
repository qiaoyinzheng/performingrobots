# midtermProject according to syllabus
Performing Robots Fall 2025  Joy Zheng & Mariam

## Project goal
Complete a robot base that can:
- Move forward and backward
- Turn left and right
- Operate at different speeds
- Select a personality for the robot base and express it using only movement

--- 
## Timeline and build process

### Sep 4. Base preparation
- Cut robot base to 40 cm width in the scene shop
- Started planning how electronics would be attached to the base
- Cut additional base support pieces for stability

<img src="https://github.com/user-attachments/assets/457d9c3e-dcf6-4668-844b-0ecc8ec81ab7" alt="Base Support Cutting" width="250" style="height:auto;" />


### Sep 23. Motor control and soldering fundamentals
- Learned soldering techniques in class
- Learned L298 motor driver and H-bridge basics
- Reviewed L298 interface board and Arduino shield
- Continued planning mounting points so components could be attached cleanly to the base

**Key lecture focus**
- Heat shrink tubing
- Stranded wire to board connections
- Pins and header sockets
- Wire mapping
- Ensuring header pins are straight
- Avoiding short circuits
- Placing components on the correct side of the board


### Sep 25. Arduino soldering and remote control integration

#### Electronics assembly
- Mounted the Arduino on the robot base
- Mounted the L298 H-bridge
- Mounted the battery and power bank
- Soldered headers on the PCB labeled Arduino Shield Hobby RC and Motor Control
- Installed RC receiver header sockets and ensured equal height
- Installed Arduino feed-through headers and aligned them correctly
- Soldered the header socket and screw terminal on the PCB labeled L298 Interface
- Wired between Arduino Shield and L298 Interface PCB

<img src="https://github.com/user-attachments/assets/bf65d4a6-c749-4e1e-a3c8-c8b8487a5cc9" alt="Arduino Soldering" width="250" style="height:auto;" />

<img src="https://github.com/user-attachments/assets/1b396cde-1561-4e67-8fcc-66b3744266d6" alt="Testing Transmitter" width="250" style="height:auto;" />


#### Wire mapping
I used color-labeled wires to make debugging and reasoning about connections more intuitive.
<img src="https://github.com/user-attachments/assets/a0ca8aa2-25c6-4ad8-9d7a-223e91d6b7a0" alt="Color Label Wire" width="250" style="height:auto;" />

#### Power configuration
- Red wire from the corner of the L298 connected to the + terminal of the coax connector
- Coax connector ground connected to the GND on the L298 Interface PCB
- Additional ground wire connected from the L298 Interface PCB to the L298 H-bridge screw terminal

#### Remote control testing
- Plugged in RC receiver with correct orientation using PCB labels
- Verified +5V, GND, and signal alignment
- Read pairing instructions from RC4GS user manual
- Tested RC input using provided code
- Combined RC input code with motor control logic

#### Result
- Successfully controlled forward, backward, turning, and speed variation
- Base movement fully functional
- Robot base finished



## Hardware overview

- Arduino microcontroller
- Arduino Shield Hobby RC and Motor Control
- L298 H-bridge motor driver
- DC motors with differential drive
- RC receiver and transmitter
- Battery and power bank



## Control logic and code structure

### Motor pin configuration

const int LEFT_MOTOR_EN = 9;
const int LEFT_MOTOR_INA = 8;
const int LEFT_MOTOR_INB = 7;

const int RIGHT_MOTOR_EN = 11;
const int RIGHT_MOTOR_IN1 = 10;
const int RIGHT_MOTOR_IN2 = 12;

### Speed control

* Used analogWrite() on enable pins to control motor speed
* Tested different PWM values to create slow, medium, and fast movement states

### RC behavior logic

* Neutral stick position stops the robot
* Forward stick moves robot forward
* Turning achieved through differential motor control
* Code adapted from lecture examples



## Robot personality through movement

### Personality concept

**A worried multitasking mom**
Always moving, slightly rushed, switching tasks quickly, and occasionally aggressive when stressed.

### Movement language

**Idle behavior**

* Moves forward and backward repeatedly while “talking”
* Feels restless and never fully still

**Dance behavior**

* Turns in a full circle
* Reads as performative and expressive

**Angry behavior**

* Moves forward very quickly
* Pan raised while advancing
* Aggressive and direct

**Signature move**

* Rapid short movements forward and backward
* Slight turns
* Feels anxious, busy, and multitasking

--- 

## Reflection

### What worked

* Color labeling wires made debugging significantly easier
* RC control allowed expressive movement without additional sensors
* Differential drive provided clear personality expression using only motion

### What was challenging

* Revise the code to achieve ideal speed and angle

### What I would improve

* More refined speed curves for smoother personality transitions


