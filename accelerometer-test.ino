/*
    Arduino and ADXL345 Accelerometer - 3D Visualization Example 
     by Dejan, https://howtomechatronics.com
*/
#include <Wire.h>  // Wire library - used for I2C communication

int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs
float roll,pitch,rollF,pitchF=0;

const int pitchPositiveThreshold = 10;
const int pitchNegativeThreshold = -10;
const int rollPositiveThreshold = 10;
const int rollNegativeThreshold = -10;

//void setup() {
//  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
// 
//  Wire.begin(); // Initiate the Wire library
//  // Set ADXL345 in measuring mode
//  Wire.beginTransmission(ADXL345); // Start communicating with the device
//  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
//  // Enable measurement
//  Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
//  Wire.endTransmission();
//  delay(10);
//
//  //Off-set Calibration
//  //X-axis
//  Wire.beginTransmission(ADXL345);
//  Wire.write(0x1E);
//  Wire.write(1);
//  Wire.endTransmission();
//  delay(10);
//  //Y-axis
//  Wire.beginTransmission(ADXL345);
//  Wire.write(0x1F);
//  Wire.write(-2);
//  Wire.endTransmission();
//  delay(10);
//
//  //Z-axis
//  Wire.beginTransmission(ADXL345);
//  Wire.write(0x20);
//  Wire.write(-9);
//  Wire.endTransmission();
//  delay(10);
//}
//
//void loop() {
//  // === Read acceleromter data === //
//  Wire.beginTransmission(ADXL345);
//  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
//  Wire.endTransmission(false);
//  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
//  X_out = ( Wire.read() | Wire.read() << 8); // X-axis value
//  X_out = X_out / 256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
//  Y_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
//  Y_out = Y_out / 256;
//  Z_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
//  Z_out = Z_out / 256;
//
//  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
//  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
//  pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180 / PI;
//
//  // Low-pass filter
//  rollF = 0.94 * rollF + 0.06 * roll;
//  pitchF = 0.94 * pitchF + 0.06 * pitch;
//
//  Serial.print("roll: ");
//  Serial.print(rollF);
//  Serial.print("/");
//  Serial.print("pitch: ");
//  Serial.print(pitchF);
//
//  double motor1Offset = 0;
//  double motor2Offset = 0;
//  double motor3Offset = 0;
//  double motor4Offset = 0;
//
//  if (pitchF > pitchPositiveThreshold) {
//    motor1Offset += -1 * pitchF;
//    motor2Offset += -1 * pitchF;
//    motor3Offset += pitchF;
//    motor4Offset += pitchF;
//  }
//  if (pitchF < pitchNegativeThreshold) {
//    motor1Offset += pitchF;
//    motor2Offset += pitchF;
//    motor3Offset += -1 * pitchF;
//    motor4Offset += -1 * pitchF;
//  }
//  if (rollF > rollPositiveThreshold) {
//    motor1Offset += rollF;
//    motor2Offset += -1 * rollF;
//    motor3Offset += -1 * rollF;
//    motor4Offset += rollF;
//  }
//  if (rollF < rollNegativeThreshold) {
//    motor1Offset += -1 * rollF;
//    motor2Offset += rollF;
//    motor3Offset += rollF;
//    motor4Offset += -1 * rollF;
//  }
//
//  motor1Offset /= 200;
//  motor2Offset /= 200;
//  motor3Offset /= 200;
//  motor4Offset /= 200;
//
//  Serial.print(" Motor 1 offset: ");
//  Serial.print(motor1Offset);
//  Serial.print(" Motor 2 offset: ");
//  Serial.print(motor2Offset);
//  Serial.print(" Motor 3 offset: ");
//  Serial.print(motor3Offset);
//  Serial.print(" Motor 4 offset: ");
//  Serial.println(motor4Offset);
//}
