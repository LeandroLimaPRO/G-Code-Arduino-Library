#include <gcode.h>

#define Speed 100
#define NumCommands 2
void homing();
void moviment();
commandscallback commands[NumCommands] = {{"G28",homing},{"G29",moviment}};
gcode Commands(NumCommands,commands);

double X;
double Y;
double A;
double B;

void setup()
{
  Commands.begin();
}

void loop() 
{
  Commands.available()

}
void moviment(){
  double newXValue = X;
    double newYValue = Y;
    
    if(Commands.availableValue('X'))
      newXValue = Commands.GetValue('X');
    if(Commands.availableValue('Y'))
      newYValue = Commands.GetValue('Y');

    gotoLocation(newXValue,newYValue);
}
void homing()
{
  // code to home machine
}

void gotoLocation(double NewX,double NewY)
{
  double YCurrent = 0.5*(A + B);
  double XCurrent = 0.5*(A - B);
  double R = sqrt((NewY-YCurrent)*(NewY-YCurrent)+(NewX-XCurrent)*(NewX-XCurrent));
  double t = R/Speed;

  double ANewPosition = NewX+NewY;
  double BNewPosition = NewX-NewY;
  double SpeedA = abs(ANewPosition - A)/t;
  double SpeedB = abs(ANewPosition - B)/t;
  
  X = NewX;
  Y = NewY;
  A = ANewPosition;
  B = BNewPosition;
  
  Serial.print(X);
  Serial.print(" ");
  Serial.print(Y);


  // code to run machine to location using:
  //  - ANewPosition (or A) and BNewPosition (or B)
  //  - SpeedA and SpeedB
}
