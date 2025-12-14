# Performing Robots Fall 2025 - Joy Zheng & Mariam - Wife

## Robot Feature
### 1. NeoMatrix
- Design talking sprites
  - Regular (Marilyn Monroe)
  - Switching between closed mouth and open mouth
- Angry (Inside Out)
- Light up and black out NeoMatrix

### 2. Script + Sound (ElevenLabs)
- Organized voice lines into highlighted case blocks
  - https://docs.google.com/document/d/1EIHsOlQh53dqaFov1w1aS358Y4-wtV9ejwBwsOQNf1Q/edit?usp=sharing
- Adding Audio Tags using V3 Tag Generator
  - https://audio-generation-plugin.com/elevenlabs-v3-tag-generator/
- Generate voice using ElevenLabs
  - https://elevenlabs.io/voice-library/mother
  - The Multitasking Mom, English, Eleven V3 (Alpha), mid speed
- Export clips
- Send to SD cards

### 3. Servos
- Ear wiggles when dancing
- Dance move
- Raise pan when angry

---

## Timeline

### Sep 4 Base prep
- Cut base to 40 cm width in the scene shop
- Started planning how electronics will be attached to the base

### Sep 23
- Learned soldering in class
- Learned L298 motor and H-bridge basics
- Continued planning mounting points so components can be attached cleanly to the base

### Sep 25
**Arduino Soldering & Connecting**  
<img src="https://github.com/user-attachments/assets/bf65d4a6-c749-4e1e-a3c8-c8b8487a5cc9" alt="Arduino Soldering" width="250" style="height:auto;" />

**Testing RC Transmitter**  
<img src="https://github.com/user-attachments/assets/1b396cde-1561-4e67-8fcc-66b3744266d6" alt="Testing Transmitter" width="250" style="height:auto;" />

- Attached Arduino and power bank onto the base
- Learned hobby RC workflow
- Edited code and successfully controlled turning and driving
- Base finished

### Sep 30
- Learned cardboard building techniques using triangle supports
- Started designing the robot body structure

### Oct 2
<img src="https://github.com/user-attachments/assets/a3e58bad-e634-40e1-ab1e-58697cf8e3a9" alt="Prototyping" width="250" style="height:auto;" />
<img src="https://github.com/user-attachments/assets/3e4228b0-a1c9-4125-b834-30c5b01becab" alt="Size Sketch" width="250" style="height:auto;" />
<img src="https://github.com/user-attachments/assets/56a9a19a-a2cc-45f7-863c-713b59e43d96" alt="Building" width="250" style="height:auto;" />

### Oct 9
<img src="https://github.com/user-attachments/assets/ccb640eb-003d-4e76-a442-d628d5e60197" alt="Arm Building & Measuring 1" width="250" style="height:auto;" />
<img src="https://github.com/user-attachments/assets/4181a628-df42-4f8c-92d1-8848817d4724" alt="Arm Building & Measuring 2" width="250" style="height:auto;" />

**Arduino Mega attachment**  
<img src="https://github.com/user-attachments/assets/5fc7dbfc-743a-45bc-bd57-7e526a9ea6bb" alt="Arduino Mega Building" width="250" style="height:auto;" />

- Design idea: Cat lady with half diva and half trad wife. Her potential design hints at the different sides and characters she might represent
- Ideas to consider: adding a frying pan in one hand and a moving fan in the other
- The robot body is assembled from wood and cardboard. We hope to achieve a more shaped figure as we progress
- Body structure finished
- Code testing

### Oct 23
- Servo attached
- Servo code tested
- Sample code reference (Fall24): https://github.com/oomie/performingRobots/blob/main/code/finalRecieverCode.ino

<img src="https://github.com/user-attachments/assets/1426f04a-895b-4377-8518-4fc75c7733e4" alt="Servo" width="250" style="height:auto;" />

**Design finished**  
<img src="https://github.com/user-attachments/assets/751359aa-cdee-46fb-819f-09203b0cb613" alt="Design Finished" width="250" style="height:auto;" />

- We agreed on adding wiggling ears and a NeoMatrix for half the face for the diva side

**Entire body finished**
- Servo attachment and arm readjustment to attach to the servo
- Started the cardboard head skeleton

<img src="https://github.com/user-attachments/assets/68b7ac3a-cc57-466d-bec2-d9301b870129" alt="IMG_9407" width="250" style="height:auto;" />

### Oct 30
- Finish head skeleton
- Build ears wiggling mechanism
- Attach head to body
- Prepare fabrication shop costume
- Mariam and Joy channel 50, addr = 0x7c

### Nov 5
- Soldered the NeoMatrix

### Nov 6
- Prepared for rehearsal
- Bugs faced
  - Robot tripping
  - Arm not driven by servo
  - Music Maker Shield not outputting audio
- nRF system to control servos
- nRF system to control Music Maker Shield 2 sound clips
  - Used a switching debug strategy to find that the cable with adapter was not connecting well, which caused the bug
- Batteries charged
- Names on all items
- Robot can drive

### Nov 7
- Rewrote code based on updated servo angle constraints

### Nov 10
- Added an extra caster to avoid tipping backward

### Nov 12
- Realized the wheels were also unstable because the nuts and bolts were loose
<img src="https://github.com/user-attachments/assets/e513451d-27ea-4103-8513-f208b73c1c52" alt="loose bolts" width="250" style="height:auto;" />

### Nov 13
- 25 kg motor re-attachment
- Used clay to build the nose

### Nov 17
- Balanced the wheels and servos
- Face building
- Brainstorming pixel face

### Nov 18
- Prepared pixel map and color array
- Created pixelated ideal images
- Resized into 8 × 24 px images
  - https://retoucher.online/image-resizer
- Converted PNGs to RGB value arrays
  - https://onlinepngtools.com/convert-png-to-rgb-values

Inside Out Angry  
<img src="https://github.com/user-attachments/assets/fe356e5d-976a-4183-87c8-73f061931e47" alt="Inside Out Angry" width="250" style="height:auto;" />

Open mouth Marilyn Monroe  
<img src="https://github.com/user-attachments/assets/b70d8e6c-f3e5-4caa-8981-dc2728c7c161" alt="Open mouth Marilyn Monroe" width="250" style="height:auto;" />

Closed mouth Marilyn Monroe  
<img src="https://github.com/user-attachments/assets/540438ae-20f1-4d33-87e1-bdbb91351321" alt="Closed mouth Marilyn Monroe" width="250" style="height:auto;" />

Anime girl open mouth  
<img src="https://github.com/user-attachments/assets/c9ef6c72-ac84-4ace-b1d3-8567dc17d2b3" alt="Anime girl open mouth" width="250" style="height:auto;" />

Anime girl closed mouth  
<img src="https://github.com/user-attachments/assets/fb4e3e0c-4e42-4fcf-bd00-c6d73c263a80" alt="Anime girl closed mouth" width="250" style="height:auto;" />

### Nov 20
- NeoPixels and servo coding
- Power management needed
- Making head
- Sound (ElevenLabs)

### Nov 25
- Clothes and sound clips
- Painting
- Makeup
- Cutting wigs
- Attach head
- Cases
- Ears
- Eye
- Sprites
- Sound clips
- Clothing
- Paint hands and face
- Wire management

### Dec 4
No.1 priority: fix audio bug
- During the previous two rehearsals audio stopped after playing around 15 cases, so I spent a whole week working on this
  - Compared and debugged everything including removing overly frequent interrupt commands in one case
- Sound debugging
- Transmitter debugging
- Refined costume
  - Hid bundle clip
- Wheels re-attachment
- Rehearsal

### Dec 6
- 35 kg motor re-attachment
- Plastic motor horn was not attached and not driving, so we switched to a metal horn following professor advice
- RAM issue seems not to be the reason that caused the audio problem.
- Adding soft reset and servo detach to avoid interrupt noise fixed the bug!!!!!
- Started case testing for 10 rounds
- Some Documentations of Case testing
    - time gap
      - case 3
      - 4 mins
      - case 4
  - case 10* 10 times
  - Free Memory = 3695 after 2 rounds same

### Dec 7
- Case testing for 10 rounds

### Dec 8
- Background slides and background music
  - https://www.canva.com/design/DAG670xIaUM/xav-OgvwMBQd7Y1wmPYgXA/edit?utm_content=DAG670xIaUM&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton
- Switched Arduino to fix the transmitter
- Case testing for 10 rounds

### Dec 9 The day!!!
- Rehearsal
- Audio testing
- Decided to switch back to the original Arduino before the show because case response became less reliable on the new one
- Final look

<img src="https://github.com/user-attachments/assets/85171516-a878-4bb7-8821-9682aa4218e6" alt="Final look" width="250" style="height:auto;" />

- Final Show

<img src="https://github.com/user-attachments/assets/49ce9061-5fb6-44c8-ab3d-ebefa5da12b5" alt="Final Show" width="250" style="height:auto;" />


---

## Team workflow
### Split responsibilities with Mariam
- Mariam had a family emergency after fall break, so we discussed the best collaboration method and decided she would mainly help with decoration and assist me in class by recapping what I completed after class.
- I worked through the main fabrication, coding, and debugging sessions, and I was proud and surprised by how much I learned running the entire setup.

# Thank you Performing Robots Fall25!! Thank you Mariam! Thank you Professor Shiloh!! 🫶  
I am so glad I could come to Abu Dhabi this semester and register for this class. It is truly a once in a lifetime opportunity.
