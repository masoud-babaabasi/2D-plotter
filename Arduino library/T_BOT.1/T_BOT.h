#include <Stepper.h>
#include <Servo.h>
class T_BOT{
  float preX,preY;
  int N1,N2;
  int SperR,reduis,stpSpeed;
  float coef;
  Stepper stp1,stp2;
  Servo pen;
  int st1e,st2e;
  public:
  T_BOT(int SperR, int reduis, int stpSpeed,
		int st11, int st12, int st13, int st14, int st1E, 
		int st21, int st22, int st23, int st24, int st2E,
											int servoPin);
  void upDown(bool UP_DOWN);  
  int up = 0;//servo position in degrees
  int down = 90;//servo position in degrees
  void gotoxy(float X,float Y);
  float getX();
  float getY();
};