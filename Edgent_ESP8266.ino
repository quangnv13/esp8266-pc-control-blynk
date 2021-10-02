// Config blynk
#define BLYNK_TEMPLATE_ID "TMPLBeq59aqe"
#define BLYNK_DEVICE_NAME "PC Power control"
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial

// Define GPIO Wemos D1 mini
#define D1 5
#define D4 2

#include "BlynkEdgent.h"

String content = "";
char character;
bool isInit = true;

BlynkTimer timer;

BLYNK_WRITE(V0)
{
  if (digitalRead(param.asInt()) == HIGH)
  {
    digitalWrite(D1, LOW);
    Blynk.virtualWrite(V5, "Pressing button power PC!!!\n");
    timer.setTimeout(1000L, []()
                     {
                       digitalWrite(D1, HIGH);
                       Blynk.virtualWrite(V5, "Power on PC completed!!!\n=====================\n");
                     });
  }
}

BLYNK_WRITE(V2)
{
  if (digitalRead(param.asInt()) == HIGH)
  {
    digitalWrite(D4, LOW);
    Blynk.virtualWrite(V5, "Pressing button reset PC!!!\n");
    timer.setTimeout(1000L, []()
                     {
                       digitalWrite(D4, HIGH);
                       Blynk.virtualWrite(V5, "Reset PC completed!!!\n=====================\n");
                     });
  }
}

void checkBlynkStatus() 
{
  if(isInit && Blynk.connected()) 
  {
    Blynk.virtualWrite(V5, "PC control setup ok!!!\n=====================\nPC control started!!!\n=====================\nPC control connected to Blynk Cloud!!!\n=====================\n");
    isInit = false;
  }
}

void setup()
{
  // Set pin mode output for D1,D4
  pinMode(D1, OUTPUT);
  pinMode(D4, OUTPUT);

  // Set default state
  digitalWrite(D1, HIGH);
  digitalWrite(D4, HIGH);

  BlynkEdgent.begin();
  timer.setInterval(1000L, checkBlynkStatus);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();
}
