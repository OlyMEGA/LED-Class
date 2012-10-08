Sketches for LED Light Classes at OlyMEGA

---

Examples/LightDecay:

Wiring: (for fast SPI on non-leo board)

- Ground -> Arduino Ground
-  Clock -> Digital 13
-   Data -> Digital 11
-    +5v -> Arduino +5v

Setup:

1. Hook up your LPD8806 based strip

2. Open LightDecay.ino in Arduino IDE (utils.h should also open)

3. Tell it how many LEDs you have (set numLEDs in utils.h)

4. Upload and watch the fireworks :)

5. Open utils.h and play with values for decayAmount, decayFactor, and addInterval, to affect how often new colors appear, and how quickly they fade out (decay)

---
