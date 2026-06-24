// ================= UV SENSOR TEST =================

// GUVA-S12SD connected to A0
#define UV_PIN A0


void setup()
{
  Serial.begin(9600);

  Serial.println("UV Sensor Test");
  Serial.println("----------------");

}


void loop()
{

  int sensorValue = readUVSensor();

  float voltage = sensorValue * (5.0 / 1023.0);

  int uvIndex = voltage * 10;


  if(uvIndex < 0)
    uvIndex = 0;

  if(uvIndex > 11)
    uvIndex = 11;



  Serial.print("Analog Value: ");
  Serial.println(sensorValue);


  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");


  Serial.print("UV Index: ");
  Serial.println(uvIndex);


  Serial.print("UV Level: ");
  Serial.println(getUVRange(uvIndex));


  Serial.println("----------------");


  delay(1000);

}



// ================= SENSOR READING =================
// Average 20 readings

int readUVSensor()
{

  long total = 0;


  for(int i = 0; i < 20; i++)
  {

    total += analogRead(UV_PIN);

    delay(5);

  }


  return total / 20;

}



// ================= UV RANGE =================

const char* getUVRange(int uv)
{

  if(uv <= 2)
    return "Low";


  else if(uv <= 5)
    return "Moderate";


  else if(uv <= 7)
    return "High";


  else if(uv <= 10)
    return "Very High";


  else
    return "Extreme";

}
