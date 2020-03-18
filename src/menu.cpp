#include "menu.h"

uint8_t currentRow = 0; 
uint8_t scroll = 0;
uint8_t cursorPos = 0;

SettingPage currentPage;
ConfirmPage confirmPage;
KeyboardPage keyboardPage;

/////////////////
//             //      
// DESCRIPTION //
//             //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  1. Adding setting page
//     |----- 1.1 : Add directoryCode which is at the "menu.h" with Page title
//     |----- 1.2 : And then, move to this file("menu.cpp") and add page's content and menu class. ( like line 67 at this file. )
//     |      |         When you add back button, go to line 300 and add action.
//     |----- 1.3 : Next, put to the class menu array ( pages[4] ) what you made at 1.2 and increase pages length. ( line 91 )
//     |                And move to menu.h and also increase pages length. ( line 262 at "menu.h" )
//     +----- 1.4 : Add action when you click the menu. ( line 257)
//            |------ 1.4.1 : Add " case 'directorycode': " 
//            |               |  Action here.( when you want to move to the other page, add 'currentPage.setCurrentPage(class name of page)' )
//            |               |  Or just your function. Don't forget " break; ". when you use your own function,
//            |               |  you need to add clear() or display() function, manually.
//            |               |    
//            |               +-> When you want to use tmpPage, Do " clearTmp() " and open your function.
//            |                  And store like tmp[i] = { string that you want to display, connected page title, directorycode(if you don't want any
//            |                  action, just set 0.) } -> (struct content)
//            |                  If you want to add " back " button, add tmp[i] = { "BACK", page title to go back, BACK }; 
//            |                     and go to line 300, and add action when clicked back button
//            |                  And lastly, set tmpLen inside your function. After that, go back to here and open tmpToCurrentPage function and
//            |                  add " break; ".
//            |                 
//  2. Adding confirm page
//     |----- 2.1 : At the line 271 ( same as 1.4.1 ), Add case of directorycode.------------------------------------+
//     |      |        add " confirmPage.setNewConfirmPage(&currentPage, confirmpage title, confirmpage subtitle);   |
//     +----- 2.2 : And then, you need to add action when you choose YES or NO.                                      |
//            |        Go to line 320, inside the switch statement, add case of directorycode form here <------------+
//            |        And add 
//            |             if(confirmPage.isYES()) {
//            |                 * Action here when clicked YES *
//            |             } else {
//            |                 * Action here when clicked NO *
//            |             }
//            |                 * Action when closing confirm page *
//            |                 confirmPage.clearConfirmPage();
//            |             break;
//            |
//  3. Adding keyboard page
//     +----- 3.1 : Add keyboard action first.
//            |         keyboardPage.initialize(&currentPage, title, message);
//            3.2 : Go to line 370, add action when clicked close and enter with current directory code ( switch statement ).
//            3.3 : You can access a string what you typed via keyboardPage.Entered.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////
//          //
//   PAGE   //
//          //
//////////////

// Add page like below codes.-----------------------------------------------------------
//                                       { contents title, connected to, directory code(int) }
content mainContents[ROW_SIZE] PROGMEM = {{"wifi",     "wifi_page", WIFI_PAGE},//     |------ LINE 67
                                          {"bluetooth","bluetooth_page", BLUETOOTH_PAGE},//     |
                                          {"debug",    "debug",     DEBUG_PAGE}};//        |
// mainpage(title, length of row, content)--------------------------------------------+
Menu mainPage("main_page", 3, mainContents);
// wifi
content wifiContents[ROW_SIZE] PROGMEM = {{"scan wifi",              "scan_wifi",  SCAN_WIFI}, 
                                         {"connect known wifi"},
                                         {"disconnect current wifi", "disconnect wifi", WIFI_DISCONNECT}, 
                                         {"current wifi information", "current_wifi_info", WIFI_INFO},
                                         {"back",                   "main_page",  BACK}};
Menu wifiPage("wifi_page", 5, wifiContents);

// BLUETOOTH_PAGE
content bluetoothContents[ROW_SIZE] PROGMEM = {{"test", "", 0},
                                               {"back", "main_page", BACK}};

Menu bluetoothPage("bluetooth_page", 2, bluetoothContents);

// provisional page for wifi scanned list, and etc
content dummyContents[ROW_SIZE] = {{}};
Menu dummyPage("dummy_page", 0, dummyContents);

content dummyContents2[ROW_SIZE] = {{}};
Menu dummyPage2("dummy_page2", 0, dummyContents2);

content debugContents[ROW_SIZE] = {{"keyboard", "keyboard_page", KEYBOARD_PAGE},
                           {"back", "main_page", BACK}};
Menu debugPage("debug_page", 2, debugContents);

content tmp[ROW_SIZE];
uint8_t tmpLen;

Menu pages[6] = {mainPage, wifiPage, dummyPage, dummyPage2, bluetoothPage, debugPage};//----- LINE 91
//  pages[pages length]


void drawIcon(int16_t x, int16_t y, const bool icon[][ICON_WIDTH]) {
    for(int y_i = 0; y_i < ICON_HEIGHT; y_i++) {
        for(int x_i = 0; x_i < ICON_WIDTH; x_i++) {
            if(icon[y_i][x_i]) {
                setPixel(x+x_i, y+y_i);
            }
        }
    }
}

void drawBigIcon(int16_t x, int16_t y, const bool icon[][ICON_WIDTH+2]) {
    for(int y_i = 0; y_i < ICON_HEIGHT; y_i++) {
        for(int x_i = 0; x_i < ICON_WIDTH+2; x_i++) {
            if(icon[y_i][x_i]) {
                setPixel(x+x_i, y+y_i);
            }
        }
    }
}


void wifi_connection() {
    long signalStrong = getWifiSignal_func() * (-1);
    if(signalStrong == 0) {
        drawIcon(SCREEN_PIXEL_WIDTH-ICON_WIDTH-4, LAST_ROW+5, wifi_disconnet);
    } else if(signalStrong < 30) {
        drawBigIcon(SCREEN_PIXEL_WIDTH-ICON_WIDTH-5, LAST_ROW+5, wifi_signal_strong);
    } else if(signalStrong < 60) {
        drawIcon(SCREEN_PIXEL_WIDTH-ICON_WIDTH-4, LAST_ROW+5, wifi_signal_normal);
    } else {
        drawIcon(SCREEN_PIXEL_WIDTH-ICON_WIDTH-4, LAST_ROW+5, wifi_signal_weak);
    }
    
}

//////////////////////////
//                      //
//   MENU DEFINITION    //
//                      //
//////////////////////////

void Menu::appendContent(content contentsInput) {
    if(this->rowSize < ROW_SIZE) {
        COPY_CONTENT(contents[this->rowSize], contentsInput);
        this->rowSize += 1;
    }
}

void Menu::addContent(content contentInput, uint8_t pos) {
    if(this->rowSize < ROW_SIZE) {
        for(int i = ROW_SIZE-1; i > pos; i--) { COPY_CONTENT(this->contents[i], this->contents[i-1]); }
        COPY_CONTENT(this->contents[pos], contentInput);
    }
}

void Menu::removeContent(uint8_t pos) {
    content blankContent = { "", "", 0 };
    this->contents[pos] = blankContent;
    for(int i = pos; i < ROW_SIZE; i++) {
        COPY_CONTENT(this->contents[pos], this->contents[pos+1]);
    }
}

/////////////////////////////////////
//                                 //
//  CURRENT PAGE INFO DEFINITION   //
//                                 //
/////////////////////////////////////

void SettingPage::setCurrentPage(Menu page, bool resetSelectionBarPos) {
    this->withSelectionBar = true;
    this->isMenu = true;
    clearCurrentPage();
    this->title = page.title;
    this->rowSize = page.rowSize;
    for(int i = 0; i < ROW_SIZE; i++) { COPY_CONTENT(this->contents[i], page.contents[i]); }
    if(resetSelectionBarPos) {
        currentRow = 0;
        scroll = 0;
        cursorPos = 0;
    }
}

void SettingPage::tmpToCurrentPage(bool resetSelectionBarPos) {
    if(resetSelectionBarPos) {
        currentRow = 0;
        scroll = 0;
        cursorPos = 0;
    }
    this->withSelectionBar = true;
    this->title = "tmp";
    this->rowSize = tmpLen;
    for(int i = 0; i < ROW_SIZE; i++) { COPY_CONTENT(this->contents[i], tmp[i]); }
}

void SettingPage::clearTmp() {
    tmpLen = 0;
    content blankContent[ROW_SIZE];
    for(int i = 0; i < ROW_SIZE; i++) { COPY_CONTENT(tmp[i], blankContent[i]); }
}

void SettingPage::clearCurrentPage() {
    this->title = "";
    this->rowSize = 0;
    content blankContent[ROW_SIZE];
    for(int i = 0; i < ROW_SIZE; i++) { COPY_CONTENT(this->contents[i], blankContent[i]); }
}

void SettingPage::printPage(bool notificationBar) {
    for(int i = 0; i < SCREEN_ROW_SIZE; i++) {
        String temp = this->contents[i+scroll].name;
        drawString(0, i*10, temp);
    }
    if(notificationBar) {
        drawHorizontalLine(0, SCREEN_PIXEL_HEIGHT-11, SCREEN_PIXEL_WIDTH);
        drawString(0, NOTIFICATION_ROW, String(currentRow));
        drawString(40, NOTIFICATION_ROW, currentPage.title);
        wifi_connection();
    }
    
}

void SettingPage::buttonAction(bool left, bool right, bool select) {
    // for scroll motion
    if(left || right || select) {
        this->getDisplayDataToBuffer = true; // start to get screen data to a buffer
        if(this->withSelectionBar) {
            if(left) {
                currentRow = currentRow > 0 ? currentRow - 1 : currentRow;
                cursorPos = cursorPos > 0 ? cursorPos - 1 : cursorPos;
                if(cursorPos == UP_SCROLL && scroll != 0) {
                    scroll -= 1;
                    cursorPos += 1;
                }
                // if the selectionbar is reach the front of row, no action.
                // if not, cursorposition is increase. when the cursorposition is reached the UP_SCROLL which is 1, and scroll isn't 0,
                // decrease scroll, and increase cursorposition so that cursor will look like stopped.
            } else if(right) {
                if(rowSize-1 > currentRow) {
                    currentRow += 1;
                    if(rowSize-1 > cursorPos && SCREEN_ROW_SIZE-1 > cursorPos) {
                        if(cursorPos < DOWN_SCROLL) {
                            cursorPos += 1;
                        } else {
                            if(SCREEN_ROW_SIZE-DOWN_SCROLL > rowSize-1-currentRow) {
                                cursorPos += 1;
                            } else {
                                scroll += 1;
                            }
                        }
                    }
                }
                // if the selectionbar is reach the end of row, no action
                // if not, increase currentrow. if the rowsize(current content's row length) is bigger than cursorposition, 
                // and SCREEN_ROW_SIZE which is 5 - 1 is bigger than cursorposition, and also the cursorposition is smaller than
                // DOWN_SCROLL which is 3, then increase cursorposition. 
            } else if(select) {
                // touch effect
                selectEffect();
                
                uint16_t code = this->contents[currentRow].code;

                // special action here, code enum is defined at menu.h
                // Page action here
                switch(code) { // ----- LINE 257

                    case MAIN_PAGE:
                        currentPage.setCurrentPage(mainPage);
                        break;

                    case WIFI_PAGE:
                        currentPage.setCurrentPage(wifiPage);
                        break;

                    case DUMMY_PAGE:
                        currentPage.setCurrentPage(dummyPage);
                        break;

                    case WIFI_CONNECTION:
                        confirmPage.setNewConfirmPage(&currentPage, "=Connect Wifi to=", this->contents[currentRow].connectedTo);
                        break;

                    case BLUETOOTH_PAGE:
                        currentPage.setCurrentPage(bluetoothPage);
                        break;
        
                    case SCAN_WIFI:
                        clearTmp();
                        scanWifi_func();
                        tmpToCurrentPage();
                        break;

                    case WIFI_INFO:
                        clearTmp();
                        currentWifiInfo_func();
                        tmpToCurrentPage();
                        break;

                    case WIFI_DISCONNECT:
                        if(getWifiSignal_func()) {
                            confirmPage.setNewConfirmPage(&currentPage, "Are you sure you want", "to disconnect wifi");
                        } else {
                            warningPage("Your not connected");
                        }
                        
                        break;

                    case DEBUG_PAGE:
                        currentPage.setCurrentPage(debugPage);
                        break;

                    case KEYBOARD_PAGE:
                        keyboardPage.initialize(&currentPage, "title", "message");
                        break;

                    case BACK:  // line 300
                        String backTo = this->contents[currentRow].connectedTo;
                        if(backTo == "main_page") {
                            currentPage.setCurrentPage(mainPage);
                        } else if(backTo == "wifi_page") {
                            currentPage.setCurrentPage(wifiPage);
                        }
                        break;
                }
            }

        } else if(this->isConfirmPage) {
            if(left) {
                confirmPage.confirm = YES;
            } else if(right) {
                confirmPage.confirm = NO;
            } else if(select) {
                uint16_t code = this->contents[currentRow].code;
                // confirm message action here
                switch (code) {
                    case WIFI_CONNECTION:
                        if(confirmPage.isYES()) {
                            keyboardPage.initialize(&currentPage, "Enter wifi password", confirmPage.confirmMessage);
                        } else {
                            tmpToCurrentPage(false); // go back to wifi list
                        }
                        confirmPage.clearConfirmPage();
                        break;
                    
                    case WIFI_DISCONNECT:
                        if(confirmPage.isYES()) {
                            disconnectWifi_func();
                        }
                        currentPage.setCurrentPage(wifiPage, false);
                        confirmPage.clearConfirmPage();
                        break;
          
                }

                
            }
        } else if(this->KeyboardOn) {
            if(left) {
                if(keyboardPage.charSelectBarPos != 0) {
                    keyboardPage.charSelectBarPos -= 1;
                } else {
                    keyboardPage.charSelectBarPos = KEYBOARD_THIRD_ROW-1;
                }
            } else if(right) {
                if(keyboardPage.charSelectBarPos != KEYBOARD_THIRD_ROW-1) {
                    keyboardPage.charSelectBarPos += 1;
                } else {
                    keyboardPage.charSelectBarPos = 0;
                }
            } else if(left && right) {
                if(keyboardPage.charSelectBarPos < KEYBOARD_THIRD_ROW && keyboardPage.charSelectBarPos > KEYBOARD_SECONDE_ROW) {
                    keyboardPage.charSelectBarPos -= KEYBOARD_SECONDE_ROW;
                } else {
                    keyboardPage.charSelectBarPos += KEYBOARD_FIRST_ROW;
                }
                
            } else if(select) {
                uint16_t code = this->contents[currentRow].code;

                switch (keyboardPage.smallAlphabet[keyboardPage.charSelectBarPos]) {

                    case DELETE_ICON_CODE:

                        keyboardPage.Entered.remove(keyboardPage.Entered.length()-1);
                        break;
                    
                    case CLOSE_ICON_CODE:
                        // close keyboard action here
                        switch (code) {
                            case WIFI_CONNECTION:
                                keyboardPage.clearKeyboardSection();
                                tmpToCurrentPage(false);
                                break;

                            case KEYBOARD_PAGE:
                                keyboardPage.clearKeyboardSection();
                                currentPage.setCurrentPage(debugPage, false);
                                break;
                            
                            }

                        break;

                    case ENTER_ICON_CODE:

                        // enter keyboard action here
                        switch (code) {
                            case WIFI_CONNECTION:
                                if(connectWifi_func(keyboardPage.subInfo, keyboardPage.Entered)) {
                                    keyboardPage.clearKeyboardSection();
                                    currentPage.setCurrentPage(wifiPage);
                                } else {
                                    keyboardPage.clearKeyboardSection();
                                    tmpToCurrentPage(false);
                                }
                                break;

                            case KEYBOARD_PAGE:                               
                                warningPage(keyboardPage.Entered);
                                delay(2000);
                                keyboardPage.clearKeyboardSection();
                                currentPage.setCurrentPage(debugPage, false);
                                break;
                            
                        }

                        break;
                    
                    case CHANGE_ICON_CODE:

                        if(!keyboardPage.isNumericKeyboard && !keyboardPage.isUppercaseKeyboard) {
                            keyboardPage.isNumericKeyboard = true;
                        } else if(keyboardPage.isNumericKeyboard) {
                            keyboardPage.isNumericKeyboard = false;
                            keyboardPage.isUppercaseKeyboard = true;
                        } else {
                            keyboardPage.isUppercaseKeyboard = false;
                        }
                        break;

                    default:

                        if(!keyboardPage.isNumericKeyboard && !keyboardPage.isUppercaseKeyboard) {
                            keyboardPage.Entered += String(keyboardPage.smallAlphabet[keyboardPage.charSelectBarPos]);
                        } else if(keyboardPage.isNumericKeyboard) {
                            keyboardPage.Entered += String(keyboardPage.numericAndSpecialCharacter[keyboardPage.charSelectBarPos]);
                        } else {
                            keyboardPage.Entered += String(keyboardPage.bigAlphabet[keyboardPage.charSelectBarPos]);
                        }
                        
                }
                
            }
        }
    }
}

// print with below function 
void SettingPage::printBufferPage() {
    if(withSelectionBar) {
        unsigned long currentTime = millis();
        if(currentTime - this->previousTime >= 300) { // display every 300ms
            this->previousTime = currentTime;
            if(!this->blinkBar) {
                clear();
                printPage();
                this->blinkBar = true;
                display();
            } else {
                clear();
                drawHorizontalLine(0, (CHAR_HEIGHT+cursorPos*CHAR_HEIGHT), getStringWidth(this->contents[currentRow].name)+1);
                printPage();
                this->blinkBar = false;
                display();
            }
        }
    } else if(!withSelectionBar && isConfirmPage && this->getDisplayDataToBuffer) { // put screen datas to a buffer when it detected touch
        confirmPage.printConfirmScreenUI();
        
    } else if(this->KeyboardOn) {
        unsigned long currentTime = millis();

        if(currentTime-this->previousTime >= 300) { // display every 300ms
            this->previousTime = currentTime;
            if(!this->blinkBar) {
                clear();
                keyboardPage.openKeyboard();
                this->blinkBar = true;
                display();
            } else {
                clear();
                drawRect(10+getStringWidth(keyboardPage.Entered), THIRD_ROW, 2, CHAR_HEIGHT-1);
                keyboardPage.openKeyboard();
                this->blinkBar = false;
                display();
            }
        } 

    } else {
        if(this->getDisplayDataToBuffer) { // put screen datas to a buffer it detected touch
            printPage();
        }
    }

    if(this->getDisplayDataToBuffer) { // display screen from buffer and reset buffer
        display();
        this->getDisplayDataToBuffer = false;
    }

    

}

//////////////////
//              //
//   KEYBOARD   //
//              //
//////////////////

void KeyboardPage::openKeyboard() {
    drawString(10, THIRD_ROW-1, this->Entered);
    drawString(12, FIRST_ROW+3, this->title);
    drawRect(5, FIRST_ROW, getStringWidth(this->title)+14, CHAR_HEIGHT+7);
    drawHorizontalLine(0, FOURTH_ROW+2, SCREEN_PIXEL_WIDTH);
    drawHorizontalLine(7, FOURTH_ROW, SCREEN_PIXEL_WIDTH-16);
    
    if(this->isNumericKeyboard) {
        printKeyboard(this->numericAndSpecialCharacter);
    } else if(this->isUppercaseKeyboard) {
        printKeyboard(this->bigAlphabet);
    } else {
        printKeyboard(this->smallAlphabet);
    }

    drawIcon(SCREEN_PIXEL_WIDTH-16, FIFTH_ROW+6, delete_icon);
    drawIcon(SCREEN_PIXEL_WIDTH-14, LAST_ROW+6, close_icon);
    drawIcon(SCREEN_PIXEL_WIDTH-26, LAST_ROW+6, enter_icon);
    drawIcon(5, LAST_ROW+6, change_icon);
}

void KeyboardPage::printKeyboard(const char keyArray[30]) {
    for(int y = 0; y < KEYBOARD_THIRD_ROW; y++) {
            if(y < KEYBOARD_FIRST_ROW) {
                drawString(y*(CHAR_WIDTH+CHAR_WIDTH)+CHAR_WIDTH/* (y*12+6) */, FOURTH_ROW+2, String(keyArray[y]))
                if(this->charSelectBarPos == y) {
                    drawHorizontalLine(y*(CHAR_WIDTH+CHAR_WIDTH)+CHAR_WIDTH, FOURTH_ROW+CHAR_HEIGHT+3, getStringWidth(keyArray[y]));
                }

            } else if(y < KEYBOARD_SECONDE_ROW) {
                drawString((y-KEYBOARD_FIRST_ROW)*(CHAR_WIDTH+CHAR_WIDTH)+CHAR_WIDTH/* (y*12+6) */, FIFTH_ROW+2, String(keyArray[y])); 
                if(this->charSelectBarPos == y) {
                    if(IS_ICON(keyArray[y])) {
                        drawHorizontalLine((y-KEYBOARD_FIRST_ROW)*(CHAR_WIDTH+CHAR_WIDTH)+CHAR_WIDTH, FIFTH_ROW+CHAR_HEIGHT+3, ICON_WIDTH);
                    } else {
                        drawHorizontalLine((y-KEYBOARD_FIRST_ROW)*(CHAR_WIDTH+CHAR_WIDTH)+CHAR_WIDTH, FIFTH_ROW+CHAR_HEIGHT+3, getStringWidth(keyArray[y])+1);
                    }
                }
                
            } else if(y < KEYBOARD_THIRD_ROW) {
                drawString((y-KEYBOARD_SECONDE_ROW)*(CHAR_WIDTH+CHAR_WIDTH)+ICON_WIDTH-3/* (y*12+9+9) */, LAST_ROW+2, String(keyArray[y]));
                if(this->charSelectBarPos == y) {
                    if(IS_ICON(keyArray[y])) {
                        drawHorizontalLine((y-KEYBOARD_SECONDE_ROW)*(CHAR_WIDTH+CHAR_WIDTH)+ICON_WIDTH-3, LAST_ROW+CHAR_HEIGHT+3, ICON_WIDTH);
                    } else {
                        drawHorizontalLine((y-KEYBOARD_SECONDE_ROW)*(CHAR_WIDTH+CHAR_WIDTH)+ICON_WIDTH-3, LAST_ROW+CHAR_HEIGHT+3, getStringWidth(keyArray[y])+1);
                    }
                    
                }
                
            }
            
        }
}


//////////////////
//              //
//   EXTRA UI   //
//              //
//////////////////

void ConfirmPage::printConfirmScreenUI() {
    clear();
    drawRect(2, 5, SCREEN_PIXEL_WIDTH-2, SCREEN_PIXEL_HEIGHT-5);
    drawRect(4, 7, SCREEN_PIXEL_WIDTH-6, SCREEN_PIXEL_HEIGHT-9)
    drawString(20, SECOND_ROW, this->confirmTitle);
    drawString(10, THIRD_ROW+3, "< "+this->confirmMessage+ " >");
    if(this->confirm == YES) {
        drawRect(15, FIFTH_ROW, 21+CHAR_WIDTH*2, CHAR_HEIGHT+ROW_HEIGHT-2);
        drawRect(19, FIFTH_ROW+4, 21+CHAR_WIDTH*2-8, CHAR_HEIGHT+ROW_HEIGHT-2-8)
        drawString(21, FIFTH_ROW+3, "YES");
        drawRect(SCREEN_PIXEL_WIDTH-31-CHAR_WIDTH*3, FIFTH_ROW, 21+CHAR_WIDTH*2, CHAR_HEIGHT+ROW_HEIGHT-2)
        drawString(SCREEN_PIXEL_WIDTH-23-CHAR_WIDTH*3, FIFTH_ROW+3, "NO");
    } else { // confirm == NO
        drawRect(15, FIFTH_ROW, 21+CHAR_WIDTH*2, CHAR_HEIGHT+ROW_HEIGHT-2);
        drawString(21, FIFTH_ROW+3, "YES");
        drawRect(SCREEN_PIXEL_WIDTH-31-CHAR_WIDTH*3, FIFTH_ROW, 21+CHAR_WIDTH*2, CHAR_HEIGHT+ROW_HEIGHT-2)
        drawRect(SCREEN_PIXEL_WIDTH-31-CHAR_WIDTH*3+4, FIFTH_ROW+4, 21+CHAR_WIDTH*2-8, CHAR_HEIGHT+ROW_HEIGHT-2-8)
        drawString(SCREEN_PIXEL_WIDTH-23-CHAR_WIDTH*3, FIFTH_ROW+3, "NO");
    }
    
}

void selectEffect() {
    for(int i = 0; i < 4; i++) {
        drawRect(0+i, 0+i, SCREEN_PIXEL_WIDTH-(i*2), SCREEN_PIXEL_HEIGHT-(i*2));
        delay(100);
        display();
    }
}


void warningPage(String message) {
    clear();
    drawString(0, 0, message);
    display();
    delay(2000);
}

void initialize_display() {
    #ifdef __HELTEC__
        Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
    #endif
    #ifdef __SSD1306__
        Serial.begin(9600);
        if(!display_.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
            Serial.println(F("SSD1306 allocation failed"));
            for(;;); // Don't proceed, loop forever
        }
    #endif
    clear();
    currentPage.setCurrentPage(pages[0]);
    currentPage.printBufferPage();
    display();
}