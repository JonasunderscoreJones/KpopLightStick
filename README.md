# K-Pop Lightstick
This Repo features the software of an Arduino Lightstick as well as the 3D Files for a custom **NCT DREAM** Lightstick

![Alt text](/pictures/lightstick_top3d.png)

## 3D-Print
The Lightstick was printed in 3 different colors.

The `Block Top.stl` file can be modified to not come with holes for the `Neo_City.stl` cubes rising out of the top to match the official lightstick more accurately.

*Be aware, that this 3D Build is slightly larger than the Official NCT DREAM Lightstick and you may not be allowed into concerts with it. I had no issues at the NCT DREAM Tour 2024 in Rotterdam but the security checks at the entrance were cursory, lacking the thoroughness you would usually have at different concerts.*

**WHITE:**
- `Block Base.stl`
- `Block Side.stl`
- `Block Top.stl`
- `Handle Base Bottom.stl`
- `Handle Base.stl`

**BLACK:**
- `Handle Ring Bottom`
- `Handle Ring Top`
- `Power Button`

**TRANSPARENT NEON GREEN:**
- `Neo_City.stl`
- `shiny_c_thicker.stl`
- `shiny_c.stl`
- `shiny_n_thicker.stl`
- `shiny_n.stl`
- `shiny_t_thicker.stl`
- `shiny_t.stl`

*Since I had issues with the prints of the letters, I made a thicker version of each letter to ensure that there would be no holes.*

## Assembly
The Assembly of the Prints is pretty self-explanatory. Take a look at the pictures in the `/picture` folder of the repo.

I chose to not glue the `Block Base.stl` and the `Handle Base.stl` pieces together to be able to troubleshoot/replace the electronics inside at any time.

## Electronics
The `arduino.ino` file contains the Arduino code I used for the lightstick.

An **Arduino Nano** was used with the following Pin-Out:
```cpp
const int buttonPin = 2; // Pin for the button
const int redPin = 11; // Pin for the red channel of RGB LED
const int greenPin = 10; // Pin for the green channel of RGB LED
const int bluePin = 9; // Pin for the blue channel of RGB LED
const int motorPin = 8; // Pin to control the motor
```
*Note: These are the Digital Pins on the Arduino Nano*

### Features of the Program
- The `buttonPin` is for the Power Button on the `Handle Base.stl` and is used for controlling the Light.
- The `redPin`, `greenPin` and `bluePin` are used for controlling the LED. IMPORTANT: These are **ANODE RGB LEDs**. If You plan on using *Kathode LEDs*, simply remove `255 - ` from the `setRGB` function at the bottom of the Program, to invert the values. (This is only a fix based on logic, I have no LEDs to test it)
- The `motorPin` is used for controlling a simple Vibration Motor that runs for 1 second when turning on the Lightstick. This is inspired from the *VIXX Official Lightstick* that has similar behaviour. It is completely irrelevant to the general functionality of the Lightstick which is, well, to have Light.

### Instructions
1. Connect a Power button to the Arduino `buttonPin` and groud
2. Connect the Vibration Motor (A simple motor with some weight glued of axis to make it vibrate when rotating) to the `motorPin` and ground
3. Connect the RGB LEDs to the 3 color pins and 3.3V
4. Glue together 3 AAA Batteries, solder them together and connect them to the Voltage In` and ground
5. Flash the Arduino Nano with the program and you're done.
6. Insert the electronics into the Arduino and close it up.

## Usage
Hold the Power Button for approx. 1 second and release it. The Lightstick should vibrate for a second and then the lights turn on, defaulting to a neon green.

Press the button to cycle between colors and hold it for a second to turn it off again.
