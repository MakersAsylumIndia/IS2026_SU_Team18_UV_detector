#include <U8g2lib.h>


// ================= OLED =================

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);


// ================= LDR MODULE =================

#define LDR_PIN A1

int lightValue = 0;       // FIXED
int UV_index = 1;
int previousUV = 1;


// ================= TIMER =================

unsigned long startTime;
unsigned long exposureTime;



// ================= SETUP =================

void setup()
{
  u8g2.begin();

  Serial.begin(9600);


  UV_index = readLightSensor();


  if(UV_index < 1)
    UV_index = 1;


  previousUV = UV_index;


  exposureTime =
  (unsigned long)((200.0 /
  (3.0 * UV_index))*1000);


  startTime = millis();

}



// ================= LOOP =================

void loop()
{

  unsigned long currentTime = millis();


  UV_index = readLightSensor();



  if(UV_index < 1)
    UV_index = 1;



  Serial.print("Light Level: ");
  Serial.println(lightValue);



  unsigned long elapsedTime =
  currentTime - startTime;



  // Adjust timer if light changes

  if(UV_index != previousUV)
  {

    float progress =
    (float)elapsedTime /
    (float)exposureTime;


    exposureTime =
    (unsigned long)((200.0 /
    (3.0 * UV_index))*1000);


    startTime =
    currentTime -
    (unsigned long)
    (progress * exposureTime);


    previousUV = UV_index;

  }



  elapsedTime =
  currentTime - startTime;



  if(elapsedTime > exposureTime)
    elapsedTime = exposureTime;



  int percentage =
  (elapsedTime * 100) /
  exposureTime;



  if(percentage > 100)
    percentage = 100;



  u8g2.firstPage();

  do
  {

    drawDisplay(
      percentage,
      elapsedTime
    );


  }while(u8g2.nextPage());



  delay(200);

}



// ================= DISPLAY =================

void drawDisplay(
int percentage,
unsigned long elapsedTime
)
{

  char lightText[20];
  char uvText[25];
  char timeText[10];



  unsigned long remaining;


  if(elapsedTime >= exposureTime)
    remaining = 0;

  else
    remaining =
    exposureTime - elapsedTime;



  int minutes =
  remaining / 60000;


  int seconds =
  (remaining % 60000) / 1000;



  sprintf(timeText,
  "%02d:%02d",
  minutes,
  seconds);



  sprintf(lightText,
  "Light:%d",
  lightValue);



  sprintf(uvText,
  "UV:%d %s",
  UV_index,
  getUVRange(UV_index));



  // -------- OLED --------


  u8g2.setFontMode(1);



  // Title

  u8g2.setFont(
  u8g2_font_profont12_tr);


  u8g2.drawStr(
  40,
  10,
  "UV Monitor"
  );



  // Light

  u8g2.setFont(
  u8g2_font_profont12_tr);


  u8g2.drawStr(
  5,
  28,
  lightText
  );



  // UV

  u8g2.drawStr(
  72,
  28,
  uvText
  );



  // Time

  u8g2.setFont(
  u8g2_font_profont15_tr);


  u8g2.drawStr(
  5,
  45,
  "Time Left:"
  );



  u8g2.setFont(
  u8g2_font_profont22_tr);


  u8g2.drawStr(
  75,
  46,
  timeText
  );



  // Progress bar

  u8g2.drawFrame(
  5,
  53,
  118,
  8
  );


  int barWidth =
  (116 * percentage) / 100;


  u8g2.drawBox(
  6,
  54,
  barWidth,
  6
  );

}



// ================= LDR READING =================

int readLightSensor()
{

  long total = 0;


  // Average 20 samples

  for(int i=0;i<20;i++)
  {

    total += analogRead(LDR_PIN);

    delay(5);

  }



  lightValue =
  total / 20;



  // Convert light level to fake UV

  int uv =
  map(lightValue,0,1023,0,11);



  if(uv < 0)
    uv = 0;


  if(uv > 11)
    uv = 11;



  return uv;

}



// ================= UV RANGE =================

const char* getUVRange(int uv)
{

  if(uv <= 2)
    return "Low";

  else if(uv <= 5)
    return "Mod";

  else if(uv <= 7)
    return "High";

  else if(uv <= 10)
    return "VHigh";

  else
    return "Extreme";

}

