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
	[This file] flexsea_cmd_control: commands specific to the motor & control
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-09 | jfduval | Initial GPL-3.0 release
	*
****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea_system.h"
#include "../inc/flexsea_cmd_control.h"

//Plan boards only:
#ifdef BOARD_TYPE_FLEXSEA_PLAN
//...
#endif	//BOARD_TYPE_FLEXSEA_PLAN

//Manage boards only:
#ifdef BOARD_TYPE_FLEXSEA_MANAGE
//...
#endif	//BOARD_TYPE_FLEXSEA_MANAGE

//Execute boards only:
#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
#include "main.h"
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Variable(s)
//****************************************************************************

//Will change this, but for now the payloads will be stored in:
uint8_t tmp_payload_xmit[PAYLOAD_BUF_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//This gets called by flexsea_system's init_flexsea_payload_ptr(). Map all
//functions from this file to the array here. Failure to do so will send all
//commands to flexsea_payload_catchall().
void init_flexsea_payload_ptr_control(void)
{
	//Control mode:
	flexsea_payload_ptr[CMD_CTRL_MODE][RX_PTYPE_READ] = &rx_cmd_ctrl_mode_rw;
	flexsea_payload_ptr[CMD_CTRL_MODE][RX_PTYPE_WRITE] = &rx_cmd_ctrl_mode_w;
	flexsea_payload_ptr[CMD_CTRL_MODE][RX_PTYPE_REPLY] = &rx_cmd_ctrl_mode_rr;

	//Controllers:
	/* TODO
	flexsea_payload_ptr[CMD_CTRL_O][RX_PTYPE_READ] = &rx_cmd_ctrl_o_rw;
	flexsea_payload_ptr[CMD_CTRL_O][RX_PTYPE_WRITE] = &rx_cmd_ctrl_o_w;
	flexsea_payload_ptr[CMD_CTRL_O][RX_PTYPE_REPLY] = &rx_cmd_ctrl_o_rr;
	flexsea_payload_ptr[CMD_CTRL_I][RX_PTYPE_READ] = &rx_cmd_ctrl_i_rw;
	flexsea_payload_ptr[CMD_CTRL_I][RX_PTYPE_WRITE] = &rx_cmd_ctrl_i_w;
	flexsea_payload_ptr[CMD_CTRL_I][RX_PTYPE_REPLY] = &rx_cmd_ctrl_i_rr;
	flexsea_payload_ptr[CMD_CTRL_P][RX_PTYPE_READ] = &rx_cmd_ctrl_p_rw;
	flexsea_payload_ptr[CMD_CTRL_P][RX_PTYPE_WRITE] = &rx_cmd_ctrl_p_w;
	flexsea_payload_ptr[CMD_CTRL_P][RX_PTYPE_REPLY] = &rx_cmd_ctrl_p_rr;
	*/

	//Controller gains:
	/* TODO
	flexsea_payload_ptr[CMD_CTRL_I_G][RX_PTYPE_READ] = &rx_cmd_ctrl_i_g_rw;
	flexsea_payload_ptr[CMD_CTRL_I_G][RX_PTYPE_WRITE] = &rx_cmd_ctrl_i_g_w;
	flexsea_payload_ptr[CMD_CTRL_I_G][RX_PTYPE_REPLY] = &rx_cmd_ctrl_i_g_rr;
	flexsea_payload_ptr[CMD_CTRL_P_G][RX_PTYPE_READ] = &rx_cmd_ctrl_p_g_rw;
	flexsea_payload_ptr[CMD_CTRL_P_G][RX_PTYPE_WRITE] = &rx_cmd_ctrl_p_g_w;
	flexsea_payload_ptr[CMD_CTRL_P_G][RX_PTYPE_REPLY] = &rx_cmd_ctrl_p_g_rr;
	flexsea_payload_ptr[CMD_CTRL_Z_G][RX_PTYPE_READ] = &rx_cmd_ctrl_z_g_rw;
	flexsea_payload_ptr[CMD_CTRL_Z_G][RX_PTYPE_WRITE] = &rx_cmd_ctrl_z_g_w;
	flexsea_payload_ptr[CMD_CTRL_Z_G][RX_PTYPE_REPLY] = &rx_cmd_ctrl_z_g_rr;
	*/

	//Controller setpoints:
	/* TODO
	flexsea_payload_ptr[CMD_CTRL_O][RX_PTYPE_READ] = &rx_cmd_ctrl_o_rw;
	flexsea_payload_ptr[CMD_CTRL_O][RX_PTYPE_WRITE] = &rx_cmd_ctrl_o_w;
	flexsea_payload_ptr[CMD_CTRL_O][RX_PTYPE_REPLY] = &rx_cmd_ctrl_o_r;
	flexsea_payload_ptr[CMD_CTRL_I][RX_PTYPE_READ] = &rx_cmd_ctrl_i_rw;
	flexsea_payload_ptr[CMD_CTRL_I][RX_PTYPE_WRITE] = &rx_cmd_ctrl_i_w;
	flexsea_payload_ptr[CMD_CTRL_I][RX_PTYPE_REPLY] = &rx_cmd_ctrl_i_rr;
	flexsea_payload_ptr[CMD_CTRL_P][RX_PTYPE_READ] = &rx_cmd_ctrl_p_rw;
	flexsea_payload_ptr[CMD_CTRL_P][RX_PTYPE_WRITE] = &rx_cmd_ctrl_p_r;
	flexsea_payload_ptr[CMD_CTRL_P][RX_PTYPE_REPLY] = &rx_cmd_ctrl_p_rr;
	*/

	//Misc:
	//flexsea_payload_ptr[SHORTED_LEADS = &;
//	flexsea_payload_ptr[CMD_IN_CONTROL][RX_PTYPE_READ] = &rx_cmd_in_control;
}

//Transmit Control Mode:
//======================

//Test code? Yes
void tx_cmd_ctrl_mode_w(uint8_t *shBuf, uint8_t *cmd, uint8_t *cmdType, \
						uint16_t *len, uint8_t ctrlMode)
{
	uint16_t index = 0;

	//Formatting:
	(*cmd) = CMD_CTRL_MODE;
	(*cmdType) = CMD_WRITE;

	//Data:
	shBuf[index++] = ctrlMode;

	//Payload length:
	(*len) = index;
}

//Test code? Yes
void tx_cmd_ctrl_mode_r(uint8_t *shBuf, uint8_t *cmd, uint8_t *cmdType, \
						uint16_t *len)
{
	uint16_t index = 0;

	//Formatting:
	(*cmd) = CMD_CTRL_MODE;
	(*cmdType) = CMD_READ;

	//Data:
	//(none)
	(void)shBuf;

	//Payload length:
	(*len) = index;
}

//Receive Control Mode:
//======================

//Test code? No
void rx_cmd_ctrl_mode_w(uint8_t *buf, uint8_t *info)
{
	(void)info;

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		control_strategy(buf[P_DATA1]);

	#else

		(void)buf;

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
}

//Test code? No
void rx_cmd_ctrl_mode_rw(uint8_t *buf, uint8_t *info)
{
	(void)info;

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

//Generate the reply:
//	numb = tx_cmd_ricnu_w(TX_CMD_DEFAULT, ctrl.active_ctrl);	//ToDo
//	COMM_GEN_STR_DEFAULT
//	flexsea_send_serial_master(myPort, myData, myLen);	//ToDo

	#else
		(void)buf;
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
}

//Test code? No
void rx_cmd_ctrl_mode_rr(uint8_t *buf, uint8_t *info)
{
	(void)info;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Decode data:
	uint8_t controller = buf[P_DATA1];
	//Store value:
//	exec1.ctrl.active_ctrl = controller;
		//ToDo use pointer, too specific

	#else
		(void)buf;
	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
}

//Transmit Control Current Setpoint:
//==================================

//Test code? Yes
void tx_cmd_ctrl_i_w(uint8_t *shBuf, uint8_t *cmd, uint8_t *cmdType, \
						uint16_t *len, int16_t currentSetpoint)
{
	uint16_t index = 0;

	//Formatting:
	(*cmd) = CMD_CTRL_I;
	(*cmdType) = CMD_WRITE;

	//Data:
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		//Execute: reply only
		(void)currentSetpoint;
		SPLIT_16((uint16_t)ctrl.current.actual_val, shBuf, &index);
		SPLIT_16((uint16_t)ctrl.current.setpoint_val, shBuf, &index);
	#else
		//Other boards can write a new setpoint
		SPLIT_16((uint16_t)0, shBuf, &index);
		SPLIT_16((uint16_t)currentSetpoint, shBuf, &index);
	#endif

	//Payload length:
	(*len) = index;
}

//Test code? Yes
void tx_cmd_ctrl_i_r(uint8_t *shBuf, uint8_t *cmd, uint8_t *cmdType, \
						uint16_t *len)
{
	uint16_t index = 0;

	//Formatting:
	(*cmd) = CMD_CTRL_I;
	(*cmdType) = CMD_READ;

	//Data:
	//(none)
	(void)shBuf;

	//Payload length:
	(*len) = index;
}

//Receive Control Current Setpoint:
//=================================

//Test code? No
void rx_cmd_ctrl_i_w(uint8_t *buf, uint8_t *info)
{
	uint16_t index = P_DATA1;
	int16_t tmp_wanted_current = 0, tmp_measured_current = 0;

	tmp_measured_current = (int16_t) REBUILD_UINT16(buf, &index);
	tmp_wanted_current = (int16_t) REBUILD_UINT16(buf, &index);

	(void)info;

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Only change the setpoint if we are in current control mode:
		if(ctrl.active_ctrl == CTRL_CURRENT)
		{
			ctrl.current.setpoint_val = tmp_wanted_current;
		}

	#else

		(void)buf;

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
}

//Test code? No
void rx_cmd_ctrl_i_rw(uint8_t *buf, uint8_t *info)
{
	(void)info;

//Generate the reply:
	//Return (0)
//	numb = tx_cmd_ricnu_w(TX_CMD_DEFAULT, ctrl.active_ctrl);	//ToDo
//	COMM_GEN_STR_DEFAULT
//	flexsea_send_serial_master(myPort, myData, myLen);	//ToDo

}

//Test code? No
void rx_cmd_ctrl_i_rr(uint8_t *buf, uint8_t *info)
{
	uint16_t index = P_DATA1;
	int16_t tmp_wanted_current = 0, tmp_measured_current = 0;

	tmp_measured_current = (int16_t) REBUILD_UINT16(buf, &index);
	tmp_wanted_current = (int16_t) REBUILD_UINT16(buf, &index);

	(void)info;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Store value:
	exec1.current = tmp_measured_current;
	//ToDo shouldn't be exec1!

	#else
		(void)buf;
	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
}

//Transmit Control Open Setpoint:
//===============================

//Transmission of a CTRL_O command
//Test code? No
uint32_t tx_cmd_ctrl_o(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t open_spd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_O);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_O);

		//Arguments:
		uint16_to_bytes(open_spd, &tmp0, &tmp1);
		buf[P_DATA1] = tmp0;
		buf[P_DATA1 + 1] = tmp1;

		bytes = P_DATA1 + 2;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Receive Control Open Setpoint:
//==============================

//Reception of a CTRL_O command
void rx_cmd_ctrl_o(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_open_spd = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_o(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.pwm);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_open_spd = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1], buf[P_DATA1+1]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_MANAGE

			//Store value:
			exec1.ctrl.pwm = tmp_open_spd;

			#endif	//BOARD_TYPE_FLEXSEA_MANAGE

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			#ifdef USE_PRINTF
			printf("Received CMD_CTRL_O. PWM DC = %i.\n", tmp_open_spd);
			#endif	//USE_PRINTF

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			if(ctrl.active_ctrl == CTRL_OPEN)
			{
				motor_open_speed_1(tmp_open_spd);
			}

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmit Control Position Setpoint:
//===================================

//Transmission of a CTRL_P command
uint32_t tx_cmd_ctrl_p(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int32_t pos, int32_t posi, int32_t posf, int32_t spdm, int32_t acc)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_P);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_P);

		//Arguments:
		uint32_to_bytes((uint32_t)pos, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		buf[P_DATA1 + 2] = tmp2;
		buf[P_DATA1 + 3] = tmp3;
		uint32_to_bytes((uint32_t)posi, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;
		buf[P_DATA1 + 6] = tmp2;
		buf[P_DATA1 + 7] = tmp3;
		uint32_to_bytes((uint32_t)posf, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 8] = tmp0;
		buf[P_DATA1 + 9] = tmp1;
		buf[P_DATA1 + 10] = tmp2;
		buf[P_DATA1 + 11] = tmp3;
		uint32_to_bytes((uint32_t)spdm, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 12] = tmp0;
		buf[P_DATA1 + 13] = tmp1;
		buf[P_DATA1 + 14] = tmp2;
		buf[P_DATA1 + 15] = tmp3;
		uint32_to_bytes((uint32_t)acc, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 16] = tmp0;
		buf[P_DATA1 + 17] = tmp1;
		buf[P_DATA1 + 18] = tmp2;
		buf[P_DATA1 + 19] = tmp3;

		bytes = P_DATA1 + 20;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Receive Control Position Setpoint:
//==================================

//Reception of a CTRL_P command
void rx_cmd_ctrl_p(uint8_t *buf)
{
	uint32_t numb = 0;
	int32_t tmp_pos = 0, tmp_posi = 0, tmp_posf = 0, tmp_spdm = 0, tmp_acc = 0;
	int16_t tmp_z_k = 0, tmp_z_b = 0, tmp_z_i = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_p(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.position.pos, ctrl.position.posi, ctrl.position.posf, ctrl.position.spdm, ctrl.position.acc);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_pos = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 0], buf[P_DATA1 + 1], buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_posi = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 4], buf[P_DATA1 + 5], buf[P_DATA1 + 6], buf[P_DATA1 + 7]));
		tmp_posf = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 8], buf[P_DATA1 + 9], buf[P_DATA1 + 10], buf[P_DATA1 + 11]));
		tmp_spdm = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 12], buf[P_DATA1 + 13], buf[P_DATA1 + 14], buf[P_DATA1 + 15]));
		tmp_acc = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 16], buf[P_DATA1 + 17], buf[P_DATA1 + 18], buf[P_DATA1 + 19]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.position.pos = tmp_pos;
			exec1.ctrl.position.posi = tmp_posi;
			exec1.ctrl.position.posf = tmp_posf;
			exec1.ctrl.position.spdm = tmp_spdm;
			exec1.ctrl.position.acc = tmp_acc;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			//ctrl.position.pos = tmp_pos;
			//ctrl.position.posi = tmp_posi;

			ctrl.position.posf = tmp_posf;
			ctrl.position.spdm = tmp_spdm;
			ctrl.position.acc = tmp_acc;

			if(ctrl.active_ctrl == CTRL_POSITION)
			{
				ctrl.position.posi = ctrl.position.setp;
				steps = trapez_gen_motion_1(ctrl.position.posi, ctrl.position.posf, ctrl.position.spdm, ctrl.position.acc = tmp_acc);
			}
			else if(ctrl.active_ctrl == CTRL_IMPEDANCE)
			{
				//Backup gains
				tmp_z_k = ctrl.impedance.gain.Z_K;
				tmp_z_b = ctrl.impedance.gain.Z_B;
				tmp_z_i = ctrl.impedance.gain.Z_I;

				//Zero them
				ctrl.impedance.gain.Z_K = 0;
				ctrl.impedance.gain.Z_B = 0;
				ctrl.impedance.gain.Z_I = 0;

				//New trajectory
				ctrl.position.posi = ctrl.impedance.setpoint_val;
				steps = trapez_gen_motion_1(ctrl.position.posi, ctrl.position.posf, ctrl.position.spdm, ctrl.position.acc = tmp_acc);


				//Restore gains
				ctrl.impedance.gain.Z_K = tmp_z_k;
				ctrl.impedance.gain.Z_B = tmp_z_b;
				ctrl.impedance.gain.Z_I = tmp_z_i;
			}


			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmit Control Current Gains:
//===============================

//Transmission of a CTRL_I_G command
uint32_t tx_cmd_ctrl_i_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_I_G);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_I_G);

		//Arguments:
		uint16_to_bytes((uint16_t)kp, &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)ki, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)kd, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;


		bytes = P_DATA1 + 6;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Receive Control Current Gains:
//==============================

//Reception of a CTRL_I_G command
void rx_cmd_ctrl_i_g(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_kp = 0, tmp_ki = 0, tmp_kd = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_i_g(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.current.gain.I_KP, ctrl.current.gain.I_KI, ctrl.current.gain.I_KD);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_kp = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 0], buf[P_DATA1 + 1]));
		tmp_ki = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_kd = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 4], buf[P_DATA1 + 5]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.current.gain.I_KP = tmp_kp;
			exec1.ctrl.current.gain.I_KI = tmp_ki;
			exec1.ctrl.current.gain.I_KD = tmp_kd;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			ctrl.current.gain.I_KP = tmp_kp;
			ctrl.current.gain.I_KI = tmp_ki;
			ctrl.current.gain.I_KD = tmp_kd;
			//ToDo: do we need to call something?

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmit Control Position Gains:
//================================

//Transmission of a CTRL_P_G command
uint32_t tx_cmd_ctrl_p_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_P_G);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_P_G);

		//Arguments:
		uint16_to_bytes((uint16_t)kp, &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)ki, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)kd, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;


		bytes = P_DATA1 + 6;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Receive Control Position Gains:
//===============================

//Reception of a CTRL_P_G command
void rx_cmd_ctrl_p_g(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_kp = 0, tmp_ki = 0, tmp_kd = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_p_g(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.position.gain.P_KP, ctrl.position.gain.P_KI, ctrl.position.gain.P_KD);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_kp = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 0], buf[P_DATA1 + 1]));
		tmp_ki = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_kd = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 4], buf[P_DATA1 + 5]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.position.gain.I_KP = tmp_kp;
			exec1.ctrl.position.gain.I_KI = tmp_ki;
			exec1.ctrl.position.gain.I_KD = tmp_kd;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			ctrl.position.gain.P_KP = tmp_kp;
			ctrl.position.gain.P_KI = tmp_ki;
			ctrl.position.gain.P_KD = tmp_kd;
			//ToDo: do we need to call something?

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmit Control Impedance Gains:
//=================================

//Transmission of a CTRL_Z_G command
uint32_t tx_cmd_ctrl_z_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t zk, int16_t zb, int16_t zi)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_Z_G);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_Z_G);

		//Arguments:
		uint16_to_bytes((uint16_t)zk, &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)zb, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)zi, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;


		bytes = P_DATA1 + 6;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Receive Control Impedance Gains:
//================================

//Reception of a CTRL_Z_G command
void rx_cmd_ctrl_z_g(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_zk = 0, tmp_zb = 0, tmp_zi = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_z_g(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.impedance.gain.Z_K, ctrl.impedance.gain.Z_B, ctrl.impedance.gain.Z_I);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_zk = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 0], buf[P_DATA1 + 1]));
		tmp_zb = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_zi = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 4], buf[P_DATA1 + 5]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.impedance.gain.Z_K = tmp_zk;
			exec1.ctrl.impedance.gain.Z_B = tmp_zb;
			exec1.ctrl.impedance.gain.Z_I = tmp_zi;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			ctrl.impedance.gain.Z_K = tmp_zk;
			ctrl.impedance.gain.Z_B = tmp_zb;
			ctrl.impedance.gain.Z_I = tmp_zi;
			//ToDo: do we need to call something?

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmit In Control Command:
//============================

//Transmission of an IN_CONTROL command
//Note: we can only write one parameter at the time (that's what we need for typical use cases).
//'select_w' will determine what variable is written.
uint32_t tx_cmd_in_control(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, uint8_t select_w)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_IN_CONTROL);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_IN_CONTROL);

		//Arguments:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		buf[P_DATA1 + 1] = select_w; //Parameter written
		uint32_to_bytes((uint32_t)in_control.w[select_w], &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 1] = tmp0;
		buf[P_DATA1 + 2] = tmp1;
		buf[P_DATA1 + 3] = tmp2;
		buf[P_DATA1 + 4] = tmp3;

		uint32_to_bytes((uint32_t)in_control.setp, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 5] = tmp0;
		buf[P_DATA1 + 6] = tmp1;
		buf[P_DATA1 + 7] = tmp2;
		buf[P_DATA1 + 8] = tmp3;

		uint32_to_bytes((uint32_t)in_control.actual_val, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 9] = tmp0;
		buf[P_DATA1 + 10] = tmp1;
		buf[P_DATA1 + 11] = tmp2;
		buf[P_DATA1 + 12] = tmp3;

		uint32_to_bytes((uint32_t)in_control.error, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 13] = tmp0;
		buf[P_DATA1 + 14] = tmp1;
		buf[P_DATA1 + 15] = tmp2;
		buf[P_DATA1 + 16] = tmp3;

		uint16_to_bytes((uint16_t)in_control.output, &tmp0, &tmp1);
		buf[P_DATA1 + 17] = tmp0;
		buf[P_DATA1 + 18] = tmp1;

		//Combine 3 fields in 1 uint16:
		in_control_get_pwm_dir();
		in_control_combine();
		uint16_to_bytes((uint16_t)in_control.combined, &tmp0, &tmp1);
		buf[P_DATA1 + 19] = tmp0;
		buf[P_DATA1 + 20] = tmp1;

		uint16_to_bytes((uint16_t)ctrl.current.actual_val, &tmp0, &tmp1);
		buf[P_DATA1 + 21] = tmp0;
		buf[P_DATA1 + 22] = tmp1;

		//User fields:
		uint32_to_bytes((uint32_t)in_control.r[0], &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 23] = tmp0;
		buf[P_DATA1 + 24] = tmp1;
		buf[P_DATA1 + 25] = tmp2;
		buf[P_DATA1 + 26] = tmp3;
		uint32_to_bytes((uint32_t)in_control.r[1], &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 27] = tmp0;
		buf[P_DATA1 + 28] = tmp1;
		buf[P_DATA1 + 29] = tmp2;
		buf[P_DATA1 + 30] = tmp3;

		bytes = P_DATA1 + 31;     //Bytes is always last+1

		#endif //BOARD_TYPE_FLEXSEA_EXECUTE

		#ifdef BOARD_TYPE_FLEXSEA_PLAN

		buf[P_DATA1 + 0] = select_w; //Parameter written
		uint32_to_bytes((uint32_t)in_control_1.w[select_w], &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 1] = tmp0;
		buf[P_DATA1 + 2] = tmp1;
		buf[P_DATA1 + 3] = tmp2;
		buf[P_DATA1 + 4] = tmp3;

		bytes = P_DATA1 + 5;     //Bytes is always last+1

		#endif  //BOARD_TYPE_FLEXSEA_PLAN
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Receive In Control Command:
//===========================

//Reception of an IN_CONTROL command
void rx_cmd_in_control(uint8_t *buf)
{
	uint8_t numb = 0, w_select = 0;
	int32_t w_val = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_in_control(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#ifdef USE_USB
		usb_puts(comm_str_485_1, (numb));
		#endif

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		w_select = buf[P_DATA1];
		w_val = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 1], buf[P_DATA1 + 2], buf[P_DATA1 + 3], buf[P_DATA1 + 4]));

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			in_control_1.setp = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 5], buf[P_DATA1 + 6], buf[P_DATA1 + 7], buf[P_DATA1 + 8]));
			in_control_1.actual_val = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 9], buf[P_DATA1 + 10], buf[P_DATA1 + 11], buf[P_DATA1 + 12]));

			in_control_1.error = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 13], buf[P_DATA1 + 14], buf[P_DATA1 + 15], buf[P_DATA1 + 16]));
			in_control_1.output = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 17], buf[P_DATA1 + 18]));

			in_control_1.combined = (BYTES_TO_UINT16(buf[P_DATA1 + 19], buf[P_DATA1 + 20]));
			in_control_1.current = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 21], buf[P_DATA1 + 22]));

			in_control_1.r[0] = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 23], buf[P_DATA1 + 24], buf[P_DATA1 + 25], buf[P_DATA1 + 26]));
			in_control_1.r[1] = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 27], buf[P_DATA1 + 28], buf[P_DATA1 + 29], buf[P_DATA1 + 30]));

			in_control_1.controller = IN_CONTROL_CONTROLLER(in_control_1.combined);
			in_control_1.mot_dir = IN_CONTROL_MOT_DIR(in_control_1.combined);
			in_control_1.pwm = IN_CONTROL_PWM(in_control_1.combined);

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			in_control.w[w_select] = w_val;

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

#ifdef __cplusplus
}
#endif
