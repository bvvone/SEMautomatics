#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
int val = 55;

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.println("Example: Font_simple");
    Serial.print("found ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
    showmsgXY(10, 80, 2, &FreeSans12pt7b, "TEN1");   
    showmsgXY(10, 180, 2, &FreeSans12pt7b, "TEN2");

}

void loop(void)
{
//  count = count + 1;


//    tft.fillScreen(BLACK);
//    showmsgXY(10, 80, 2, &FreeSans12pt7b, "TEN1");              //перша цифра позиція від лівого краю, друга цифра зміщення вертикально, 3 цифра збільшує величину шрифту 
    showvalXY(180, 80, 1, &FreeSevenSegNumFont, val);
//    showmsgXY(10, 180, 2, &FreeSans12pt7b, "TEN2");
    showmsgXY(180, 180, 1, &FreeSevenSegNumFont, "123");
    delay(5000);
//    if (count <= 100)
//    {
//      count = 0;
//    }
    
}

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
    int16_t x1, y1;
    uint16_t wid, ht;
    tft.drawFastHLine(0, y, tft.width(), WHITE);
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(GREEN);
    tft.setTextSize(sz);
    tft.print(msg);
    delay(1000);
}

void showvalXY(int x, int y, int sz, const GFXfont *f, int val)
{
    char buf[7];   //big enough for -32768 and terminating NUL
    showmsgXY(x, y, sz, f, itoa(val, buf, 10));
}

