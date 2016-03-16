#include <NXPMotionSense.h>
#include <Wire.h>
#include <EEPROM.h>

NXPMotionSense imu;

void setup() {
  float hardIron[3];
  float softIron[9];
  float fieldStrength;
  int i, j;

  Serial.begin(9600);
  while (!Serial) ; // wait for serial port open
  imu.begin();
  imu.getCalibration(hardIron, softIron, &fieldStrength);
  Serial.println("Magnetic Calibration");
  Serial.println(); 
  Serial.println("Hard Iron Offset"); 
  for (i=0; i<3; i++) {
    Serial.print("  ");
    if (hardIron[i] >= 0.0f) Serial.print(' ');
    Serial.println(hardIron[i]);
  }
  Serial.println(); 
  Serial.println("Soft Iron Mapping"); 
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      Serial.print("  ");
      if (softIron[i*3+j] >= 0.0f) Serial.print(' ');
      Serial.print(softIron[i*3+j], 4);
    }
    Serial.println();
  }
  Serial.println(); 
  Serial.println("Expected Magnetic Field Strength"); 
  Serial.print("  ");
  Serial.print(fieldStrength);
  Serial.println(" uT");
}

void loop() {
}
