int  LED = 12;// LED pin

long val = 500; // Don't forget to initialize to something
uint32_t lastBlink = 0UL; // Last time we toggled the LED
char inputBuffer[11]; // Handles up to a 10-digit number, the most a 32-bit unsigned integer can be

void setup() 
{
  Serial.begin(9600); // initialization
  pinMode(LED, OUTPUT);
  //Serial.println("Press 1 to LED ON or 0 to LED OFF...");
  inputBuffer[0] = '\0'; //Initialize string to emtpy.
}
void loop() {

  uint32_t currentMillis = millis();
  uint8_t ledState = digitalRead(LED);
  
  if (Serial.available()>0)
  {
    char input = Serial.read();
    int s_len = strnlen(inputBuffer, 11);
    inputBuffer[s_len++] = input;
    inputBuffer[s_len] = '\0'; // Make string null-terminated again
    if (input == '\r') {
      // Have received a CR

      // Flush the receive buffer from linefeed, etc
      while(Serial.available()) {
        Serial.read();
      }

      val = strtol(inputBuffer, NULL, 10);  // Convert string to number
      Serial.print("New Delay: ");
      Serial.println(val);

      inputBuffer[0] = '\0'; // Reset input buffer
    }
  }
  
  if (currentMillis - lastBlink > val) {
    // Time to toggle
    digitalWrite(LED, !ledState);
    lastBlink += val;
  }

}

