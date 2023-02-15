//advanced line following 
//student id: 20363161

#include <Wire.h> //include wire library
#define I2C_SLAVE_ADDR 0x04 //Arduino slave address

#define VOUT1 14 //define pin number for signal from amplifier circuit
#define VOUT2 27 //define pin number for signal from amplifier circuit
#define VOUT3 26 //define pin number for signal from amplifier circuit
#define VOUT4 25 //define pin number for signal from amplifier circuit

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(VOUT1, INPUT); //set pins as inputs
  pinMode(VOUT2, INPUT); //set pins as inputs
  pinMode(VOUT3, INPUT); //set pins as inputs
  pinMode(VOUT4, INPUT); //set pins as inputs
}
int x = 0; //declare left motor speed 
int y = 0; //declare right motor speed 
int z = 0; //declare servo angle

int baseSpeed = 180; //define base speed
int centreAngle = 75; //define centre angle

float u; //define PID output
int Kp = 0.5; //define proportional constant
int Kd = 4; //define derivative constant
int Ki = 2; //define integral constant
int K = 0.9; //define scaling factor
float setPoint = 6.6; //define setpoint
float weightedAverage1, weightedAverage2; //define weighted average
float error1; //define error
float error2; // define error

void loop() 
{
  Wire.beginTransmission(I2C_SLAVE_ADDR); //begin transmission

  int Vout1 = analogRead(VOUT1); //read analogue value and store in Vout1
  Serial.print("Vout1: "); //print the sensor reading
  Serial.print(Vout1);

  int Vout2 = analogRead(VOUT2); //read analogue value and store in Vout2
  Serial.print("  Vout2: "); //print the sensor reading
  Serial.print(Vout2);
 
  int Vout3 = analogRead(VOUT3); //read analogue value and store in Vout3
  Serial.print("  Vout3: "); //print the sensor reading
  Serial.print(Vout3);
  
  int Vout4 = analogRead(VOUT4); //read analogue value and store in Vout4
  Serial.print("  Vout4: "); //print the sensor reading
  Serial.println(Vout4);
  
  weightedAverage1 = ((9*Vout1) + (3*Vout2) + (7*Vout3) + (5*Vout4))/(Vout1+Vout2+Vout3+Vout4);//calculate weighted average
  error1 = setPoint - weightedAverage1; //calculate error
  Vout1 = analogRead(VOUT1); //read analogue value again
  Vout2 = analogRead(VOUT2); //read analogue value again
  Vout3 = analogRead(VOUT3); //read analogue value again
  Vout4 = analogRead(VOUT4); //read analogue value again
  weightedAverage2 = ((9*Vout1) + (3*Vout2) + (7*Vout3) + (5*Vout4))/(Vout1+Vout2+Vout3+Vout4);//calculate new weighted average
  error2 = setPoint - weightedAverage2;//calculate new error
  
  u = (Kp*error2) + (Ki*error2) + (Kd*(error2 - error1)); //calculate PID output

  x = baseSpeed + (K*u); //set left motor speed
  y = baseSpeed - (K*u); //set right motor speed
  z = centreAngle + u; //set servo angle

  Wire.write((byte)((x & 0x0000FF00) >> 8)); //first byte of x, containing bits 16 to 9
  Wire.write((byte)(x & 0x000000FF)); //second byte of x, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((y & 0x0000FF00) >> 8)); // first byte of y, containing bits 16 to 9  
  Wire.write((byte)(y & 0x000000FF));// second byte of y, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((z & 0x0000FF00) >> 8));// first byte of z, containing bits 16 to 9 
  Wire.write((byte)(z & 0x000000FF));// second byte of z, containing the 8 LSB - bits 8 to 1

  Wire.endTransmission();   //end transmission
  delay(1000); //repeat every second
  }

  

