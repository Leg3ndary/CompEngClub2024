// This is some arduino code for a BoeBot.
// It uses an IR sensor to detect objects in front of it!

// Importing the Servo library
#include <Servo.h>

// Creating 2 instances of the Servo class, one for each motor
Servo left;
Servo right;

// Defining constants for pins, constants mean that this should never change throughout the entire program
const int irLed = 3;
const int irReceiver = 4;
const long frequency = 19000;

// Defining a var to hold the random direction the bot may go in
int direction;

void setup()
{
    // "Attaching" each motor to a pin
    left.attach(10);
    right.attach(11);

    // Setting the IR receivers to input or output.
    pinMode(4, INPUT);
    pinMode(3, OUTPUT);
}

// Create a function to detect when an object is in front of the bot
bool detect()
{
    tone(irLed, frequency, 8);
    delay(1);
    int ir = digitalRead(irReceiver);
    delay(1);
    return !ir;
}

void loop()
{
    delay(50);
    int objectDetected = detect();

    if (objectDetected)
    {
        // Go backwards for 1 second
        left.write(0);
        right.write(180);
        delay(1000);

        // Turn left or right randomly
        if (random(0, 2))
        {
            direction = 0;
        }
        else
        {
            direction = 180;
        }
        left.write(direction);
        right.write(direction);
        delay(1000);
    }
    else
    {
        // Otherwise we can just run forward!
        left.write(180);
        right.write(0);
    }
}
