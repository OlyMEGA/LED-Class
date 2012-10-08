#include "LPD8806.h"
#include "SPI.h"
#include "utils.h"

LPD8806 strip = LPD8806(numLEDs); // The object for controlling the strip
LightEntity lights[numLEDs];      // An array of "entities" (just a color for now, but can be more)
LightEntity newLights[numLEDs];   // A temp array for calculating the next state of the board
unsigned long lastAddTime;        // Timestamp of when we last added a new random light

void setup() 
{
  initProgram();  
  initCells();
  initStrip();
  updateStrip();
}


void loop()
{
  updateCells();
  updateStrip();

  delay(FRAME_DELAY);
}


// ===========================================================================

// Set up non-directly related subsystems like Serial and the RNG
void initProgram()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0) * analogRead(A1));
}


// Sets all cells (array elements, not strip lights) to black (CZERO) then optionally initializes a few "seed" cells
void initCells()
{
  for (int i=0; i<numLEDs; i++)
  {
    LightEntity newEntity = { };
    newEntity.color = CZERO;

    lights[i] = newEntity;
    newLights[i] = newEntity;
  }

  lights[0].color  = (Color){ 127,   0,   0 }; // Red
  lights[6].color  = (Color){   0, 127,   0 }; // Green
  lights[12].color = (Color){   0,   0, 127 }; // Blue

  lights[3].color  = (Color){ 127,   0,   0 }; // Red
  lights[9].color  = (Color){   0, 127,   0 }; // Green
  lights[15].color = (Color){   0,   0, 127 }; // Blue
}


// Initialize LPD8806 object and blank all lights
void initStrip()
{
  strip.begin();
  strip.show();
}

// ===========================================================================

// Updates values in our main array, by calculating a new value for each 
// non-black cell and its neighbors, setting these new values into a temp
// array, then copying the new array back over the original one
void updateCells()
{
  for (int i=0; i<numLEDs; i++)
  {
    // Get the current color of our primary light.
    Color mainColor = lights[i].color;

    // If it's a black cell, do nothing.
    if (mainColor == CZERO) continue; 

    // If it has a color, process it, and its neighbors, into the newLights array
    calcMainLight(i);
    calcSecondaryLight(i-1, mainColor);
    calcSecondaryLight(i+1, mainColor);
  }

    
  unsigned long now = millis();
  if (now - lastAddTime > addInterval) {
    addRandom(); 
    lastAddTime = now;
  }

  // Copy "temp" array to new array
  for (int i=0; i<numLEDs; i++) {
    lights[i] = newLights[i]; 
  }  
}

void calcMainLight(int index)
{
  LightEntity newLight = (LightEntity){ (lights[index].color - secondaryDecayAmount) * decayFactor};
  newLights[index] = newLight;
}

void calcSecondaryLight(int index, Color mainColor)
{
  if (onStrip(index))
  {    
    Color secondColor = newLights[index].color;
    Color newColor = ( averageColor(mainColor, secondColor) - secondaryDecayAmount ) * decayFactor; 
    newLights[index].color = (Color){newColor}; 
  }
}

// 
void updateStrip()
{
  for (int i=0; i<numLEDs; i++)
  {
    uint32_t stripColor = strip.Color((int)lights[i].color.red, (int)lights[i].color.green, (int)lights[i].color.blue);
    strip.setPixelColor(i, stripColor);
  }  
  strip.show();
}

// ===========================================================================

// Determines whether a light falls on the strip or not
boolean onStrip(int idx)
{
  return ( (idx >= 0) && (idx < numLEDs) );
}


// Lights up a random light a random (HSV) color
void addRandom()
{
  unsigned int r,g,b;
  unsigned int h = random(255);
  HSVtoRGB(&r, &g, &b, h, 255, 255);

  Serial.print("H: "); Serial.println(h);

  int counter = 0;
  int randomPos = random(15);  
  while ( (lights[randomPos].color != CZERO) && (counter < 64) )
  {
    randomPos = random(15);
    counter++;
  }

  newLights[randomPos] = (LightEntity){ makeColor(r/2, g/2, b/2) }; 
}

//  Serial.print("R:"); Serial.print(currentColor.red);
//  Serial.print(" G:"); Serial.print(currentColor.green);
//  Serial.print(" B:"); Serial.print(currentColor.blue);
//  Serial.println();


