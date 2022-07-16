#define BLYNK_TEMPLATE_ID "TMPLxgGDAreU"
#define BLYNK_DEVICE_NAME "PreIoT8th"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG

#include "BlynkEdgent.h" 

#define VPin_LightState V0
#define VPin_LightValue V1
#define VPin_AutoState V2

#define led_Light 12
#define led_Connect 14
#define AutoStatus 27
#define LDR 34

int LightState = 0;
int AutoState = 0;
int LightValue;

BLYNK_WRITE(Vpin_LightState){
  LightState = param.asInt();
}
BLYNK_WRITE(VPin_AutoState){
  AutoState = param.asInt();
  digitalWrite(AutoStatus,Auto);
}

void setup()
{
  Serial.begin(115200);
  pinMode(led_Light,OUTPUT);
  pinMode(led_Connect,OUTPUT);
  pinMode(AutoStatus,OUTPUT);
  pinMode(LDR,INPUT);

  delay(100);
  BlynkEdgent.begin();
}

void loop()
{
  if(Blynk.connected())
    digitalWrite(led_Connect,1);
  else
    digitalWrite(led_Connect,0);
  
  LightValue = analogRead(LDR);
  Serial.print("Light Value = ");
  Serial.println(LightValue);
  Blynk.virtualWrite(VPin_Lightstate,LightValue);
  
  if(AutoState){
    if(Val<=300){
      digitalWrite(led_Light,1);
    }else{
      digitalWrite(led_Light,0);
    }
  }
  else if(!AutoState){
    digitalWrite(led_Light,LightState);
  }
  
  BlynkEdgent.run();
}
