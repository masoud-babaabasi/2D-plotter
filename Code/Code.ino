#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <SPI.h>
#include <SD.h>
/* 
 *  Author: Masoud Babaabasi 
 *  Email: masoud.tafresh@gmail.com
 *  Version 1 created 28/8/2017
 *  For the perpose of this project the origanal library of Arduino PINS "pins_arduino.h" 
 *  for mega2560 is changed 
 *  "C:\Program Files\arduino-1.8.3\hardware\arduino\avr\variants\mega\pins_arduino.h"
 *  The changes are{
 *                            changing PG5 to PH2 for digital pin NO4 //lines 169 and 244
 *                            changing PG2 to PE6 for digital pin NO 39 // line 204 and 279
 *                            changing PG1 to PE2 for digital pin NO 40//line 205 and 
 *                            }
  */
/************************************************************************************************************************************/
/************************************************************************************************************************************/
/*
 * pin assignment
 */
#define SERVO_PIN 11
#define LCD_BACK A14
#define BUZ A15

#define Y_AX A0
#define X_AX A1
#define JOY_SW A3

#define ST1_1 43
#define ST1_2 42
#define ST1_3 45
#define ST1_4 44
#define ST1_E 46

#define ST2_1 3
#define ST2_2 39
#define ST2_3 5
#define ST2_4 2
#define ST2_E 40
#define stepsPerRevolution 200

#define MS1 25  // Micro switch NO1
#define MS2 26  // Micro switch NO2
#define MS3 27  // Micro switch NO3
#define MS4 28  // Micro switch NO4

#define chipSelect 10 // chip select of SD card

#define Rd 13  //reduis of the pully
#define UP 180
#define DOWN 90

#define LCD_ON digitalWrite(LCD_BACK,HIGH)
#define LCD_OFF digitalWrite(LCD_BACK,LOW)
#define BUZ_ON digitalWrite(BUZ,HIGH)
#define BUZ_OFF digitalWrite(BUZ,LOW)
#define ST1_EN digitalWrite(ST1_E,HIGH)
#define ST2_EN digitalWrite(ST2_E,HIGH)
#define ST1_DIS digitalWrite(ST1_E,LOW)
#define ST2_DIS digitalWrite(ST2_E,LOW)
#define HomeX -200
#define HomeY -130
#define xMax 200
#define xMin -200
#define yMax 130
#define yMin -130
/************************************************************************************************************************************/
/************************************************************************************************************************************/
LiquidCrystal lcd(A8, A9, A10, A11, A12, A13);
/************************************************************************************************************************************/
/************************************************************************************************************************************/
const byte ROWS = 3; //three rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
};
byte rowPins[ROWS] = {7,8,9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 6,53}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/************************************************************************************************************************************/
/************************************************************************************************************************************/
Servo pen;
Stepper stepper1(stepsPerRevolution, ST1_1, ST1_2, ST1_3, ST1_4);
Stepper stepper2(stepsPerRevolution, ST2_1, ST2_2, ST2_3, ST2_4);
/************************************************************************************************************************************/
/************************************************************************************************************************************/
float preX,preY,preZ;
int sp = 120;
File shape,back;
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void gotoXY(float inX,float inY);
void goHome();
void drawSnail(float centerX, float centerY);
void drawRose(float centerX, float centerY, float R);
void manualDraw();
void drawStar(float centerX, float centerY, float R);
void drawFiveangle(float centerX, float centerY, float A);
void drawStar2(float centerX, float centerY, float R);
void drawCircle(float centerX, float centerY, float R);
void spirograph(float r,float R,float w,bool sign);
void spirograph2();
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void setup() {
 pen.attach(SERVO_PIN); 
 pen.write(UP);
 Serial.begin(115200);
 lcd.begin(16, 2);
pinMode(LCD_BACK,OUTPUT);
pinMode(BUZ,OUTPUT);
pinMode(ST2_E,OUTPUT);
pinMode(ST2_E,OUTPUT);
ST1_EN;
ST2_EN;
preX = HomeX;
preY = HomeY;
preZ = 1;
lcd.print("setup OK!");
LCD_ON;
delay(600);
lcd.clear();
/**********************************/
/**********************************/
stepper1.setSpeed(sp);
stepper2.setSpeed(sp);
//drawSnail(0,0);
//drawRose(0,0,80);
//drawStar(0,0,80);
//drawFiveangle(0,0,94);
//drawStar2(0,0,80);
//spirograph(70,20,10,0);
//spirograph2();
//drawCircle(0,0,100);
/*for(int i=5;i<=80;i+=15) {
  drawCircle(0,0,i);
  delay(600);
}*/
/*for(int i=5;i<=85;i+=10) {
  drawRose(0,0,i);
  delay(600);
}*/
  //draw Square
  /*gotoXY(80,80);
  gotoXY(80,-80);
  gotoXY(-80,-80);
  gotoXY(-80,80);
  gotoXY(80,80);*/
  //SD card read formated data
   /*if (!SD.begin(chipSelect)) lcd.print(F("Card failed, or not present"));
   shape = SD.open("masoud.txt", FILE_READ);
   back = SD.open("backup.txt",FILE_WRITE);
   shape.setTimeout(1);
   if(shape){
    String str,stX,stY;
    float x,y;
    while(shape.position() != shape.size()){
    str =shape.readStringUntil(',');
    if( str.startsWith(F("x=-")))  {
      stX = str.substring(3);
      x = stX.toFloat();
      x= -x;
    }
   else if( str.startsWith(F("x=")))  {
      stX = str.substring(2);
      x = stX.toFloat();
    }
      str =shape.readStringUntil('\n');
    if( str.startsWith(F("y=-")))  {
      stY = str.substring(3);
      y = stY.toFloat();
      y= -y;
    }
   else if( str.startsWith(F("y=")))  {
      stY = str.substring(2);
      y = stY.toFloat();
    }
    gotoXY(x,y);
    //back.print("x=");
    //back.print(x);
    //back.print(",y=");
   // back.println(y);
   // for(int i=0;i<5;i++) str =shape.readStringUntil('\n');
    }

   }
   shape.close();
   back.close();
   lcd.print("done");*/
   
}
void loop() {
  int i;
  String rec,stX,stY,stZ,str;
  float x,y,z;
 char key = keypad.getKey();
 if(key){
  lcd.clear();
  lcd.print(key);
  switch(key){
    case '1': lcd.print("Draw a star");
                  drawStar2(0,0,80);
                  lcd.clear();
                  break;
   case '2': lcd.print("Draw a pentagonangle");
                  drawFiveangle(0,0,94);
                  lcd.clear();
                  break;
   case '3': lcd.print("Draw a Rose");
                  drawRose(0,0,80);
                  lcd.clear();
                  break;
   case '4': lcd.print("Draw a Spirograph");
                  spirograph(70,20,10,0);
                  lcd.clear();
                  break;
   case '5': lcd.print("Draw a Spirograph");
                  spirograph2();
                  lcd.clear();
                  break;
   case '6': lcd.print("Draw a Snail");
                  drawSnail(0,0);
                  lcd.clear();
                  break;
   case '7': lcd.print("Draw masoud");
                    if (!SD.begin(chipSelect)) lcd.print(F("Card failed, or not present"));
                       shape = SD.open("part.txt", FILE_READ);
                       shape.setTimeout(1);
                       if(shape){

                        while(shape.position() != shape.size()){
                        str =shape.readStringUntil(',');
                        if( str.startsWith(F("x=-")))  {
                          stX = str.substring(3);
                          x = stX.toFloat();
                          x= -x;
                        }
                       else if( str.startsWith(F("x=")))  {
                          stX = str.substring(2);
                          x = stX.toFloat();
                        }
                          str =shape.readStringUntil(',');
                        if( str.startsWith(F("y=-")))  {
                          stY = str.substring(3);
                          y = stY.toFloat();
                          y= -y;
                        }
                       else if( str.startsWith(F("y=")))  {
                          stY = str.substring(2);
                          y = stY.toFloat();
                        }
                        str =shape.readStringUntil('\n');
                        if( str.startsWith(F("z=-")))  {
                          stZ = str.substring(3);
                          z = stZ.toFloat();
                          z= -z;
                        }
                       else if( str.startsWith(F("z=")))  {
                          stZ = str.substring(2);
                          z = stZ.toFloat();
                        }
                        if(z>0 && preZ<0) {
                          pen.write(UP);
                          delay(500);
                        }
                        else if(z<0 && preZ>0) {
                          pen.write(DOWN);
                          delay(500);
                        }
                        gotoXY(x,y);
                        preZ = z;
                       // for(int j=0;j<30;j++) str =shape.readStringUntil('\n');
                        }
                       }
                       shape.close();
                       lcd.print("done");
                       goHome();
                  break;
  
  }
 }
 if(Serial.available()){
  rec =Serial.readStringUntil(',');
    if( rec.startsWith(F("x=")))  {
      stX = rec.substring(2);
      x = stX.toFloat();
    }
      rec =Serial.readStringUntil('\n');
    if( rec.startsWith(F("y=")))  {
      stY = rec.substring(2);
      y = stY.toFloat();
    }
    gotoXY(x,y);
    
 }

}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void gotoXY(float inX,float inY){
    int N1,N2,n1,n2;
    int Np1,Np2;
  float coef;
    float dx,dy,X,Y;
  uint32_t t,lastT;
  uint32_t interval1,interval2;
  Np1 = Np2 = 0;
  if(inX > xMax) X = xMax;
  else if(inX < xMin) X = xMin;
  else X = inX;
    if(inY > yMax) Y = yMax;
  else if(inY < yMin) Y = yMin;
  else Y = inY;
  dx = X - preX;
  dy = Y - preY;

  coef =  200 / ( 2.0  * PI * Rd);//coef = SperR / ( 2.0  * PI * reduis);
 
  N1 = ( coef * dx ) + ( coef * dy);
  N2 = ( coef * dx ) + ( -coef * dy);

  n1 = abs(N1);
  n2= abs(N2);
  if( n1 == n2 ){
    stepper1.setSpeed(sp/sqrt(2));
    stepper2.setSpeed(sp/sqrt(2));
    for(int i = 0;i<n1;i++){
    stepper1.step(N1/n1);
    stepper2.step(N2/n2);
    }
  }
  else{
    stepper1.setSpeed(sp);
    stepper2.setSpeed(sp);
  t = (max(n1,n2) * 60.0) / ( 120 * 200 )  * 1000000.0; // time in microsec

  if( N1 == 0 ) interval1 = 0;
  else interval1 = t / abs(N1);
  if( N2 == 0 ) interval2 = 0;
  else interval2 = t / abs(N2);

  lastT = micros();

  while(1){
      if( micros() - lastT > ( (Np1+1) * interval1 ) ) 
      {
        if(N1 && Np1 < abs(N1)){
                    stepper1.step(N1/n1);
                    Np1++; 

        }
      }
      if( micros() - lastT > ( (Np2+1) * interval2 ) ) 
      {
        if(N2 && Np2 < abs(N2)){
                    stepper2.step(N2/n2);
                    Np2++; 
        }
      }
      if( Np1 == abs(N1) && Np2 == abs(N2) ) break;
  }
  }
  dx =  (1 / (2 * coef)) * ( N1 + N2);
  dy =  (1 / (2 * coef)) * ( N1 - N2); 
  preX += dx;
  preY += dy;

  Serial.println("ready");
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void goHome(){
  pen.write(UP);
  gotoXY(HomeX,HomeY);
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void drawSnail(float centerX, float centerY){
  float x,y,theta,r;
  gotoXY(centerX,centerY);
  pen.write(DOWN);
  for( theta = 0 ; theta <= ( 8 * PI ) ; theta+=0.001){
    r = 20 / ( 2 * PI ) * theta;
    x = centerX + r * cos(theta);
    y = centerY + r * sin(theta);
    gotoXY(x,y);
  }
  goHome();
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void drawRose(float centerX, float centerY, float R){
  float x,y,theta,r;
  gotoXY(centerX,centerY);
  for( theta = 0 ; theta <= ( 2 * PI ) ; theta+=0.008){
    r = R * sin(3*theta);
    x = centerX + r * cos(theta);
    y = centerY + r * sin(theta);
    gotoXY(x,y);
  }
  goHome();
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void manualDraw(){
int val1,val2;
int DELAY = 180;
int SPEED = 180;
val1 = analogRead(Y_AX); 
val2 = analogRead(X_AX); 
if( val1<520 && val1 > 500 ) val1 = 512;
if( val2<520 && val2 > 500 ) val2 = 512;
int MAX = (2 * PI *  Rd * SPEED * DELAY)/60000; //rd = 13  , speed = 150 , delay = 100ms
val1 = map(val1, 0, 1023, MAX, -MAX);  //formula for maping between timiming intervals {max = (2*pi*Rd*speed*interval)/ 60000}
val2 = map(val2, 0, 1023, -MAX, MAX);  
Serial.print("val1 = ");
Serial.println(val1);
Serial.print("val2 = ");
Serial.println(val2);
val1 += preX;
val2 += preY;
if(digitalRead(JOY_SW)) pen.write(UP);
else pen.write(DOWN);
gotoXY(val1,val2);
lcd.clear();
lcd.print("X = ");
lcd.print(val1);
lcd.print(",Y = ");
lcd.print(val2);
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void drawStar(float centerX, float centerY, float R){
  float x,y;
  gotoXY(centerX,centerY+R);
  pen.write(DOWN);
  gotoXY(centerX+( R * sin(PI * 36 /180)),centerY-( R * cos(PI * 36 /180)));
  gotoXY(centerX- ( R * cos(PI * 18 /180)),centerY+( R * sin(PI * 18 /180)));
  gotoXY(centerX+( R * cos(PI * 18 /180)),centerY+(R * sin(PI * 18 /180)));
  gotoXY(centerX-( R * sin(PI * 36 /180)),centerY-( R * cos(PI * 36 /180)));
  gotoXY(centerX,centerY+R);
  goHome();
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void drawFiveangle(float centerX, float centerY, float A){
  float x,y;
  float R = A / ( 2 * sin( PI * 36 / 180));
  gotoXY(centerX,centerY+R);
  pen.write(DOWN);
  delay(300);
  gotoXY(centerX+( R * cos(PI * 18 /180)),centerY+(R * sin(PI * 18 /180)));
  delay(300);
  gotoXY(centerX+( R * sin(PI * 36 /180)),centerY-( R * cos(PI * 36 /180)));
  delay(300);
  gotoXY(centerX-( R * sin(PI * 36 /180)),centerY-( R * cos(PI * 36 /180)));
  delay(300);
  gotoXY(centerX- ( R * cos(PI * 18 /180)),centerY+( R * sin(PI * 18 /180)));
  delay(300);
  gotoXY(centerX,centerY+R);
  pen.write(UP);
  goHome();
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void drawStar2(float centerX, float centerY, float R){
  float x,y;
  float r = R * sin(PI * 18 / 180) / cos(PI * 36 /180);
  
  gotoXY(centerX,centerY+R);
  pen.write(DOWN);
  delay(1000);
  gotoXY(centerX+( r * sin(PI * 36 /180)),centerY+( R * sin(PI * 18 /180)));
  delay(1000);
  gotoXY(centerX+( R * cos(PI * 18 /180)),centerY+( R * sin(PI * 18 /180)));
  delay(1000);
  gotoXY(centerX+ ( r * cos(PI * 18 /180)),centerY-( r * sin(PI * 18 /180)));
  delay(1000);
  gotoXY(centerX+( R * sin(PI * 36 /180)),centerY-(R * cos(PI * 36 /180)));
  delay(1000);
  gotoXY(centerX,centerY- r );
  delay(1000);
  gotoXY(centerX-( R * sin(PI * 36 /180)),centerY-(R * cos(PI * 36 /180)));
  delay(1000);
  gotoXY(centerX- ( r * cos(PI * 18 /180)),centerY-( r * sin(PI * 18 /180)));
  delay(1000);
  gotoXY(centerX-( R * cos(PI * 18 /180)),centerY+( R * sin(PI * 18 /180)));
  delay(1000);
  gotoXY(centerX-( r * sin(PI * 36 /180)),centerY+( R * sin(PI * 18 /180)));
  delay(1000);
  gotoXY(centerX,centerY+R);
  goHome();

}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void drawCircle(float centerX, float centerY, float R){
  float x,y,theta;
  gotoXY(centerX+R,centerY);
  pen.write(DOWN);
  for( theta = 0 ; theta <= ( 2 * PI ) ; theta+=.001){
    x = centerX + R * cos(theta);
    y = centerY + R * sin(theta);
    gotoXY(x,y);
  }
  goHome();
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void spirograph(float r,float R,float w,bool sign){
float x,y;
float theta;
gotoXY(0,R+r);
pen.write(DOWN);
if(sign){
  for( theta = 0 ; theta <= ( 2 * PI ) ; theta+=1){
    x = R * sin(theta) + r * sin( w * theta);
    y = R * cos(theta) + r * cos( w * theta);
    gotoXY(x,y);
  }
}
else {
    for( theta = 0 ; theta <= ( 2 * PI ) ; theta+=1){
    x = R * sin(theta) - r * sin( w * theta);
    y = R * cos(theta) + r * cos( w * theta);
    gotoXY(x,y);
  }
}
goHome();
}
/************************************************************************************************************************************/
/************************************************************************************************************************************/
void spirograph2(){
float x,y;
float theta;
float r,R1,R2,w;
r=150;
R1=20;
w = 0.5;
R2 = 50;
gotoXY( 0 , 0.5 * ( R2 + 0.6 * (R1 + r)) );
pen.write(DOWN);
  for( theta = 0 ; theta <= ( 200 * PI ) ; theta+=0.05){
    x = 0.5 * ( R2 * sin(0.01 * theta) + 0.6 * ( R1 * sin(theta) - r * sin( w * theta)) );
    y = 0.5 * ( R2 * cos(0.01 * theta) + 0.6 * (R1 * cos(theta) + r * cos( w * theta)) );
    gotoXY(x,y);
  }
  goHome();
}
