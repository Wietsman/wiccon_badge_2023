#include <Adafruit_NeoPixel.h>
#include <painlessMesh.h>

#define MESH_PREFIX "WICCON_2023"
#define MESH_PASSWORD "WICCON_2023_IS_FUN!!!!"
#define MESH_PORT 5555

#define NEOPIXEL_PIN 14        // Pin where the NeoPixel is connected
#define NUMPIXELS 8         // Number of NeoPixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

const int buttonPin = 4;  // Pin number for the button
int buttonState = HIGH;   // Variable to store the button state
int lastButtonState = HIGH; // Variable to store the previous button state
bool isRunning = true;    // Flag to control the effect
int effectNumber = 0;

unsigned long previousMillis = 0;
unsigned long pm = 0;
const long interval = 1000; // Interval between effect changes in milliseconds

bool resumePause();

void continuousEffect();
void theaterChase(uint32_t color, int wait);
void rainbowCycle(int wait);
void policeLights(int wait);
void sparkle(int wait);
void colorWipe(uint32_t color, int wait);
void cylonScanner(uint32_t color, int eyeSize, int speed);
void colorFade(uint32_t color1, uint32_t color2, int steps, int wait);
void comet(uint32_t color, int tailLength, int wait);
uint32_t Wheel(byte WheelPos);


// Morse Code Definitions
#define DOT_DURATION 250 // Duration of a dot in milliseconds
#define DASH_DURATION 3 * DOT_DURATION // Duration of a dash (3 times dot duration)
#define SYMBOL_GAP 3 * DOT_DURATION // Gap between symbols (3 times dot duration)
#define WORD_GAP 7 * DOT_DURATION // Gap between words (7 times dot duration)

void sendMorseCode(const char *message);


painlessMesh mesh;
String receivedMessage = "";
bool isMasterMesh = false;
bool masterIsClose = false;
uint32_t masterID;
void receivedCallback(uint32_t from, String &msg) {
  masterID = from; 
  // Serial.printf("Received from %u: %s\n", from, msg.c_str());
  receivedMessage = msg;  // Store the received message in the global variable
}

void setup() {
  strip.begin();
  strip.show();  // Initialize all NeoPixels to 'off'
  pinMode(buttonPin, INPUT_PULLUP); // Configure the button pin as an input with a pull-up resistor
  // mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);  // Enable debug messages
  // mesh.setDebugMsgTypes(CONNECTION);
  mesh.setContainsRoot(true);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(receivedCallback);  // Register the receivedCallback

  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  resumePause();

  if (isRunning) {

    // Run the NeoPixel effect when the effect is not paused
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Clear the NeoPixel strip
      strip.fill(0); // Turn off NeoPixels
      strip.show();
      strip.clear();

      // Call your continuous effect function here
      continuousEffect();
    }
  } else {

    // When the effect is paused, you can keep the NeoPixels off or set them to a specific state
    strip.fill(0); // Turn off NeoPixels
    strip.show();
    strip.clear();
  }

  strip.show();
  masterIsClose = false;
  // Your non-blocking code for other tasks can go here


}

// Define your continuous NeoPixel effect function
void continuousEffect() {
  // Your code to create the continuous NeoPixel effect goes here
  // For example, you can implement a color cycle or any other animation
  switch(effectNumber){
    case 0:
      strip.fill(0); // Turn off NeoPixels
      strip.show();
      sendMorseCode("To find the truth  shoot for the moon  ");

      break;
    case 1:
      theaterChase(strip.Color(random(256), random(256), random(256)), 250);
      break;
    case 2:
      rainbowCycle(50);
      break;
    case 3:
      policeLights(50);
      break;
    case 4:
      sparkle(100);
      break;
    case 5:
      colorWipe(strip.Color(random(256), random(256), random(256)), 50);
      break;
    case 6:
      cylonScanner(strip.Color(random(256), random(256), random(256)), 3, 100);
      break;
    case 7:
      colorFade(strip.Color(random(256), random(256), random(256)), strip.Color(random(256), random(256), random(256)), 100, 30);
      break;
    case 8:
      comet(strip.Color(random(256), random(256), random(256)), 3, 100); // Comet with red tail
      break;
  }
}


// NeoPixel effect functions

void rainbowCycle(int wait) {
  for (int j = 0; j < 256; j++) { // One cycle of color wheel
    for (int i = 0; i < strip.numPixels(); i++) {
      if (i <= 3) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      } else {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      if (!resumePause()){ 
        return; 
      }
    }
    if (!resumePause()){ 
      return; 
    }

    strip.show();
    delay(wait);
  }
  return;
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    if (!resumePause()){ 
      return; 
    }
    if (i <= 3) {
      strip.setPixelColor(i, color/4);
    } else {
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(wait);
  }
}

bool resumePause(){
  mesh.update();
    // Serial.println(mesh.getAPIP());
    // Serial.println(mesh.getNodeId());
    // Serial.println(mesh.getStationIP());

    // Serial.println("WiFi signal: " + String(WiFi.RSSI()) + " db");
  if (!isMasterMesh) {
    if (!receivedMessage.isEmpty()) {
      if (receivedMessage == "I_AM_THE_MASTER!" && !masterIsClose){
        masterIsClose = true;
      // Serial.println("Processing received message: " + receivedMessage);
        Serial.println("Master is close, start listening");
      
        while (mesh.isConnected(masterID)){
          Serial.println(mesh.isConnected(masterID));
          policeLights(50);
        }
      }

      receivedMessage = "";
    }
  } else {
    mesh.sendBroadcast("I_AM_THE_MASTER!");
  }
  unsigned long cm = millis();
  if (cm - pm >= interval/2) {
      pm = cm;
    Serial.println(String(effectNumber));
    buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState) {
      if (buttonState == LOW) {
        // isRunning = !isRunning; // Toggle the running state when the button is pressed
        // Serial.println(isRunning ? "Effect resumed" : "Effect paused");
      // } else {
        effectNumber = effectNumber + 1;
        if (effectNumber == 9){
          effectNumber = 0;
        }
        return false;
      }
      lastButtonState = buttonState;
    }
  }
  
  return true;

}

void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times
    if (!resumePause()){ 
      return; 
    }
    for (int b = 0; b < 3; b++) {
      strip.clear();
      if (!resumePause()){ 
        return; 
      }
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color);
        if (!resumePause()){ 
          return; 
        }
      }
      strip.show();
      delay(wait);
    }
  }
}

void policeLights(int wait) {
  for (int i = 0; i < 5; i++) { // Repeat 5 times
    if (!resumePause()){ 
      return; 
    }
    strip.setPixelColor(0, strip.Color(112, 0, 0)); // Red
    strip.setPixelColor(1, strip.Color(112, 0, 0)); // Red
    strip.setPixelColor(2, strip.Color(112, 0, 0)); // Red
    strip.setPixelColor(3, strip.Color(112, 0, 0)); // Red
    strip.setPixelColor(4, strip.Color(0, 0, 255)); // Blue
    strip.setPixelColor(5, strip.Color(0, 0, 255)); // Blue
    strip.setPixelColor(6, strip.Color(0, 0, 255)); // Blue
    strip.setPixelColor(7, strip.Color(0, 0, 255)); // Blue
    strip.show();
    if (!resumePause()){ 
      return; 
    }
    delay(wait);
    if (!resumePause()){ 
      return; 
    }
    strip.clear();
    strip.show();
    delay(wait);
  }
}

void sparkle(int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    if (!resumePause()){ 
      return; 
    }
    if (i < 3){ 
      strip.setPixelColor(i, strip.Color(random(125), random(125), random(125)));
    } else {
      strip.setPixelColor(i, strip.Color(random(256), random(256), random(256)));
    }
    strip.show();
    delay(wait);
    if (!resumePause()){ 
      return; 
    }
    strip.setPixelColor(i, 0); // Turn off the pixel
  }
  if (!resumePause()){ 
    return; 
  }

  strip.show();
}

// Wheel function for rainbow effect
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// Cylon Scanner
void cylonScanner(uint32_t color, int eyeSize, int speed) {
  
  for (int i = 0; i < strip.numPixels() - eyeSize + 1; i++) {
    if (!resumePause()){ 
      return; 
    }
    strip.clear();
    for (int j = 0; j < eyeSize; j++) {
      if (!resumePause()){ 
        return; 
      }
      strip.setPixelColor(i + j, color);
    }
    strip.show();
    delay(speed);
  }
  if (!resumePause()){ 
    return; 
  }
  for (int i = strip.numPixels() - eyeSize + 1; i > 0; i--) {
    if (!resumePause()){ 
      return; 
    }
    strip.clear();
    for (int j = 0; j < eyeSize; j++) {
      strip.setPixelColor(i + j - 1, color);
      if (!resumePause()){ 
        return; 
      }
    }
    strip.show();
    delay(speed);
  }
}

//Color Fade
void colorFade(uint32_t color1, uint32_t color2, int steps, int wait) {
  uint8_t r1 = (color1 >> 16) & 0xFF;
  uint8_t g1 = (color1 >> 8) & 0xFF;
  uint8_t b1 = color1 & 0xFF;
  uint8_t r2 = (color2 >> 16) & 0xFF;
  uint8_t g2 = (color2 >> 8) & 0xFF;
  uint8_t b2 = color2 & 0xFF;

  for (int k = 0; k < steps; k++) {
    uint8_t r = map(k, 0, steps - 1, r1, r2);
    uint8_t g = map(k, 0, steps - 1, g1, g2);
    uint8_t b = map(k, 0, steps - 1, b1, b2);
    uint32_t blendedColor = strip.Color(r, g, b);

    strip.fill(blendedColor);
    strip.show();
    delay(wait);
  }
}


//Comet
void comet(uint32_t color, int tailLength, int wait) {
  for (int i = 0; i < strip.numPixels() + tailLength; i++) {
    if (!resumePause()){ 
      return; 
    }
    // Calculate the position of the comet
    int pos = i - tailLength;
    
    // Draw the comet
    for (int j = 0; j < strip.numPixels(); j++) {
      if (!resumePause()){ 
        return; 
      }
      if (j >= pos && j < pos + tailLength) {
        strip.setPixelColor(j, color);
        if (!resumePause()){ 
           return; 
        }
      } else {
        strip.setPixelColor(j, 0);
        if (!resumePause()){ 
          return; 
        }
      }
    }
    
    strip.show();
    delay(wait);
  }
}

void sendMorseCode(const char *message) {
  const char *morseCode[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--..", " ", // Morse code for letters and space
  };
  
  for (int i = 0; message[i] != '\0'; i++) {
    if (!resumePause()){ 
      return; 
    }
    char c = tolower(message[i]);
    if (c >= 'a' && c <= 'z') {
      if (!resumePause()){ 
        return; 
      }
      int index = c - 'a';
      for (int j = 0; morseCode[index][j] != '\0'; j++) {
        if (!resumePause()){ 
          return; 
        }
        char symbol = morseCode[index][j];
        switch (symbol) {
          case '.':
            strip.fill(strip.Color(random(256), random(256), random(256))); // Turn NeoPixels red for a dot
            strip.show();
            delay(DOT_DURATION);
            break;
          case '-':
            strip.fill(strip.Color(random(256), random(256), random(256))); // Turn NeoPixels blue for a dash
            strip.show();
            delay(DASH_DURATION);
            break;
        }
        strip.fill(0); // Turn off NeoPixels for the gap
        strip.show();
        delay(SYMBOL_GAP);
      }
    } else if (c == ' ') {
      if (!resumePause()){ 
        return; 
      }
      strip.fill(0); // Space between words
      strip.show();
      delay(WORD_GAP);
    }
  }
  if (!resumePause()){ 
    return; 
  }
}