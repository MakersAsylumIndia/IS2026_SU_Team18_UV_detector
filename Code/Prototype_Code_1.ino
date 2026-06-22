#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); 

unsigned long startTime;
unsigned long currentTime;
int UV_index = 7;
int UV_index_prev = 7;
int time_remaining=0;
int secs=0;
int mins=0;
float percent_time_left = 100;
bool time_out=false;
bool vitD_maxxed=false;

void setup() {
  u8g2.begin();
  startTime = millis();
  time_remaining = 200/(3*UV_index);
}

void loop() {
  UV_index_prev = UV_index;
  //read UV index and store in UV_index
  currentTime = millis();
  int timeElapsed = 0;
  if(time_out){
    timeElapsed = time_remaining;
  }
  else{
    timeElapsed = currentTime-startTime;
  }
  if(UV_index!= UV_index_prev){
    percent_time_left = timeElapsed/time_remaining;
    time_remaining = percent_time_left * 200/(3*UV_index);
    percent_time_left=0;
  }
  if(timeElapsed>= 0.75*time_remaining){
    vitD_maxxed=true;
  }
  else if(timeElapsed>=time_remaining){
    time_out=true;
  }
  if(secs>=60){
    secs-=60;
    mins++;
  }
  u8g2.firstPage();
    do {
        drawScreen_3(timeElapsed/time_remaining);
    } while (u8g2.nextPage());
}

void drawScreen_3(int percent) {
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    // rect 1
    u8g2.drawFrame(0, 1, 128, 63);
    // rect 2
    u8g2.drawFrame(5, 41, 119, 18);
    // string 3
    u8g2.setFont(u8g2_font_profont15_tr);
    u8g2.drawStr(5, 18, "Time Left: ");
    // string 4
    u8g2.setFont(u8g2_font_profont22_tr);
    u8g2.drawStr(10, 49, "");
    // prg_bar
    u8g2.drawBox(6, 42, percent*177, 16);
    // string 6
    u8g2.setFont(u8g2_font_profont15_tr);
    u8g2.drawStr(6, 33, "UV Index:");
    // string 7
    u8g2.drawStr(73, 33, "X");
}