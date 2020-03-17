#ifndef MENU_H
#define MENU_H

#include "arduino.h"
#include "network/network.h"
#include "heltec.h"
#include "icon.h"

// Display command shortcuts for heltec library
//==============================================
#define drawString(x, y, str)               { Heltec.display -> drawString(x, y, str);          }
#define clear()                             { Heltec.display -> clear();                        }
#define display()                           { Heltec.display -> display();                      }
#define drawHorizontalLine(x, y, len)       { Heltec.display -> drawHorizontalLine(x, y, len);  }
#define drawVerticalLine(x, y, len)         { Heltec.display -> drawVerticalLine(x, y, len);    }
#define drawRect(x, y, width, height)       { Heltec.display -> drawRect(x, y, width, height);  }
#define drawLine(x0, y0, x1, y1)            { Heltec.display -> drawLine(x0, y0, x1, y1);       }
#define getStringWidth(str)                  Heltec.display -> getStringWidth(String(str))     
#define setPixel(x, y)                      { Heltec.display -> setPixel(x, y);                 }

// For ssd1306 library (Not tested)
//==================================
//
// #define drawString(x, y, str)            { display.setTextSize(1); display.setCursor(x, y); display.println(F(str)); }
// #define clear()                          { display.clearDisplay();                                                   }
// #define display()                        { display.display();                                                        }
// #define drawHorizontalLine(x, y, len)    { display.drawLine(x, y, x, y+len, SSD1306_WHITE);                          }
// #define drawVerticalLine(x, y, len)      { display.drawLine(x, y, x+len, y, SSD1306_WHITE);                          }
// #define drawRect(x, y, width, height)    { display.drawRect(x, y, width, height, SSD1306_WHITE);                     }
// #define drawLine(x0, y0, x1, y1)         { display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);                          }
// #define getStringWidth(str)              { (str * 6)                                                                 }
// #define setPixel(x, y)                   { display.drawPixel(x, y, SSD1306_WHITE);                                   }


#define CHAR_WIDTH 6
#define CHAR_HEIGHT 10
#define SCREEN_ROW_SIZE 5
#define SCREEN_PIXEL_HEIGHT 64
#define SCREEN_PIXEL_WIDTH 128
#define ROW_SIZE 20
#define ROW_HEIGHT 10
#define DOWN_SCROLL SCREEN_ROW_SIZE-2 // 3
#define UP_SCROLL 1
#define COPY_CONTENT(p1, p2)  { p1.name=p2.name; p1.connectedTo=p2.connectedTo; p1.code=p2.code; }

#define YES 1
#define NO 0

#define FIRST_ROW 0
#define SECOND_ROW 10
#define THIRD_ROW 20
#define FOURTH_ROW 30
#define FIFTH_ROW 40
#define LAST_ROW 50
#define NOTIFICATION_ROW 52

#define KEYBOARD_FIRST_ROW 10
#define KEYBOARD_SECONDE_ROW 20
#define KEYBOARD_THIRD_ROW 30

#define ENTER_ICON_CODE 4
#define CLOSE_ICON_CODE 215
#define DELETE_ICON_CODE 17
#define CHANGE_ICON_CODE 169

#define IS_ICON(checkicon) ( checkicon == ENTER_ICON_CODE || checkicon == CLOSE_ICON_CODE ||\
                             checkicon == DELETE_ICON_CODE || checkicon == CHANGE_ICON_CODE )

//icon
extern const bool close_icon[ICON_HEIGHT][ICON_WIDTH];
extern const bool enter_icon[ICON_HEIGHT][ICON_WIDTH];
extern const bool delete_icon[ICON_HEIGHT][ICON_WIDTH];
extern const bool change_icon[ICON_HEIGHT][ICON_WIDTH];
extern const bool wifi_signal_weak[ICON_HEIGHT][ICON_WIDTH];
extern const bool wifi_signal_normal[ICON_HEIGHT][ICON_WIDTH];
extern const bool wifi_signal_strong[ICON_HEIGHT][ICON_WIDTH+2];
extern const bool wifi_disconnet[ICON_HEIGHT][ICON_WIDTH];

void drawIcon(int16_t x, int16_t y, const bool icon[][ICON_WIDTH]);
void drawBigIcon(int16_t x, int16_t y, const bool icon[][ICON_WIDTH+2]);

// Need to add page code after adding pages.-----------------------------------------------------------
enum directoryCode {
    MAIN_PAGE=1, WIFI_PAGE, SCAN_WIFI=299, WIFI_CONNECTION, WIFI_DISCONNECT, WIFI_INFO, BLUETOOTH_PAGE=500, DUMMY_PAGE, BACK, DEBUG=999
};

typedef struct content {

    String name;
    String connectedTo;
    uint16_t code; 

} content;

class Menu {

    public:

        String title;
        uint8_t rowSize;
        
    public:

        content contents[ROW_SIZE];

        Menu(String title, uint8_t rowSize, content contentsInput[ROW_SIZE]) {

            this->title = title;
            this->rowSize = rowSize;
            for(uint8_t i = 0; i < rowSize; i++) { COPY_CONTENT(contents[i], contentsInput[i]) }

        }
        
        void appendContent(content contentInput);
        void addContent(content contentInput, uint8_t pos);
        void removeContent(uint8_t pos);

};

class SettingPage {

    private:
        //for blinking
        unsigned long previousTime = 0;
        bool blinkBar = false;
        bool getDisplayDataToBuffer = false;

    public:

        String title;
        String subinfo;
        uint8_t rowSize; // Current content's row length
        content contents[ROW_SIZE];
        bool isConfirmPage = false;
        bool withSelectionBar = true;
        bool isMenu = true;
        bool KeyboardOn = false;

    public:

        void setCurrentPage(Menu page, bool resetSelectionBarPos = true);
        void printPage(bool notificationBar=true);
        void printBufferPage();
        void tmpToCurrentPage(bool resetSelectionBarPos=true);
        void clearTmp();
        void clearCurrentPage();
        void buttonAction(bool left, bool right, bool select);
        
        //void stringArrayToContentsFormat(String stringContent[]);

        //Menu setPages(Menu*& pages, int pagesLen);
        
};

class ConfirmPage {

    private:

        SettingPage *currentpage;

    public:

        bool confirm = YES;
        String confirmMessage;
        String confirmTitle;

    public:

        void setNewConfirmPage(SettingPage *currentpage, String confirmTitle, String confirmMessage) {
            this->currentpage = currentpage;
            this->confirmMessage = confirmMessage;
            this->confirmTitle = confirmTitle;
            this->currentpage->isConfirmPage = true;
            this->currentpage->withSelectionBar = false;
            this->currentpage->isMenu = false;
        }
        
        void clearConfirmPage() {
            this->currentpage->isConfirmPage = false;
            this->confirmMessage = YES;
            clear();
        }

        void printConfirmScreenUI();
        bool isYES() {
            if(this->confirm) {
                return YES;
            } else {
                this->confirm = YES; // reset selection
                return NO;
            }
        }

};

class KeyboardPage {

    private:

        SettingPage *currentpage;
    
    public:

        const char smallAlphabet[30] PROGMEM = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  
                                                'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', DELETE_ICON_CODE, 
                                   CHANGE_ICON_CODE, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ENTER_ICON_CODE, CLOSE_ICON_CODE};

        const char bigAlphabet[30] PROGMEM =   {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  
                                                'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', DELETE_ICON_CODE, 
                                   CHANGE_ICON_CODE, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ENTER_ICON_CODE, CLOSE_ICON_CODE};

        const char numericAndSpecialCharacter[30] PROGMEM = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                                                             '-', '/', ':', ';', '(', ')', '&', '@', '\"', DELETE_ICON_CODE,
                                                CHANGE_ICON_CODE, '.', ',', '?', '!', '\'', '<', '>', ENTER_ICON_CODE, CLOSE_ICON_CODE};

        String title;
        String Entered = "";
        String subInfo = "";

        uint8_t charSelectBarPos = 0;
        bool isNumericKeyboard = false;
        bool isUppercaseKeyboard = false;

        void initialize(SettingPage *currentpage, String title, String subInfo = "") {
            this->currentpage = currentpage;
            this->title = title;
            this->currentpage->withSelectionBar = false;
            this->currentpage->isMenu = false;
            this->currentpage->KeyboardOn = true;
            this->subInfo = subInfo;
        }

        void openKeyboard();
        void printKeyboard(const char keyArray[30]);
        void clearKeyboardSection() {
            this->title = "";
            this->Entered = "";
            this->currentpage->KeyboardOn = false;
            this->charSelectBarPos = 0;
            this->subInfo = "";
            this->isNumericKeyboard = false;
            this->isUppercaseKeyboard = false;
        }

};

void warningPage(String message);

void wifi_initialize();
void scanWifi_func();
void wifi_connection();

bool confirmScreeUI(String confirmMessage);

void selectEffect();
void initialize_display();

extern uint8_t currentRow;
extern uint8_t scroll;
extern uint8_t cursorPos;
extern SettingPage currentPage;
extern Menu pages[5]; //----- LINE 262

// provisional page for wifi scanned list, and etc
extern content tmp[ROW_SIZE];
extern uint8_t tmpLen;

#endif
