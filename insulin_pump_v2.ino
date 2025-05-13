#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BTN_UP 14   
#define BTN_DOWN 12 
#define BTN_SELECT 13
#define STEP_PIN 18
#define DIR_PIN 19
#define ENABLE_PIN 4  // Changed to GPIO 4 to avoid conflicts

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

int menuIndex = 0;
bool inSubMenu = false;
int doseOptions[] = {2, 3.9, 5}; // Time values for doses
const char* menuItems[] = {"5 units", "10 units", "15 units"};
const int menuSize = 3;
const char* subMenuItems[] = {"Inject", "Refill", "Back"};
int subMenuIndex = 0;
const int subMenuSize = 3;
unsigned long lastButtonPress = 0;
const int debounceDelay = 200;

void drawMenu() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(25, 3);
    display.print(inSubMenu ? "Select Action" : "Select Dose");

    for (int i = 0; i < (inSubMenu ? subMenuSize : menuSize); i++) {
        if ((inSubMenu && i == subMenuIndex) || (!inSubMenu && i == menuIndex)) {
            display.fillRoundRect(5, 20 + (i * 12), 118, 12, 4, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        } else {
            display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        }
        display.setCursor(20, 20 + (i * 14));
        display.print(inSubMenu ? subMenuItems[i] : menuItems[i]);
    }
    display.display();
}

void moveStepper(int steps) {
    digitalWrite(ENABLE_PIN, LOW); // Enable the stepper driver
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
    stepper.move(steps);
    while (stepper.distanceToGo() != 0) {
        stepper.run();
    }
    digitalWrite(ENABLE_PIN, HIGH); // Disable the stepper driver after movement
}

void setup() {
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_SELECT, INPUT_PULLUP);
    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, HIGH); // Keep disabled initially

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for (;;);
    }
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
    drawMenu();
}

void loop() {
    if (millis() - lastButtonPress > debounceDelay) {
        if (digitalRead(BTN_UP) == LOW) {
            if (inSubMenu) {
                subMenuIndex = (subMenuIndex > 0) ? subMenuIndex - 1 : subMenuSize - 1;
            } else {
                menuIndex = (menuIndex > 0) ? menuIndex - 1 : menuSize - 1;
            }
            drawMenu();
            lastButtonPress = millis();
        }

        if (digitalRead(BTN_DOWN) == LOW) {
            if (inSubMenu) {
                subMenuIndex = (subMenuIndex < subMenuSize - 1) ? subMenuIndex + 1 : 0;
            } else {
                menuIndex = (menuIndex < menuSize - 1) ? menuIndex + 1 : 0;
            }
            drawMenu();
            lastButtonPress = millis();
        }

        if (digitalRead(BTN_SELECT) == LOW) {
            if (!inSubMenu) {
                inSubMenu = true;
            } else {
                int steps = doseOptions[menuIndex] * 200;
                if (subMenuIndex == 0) {
                    moveStepper(steps); // Inject
                } else if (subMenuIndex == 1) {
                    moveStepper(-steps); // Refill
                } else {
                    inSubMenu = false; // Exit submenu
                }
            }
            drawMenu();
            lastButtonPress = millis();
        }
    }
}
