bit oldstate;              // Old state flag

void main() {
  ANSEL  = 0;              // Configure AN pins as digital
  CMCON  = 7;              // Turn off the comparators
  TRISIO = 0;              // configure pins of GPIO as output
  TRISIO3_bit = 1;
  GPIO = 0xFF;
  do {
    if (Button(&GPIO, 3, 1, 1)) {  // Detect logical one
      oldstate = 1;                // Update flag
    }
    if (oldstate && Button(&GPIO, 3, 1, 0)) {
      // Detect one-to-zero transition
      GPIO = ~GPIO;               // Invert GPIO
      oldstate = 0;               // Update flag
    }                     // beginning of a repeat loop
  }  while(1);           // endless loop
}
