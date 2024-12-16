# Snake

## Introduction
**The Snake game** is a classic arcade-style game where players control a snake that grows longer as it consumes food. The objective is to navigate the snake around the playing field, avoiding collisions with walls or its own tail. With each piece of food eaten, the game becomes progressively more challenging as the snake grows longer.

## General Description
![Block Diagram](images/schema_Bloc.png)

### Component Description
**1. Arduino Uno R3:**
- The central microcontroller of the project that manages the system's logic. It reads signals from the joystick, controls the buzzer, and updates the OLED display. Additionally, it executes commands based on user inputs. 

**2. OLED Display (128x64, I2C):**
- This display serves as the system's visual interface. Communication with the Arduino is done via the I2C protocol using the SCL (A5) and SDA (A4) pins.

**3. Joystick:**
- The joystick is used to control the direction of movement in the Snake game. It has two analog axes (vertical on A0 and horizontal on A1) and a button (SEL) on pin 2.

**4. Buzzer:**
- Connected to pin 9 of the Arduino, the buzzer emits sounds or tones in response to various events.

### Interaction Between Components
**1. Arduino and Joystick:**
- The joystick sends analog signals for the vertical axis (A0) and horizontal axis (A1) to the Arduino. Based on the joystick's movements, the Arduino updates the display and can trigger the buzzer if necessary. 

**2. Arduino and OLED Display:**
- The Arduino processes data from the joystick and uses the I2C protocol to update the OLED display. The snake's position and movement are displayed graphically, providing real-time feedback to the user.

**3. Arduino and Buzzer:**
- The Arduino controls the buzzer via pin 9, activating it to emit sounds. For example, the buzzer might signal when the snake eats food, hits a wall, or when the SEL button is pressed to pause or restart the game, providing an auditory response to key events in the game.

## Hardware Design

| Component               | Qty                |
|----------------------|--------------------|
|  **Arduino Uno R3**           | 1                  |
| **OLED Display (128x64, I2C)** | 1                |
| **Joystick**  | 1 |
| **Buzzer**                  | 1                  |
| **Wires**                 | Multiple           |

![Circuit](images\circuit.png)





| Component                | Connected Pins           |
|--------------------------|--------------------------|
| **Arduino Uno R3**        | GND (2), 5V, A5 (SCL), A4 (SDA), A0 (VERT), A1 (HORZ), 2 (SEL), 9 (Buzzer) |
| **OLED Display (128x64, I2C)**| SCL (A5), SDA (A4), VCC, GND |
| **Joystick**              | VCC, GND, VERT (A0), HORZ (A1), SEL (Pin 2) |
| **Buzzer**                | Pin 9                    |


## Software Design

## Results 

## Conclusions