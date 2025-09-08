#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Eye properties
int eyeWidth = 50;
int eyeHeight = 30;
int eyeX = 64; // Start in the middle of the screen
int eyeY = 32; // Vertical center of the screen
int direction = 1; // 1 for right, -1 for left

void setup() {
  // Initialize the display
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  // Clear the display
  display.clearDisplay();

  // Draw the oval eye
  drawEye(eyeX, eyeY, eyeWidth, eyeHeight);

  // Update the eye position
  eyeX += direction;
  if (eyeX - eyeWidth / 2 <= 0 || eyeX + eyeWidth / 2 >= SCREEN_WIDTH) {
    direction *= -1;
  }

  // Display the buffer
  display.display();

  // Delay for animation smoothness
  delay(50);
}

void drawEye(int x, int y, int w, int h) {
  // Draw an oval using the drawEllipse function
  display.drawEllipse(x, y, w / 2, h / 2, SSD1306_WHITE);
}