/**
 * @file rc_robot_controller.ino
 * @author krkrkrrn (@krkrkrkrrn)
 * @brief 
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// https://ideal-reality.com/computer/arduino/esp32-http-server/

#define AIN1 21
#define AIN2 19
#define BIN1 4
#define BIN2 18

#include <WiFi.h>
#include <WebServer.h>
#include "credential.hpp"

WebServer server(80);
String target = "Initial String"; // この変数をPOSTメソッドで書き換える
String forward_text = "Forward...";
String coast_text = "Coast...";

void setup_actuator() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
}

void forward() {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    Serial.println("forward...");
}

void coast() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    Serial.println("coast...");
}

void setup() {
  // シリアルコンソールのセットアップ
  Serial.begin(115200);
  delay(10);
  Serial.println();

  // SSID・password確認
  Serial.print("-- SSID --");
  Serial.print(ssid);
  Serial.print("-- Password --");
  Serial.print(password);

  // 駆動系の初期化
  setup_actuator();
  
  // WiFiに接続
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // アクセスされた際に行う関数を登録する
  server.on("/target", HTTP_ANY, [](){
    if (server.method() == HTTP_POST) { // POSTメソッドでアクセスされた場合
      target = server.arg("plain"); // server.arg("plain")でリクエストボディが取れる。targetに格納
    }
    server.send(200, "text/plain", target); // 値をクライアントに返す
  });

  // 前進する
  server.on("/forward", HTTP_ANY, [](){
    if (server.method() == HTTP_POST) { // POSTメソッドでアクセスされた場合
      target = server.arg("plain"); // server.arg("plain")でリクエストボディが取れる。targetに格納
    }
    forward();
    server.send(200, "text/plain", forward_text); // 値をクライアントに返す
  });

  // 空転する
  server.on("/coast", HTTP_ANY, [](){
    if (server.method() == HTTP_POST) { // POSTメソッドでアクセスされた場合
      target = server.arg("plain"); // server.arg("plain")でリクエストボディが取れる。targetに格納
    }
    coast();
    server.send(200, "text/plain", coast_text); // 値をクライアントに返す
  });

  // 登録されてないパスにアクセスがあった場合
  server.onNotFound([](){
    server.send(404, "text/plain", "Not Found."); // 404を返す
  });

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}