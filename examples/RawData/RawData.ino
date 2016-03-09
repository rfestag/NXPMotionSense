#include <NXPMotionSense.h>
#include <Wire.h>
#include <EEPROM.h>

NXPMotionSense imu;

void setup()
{
  Serial.begin(115200);
  while (!Serial) ; // wait for serial port open
  imu.begin();
}

void loop()
{
  int16_t accel[3], gyro[3], mag[3];

  if (imu.available()) {
    // get and print data
    imu.readRawAccelerometer(accel);
    imu.readRawGyroscope(gyro);
    imu.readRawMagnetometer(mag);
    Serial.print(accel[0]);
    Serial.print(',');
    Serial.print(accel[1]);
    Serial.print(',');
    Serial.print(accel[2]);
    Serial.print(',');
    Serial.print(gyro[0]);
    Serial.print(',');
    Serial.print(gyro[1]);
    Serial.print(',');
    Serial.print(gyro[2]);
    Serial.print(',');
    Serial.print(mag[0]);
    Serial.print(',');
    Serial.print(mag[1]);
    Serial.print(',');
    Serial.print(mag[2]);
    Serial.println();
  }

}




