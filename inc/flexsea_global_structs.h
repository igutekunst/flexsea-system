/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-system' System commands & functions
	Copyright (C) 2016 Dephy, Inc. <http://dephy.com/>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************
	[Lead developper] Jean-Francois (JF) Duval, jfduval at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors]
*****************************************************************************
	[This file] flexsea_global_structs: contains all the data structures
	used across the project
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-10-19 | jfduval | Initial release
	*
****************************************************************************/

#ifndef INC_FLEXSEA_GLOBAL_STRUCT_H
#define INC_FLEXSEA_GLOBAL_STRUCT_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>

//****************************************************************************
// Prototype(s):
//****************************************************************************

//****************************************************************************
// Definition(s):
//****************************************************************************

//****************************************************************************
// Structure(s):
//****************************************************************************

/*Note: most structures will have two versions. The original, aka 'raw'
version has multiple data types, and is used by the different boards.
It includes a sub-structure named decoded_X that contains decoded values
(physical units, not ticks). The decoded values are always int32*/

//Gains
struct gains_s
{
	 uint16_t g0, g1, g2, g3, g4, g5;
};

//Generic controller
struct gen_ctrl_s
{
	//Gains:
	struct gains_s gain;

	//Value wanted and setpoint value:
	int32_t actual_val;
	int32_t setpoint_val;
	int32_t actual_vel;

	//Errors:
	int32_t error;						//Current error
	int32_t error_prev;					//Past error
	int32_t error_sum;					//Integral
	int32_t error_dif;					//Differential

	//trapezoidal time
	int64_t trap_t;
};

//Position controller
struct pos_ctrl_s
{
	//Gains:
	struct gains_s gain;

	//Value wanted and setpoint value:
	int32_t pos;
	int32_t setp;
	int32_t posi;
	int32_t posf;
	int32_t spdm;
	int32_t acc;

	//Errors:
	int32_t error;						//Current error
	int32_t error_prev;					//Past error
	int32_t error_sum;					//Integral
	int32_t error_dif;					//Differential

	//trapezoidal time
	int64_t trap_t;
};

//Main data structure for all the controllers:
struct ctrl_s
{
	uint8_t active_ctrl;
	uint8_t pwm;						//ToDo needs to be more than 8bits!
	struct gen_ctrl_s generic;
	struct gen_ctrl_s current;
	struct pos_ctrl_s position;
	struct gen_ctrl_s impedance;
};

//Encoder: //ToDo: do we still need this?
struct enc_s
{
	int32_t count;
	int32_t count_last;
	int32_t count_dif;
	uint32_t config;
	int32_t vel;
};
	
//Inner structure for the IMU:

struct decoded_xyz_s
{
	 int32_t x;
	 int32_t y;
	 int32_t z;
};

struct xyz_s
{
	 int16_t x;
	 int16_t y;
	 int16_t z;
};

//FlexSEA-Execute:

struct decoded_execute_s
{
	struct decoded_xyz_s gyro;  //deg/s
	struct decoded_xyz_s accel; //mg

	int32_t strain;				//%
	int32_t current;			//mA
	int32_t volt_batt;			//mV
	int32_t volt_int;			//mV
	int32_t temp;				//Celsius x10
	int32_t analog[8];			//mV
};

struct execute_s
{
	struct xyz_s gyro;
	struct xyz_s accel;

	uint16_t strain;
	uint16_t analog[8];
	int16_t current;
	int32_t enc_display; 		//useful?
	int32_t enc_control; //useful?
	int32_t enc_commut; //useful?
	int32_t enc_control_ang;
	int32_t enc_control_vel;
	int32_t enc_motor;
	int32_t enc_joint;
	uint8_t volt_batt;	//+VB
	uint8_t volt_int;	//+VG
	uint8_t temp;
	uint8_t pwro;
	uint8_t status1;
	uint8_t status2;

	struct ctrl_s ctrl;

	//Decoded values:
	struct decoded_execute_s decoded;
};

//FlexSEA-Manage:

struct decoded_manage_s
{
	struct decoded_xyz_s gyro;	//deg/s
	struct decoded_xyz_s accel;	//mg

	int32_t analog[8];			//mV
};

struct manage_s
{
	struct xyz_s gyro;
	struct xyz_s accel;

	uint16_t analog[8];
	uint16_t digitalIn;

	uint8_t status1;

	uint8_t sw1;
	uint8_t sampling;

	//Decoded values:
	struct decoded_manage_s decoded;
};

//FlexSEA-Strain:

struct decoded_strain_s
{
	int32_t strain[6];
};

//Strain - single channel
struct strain_1ch_s
{
	//Config:
	uint8_t offset;
	uint8_t gain;
	uint8_t oref;

	//Raw ADC values:
	uint16_t strain_raw[4];
	uint16_t vo1;
	uint16_t vo2;

	//Filtered value:
	uint16_t strain_filtered;
};

//Strain - 6 channels
struct strain_s
{
	//One structure per channel:
	struct strain_1ch_s ch[6];
	uint8_t compressedBytes[9];

	//Decoded values:
	struct decoded_strain_s decoded;
};

//Special structure for the RIC/NU Knee. 'execute_s' + extra sensors.

struct decoded_ricnu_s
{
	int32_t ext_strain[6];
};

struct ricnu_s
{
	//Execute:
	struct execute_s ex;

	//Extra sensors (Strain):
	//uint16_t ext_strain[6];
	struct strain_s st;

	//Decoded values (ext_strain only)
	struct decoded_ricnu_s decoded;
};

//FlexSEA-Gossip:

struct decoded_gossip_s
{
	struct decoded_xyz_s gyro;     //deg/s
	struct decoded_xyz_s accel;    //mg
	struct decoded_xyz_s magneto;  //uT
};

struct gossip_s
{
	struct xyz_s gyro;
	struct xyz_s accel;
	struct xyz_s magneto;

	uint16_t capsense[4];

	uint16_t io[2];
	uint8_t status;

	//Decoded values:
	struct decoded_gossip_s decoded;
};

//FlexSEA-Battery:

struct decoded_battery_s
{
	int32_t voltage;    //mV
	int32_t current;    //mA
	int32_t power;      //mW
	int32_t temp;       //C*10
};

struct battery_s
{
	uint16_t voltage;
	int16_t current;
	uint8_t temp;
	uint8_t pushbutton;
	uint8_t status;

	//Decoded values:
	struct decoded_battery_s decoded;
};

//Commands, tools, specialty, etc.:

//In Control Tool:
struct in_control_s
{
	uint8_t controller;
	int32_t setp;
	int32_t actual_val;
	int32_t error;
	int32_t output;
	int16_t pwm;
	uint8_t mot_dir;
	int16_t current;
	uint16_t combined;	//[CTRL2:0][MOT_DIR][PWM]

	int32_t r[4];
	int32_t w[4];
};

struct user_data_s
{
	int32_t r[4];
	int32_t w[4];
};

//IMU data & config
struct imu_s
{
	 struct xyz_s accel;
	 struct xyz_s gyro;
	 struct xyz_s magneto;
	 uint32_t config;
};

//AS504x Magnetic encoders:
struct as504x_s
{
	int32_t angle_raws[10];			//last 10 raw readings
	int32_t angle_conts[10];		// last 10 continuous angle readings

	int32_t angle_vel_denoms[8];	//the number of 1 MHz counts between the last two angle readings
	int32_t num_rot;				//number of rotations
	int32_t angle_vel[2];			//sensor reading - last sensor reading
	int32_t angle_vel_filt[2];		//sensor reading - last sensor reading
	int32_t angle_vel_RPMS_raw[2];	//sensor reading - last sensor reading
	int32_t angle_vel_RPMS_filt[2];
	int32_t angle_vel_RPM;
	uint16_t angle_comp;			//Sensor reading, 2/ Compensation enabled
	uint16_t angle_ctrl;			//Modified version (gain, zero). Used by controllers.

	int32_t last_angtimer_read;
	int32_t counts_since_last_ang_read;
	int32_t last_ang_read_period;
	int32_t samplefreq;				//sampling frequency of the sensor
};

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern struct execute_s exec1, exec2, exec3, exec4;
extern struct ricnu_s ricnu_1;
extern struct manage_s manag1, manag2;
extern struct strain_s strain1;
extern struct in_control_s in_control_1;
extern struct gossip_s gossip1, gossip2;
extern struct battery_s batt1;

#if defined(BOARD_TYPE_FLEXSEA_PLAN)
extern struct user_data_s user_data_1;
#endif  //defined(BOARD_TYPE_FLEXSEA_PLAN)

#if defined(BOARD_TYPE_FLEXSEA_MANAGE)
extern struct user_data_s user_data;
#endif  //defined(BOARD_TYPE_FLEXSEA_MANAGE)

#endif	//INC_FLEXSEA_GLOBAL_STRUCT_H