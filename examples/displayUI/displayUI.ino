#include "touchSensor.h"
#include "menu.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                             //
// If you're using ssd1306, go to src/menu.h and uncomment __SSD1306__ and comment __HELTEC__. //
//                                                                                             //
// Description is at < src/menu.cpp > for modifying pages.                                     //
//                                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////


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

    // currentPage.buttonAction(bool type, bool type, bool type);
    // TouchSensor.isTouched() return bool type
    currentPage.buttonAction(leftButton.isTouched(), rightButton.isTouched(), selectButton.isTouched());

    currentPage.printBufferPage();

}
