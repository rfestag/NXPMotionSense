#ifndef _NXP_Motion_Sensors_
#define _NXP_Motion_Sensors_

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

class NXPMotionSense {
public:
	bool begin();
	bool available();

	void readRawAccelerometer(int16_t data[3]) { memcpy(data, accel_mag_raw, 6); }
	void readRawGyroscope(int16_t data[3])     { memcpy(data, gyro_raw, 6); }
	void readRawMagnetometer(int16_t data[3])  { memcpy(data, accel_mag_raw+3, 6); }
private:
	void update();
	bool FXOS8700_begin();
	bool FXAS21002_begin();
	bool MPL3115_begin();
	bool FXOS8700_read(int16_t *data);
	bool FXAS21002_read(int16_t *data);
	bool MPL3115_read(int32_t *altitude, int16_t *temperature);

	int16_t accel_mag_raw[6];
	int16_t gyro_raw[3];
	int16_t temperature_raw;
	uint8_t newdata;
};



#endif
