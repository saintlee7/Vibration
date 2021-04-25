#include "I2Cdev.h" // include the I2Cdev library
#include "MPU6050.h" // include the accelerometer library
#include <SoftwareSerial.h>

SoftwareSerial DebugSerial(2, 3);

MPU6050 accelgyro;  // set device to MPU6050
int16_t ax, ay, az, gx, gy, gz;  // define accel as ax,ay,az          
int baselineX = 0;
int baselineY = 0;
int baselineZ = 0;

void setup() {
  Wire.begin();      // join I2C bus   
  Serial.begin(115200);    //  initialize serial communication
  DebugSerial.begin(115200); 

  accelgyro.initialize();  // initialize the accelerometer
  
  Serial.println("initialize the accelerometer");
  delay(3000);

  for ( int i=0 ; i< 300 ; i++) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    baselineX += ax;
    baselineY += ay;
    baselineZ += gz;
  }
    
  baselineX /= 300 ;
  baselineY /= 300;
  baselineZ /= 300;
 
}
void loop() {
    
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);  // read measurements from device  
  Serial.println((ax-baselineX));

  String tData ;
  String xData((ax-baselineX)) ;
  String yData((ay-baselineY)) ;
  String zData((gz-baselineZ)) ;
  
  tData = "E" + xData + "," + yData + "," + zData + "\n";

  DebugSerial.println (tData);
  delay(2);
}
