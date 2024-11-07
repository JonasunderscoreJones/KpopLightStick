const int buttonPin = 2; // Pin for the button
const int redPin = 11; // Pin for the red channel of RGB LED
const int greenPin = 10; // Pin for the green channel of RGB LED
const int bluePin = 9; // Pin for the blue channel of RGB LED
const int motorPin = 8; // Pin to control the motor

bool ledState = false; // State of the onboard LED
unsigned long buttonPressStartTime = 0; // Time when the button press starts
bool buttonPressed = false; // Current button pressed state
unsigned long lastButtonPress = 0; // Last time the button was pressed
int colorIndex = 0; // Index for cycling colors

// Define colors to cycle through (RGB format)
const int colors[][3] = {
    {127,255,0},     // Neon Green
    {255, 0, 0},    // Red
    {0, 255, 0},    // Green
    {0, 0, 255},    // Blue
    {255, 255, 0},  // Yellow
    {0, 255, 255},  // Cyan
    {255, 0, 255}   // Magenta
};
const int numColors = sizeof(colors) / sizeof(colors[0]);

void setup() {
    pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with pull-up resistor
    pinMode(ledPin, OUTPUT); // Set the LED pin as output
    pinMode(redPin, OUTPUT); // Set the red pin as output
    pinMode(greenPin, OUTPUT); // Set the green pin as output
    pinMode(bluePin, OUTPUT); // Set the blue pin as output
    pinMode(motorPin, OUTPUT); // Set the motor control pin as output

    // Initialize RGB LED to off and motor off
    setRGB(0, 0, 0);
    digitalWrite(motorPin, LOW); // Ensure motor is off

    pinMode(LED_BUILTIN, OUTPUT); // Set the onboard LED pin as an output
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
}

void loop() {
    // Read the button state
    bool currentButtonState = digitalRead(buttonPin) == LOW;

    if (currentButtonState && !buttonPressed) {
        // Button just pressed
        buttonPressed = true;
        buttonPressStartTime = millis(); // Record the time of the button press
    } else if (!currentButtonState && buttonPressed) {
        // Button just released
        buttonPressed = false;

        // Check duration of button press
        unsigned long pressDuration = millis() - buttonPressStartTime;

        if (pressDuration >= 500) {
            // Long press: Toggle onboard LED and motor
            ledState = !ledState;
            digitalWrite(ledPin, ledState ? HIGH : LOW);

            if (ledState) {
                // Turn motor on
                digitalWrite(motorPin, HIGH);
                delay(1000); // Keep motor on for 1 second
                digitalWrite(motorPin, LOW); // Turn motor off
                setRGB(0, 255, 0); // Start with green
                colorIndex = 0; // Reset color index
            } else {
                // Turn off RGB LED
                setRGB(0, 0, 0);
            }
        } else {
            // Short press: Cycle colors
            if (ledState) {
                colorIndex = (colorIndex + 1) % numColors; // Cycle through colors
                setRGB(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
            }
        }

        // Wait until the button is released before proceeding
        while (digitalRead(buttonPin) == LOW);
    }
}

// Function to set RGB LED color
void setRGB(int red, int green, int blue) {
    analogWrite(redPin, 255 - red);
    analogWrite(greenPin, 255 - green);
    analogWrite(bluePin, 255 - blue);
}