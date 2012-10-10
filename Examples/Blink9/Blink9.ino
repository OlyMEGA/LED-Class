/*
  Blink9
  Turns on elements of RGB LED on PORTB (8-10) for one second 
  This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
// DDRB = B11111111;  // sets Arduino pins 7 to 1 as outputs
DDRB = DDRB | B00111111;  // this is safer as it sets pins 8 to 13 as outputs
	                  // without changing the value of pins 14 and 15   
                          // Pin 13 has an LED connected on most Arduino boards.
}

// the loop routine runs over and over again forever:
void loop() {
  for (int x=0; x<9; x++) {
  PORTB=x;         // turn the LED on (HIGH is the voltage level)
  delay(1000);  }   // wait for a second
  
}
