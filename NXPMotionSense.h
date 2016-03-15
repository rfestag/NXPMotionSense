#ifndef _NXP_Motion_Sensors_
#define _NXP_Motion_Sensors_

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

// TODO: move these inside class namespace
#define G_PER_COUNT            0.0001220703125f  // = 1/8192
#define DEG_PER_SEC_PER_COUNT  0.0625f  // = 1/16
#define UT_PER_COUNT           0.1f

class NXPMotionSense {
public:
	bool begin();
	bool available() {
		update();
		if (newdata) return true;
		return false;
	}
	void readMotionSensor(int& ax, int& ay, int& az, int& gx, int& gy, int& gz) {
		if (!newdata) update();
		newdata = 0;
		ax = accel_mag_raw[0];
		ay = accel_mag_raw[1];
		az = accel_mag_raw[2];
		gx = gyro_raw[0];
		gy = gyro_raw[1];
		gz = gyro_raw[2];
	}
	void readMotionSensor(int& ax, int& ay, int& az, int& gx, int& gy, int& gz, int& mx, int& my, int& mz) {
		if (!newdata) update();
		newdata = 0;
		ax = accel_mag_raw[0];
		ay = accel_mag_raw[1];
		az = accel_mag_raw[2];
		mx = accel_mag_raw[3];
		my = accel_mag_raw[4];
		mz = accel_mag_raw[5];
		gx = gyro_raw[0];
		gy = gyro_raw[1];
		gz = gyro_raw[2];
	}
	void readMotionSensor(float& ax, float& ay, float& az, float& gx, float& gy, float& gz) {
		if (!newdata) update();
		newdata = 0;
		ax = (float)accel_mag_raw[0] * G_PER_COUNT;
		ay = (float)accel_mag_raw[1] * G_PER_COUNT;
		az = (float)accel_mag_raw[2] * G_PER_COUNT;
		gx = (float)gyro_raw[0] * DEG_PER_SEC_PER_COUNT;
		gy = (float)gyro_raw[1] * DEG_PER_SEC_PER_COUNT;
		gz = (float)gyro_raw[2] * DEG_PER_SEC_PER_COUNT;
	}
	void readMotionSensor(float& ax, float& ay, float& az, float& gx, float& gy, float& gz, float& mx, float& my, float& mz) {
		if (!newdata) update();
		newdata = 0;
		ax = (float)accel_mag_raw[0] * G_PER_COUNT;
		ay = (float)accel_mag_raw[1] * G_PER_COUNT;
		az = (float)accel_mag_raw[2] * G_PER_COUNT;
		gx = (float)gyro_raw[0] * DEG_PER_SEC_PER_COUNT;
		gy = (float)gyro_raw[1] * DEG_PER_SEC_PER_COUNT;
		gz = (float)gyro_raw[2] * DEG_PER_SEC_PER_COUNT;
		float x = (float)accel_mag_raw[3] * UT_PER_COUNT - magcalh[0];
		float y = (float)accel_mag_raw[4] * UT_PER_COUNT - magcalh[1];
		float z = (float)accel_mag_raw[5] * UT_PER_COUNT - magcalh[2];
		mx = x * magcals[0][0] + y * magcals[0][1] + z * magcals[0][2];
		my = x * magcals[1][0] + y * magcals[1][1] + z * magcals[1][2];
		mz = x * magcals[2][0] + y * magcals[2][1] + z * magcals[2][2];
	}

	bool writeCalibration(const void *data);
private:
	void update();
	bool FXOS8700_begin();
	bool FXAS21002_begin();
	bool MPL3115_begin();
	bool FXOS8700_read(int16_t *data);
	bool FXAS21002_read(int16_t *data);
	bool MPL3115_read(int32_t *altitude, int16_t *temperature);

	float magcalh[3];
	float magcals[3][3];
	int16_t accel_mag_raw[6];
	int16_t gyro_raw[3];
	int16_t temperature_raw;
	uint8_t newdata;
};



#endif
