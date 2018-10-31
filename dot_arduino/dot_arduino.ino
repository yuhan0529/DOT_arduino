#include <LiquidCrystal_I2C.h>
#include <Servo.h> //서보관련 라이브러리를 사용하기 위해
#include <SoftwareSerial.h>
#include <Wire.h>
#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 
LiquidCrystal_I2C lcd(0x27, 16, 2);
int sensorPin=1;//기울기
int speed;//dc 모터스피드
//dc모터
int motorPin = 5; //왼쪽
int motorPin2 = 11; //오른쪽
int motorA1 = 6; //전진
int motorA2 = 7; //후진
int motorB1 = 13; //전진
int motorB2 = 12; //후진

Servo myservo;  // 서보 변수 선언
const int servoPin = A0; // 서보 핀  
int cnt=0; //기울기 카운트값
int BuzzerPin=8;//버저
int tempo = 200; // duration 옵션 값 설정
int notes[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C };
SoftwareSerial btSerial(2,3);//블루투스

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin); //서보로 0핀 사용하겠다고 설정 
  btSerial.begin(9600);//블루투스 시작
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  
  while(!Serial);
  Serial.println("fine");
  
  //lcd 함수
  lcd.init();
  lcd.backlight(); // backlight를 On 시킵니다.
  lcd.setCursor(3,0);
  lcd.print("Team. DOT!"); // 화면에 Hello, world!를 출력합니다.
  lcd.setCursor(1,1);
  lcd.print("Battle of Cars");
  
  pinMode(BuzzerPin,OUTPUT);//버저 = 출력
  myservo.write(0);//초기 0도 설정 서보모터
}

void loop() {
           
  
  if(btSerial.available())//블루투스
  {
    char bt[2];
    bt[0]=btSerial.read();
    bt[1]=btSerial.read();
    if(bt[1] == 'n'){
      myservo.write(90);    //서보     
  }
  else if(bt[1] == 'f'){
  myservo.write(0);//서보        
    }
    
    if(bt[0] == 'w') {//전진
     digitalWrite(motorA1, HIGH);
     digitalWrite(motorA2, LOW);
     digitalWrite(motorB1, HIGH);
     digitalWrite(motorB2, LOW);
     analogWrite(motorPin,255); 
     analogWrite(motorPin2,255);
    }
    delay(100); 
    if(bt[0] == 'x'){//후진
      digitalWrite(motorA1, LOW);
     digitalWrite(motorA2, HIGH);
     digitalWrite(motorB1, LOW);
     digitalWrite(motorB2, HIGH);
     analogWrite(motorPin,255);
     analogWrite(motorPin2,255); 
    }
    delay(100); 
     if(bt[0] == 's'){//멈춤
     digitalWrite(motorA1, LOW);
     digitalWrite(motorA2, LOW);
     digitalWrite(motorB1, LOW);
     digitalWrite(motorB2, LOW);
     analogWrite(motorPin,0);
     analogWrite(motorPin2,0); 
    }
    delay(100);   
    if(bt[0]=='q'){//전진 좌
     digitalWrite(motorA1, HIGH);
     digitalWrite(motorA2, LOW);
     digitalWrite(motorB1, HIGH);
     digitalWrite(motorB2, LOW);
     analogWrite(motorPin,100);
     analogWrite(motorPin2,255); 
    }
    delay(100);
    if(bt[0]=='e'){//전진 우
     digitalWrite(motorA1, HIGH);
     digitalWrite(motorA2, LOW);
     digitalWrite(motorB1, HIGH);
     digitalWrite(motorB2, LOW);
     analogWrite(motorPin,255);
     analogWrite(motorPin2,160); 
    }
    delay(100);
    
    if(bt[0]=='z'){//후진 좌
     digitalWrite(motorA1, LOW);
     digitalWrite(motorA2, HIGH);
     digitalWrite(motorB1, LOW);
     digitalWrite(motorB2, HIGH);
     analogWrite(motorPin,160);
     analogWrite(motorPin2,255); 
    }
    delay(100);
    if(bt[0]=='c'){//후진 우
     digitalWrite(motorA1, LOW);
     digitalWrite(motorA2, HIGH);
     digitalWrite(motorB1, LOW);
     digitalWrite(motorB2, HIGH);
     analogWrite(motorPin,255);
     analogWrite(motorPin2,160); 
    }
    delay(100);
  }
  
   
     
int reading=analogRead(sensorPin);//기울기
  Serial.println(reading);
  if(reading>900){
    cnt++;
  delay(500);
  }
  if(cnt>5){   //기울기 횟수카운트
     digitalWrite(motorA1, LOW);
     digitalWrite(motorA2, LOW);
     digitalWrite(motorB1, LOW);
     digitalWrite(motorB2, LOW);
     analogWrite(motorPin,0);
     analogWrite(motorPin2,0); 
    btSerial.println("1");
    for(int i=0;i<12;i++){
      tone(BuzzerPin,notes[i],tempo);
      delay(300);
    }
    delay(100);//멜로디 중간에 짧게 멈춤
    for(int i=12;i<25;i++){
      tone(BuzzerPin,notes[i],tempo);
      delay(300);
    }
    cnt=0;
    }
}
