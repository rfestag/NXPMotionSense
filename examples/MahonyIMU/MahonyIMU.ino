// Inertial Monitoring Unit (IMU) using Mahony filter.
//
// To view this data, use the Arduino Serial Monitor to watch the
// scrolling angles, or run the OrientationVisualiser example in Processing.

#include <NXPMotionSense.h>
#include <MahonyAHRS.h>
#include <Wire.h>
#include <EEPROM.h>

NXPMotionSense imu;
Mahony filter;

void setup() {
  Serial.begin(9600);
  imu.begin();
  filter.begin(100); // 100 measurements per second
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch, heading;

  if (imu.available()) {
    // Read the motion sensors
    imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Scale the gyroscope.  NXPMotionSense gives degrees/sec
    // but Mahony expects radians/sec.
    float gyroScale = 0.0174533;
    gx = gx * gyroScale;
    gy = gy * gyroScale;
    gz = gz * gyroScale;

    // Update the Mahony filter
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    roll = roll * 57.2958;
    pitch = pitch * 57.2958;  // Mahony gives radians, convert to degrees
    heading = heading * 57.2958;
    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);
  }
}

