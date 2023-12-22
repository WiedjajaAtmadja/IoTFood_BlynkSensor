/*************************************************************
Device used: DHT22 on pin D7
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6TAYZNWRG"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "kvAHQyUlZPKpYZ9Ew3GALoMMGMFptWWY"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHTesp.h"
DHTesp dht;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "kelasiot";
char pass[] = "kelasiot123";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  Serial.printf("V0 Switch value: %d\n", value);
  digitalWrite(LED_BUILTIN, value);

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Request the latest state from the server
  // Blynk.syncVirtual(V0);
  }

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.printf("Temperature: %.1f °C, Humidity: %.1f \n", 
    temperature, humidity);
  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V4, humidity);
  Blynk.virtualWrite(V5, temperature);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);// turn off LED
  // Debug console
  Serial.begin(115200);
  dht.setup(D7, DHTesp::DHT22);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(2000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
