#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <string.h>

//OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {8,9,10,11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Variable
const char NEW_LINE = '\n';
const int TEXT_SCALE = 2;
const int CHAR_WIDTH = 6 * TEXT_SCALE;
const int CHAR_HEIGHT = 8 * TEXT_SCALE;

int currPosX = 1;
int currPosY = 0;
char currText[100];


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(2000);         // wait for initializing
  oled.clearDisplay();
  oled.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  char button = keypad.getKey();
  if(button != NO_KEY){
    switch(button){
      case '0':
        insertX(currText, NEW_LINE, currPosX);
        break;
      case '*':
        
        break;
      case '#':
        moveCursor(-1);
        break;
      case 'D':
        moveCursor(1);
        break;
      default:
        insertX(currText, button, currPosX);
        currPosX++;
        
        int a_size = sizeof(currText);
        String s_a = convertToString(currText, a_size);
    
        Serial.print("s_a now ");
        Serial.println(s_a);
        Serial.println(currText);
        
        oled.clearDisplay();
        oled.setTextSize(TEXT_SCALE);
        oled.setTextColor(WHITE);
        oled.setCursor(0, 0);
        oled.print(currText);
        oled.display();
        break;
    }
    currPosX = oled.getCursorX() / CHAR_WIDTH;
    currPosY = oled.getCursorY() / CHAR_HEIGHT;
    char pos[40];
    sprintf(pos, "currPosX %d, oledX %d, oledY %d", currPosX, oled.getCursorX(), oled.getCursorY());
    Serial.println(pos);
  }
}

void moveCursor(int step){
    if(currPosX > 0 ){
      currPosX += step;
    }
}

String convertToString(char* a, int size)
{
    int i;
    String s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

char* insertX(char arr[], char x, int pos)
{
   int i;
    int n = strlen(arr);
    // increase the size by 1
    n++;
  
    // shift elements forward
    for (i = n; i >= pos; i--)
        arr[i] = arr[i - 1];
  
    // insert x at pos
    arr[pos - 1] = x;
  
    return arr;
}
