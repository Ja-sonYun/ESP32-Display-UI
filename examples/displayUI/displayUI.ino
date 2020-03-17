#include "touchSensor.h"
#include "heltec.h"
#include "menu.h"

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
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
    clear();
    currentPage.setCurrentPage(pages[0]);
    currentPage.printBufferPage();
    display();
}

void loop() {
    checkSensorsInput();

    currentPage.buttonAction(leftButton.isTouched(), rightButton.isTouched(), selectButton.isTouched());

    currentPage.printBufferPage();

}
