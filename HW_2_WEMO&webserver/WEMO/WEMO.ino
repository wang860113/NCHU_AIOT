//wi-fi init
#include "ESP8266WiFi.h"
#include "ESP8266WiFiMulti.h"
ESP8266WiFiMulti WiFiMulti;
#define wifi_id "Lab731_2.4G"
#define wifi_pass "731731731"
//DHT11 init
#include "DHT.h"
#define dhtPin 13      //讀取DHT11 Data
#define dhtType DHT11 //選用DHT11   

DHT dht(dhtPin, dhtType); // Initialize DHT sensor

void setup() {
  Serial.begin(115200);//設定鮑率9600
  dht.begin();//啟動DHT
  pinMode(A0,INPUT);//光敏數值

  WiFiMulti.addAP(wifi_id, wifi_pass);
  while(WiFiMulti.run() != WL_CONNECTED){
    Serial.println("wait..");
    delay(500);
    }
}

void loop() {
  float h = dht.readHumidity();//讀取濕度
  float t = dht.readTemperature();//讀取攝氏溫度
  float f = dht.readTemperature(true);//讀取華氏溫度

  int l = analogRead(A0);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("無法從DHT傳感器讀取！");
    return;
  }
  Serial.print("濕度: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("攝氏溫度: ");
  Serial.print(t);
  Serial.print("*C\t");
  Serial.print("光敏數值:");
  Serial.println(l);

  const uint16_t port = 80;
  const char *host = "192.168.31.39";
  
  WiFiClient client; // 建立客戶端
  //檢查是否與WiFi連線
  if(!client.connect(host, port)){
      Serial.println("connect failed");
      Serial.println("wait 3 sec...");
      delay(3000);
      return;      
  }
//  //連線至伺服端後 傳送資料至getData.php
  String url ="/aiot/addData.php?t="+String(t)+"&h="+String(h)+"&l="+String(l);
  client.print(String("GET ")+url+" HTTP/1.1\r\n"+
  "Host: "+host+"\r\n"+
  "Connection: close\r\n\r\n");

  Serial.println("connect closed");
  client.stop();
  delay(5000);//延時5秒
  
}
