//basic line following
//lab report 2
//student id: 20363161

#include <Wire.h> //including the Wire library for i2c communication
#define I2C_SLAVE_ADDR 0x04 //defining slave address of Arduino

#define VOUT1 14 //defining the input pin numbers
#define VOUT2 27 //defining the input pin numbers
#define VOUT3 26 //defining the input pin numbers
#define VOUT4 25 //defining the input pin numbers

void setup() 
{
  Serial.begin(9600); 
  Wire.begin(); 

  pinMode(VOUT1, INPUT); //make the pins as inputs
  pinMode(VOUT2, INPUT); //make the pins as inputs
  pinMode(VOUT3, INPUT); //make the pins as inputs
  pinMode(VOUT4, INPUT); //make the pins as inputs
}
int x = 0; //set the left motor speed
int y = 0; //set the right motor speed
int z = 0; // set the servo angle

void loop() 
{
  Wire.beginTransmission(I2C_SLAVE_ADDR); 

  int Vout1 = analogRead(VOUT1); //read analogue value from VOUT1
  Serial.print("Vout1: "); //print the value
  Serial.print(Vout1);

  int Vout2 = analogRead(VOUT2); //read analogue value from VOUT2
  Serial.print("  Vout2: "); //print the value
  Serial.print(Vout2);
 
  int Vout3 = analogRead(VOUT3); //read analogue value from VOUT3
  Serial.print("  Vout3: "); //print the value
  Serial.print(Vout3);
  
  int Vout4 = analogRead(VOUT4); //read analogue value from VOUT4
  Serial.print("  Vout4: "); //print the value
  Serial.println(Vout4);
 

  if ((Vout3 >= 2300) && (Vout4 >= 2550)) //if sensor readings of Vout3 and Vout4 detect white surface
  {
    x = 0; //stop left motor
    y = 0; //stop right motor
    z = 75; // set servo angle to centre
  }

  else if ( ( (Vout3 > 2100) && (Vout3 < 2300) ) || ( ( (Vout4 > 2200) && (Vout4 < 2550) ))) //if Vout3 and Vout4 readings detect black surface
  {
    x = 200; //set left motor at 200
    y = 200; //set right motor at 200
    z = 75; //set servo angle to centre
  }

  else 
  {
    x = 150; //slow down left motor to find black line
    y = 150; //slow down right motor to find black line
    z = 75; //set servo angle to centre
  }

    Wire.write((byte)((x & 0x0000FF00) >> 8)); // first byte of x, containing bits 16 to 9
    Wire.write((byte)(x & 0x000000FF)); // second byte of x, containing the 8 LSB - bits 8 to 1
    Wire.write((byte)((y & 0x0000FF00) >> 8));  // first byte of y, containing bits 16 to 9  
    Wire.write((byte)(y & 0x000000FF)); // second byte of y, containing the 8 LSB - bits 8 to 1
    Wire.write((byte)((z & 0x0000FF00) >> 8));  // first byte of z, containing bits 16 to 9 
    Wire.write((byte)(z & 0x000000FF)); // second byte of z, containing the 8 LSB - bits 8 to 1

    Wire.endTransmission();   
    delay(1000);
  }

  

