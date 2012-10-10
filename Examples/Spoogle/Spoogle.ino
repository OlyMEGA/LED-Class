// Arrays of floating point values to hold R, G, B values
float rgbValue1[3];     // Current RGB value
float rgbTarget1[3];    // Target RGB value. 
float rgbIncrement1[3]; // Size of steps to go from Current to Target

float rgbValue2[3];     // Current RGB value
float rgbTarget2[3];    // Target RGB value. 
float rgbIncrement2[3]; // Size of steps to go from Current to Target

// Pin Mappings
int redPin1   = 3; 
int greenPin1 = 5;  
int bluePin1  = 6;

int redPin2   = 9; 
int greenPin2 = 10; 
int bluePin2  = 11;

// Delay amounts
int changeDelay  = 15;    // color change delay
int transitDelay = 1000; // delay between transition


void setup()
{
  // Randomize the Random Number Generator
  randomSeed(analogRead(0));

  // Initialize RGB values to 0 (black)
  rgbValue1[0] = 0; 
  rgbValue1[1] = 0; 
  rgbValue1[2] = 0;
  
  rgbValue2[0] = 0;
  rgbValue2[1] = 0;
  rgbValue2[2] = 0;
  
  // Set a random target color
  rgbTarget1[0] = random(256);
  rgbTarget1[1] = random(256);
  rgbTarget1[2] = random(256);  
  
  rgbTarget2[0] = random(256);
  rgbTarget2[1] = random(256);
  rgbTarget2[2] = random(256);
}

void loop()
{
  // Randomize the Random Number Generator (again)
  randomSeed(analogRead(0));
  
  // For each of our 3 colors (r,g,b) split the difference between 
  // current and target colors into 256 discrete steps to get there..
  for (int x=0; x<3; x++) 
  {
    rgbIncrement1[x] = (rgbValue1[x] - rgbTarget1[x]) / 256;
    rgbIncrement2[x] = (rgbValue2[x] - rgbTarget2[x]) / 256;
  }
  
  for (int x=0; x<256; x++) 
  { 
    // Write current state of rgbValue to the PWM pins
    analogWrite (redPin1,   (int)rgbValue1[0]);
    analogWrite (greenPin1, (int)rgbValue1[1]);
    analogWrite (bluePin1,  (int)rgbValue1[2]);
    
    analogWrite (redPin2,   (int)rgbValue2[0]);
    analogWrite (greenPin2, (int)rgbValue2[1]);
    analogWrite (bluePin2,  (int)rgbValue2[2]);
    
    // Increment/Decrement the RGB values for next time through
    rgbValue1[0] -= rgbIncrement1[0];
    rgbValue1[1] -= rgbIncrement1[1];
    rgbValue1[2] -= rgbIncrement1[2];
    
    rgbValue2[0] -= rgbIncrement2[0];
    rgbValue2[1] -= rgbIncrement2[1];
    rgbValue2[2] -= rgbIncrement2[2];

    // Introduce a small (few ms) delay before incrementing again
    delay(changeDelay);
  }
  
  // We've completed the fade to our target color, now initialize a new
  // target color.
  for (int x=0; x<3; x++) 
  {
    rgbTarget1[x] = random(556)-300;
    rgbTarget1[x] = constrain(rgbTarget1[x], 0, 255);
    
    rgbTarget2[x] = random(556)-300;
    rgbTarget2[x] = constrain(rgbTarget2[x], 0, 255);
  }

  delay(transitDelay);
}

