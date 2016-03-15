// https://www.arduino.cc/en/Tutorial/Genuino101CurieIMUOrientationVisualiser

#include <NXPMotionSense.h>
#include <MadgwickAHRS.h>

NXPMotionSense imu;
Madgwick filter;

void setup() {
  Serial.begin(9600);
  imu.begin();
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch, heading;

  if (imu.available()) {
    // Read the motion sensors
    imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Scale the gyroscope to the range Madgwick expects
    float gyroScale = 0.097656f; // TODO: is this really correct?
    gx = gx * gyroScale;
    gy = gx * gyroScale;
    gz = gz * gyroScale;

    // update the Madgwick filter
    filter.updateIMU(gx, gy, gz, ax, ay, az);
    //filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
  }

  if (readyToPrint()) {
    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    Serial.print(heading);
    Serial.print(",");
    Serial.print(pitch);
    Serial.print(",");
    Serial.println(roll); // TODO: roll not working... why?
  }
}

// Decide when to print more info.
bool readyToPrint() {
  static unsigned long nowMillis;
  static unsigned long thenMillis;

  // If the Processing visualization sketch is sending "s"
  // then send new data each time it wants to redraw
  while (Serial.available()) {
    int val = Serial.read();
    if (val == 's') {
      thenMillis = millis();
      return true;
    }
  }
  // Otherwise, print 8 times per second, for viewing as
  // scrolling numbers in the Arduino Serial Monitor
  nowMillis = millis();
  if (nowMillis - thenMillis > 125) {
    thenMillis = nowMillis;
    return true;
  }
  return false;
}
