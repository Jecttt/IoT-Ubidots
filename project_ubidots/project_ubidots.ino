#include "DHT.h"
#include "UbidotsMicroESP8266.h"
#define DHTPIN 4
#define TOKEN "BBFF-pPNTEDbmv71dcd98ec3871d3e47"  //token dari ubidots
#define ssid "SA70"
#define psswd "ditya30"
DHT dht(DHTPIN, DHT11);
Ubidots client(TOKEN);
unsigned long last =0;

void setup(){
  Serial.begin(9600);
  
  dht.begin();
  
  delay(20);
  
  client.wifiConnection(ssid,psswd);
  
}

void loop(){
  if (millis()-last>1000){
    float hum = dht.readHumidity();   //tipe data float untuk menampung data kelembapan

    float temp = dht.readTemperature();  //tipe data float untuk menampung data suhu


    last=millis();

    client.add("kelembapan" ,hum);

    client.add("Temp",temp);

    client.sendAll(true);
  }
}
