/*
Simon Says Program
*/

/* Variable Definitions
const means "constant", it should stay the same throughout the entire program...
int means integer, it basically means that it has to be a regular non decimal number between -32,768 and 32,767
*/
const int blueLED = 13;
const int redLED = 12;
const int greenLED = 11;
const int yellowLED = 10;

const int blueButton = 9;
const int redButton = 8;
const int greenButton = 7;
const int yellowButton = 6;

const int startButton = 2;

// This function is ran once as soon as the Arduino is ready, it run once before the loop function starts actually looping
void setup() {
    // We first have to set the mode of pins, basically saying if it will take in info, or output some sort of signal...
    pinMode(blueLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);

    pinMode(blueButton, INPUT);
    pinMode(redButton, INPUT);
    pinMode(greenButton, INPUT);
    pinMode(yellowButton, INPUT);

    pinMode(startButton, INPUT);
}

// This will literally run over and over again, forever
void loop() {
    
}