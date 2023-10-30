/*
Simon Says Program
*/

/*
These are macros, before the program is compiled, all of these will replace 
the first piece of text with the second piece of text, this is useful for
saving memory and making the code easier to read without defining vars.
*/
#define blueLED 13
#define redLED 12
#define greenLED 11
#define yellowLED 10

#define blueButton 9
#define redButton 8
#define greenButton 7
#define yellowButton 6

#define startButton 5
#define a0 14

/*
This is an array, think of it as a list of 100 numbers We will later fill 
this up with random numbers between 0 and 3 to represent blue through yellow.
*/
int gameSequence[100];

/* This is another variable, it will track the players score and how many 
correct answers the player has memorized.
*/
int moves = 0;

// 0 will be the main "screen", 1 will be when the game is playing, 3 will be when the game is over...
int gameScreen = 0;

// This function is run once as soon as the Arduino is ready, it run once before the loop function starts actually looping
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

  // We use an ungrounded pin that has random voltages to be as random as possible.
  randomSeed(analogRead(a0));
}

void genSequence() {
  // This will run 100 times, it isn't too important to understand how it works right now...
  for (int i = 0; i < 100; i++) {
    gameSequence[i] = random(0, 4);
  }
}

void mainScreen() {
  // HIGH is also 1, you can use either, you could also use true...
  // This is how we turn all of the LED's on, you use LOW to turn the LED off.
  digitalWrite(blueLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, HIGH);

  if (digitalRead(startButton) == HIGH) {
    // Turn off all the LED's
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    /* This is known as an increment operator, it just adds 1 to the variable so you don't
    have to do gameScreen = gameScreen + 1 or gameScreen += 1.
    */
    gameScreen++;

    // Call the function genSequence to generate a new game sequence
    genSequence();

    // Wait a second (1000 milliseconds) so the player can see the first flash
    delay(1000);

    // Let's first display the first LED that the player has to memorize to start the game.
    displayPattern(1);
  }
}

// This function will be called when the player is playing the game.
void playingScreen() {
  for (int i = 0; i < moves + 1; i++) {
    // This doesn't actually represent anything, it will just be 4 until we detect a button press.
    int buttonPressed = 4;
    while (buttonPressed == 4) {
      if (digitalRead(blueButton) == HIGH) {
        buttonPressed = 0;
      } else if (digitalRead(redButton) == HIGH) {
        buttonPressed = 1;
      } else if (digitalRead(greenButton) == HIGH) {
        buttonPressed = 2;
      } else if (digitalRead(yellowButton) == HIGH) {
        buttonPressed = 3;
      }
    }
    // Once we have the button pressed we see if it's right in terms of the sequence.
    if (gameSequence[i] == buttonPressed) {
      // Nice! They got it right!
      digitalWrite(13 - gameSequence[i], HIGH);
      delay(300);
      digitalWrite(13 - gameSequence[i], LOW);
    } else {
      // :( They got it wrong, let's display and flash the right one so the player knows which one it really was.
      for (int j = 0; j < 3; j++) {
        digitalWrite(13 - gameSequence[i], HIGH);
        delay(500);
        digitalWrite(13 - gameSequence[i], LOW);
        delay(500);
      }

      // Let's go back to the main screen and reset the game.
      gameScreen++;
      return;
    }
  }
  // If the code reaches this point, the player has succeeded so now we just increment and continue onto the next round.
  moves++;
  // Pause the game for half a second so the player can see the next pattern.
  delay(500);
  // Wow! They won the game, let's flash the LED's 5 times to congratulate them!
  if (moves >= 26) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(blueLED, HIGH);
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, HIGH);
      delay(500);
      digitalWrite(blueLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      delay(500);
    }
    // Technically the game is now after so let's go back to the main screen.
    gameScreen++;
  }
  // Ok, since they haven't won let's move on and display the next pattern.
  displayPattern(moves + 1);
}

void displayPattern(int numOfMoves) {
  // Loop numOfMoves times...
  for (int i = 0; i < numOfMoves; i++) {
    // Provide power to the right pin to turn on the correct LED in the pattern.
    digitalWrite(13 - gameSequence[i], HIGH);
    // Delay is in milliseconds, 500 milliseconds is equal to 0.5 seconds.
    delay(300);
    // Turn off power to the pin to turn off the LED.
    digitalWrite(13 - gameSequence[i], LOW);
    delay(300);
  }
}

// This will literally run over and over again, forever until we stop it.
void loop() {
  if (gameScreen == 0) {
    mainScreen();
  } else if (gameScreen == 1) {
    playingScreen();
  } else if (gameScreen == 2) {
    // If it's not 0 or 1 then we just have to go back to 0, you could also use a boolean value to save memory technically.
    gameScreen = 0;
  }
}
