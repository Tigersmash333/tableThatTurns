#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>


#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

#define MINPRESSURE 200
#define MAXPRESSURE 1000
#define A 49
#define B 47
#define C 45
#define D 43
#define NUMBER_OF_STEPS_PER_REV 512


// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9341
const int TS_LEFT=89,TS_RT=906,TS_TOP=132,TS_BOT=910;

 
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn, plus_btn, minus_btn;
int screenumber = 1;
int pixel_x, pixel_y;
float mopowaBaby = 2.6;
int isStepOn = 0;
float percentageOfmopowaBaby =(((5-mopowaBaby)/4)*100)+5;

bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);    
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);  
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.y, TS_LEFT, TS_RT, 0, tft.width()); 
        pixel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define LIGHTGREEN   0x7D8E



void setup(void)
{
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  
    Serial.begin(9600);
    uint16_t ID = tft.readID();

    
    if (ID == 0xD3D3) ID = 0x9486; 
    tft.begin(ID);
    tft.setRotation(1);            
    tft.fillScreen(WHITE);
    tft.setTextSize(3);
    tft.setTextColor(LIGHTGREEN);
    tft.setCursor(80, 95);
    tft.print("Tiger.inc");
    tft.setCursor(60, 135);
    tft.print("Technologies");
    
   

    delay(1500);
          tft.fillScreen(WHITE);
            
      on_btn.initButton(&tft,  80, 200, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
              off_btn.initButton(&tft, 240, 200, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
              on_btn.drawButton(false);
              off_btn.drawButton(false);
              tft.fillRect(80, 80, 160, 80, RED);
          plus_btn.initButton(&tft,  250, 40, 50, 50, WHITE, CYAN, BLACK, "+", 2);
          minus_btn.initButton(&tft, 75, 40, 50, 50, WHITE, CYAN, BLACK, "-", 2);
              plus_btn.drawButton(false);
              minus_btn.drawButton(false);
                  tft.fillRect(120, 30, 100, 35, WHITE);
                  tft.setCursor(125,30 );
               tft.print(percentageOfmopowaBaby);
               tft.setCursor(190,30);
                  tft.print("%");
    
}

void write(int a,int b,int c,int d){
digitalWrite(A,a);
digitalWrite(B,b);
digitalWrite(C,c);
digitalWrite(D,d);
} 
void onestep(){
write(1,0,0,0);
delay(mopowaBaby);
write(1,1,0,0);
delay(mopowaBaby);
write(0,1,0,0);
delay(mopowaBaby);
write(0,1,1,0);
delay(mopowaBaby);
write(0,0,1,0);
delay(mopowaBaby);
write(0,0,1,1);
delay(mopowaBaby);
write(0,0,0,1);
delay(mopowaBaby);
write(1,0,0,1);
delay(mopowaBaby);
}

 void kebab(){}

void loop(void)
{


      tft.setTextColor(BLACK);
         
   
              bool down = Touch_getXY();
              on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
              off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
              if (on_btn.justReleased())
                  on_btn.drawButton();
              if (off_btn.justReleased())
                  off_btn.drawButton();
              if (on_btn.justPressed()) {
                  on_btn.drawButton(true);
                  int sceenumber = 1;
                  tft.fillRect(80, 80, 160, 80, GREEN);
                  isStepOn = 1;
              }
              if (off_btn.justPressed()) {
                  off_btn.drawButton(true);
                  tft.fillRect(80, 80, 160, 80, RED);
                  isStepOn = 0;
               }


               
              
              plus_btn.press(down && plus_btn.contains(pixel_x, pixel_y));
              minus_btn.press(down && minus_btn.contains(pixel_x, pixel_y));
              if (plus_btn.justReleased())
                  plus_btn.drawButton();
              if (minus_btn.justReleased())
                  minus_btn.drawButton();
              if (plus_btn.justPressed()) {
                  plus_btn.drawButton(true);
                  int sceenumber = 1;
                  if(mopowaBaby > 1.2){
                  mopowaBaby = mopowaBaby-0.2;}
                  tft.fillRect(120, 30, 100, 35, WHITE);
                  tft.setTextColor(BLACK);
                  if(percentageOfmopowaBaby >= 96){
                  tft.setCursor(120,30);
                  }
                  else if(percentageOfmopowaBaby <= 9){
                  tft.setCursor(130,30);
                  }
                  else{
                  tft.setCursor(125,30);
                  }
                  tft.print(percentageOfmopowaBaby);
                  if(percentageOfmopowaBaby >= 96){
                  tft.setCursor(200,30);
                  }
                  else if(percentageOfmopowaBaby <= 9){
                  tft.setCursor(180,30);
                  }
                  else{
                  tft.setCursor(190,30);
                  }
                  tft.print("%");
              }
              if (minus_btn.justPressed()) {
                  minus_btn.drawButton(true);
                  
                  if(mopowaBaby < 4.9){
                  mopowaBaby = mopowaBaby+0.2;
                  }
                  tft.fillRect(120, 30, 100, 35, WHITE);
                  tft.setTextColor(BLACK);
                  
                  if(percentageOfmopowaBaby >= 96){
                  tft.setCursor(120,30);
                  }
                  else if(percentageOfmopowaBaby <= 9){
                  tft.setCursor(130,30);
                  }
                  else{
                  tft.setCursor(125,30);
                  }
                  tft.print(percentageOfmopowaBaby);
                  if(percentageOfmopowaBaby >= 96){
                  tft.setCursor(195,30);
                  }
                  else if(percentageOfmopowaBaby <= 9){
                  tft.setCursor(185,30);
                  }
                  else{
                  tft.setCursor(190,30);
                  }
                  tft.print("%");
               }
               
               
              
               
if (isStepOn ==1){
onestep();
}
percentageOfmopowaBaby =(((5-mopowaBaby)/4)*100)+5;
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
