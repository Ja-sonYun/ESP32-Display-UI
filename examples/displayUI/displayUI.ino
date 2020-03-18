#include "touchSensor.h"
#include "menu.h"

// If you're using ssd1306, go to menu.h and uncomment __SSD1306__ and comment __HELTEC__.

#ifdef __SSD1306__
    Adafruit_SSD1306 display_(SCREEN_PIXEL_WIDTH, SCREEN_PIXEL_HEIGHT, &Wire, OLED_RESET);
#endif

//touchsensor ***(pin number, read value, value range)
TouchSensor leftButton(T7);
TouchSensor rightButton(T8);
TouchSensor selectButton(T9);

void checkSensorsInput() {
    leftButton.checkSensor();
    rightButton.checkSensor();
    selectButton.checkSensor();
}

void setup() {
    initialize_display();
}

void loop() {
    checkSensorsInput();

    currentPage.buttonAction(leftButton.isTouched(), rightButton.isTouched(), selectButton.isTouched());

    currentPage.printBufferPage();

}
