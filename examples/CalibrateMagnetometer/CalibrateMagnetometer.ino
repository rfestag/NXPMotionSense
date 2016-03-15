#include <NXPMotionSense.h>
#include <Wire.h>
#include <EEPROM.h>
#include <util/crc16.h>

NXPMotionSense imu;

void setup() {
  Serial.begin(115200);
  while (!Serial) ; // wait for serial port open
  imu.begin();
}

void loop() {
  int ax, ay, az;
  int gx, gy, gz;
  int mx, my, mz;

  // get and print uncalibrated data
  if (imu.available()) {
    imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);
    Serial.print(ax);
    Serial.print(',');
    Serial.print(ay);
    Serial.print(',');
    Serial.print(az);
    Serial.print(',');
    Serial.print(gx);
    Serial.print(',');
    Serial.print(gy);
    Serial.print(',');
    Serial.print(gz);
    Serial.print(',');
    Serial.print(mx);
    Serial.print(',');
    Serial.print(my);
    Serial.print(',');
    Serial.print(mz);
    Serial.println();
  }

  // check for incoming calibration
  receiveCalibration();

}

byte caldata[52]; // buffer to receive magnetic calibration data
byte calcount=0;

void receiveCalibration() {
  uint16_t crc;
  byte b, i;

  if (Serial.available()) {
    b = Serial.read();
    if (calcount == 0 && b != 117) {
      // first byte must be 117
      return;
    }
    if (calcount == 1 && b != 84) {
      // second byte must be 84
      calcount = 0;
      return;
    }
    // store this byte
    caldata[calcount++] = b;
    if (calcount < 52) {
      // full calibration message is 52 bytes
      return;
    }
    // verify the crc16 check
    crc = 0xFFFF;
    for (i=0; i < 52; i++) {
      crc = _crc16_update(crc, caldata[i]);
    }
    if (crc == 0) {
      // data looks good, use it
      imu.writeCalibration(caldata);
      calcount = 0;
      return;
    }
    // look for the 117,84 in the data, before discarding
    for (i=2; i < 51; i++) {
      if (caldata[i] == 117 && caldata[i+1] == 84) {
        // found possible start within data
        calcount = 52 - i;
        memmove(caldata, caldata + i, calcount);
        return;
      }
    }
    // look for 117 in last byte
    if (caldata[51] == 117) {
      caldata[0] = 117;
      calcount = 1;
    } else {
      calcount = 0;
    }
  }
}



