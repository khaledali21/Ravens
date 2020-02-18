#include "STD_TYPES.h"
#include "UTILS.h"
#include "Constants.h"
#include "quickmath.h"
#include "Blocks.h"
/* Implementation of Controller blocks
 * This part consists of an Inner loop and an Outer loop.
 * The inner loop consists of: Body rate, roll pitch and yaw controller.
 * The outer loop consists of: altitude control and lateral control
 * Body rate: 	Inputs 	= 	p, q, r, p_cmd, q_cmd, r_cmd
 * 				outputs	= 	Moments u2, u3, u4
 *
 * Roll pitch:	Inputs 	= 	U1 (Thrust force), x_dot_dot_cmd, y_dot_dot_cmd, phi, theta, psi
 * 				outputs	=	p_cmd, q_cmd
 *
 * Yaw:			Inputs 	= 	psi_cmd, psi
 * 				outputs	=	r_cmd
 *
 * Altitude:	Inputs 	= 	z, z_dot, phi, theta, psi, z_cmd, z_dot_cmd
 * 				outputs	=	U1 (Thrust force)
 *
 * Lateral:		Inputs 	= 	x, y, x_dot, y_dot, x_cmd, y_cmd, x_dot_cmd, y_dot_cmd, phi, theta, psi
 * 				outputs	= 	x_dot_dot_cmd, y_dot_dot_cmd
 *
 *
 */
void body_rates(void *pt)
{	parameters *ptr=pt;
	while(1)
	{f32 p_error,q_error,r_error;
	p_error = ptr->p_cmd - ptr->p;
	q_error = ptr->q_cmd - ptr->q;
	r_error = ptr->r_cmd - ptr->r;
	ptr->p_dot = kp_rate * p_error;
	ptr->q_dot = kp_rate * q_error;
	ptr->r_dot = kp_rate * r_error;
	ptr->u2 = Ixx * ptr->p_dot;
	ptr->u3 = Iyy * ptr->q_dot;
	ptr->u4 = Izz * ptr->r_dot;
	vTaskDelay(1);
	}
}
void roll_pitch(void *pt)
{
	parameters * ptr = pt;
	while(1)
	{f32 dt = 0.001, b_x_dot_cmd, b_y_dot_cmd, taw=1/kp_bank;
	f32 R11 = 1;
	f32 R12 = sine(ptr->phi) * sine(ptr->theta) / cosine(ptr->theta);
	f32 R13= cosine(ptr->phi) * sine(ptr->theta) / cosine(ptr->theta);
	f32 R21 = 0;
	f32 R22 = cosine(ptr->phi);
	f32 R23= -sine(ptr->phi);
	f32 R31 = 0;
	f32 R32 = sine(ptr->phi) / cosine(ptr->theta);
	f32 R33 = cosine(ptr->phi) / cosine(ptr->theta);
	f32 R13_cmd= ptr->x_dot_dot_cmd*m/ptr->u1;
	f32 R23_cmd= ptr->y_dot_dot_cmd*m/ptr->u1;

	/*ptr->phi_dot = ptr->p + ptr->q * R12 + ptr->r * R13;
    ptr->theta_dot = ptr->q * R22 - ptr->r * R23;
    ptr->psi_dot = ptr-> q * R32 + ptr->r * R33;
    ptr->phi += ptr->phi_dot * dt;
    ptr->theta += ptr->theta_dot * dt;
    ptr->psi += ptr->psi_dot * dt;
*/
    b_x_dot_cmd= (R13-R13_cmd)/taw;
    b_y_dot_cmd= (R23-R23_cmd)/taw;

    ptr->p_cmd = 1/R33 * (R21*b_x_dot_cmd - R11*b_y_dot_cmd);
    ptr->q_cmd = 1/R33 * (R22*b_x_dot_cmd - R12*b_y_dot_cmd);
	vTaskDelay(1);

	}
}
void yaw_controller(void *pt)
{
	parameters* ptr= pt;
	while(1)
	{ptr->r_cmd = kp_rate*(ptr->psi_cmd - ptr->psi);
	vTaskDelay(100);

	}
}
void altitude_controller(void *pt)
{
	parameters* ptr= pt;
	while(1)
	{f32 R33 = cosine(ptr->phi)/cosine(ptr->theta);
	ptr->z_dot_dot_cmd= kp_rate*(ptr->z_cmd- ptr->z) + kd*(ptr->z_dot_cmd-ptr->z_dot);

	ptr->u1 = m* (ptr->z_dot_dot_cmd - g)/R33;
	vTaskDelay(100);
	}
}
void lateral_controller(void *pt)
{
	parameters* ptr= pt;
	while(1)
	{
	ptr->x_dot_dot_cmd= kp_rate*(ptr->x_cmd- ptr->z) + kd*(ptr->x_dot_cmd-ptr->x_dot);
	ptr->y_dot_dot_cmd= kp_rate*(ptr->y_cmd- ptr->z) + kd*(ptr->y_dot_cmd-ptr->y_dot);
	vTaskDelay(100);
	}
}
