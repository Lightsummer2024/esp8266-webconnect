#include <SocketIOclient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "A2024html.h"
#include "ws2812uu.h"
#include <FS.h>
#define NameSER "IOT control 8266"
#define pskD "82661024"


FSInfo csd;
ESP8266WebServer server(80);
int i, sx, SETon;
int table[7] = { 12, 13, 14, 16, 5, 4, 2 };


void setup() {
  Serial.begin(9600);
  printb("");

  WiFi.mode(WIFI_AP_STA);

  WiFi.softAP(NameSER, pskD);
  server.begin();

  if (outap()) {
    printb("Server open:192.168.5.1");
    if (SPIFFS.begin()) {
      printb("FS open");
    }
  }


 

  //==============执行联网

  connectwifi();
  server.onNotFound(UHTTP);  //设置访问配置
}



//===================日常循环==
void loop() {
  i++;
  server.handleClient();  //监听服务
  if (i == 80000) {
    i = 0;
    APconnect();
  }

  if (WiFi.status() == WL_CONNECTED && SETon == 0) {
    SETon = 1;
    sx = 1;
    GTWIFI();
    printa("您已连接路由器,IP地址:");
    printb(WiFi.localIP().toString());
  }

  onelist(5);
}
//============判断连接状态========
void APconfig() {
  if (WiFi.softAPgetStationNum() > 0) {
    printa("当前热点连接设备数:");
    printb((String)WiFi.softAPgetStationNum());
  }
}
//判断 AP 连接状态=
void APconnect() {
  if (WiFi.softAPgetStationNum() > 0) {
    APconfig();
  }

  else if (WiFi.softAPgetStationNum() == 0) {
    printb("当前热点无设备连接!");
  }
}
//===============outap
bool outap() {
  printa("您的热点ID:");
  printb(NameSER);
  printa("您的热点密码:");
  printb(pskD);
  printa("您的内网服务器IP:");
  printb(WiFi.softAPIP().toString());
  printa("当前热点连接设备数:");
  printb((String)WiFi.softAPgetStationNum());
  return true;
}
//===================读取fs配网:如果有
void connectwifi() {
  String HH, PSKw;
  if (SPIFFS.exists("SSID.txt") && SPIFFS.exists("PSK.txt")) {

    File file = SPIFFS.open("SSID.txt", "r");
    while (file.available()) { HH += (char)file.read(); }
    file.close();
    File filea = SPIFFS.open("PSK.txt", "r");
    while (filea.available()) { PSKw += (char)filea.read(); }
    filea.close();
    printb("Read ssid:" + HH);
    printb("Read psk:" + PSKw);
    WiFi.begin(HH, PSKw);
    delay(5000);
    if (WiFi.status() != WL_CONNECTED) { printb("自动连接超时!请耐心等待!或访问192.168.5.1配置WiFi网络!"); }
  }
}

//=============setwifi
void setwifi() {
  if (sx == 0) {
    server.send(200, "text/html", serwifihead);
    String ssid = server.arg("ssid");
    String pskb = server.arg("psk");
    WiFi.begin(ssid, pskb);
    delay(5000);
    if (WiFi.status() != WL_CONNECTED) {
      printb("获取设置如下连接超时!");
      printb("Server get ssid:" + ssid);
      printb("Server get psk:" + pskb);
    }
  }
}

//保存网络信息====================
void GTWIFI() {
  String ssida = WiFi.SSID();
  String paska = WiFi.psk();
  //========连接成功才 保存
  if (WiFi.status() == WL_CONNECTED) {
    File sdd = SPIFFS.open("SSID.txt", "w");
    sdd.print(ssida);
    printb("保存SSID:" + ssida);
    sdd.close();
    File pska = SPIFFS.open("PSK.txt", "w");
    pska.print(paska);
    printb("保存密码:" + paska);
    pska.close();
  }
}

//======http
void UHTTP() {
  String ttp = server.uri();
  //==============没联网 配网功能========
  //如果WiFi未 连接且请求为 / 发出 运行配网函数
  if (WiFi.status() != WL_CONNECTED && ttp.endsWith("/")) {
    setwifi();  //设置访问配置
  }
  //======================必须联网才能用功能=====
  //如果网络已连接执行操作
  else if (WiFi.status() == WL_CONNECTED) {
    if (ttp.endsWith("/")) {
      server.send(200, "text/html", indexhtml);
    }
  }
  //===============离线在线都可用功能
  //判断查询目录文件
  if (ttp.endsWith("/CDIR")) {
    httpok();
    Dir dira = SPIFFS.openDir("/");
    printb("文件目录:");
    while (dira.next()) { printb(dira.fileName()); }
  }
  //清除fs内容
  if (ttp.endsWith("/REFS")) {
    httpok();
    printb("清除FLASH");
    SPIFFS.format();
  }
  //查询内存状态
  if (ttp.endsWith("/CSD")) {
    httpok();
    SPIFFS.info(csd);
    printa("可用空间(Bytes):");
    printa((String)csd.totalBytes);
    printa("已用空间(Bytes):");
    printa((String)csd.usedBytes);
  }
  //===IO口 控制
  if (ttp.endsWith("/IO")) {
    httpok();
    String DP;
    String IOPIN = server.arg("iopin");
    String IONUM = server.arg("ionum");
    int uo;
    for (uo; uo < 7; uo++) {

      if (IOPIN.toInt() == table[uo]) {
        printb("设置IO:" + IOPIN);
        httpok();
        pinMode(IOPIN.toInt(), OUTPUT);
        if (IONUM.toInt() == 1) {

          digitalWrite(IOPIN.toInt(), HIGH);
        } else {
          digitalWrite(IOPIN.toInt(), LOW);
        }

        printb((String)digitalRead(IOPIN.toInt()));
        break;  //跳出循环体
      }
    }
  }
}
//======设置服务器地址
void zjmod() {
  if (WiFi.status() == WL_CONNECTED) {
    server.stop();
    delay(2000);
    server.begin();
  }
}


//===========覆写print
void printa(String wenben) {
  Serial.print(wenben);
}
//==========覆写println
void printb(String wenbenb) {
  Serial.println(wenbenb);
}
//=======请求处理
void httpok() {
  server.send(200, "text/html", returnhtml);
}