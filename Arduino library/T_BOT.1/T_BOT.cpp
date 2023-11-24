#include "T_BOT.h"
#include "arduino.h"
T_BOT::T_BOT(int SR, int R, int Sp, int st11, int st12, int st13, int st14, int st1E,
                                    int st21, int st22, int st23, int st24, int st2E, 
                                    int servoPin):
                                    stp1(SperR, st11, st12, st13, st14),
                                    stp2(SperR, st21, st22, st23, st24){
  SperR = SR;
  reduis = R;
  stpSpeed = Sp;
  st1e = st1E;
  st2e = st2E;
  pen.attach(servoPin);
  pinMode(st1e,OUTPUT);
  pinMode(st2e,OUTPUT);
  digitalWrite(st1e,HIGH);
  digitalWrite(st2e,HIGH);
  stp1.setSpeed(stpSpeed);
  stp2.setSpeed(stpSpeed);
  coef = SperR / ( 2.0  * PI * reduis);
  preX = preY = 0;
}

void T_BOT::gotoxy(float X,float Y){
  int Np1,Np2;
  float dx,dy;
  uint32_t t,lastT;
  uint32_t interval1,interval2;
  Np1 = Np2 = 0;
  dx = X - preX;
  dy = Y - preY;
  
  N1 = ( -coef * dx ) + (-coef * dy);
  N2 = ( coef * dx ) + ( -coef * dy);
  
  t = ((max(abs(N1),abs(N2))) * 60.0) / ( stpSpeed * SperR )  * 1000000.0; // time in microsec

  if( N1 == 0 ) interval1 = t;
  else interval1 = t / abs(N1);
  if( N2 == 0 ) interval2 = t;
  else interval2 = t / abs(N2);
  
  digitalWrite(st1e,HIGH);
  digitalWrite(st2e,HIGH);
  
  lastT = micros();
  while(1){
      if( micros() - lastT > ( (Np1+1) * interval1 ) ) 
      {
        if(N1){
                    if(Np1 < abs(N1)){
                    if(N1 > 0) stp1.step(1);
                    else stp1.step(-1);
                    Np1++; 
                    }
        }
      }
      if( micros() - lastT > ( (Np2+1) * interval2 ) ) 
      {
        if(N2){
                    if(Np2 < abs(N2)){
                    if(N2 > 0) stp2.step(1);
                    else stp2.step(-1);
                    Np2++; 
                    }
        }
      }
      if( Np1 == abs(N1) && Np2 == abs(N2) ) break;
  }
  digitalWrite(st1e,LOW);
  digitalWrite(st2e,LOW);
  preX = X;
  preY = Y;
}

void T_BOT::upDown(bool UP_DOWN){
	if(UP_DOWN) pen.write(up);
	else pen.write(down);
}
float T_BOT::getX(){
	return preX;
}
float T_BOT::getY(){
	return preY;
}