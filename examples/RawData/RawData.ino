#include <NXPMotionSense.h>

NXPMotionSense imu;

void setup()
{
  while (!Serial) ; // wait for serial port open
  imu.begin();
}

void loop()
{
  int16_t data[3];

  if (imu.available()) {
    // get and print data
    imu.readRawAccelerometer(data);
    Serial.print(data[0]);
    Serial.print(',');
    Serial.print(data[1]);
    Serial.print(',');
    Serial.print(data[2]);
    Serial.print(',');
    imu.readRawGyroscope(data);
    Serial.print(data[0]);
    Serial.print(',');
    Serial.print(data[1]);
    Serial.print(',');
    Serial.print(data[2]);
    Serial.print(',');
    imu.readRawMagnetometer(data);
    Serial.print(data[0]);
    Serial.print(',');
    Serial.print(data[1]);
    Serial.print(',');
    Serial.print(data[2]);
    Serial.println();
  }

}




