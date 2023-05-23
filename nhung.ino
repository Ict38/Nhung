#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define ldr 34
#define led1 33
#define led2 32

#define ir1 5
#define ir2 18

#define aPin 13  //
#define bPin 14  //      _____
#define cPin 4   //     |  A  |
#define dPin 15  //   F |_____| B
#define ePin 27  //     |  G  |
#define fPin 12  //   E |_____| C
#define gPin 2   //         D    

#define d1Pin 23  // Chân chung cho số thứ 1 led 7 đoạn 4 số (Nối qua chân Collector của transitor c1815)
#define d2Pin 22  // Chân chung cho số thứ 2 led 7 đoạn 4 số  (Nối qua chân Collector của transitor c1815)

#define BLYNK_TEMPLATE_ID "TMPL6jcMxWXj6";
#define BLYNK_TEMPLATE_NAME "Nhung";
#define BLYNK_AUTH_TOKEN "45M-fBcfL1dXZqdE2rkOI6eUNCWQiSbE";

char auth[] = "45M-fBcfL1dXZqdE2rkOI6eUNCWQiSbE";
char ssid[] = "HC";
char pass[] = "1234567899";

int led1_time = 0;
int led2_time = 0;
int van_toc = 0;

int On = 1, Off = 0;
int digitOn = 0, digitOff = 1;

int khoang_cach = 200;

void setup() {
  Serial.begin(115200);

  // Khai báo đầu ra cho led 7 đoạn
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(fPin, OUTPUT);
  pinMode(gPin, OUTPUT);


  pinMode(d1Pin, OUTPUT);
  pinMode(d2Pin, OUTPUT);
  
  pinMode(ldr, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
  int light = analogRead(ldr);
  int ir1_value = digitalRead(ir1);
  int ir2_value = digitalRead(ir2);
  Blynk.virtualWrite(V0, light);

  int currentTime = millis();
  int vantocFlag = 0;

    if(ir1_value == 0){
      led1_time = millis();
      if(light >= 1600){
        digitalWrite(led1, HIGH);
        Blynk.virtualWrite(V1, 1);
      }
    } 

    if(ir2_value == 0){
      led2_time = millis();
      tinhVanToc();
      if(light >= 1600){
        digitalWrite(led2, HIGH);
        Blynk.virtualWrite(V2, 1);
      }
    }
  
  if(currentTime - led1_time >= 5000){
    digitalWrite(led1, LOW);
    Blynk.virtualWrite(V1, 0);
  }
  if(currentTime - led2_time >= 5000){
    digitalWrite(led2, LOW);
    Blynk.virtualWrite(V2, 0);
  }
  
}

void tinhVanToc(){
  Serial.println(((led2_time - led1_time) / 100.0));
  van_toc =  round(khoang_cach / ((led2_time - led1_time) / 100.0));
  if(van_toc >= 99) van_toc = 99;
  Blynk.virtualWrite(V3, van_toc);
  int startTime = millis();
  while( millis() - startTime <= 8500){
    showNumber((van_toc ) % 10);
    digitalWrite(d1Pin, Off);
    delay(4);
    digitalWrite(d1Pin, On);


    showNumber((van_toc / 10) % 10);
    digitalWrite(d2Pin, Off);
    delay(4);
    digitalWrite(d2Pin, On);
  }
  digitalWrite(d1Pin, Off);
  digitalWrite(d2Pin, Off);
  Blynk.virtualWrite(V3, 0);
}
void showNumber(int x) {
  switch (x) {
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
    default: zero(); break;
  }
}

void one() {
  digitalWrite(aPin, Off);  //
  digitalWrite(bPin, On);   //      |
  digitalWrite(cPin, On);   //      |
  digitalWrite(dPin, Off);  //      |
  digitalWrite(ePin, Off);  //      |
  digitalWrite(fPin, Off);
  digitalWrite(gPin, Off);
}


void two() {
  digitalWrite(aPin, On);   //  ____
  digitalWrite(bPin, On);   //      |
  digitalWrite(cPin, Off);  //  ____|
  digitalWrite(dPin, On);   // |
  digitalWrite(ePin, On);   // |____
  digitalWrite(fPin, Off);
  digitalWrite(gPin, On);
}


void three() {
  digitalWrite(aPin, On);   //  ____
  digitalWrite(bPin, On);   //      |
  digitalWrite(cPin, On);   //  ____|
  digitalWrite(dPin, On);   //      |
  digitalWrite(ePin, Off);  //  ____|
  digitalWrite(fPin, Off);
  digitalWrite(gPin, On);
}


void four() {
  digitalWrite(aPin, Off);  //
  digitalWrite(bPin, On);   // |    |
  digitalWrite(cPin, On);   // |____|
  digitalWrite(dPin, Off);  //      |
  digitalWrite(ePin, Off);  //      |
  digitalWrite(fPin, On);
  digitalWrite(gPin, On);
}


void five() {
  digitalWrite(aPin, On);   //  ____
  digitalWrite(bPin, Off);  // |
  digitalWrite(cPin, On);   // |____
  digitalWrite(dPin, On);   //      |
  digitalWrite(ePin, Off);  //  ____|
  digitalWrite(fPin, On);
  digitalWrite(gPin, On);
}


void six() {
  digitalWrite(aPin, On);   //  ____
  digitalWrite(bPin, Off);  // |
  digitalWrite(cPin, On);   // |____
  digitalWrite(dPin, On);   // |    |
  digitalWrite(ePin, On);   // |____|
  digitalWrite(fPin, On);
  digitalWrite(gPin, On);
}


void seven() {
  digitalWrite(aPin, On);   //  ____
  digitalWrite(bPin, On);   //      |
  digitalWrite(cPin, On);   //      |
  digitalWrite(dPin, Off);  //      |
  digitalWrite(ePin, Off);  //      |
  digitalWrite(fPin, Off);
  digitalWrite(gPin, Off);
}


void eight() {
  digitalWrite(aPin, On);  //  ____
  digitalWrite(bPin, On);  // |    |
  digitalWrite(cPin, On);  // |____|
  digitalWrite(dPin, On);  // |    |
  digitalWrite(ePin, On);  // |____|
  digitalWrite(fPin, On);
  digitalWrite(gPin, On);
}


void nine() {
  digitalWrite(aPin, On);   //  ____
  digitalWrite(bPin, On);   // |    |
  digitalWrite(cPin, On);   // |____|
  digitalWrite(dPin, On);   //      |
  digitalWrite(ePin, Off);  //  ____|
  digitalWrite(fPin, On);
  digitalWrite(gPin, On);
}


void zero() {
  digitalWrite(aPin, On);  //  ____
  digitalWrite(bPin, On);  // |    |
  digitalWrite(cPin, On);  // |    |
  digitalWrite(dPin, On);  // |    |
  digitalWrite(ePin, On);  // |____|
  digitalWrite(fPin, On);
  digitalWrite(gPin, Off);
}
