//weighted average
//student id: 20363161

#include <Wire.h> //include wire library
#define I2C_SLAVE_ADDR 0x04 // include slave address

#define VOUT1 14 // define input pin number
#define VOUT2 27 // define input pin number
#define VOUT3 26 // define input pin number
#define VOUT4 25 // define input pin number

void setup() 
{
  Serial.begin(9600);
  Wire.begin();

  pinMode(VOUT1, INPUT); //define pin mode
  pinMode(VOUT2, INPUT); //define pin mode
  pinMode(VOUT3, INPUT); //define pin mode
  pinMode(VOUT4, INPUT); //define pin mode
}
int x = 0; //define left mototr speed
int y = 0; //define right mototr speed
int z = 0; //define servo angle
float weightedAverage; //define weighted average

void loop() 
{
  Wire.beginTransmission(I2C_SLAVE_ADDR); //begin transmission

  int Vout1 = analogRead(VOUT1); //read analogue value
  Serial.print("Vout1: "); //display value 
  Serial.print(Vout1);

  int Vout2 = analogRead(VOUT2); //read analogue value
  Serial.print("  Vout2: "); //display value 
  Serial.print(Vout2);
 
  int Vout3 = analogRead(VOUT3); //read analogue value
  Serial.print("  Vout3: "); //display value 
  Serial.print(Vout3);
  
  int Vout4 = analogRead(VOUT4); //read analogue value
  Serial.print("  Vout4: "); //display value 
  Serial.println(Vout4);
  
  weightedAverage = ((9*Vout1) + (3*Vout2) + (7*Vout3) + (5*Vout4))/(Vout1+Vout2+Vout3+Vout4); //calculate weighted average

  if (weightedAverage == 5.995) //perfectly aligned
  {
    x = 180; //move forwards
    y = 180; // move forwards
    z = 75; // at centre angle
  }

  else if (weightedAverage > 5.995) //slightly left
  {
    x = 180; //turn right
    y = 150; // slow right motor to turn right
    z = 90; // turn right
  }

  else //slightly right
  {
    x = 150; //slow down to turn left
    y = 180; // turn left
    z = 60; // turn left
  }

  Wire.write((byte)((x & 0x0000FF00) >> 8)); // first byte of x, containing bits 16 to 9
  Wire.write((byte)(x & 0x000000FF)); //second byte of x, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((y & 0x0000FF00) >> 8)); // first byte of y, containing bits 16 to 9 
  Wire.write((byte)(y & 0x000000FF)); // second byte of y, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((z & 0x0000FF00) >> 8)); // first byte of z, containing bits 16 to 9  
  Wire.write((byte)(z & 0x000000FF));// second byte of z, containing the 8 LSB - bits 8 to 1

  Wire.endTransmission();   //end transmission
  delay(1000); //repeat every second
  }

  

