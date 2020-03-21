/*
 * estimation.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Khaled Ali
 */

#include "STD_TYPES.h"
#include "imu6050.h"
#include "quickmath.h"
//#include "Constants.h"
	f32 ekfcov[7][7], hprimegps[6][7], hprimeMag[7] = {0},  R_GPS[6][6],Q_load[7][7], R_mag, dt = 0.001, toinvert[12][12], K[7][6], gprime[7][7] = {0};
	f32 z[6], zfromX[6];
void init_EKF(void)
{
	ekfcov[0][0] = 0.01;;
	ekfcov[1][1] = 0.01;;
	ekfcov[2][2] = 0.09;
	ekfcov[3][3] = 0.01;;
	ekfcov[4][4] = 0.01;;
	ekfcov[5][5] = 0.09;
	ekfcov[6][6] = 0.0025;
	R_GPS[0][0] = 1;
	R_GPS[1][1] = 1;
	R_GPS[2][2] = 90000; //we'll see
	R_GPS[3][3] = 0.01;
	R_GPS[4][4] = 0.01;
	R_GPS[5][5] = 0.09;
	Q_load[0][0] = 0.0025 * dt;
	Q_load[1][1] = 0.0025 * dt;
	Q_load[2][2] = 0.0025 * dt;
	Q_load[3][3] = 0.04 * dt;
	Q_load[4][4] = 0.04 * dt;
	Q_load[5][5] = 0.01 * dt;
	Q_load[6][6] = 0.0064 * dt;
	R_mag = 0.01;
}
void update_IMU(parameters *ptr)
{
	bodyrate * gyro;
	accel * acc;
	//Read_IMU_Values(acc, gyro);
	Read_Gyro_Values(gyro);
	Read_Accel_Values(acc);
	f32 dt = 0.001; f32 taw=1;
		f32 R11 = 1;
		f32 R12 = sin(ptr->phi) * sin(ptr->theta) / cos(ptr->theta);
		f32 R13= cos(ptr->phi) * sin(ptr->theta) / cos(ptr->theta);
		f32 R21 = 0;
		f32 R22 = cos(ptr->phi);
		f32 R23= -sin(ptr->phi);
		f32 R31 = 0;
		f32 R32 = sin(ptr->phi) / cos(ptr->theta);
		f32 R33 = cos(ptr->phi) / cos(ptr->theta);
		ptr->phi_dot = ptr->p + ptr->q * R12 + ptr->r * R13;
	    ptr->theta_dot = ptr->q * R22 - ptr->r * R23;
	    ptr->psi_dot = ptr-> q * R32 + ptr->r * R33;
	    f32 predictedphi = ptr->phi + ptr->phi_dot * dt;
	    f32 predictedtheta = ptr->theta + ptr->theta_dot * dt;
	    ptr->psi += ptr->psi_dot * dt;
	    if(ptr->psi > 180)
	    	ptr->psi -= 360;
	    if(ptr->psi < -180)
	    	ptr->psi += 360;
	    f32 accelPhi = arctan(acc->y/acc->z);
	    f32 acceltheta = arctan(-acc->y/9.812);
	    ptr->phi = (taw/(taw + dt))* predictedphi + (dt/(taw + dt)) * accelPhi;
	    ptr->theta = (taw/(taw + dt))* predictedtheta + (dt/(taw + dt)) * acceltheta;
	    //................
	    ptr->x_dot_dot = acc->x;
	    ptr->y_dot_dot = acc->y;
	    ptr->z_dot_dot = acc->z;

}

void predicstate(parameters *ptr)
{	f32 dt = 0.001;
	f32 euler[3]={ptr->phi, ptr->theta, ptr->psi};
	f32 q[4];
	Quaternion(q,euler);
	f32 acc[3] = {ptr->x_dot_dot, ptr->y_dot_dot, ptr->z_dot_dot};
	Rotate_BtoW(acc, q);

	ptr->x += dt * ptr->x_dot;
	ptr->y += dt * ptr->y_dot;
	ptr->z += dt * ptr->z_dot;
	ptr->x_dot += dt * acc[0];
	ptr->y_dot += dt * acc[1];
	ptr->z_dot += dt * acc[2] - dt * 9.812;
	zfromX[0] = ptr->x;
	zfromX[1] = ptr->y;
	zfromX[2] = ptr->z;
	zfromX[3] = ptr->x_dot;
	zfromX[4] = ptr->y_dot;
	zfromX[5] =	ptr->z_dot;
}

void predict(parameters *ptr)
{ 		f32 dt = 0.01;

	  f32 cosTheta = cos(ptr->theta);
	  f32 sinTheta = sin(ptr->theta);

	  f32 cosPhi = cos(ptr->phi);
	  f32 sinPhi = sin(ptr->phi);

	  f32 sinPsi = sin(ptr->psi);
	  f32 cosPsi = cos(ptr->psi);
	f32 Rprime00 =  - cosTheta * sinPsi;
	f32 Rprime01 =- sinPhi  * sinTheta * sinPsi - cosTheta * cosPsi;
	f32 Rprime02 = - cosPhi  * sinTheta * sinPsi + sinPhi   * cosPsi;
	f32 Rprime10 = cosTheta * cosPsi;
	f32 Rprime11 = sinPhi  * sinTheta * cosPsi - cosPhi * sinPsi;
	f32 Rprime12 = cosPhi  * sinTheta * cosPsi + sinPhi * sinPsi;

	gprime[0][3] = dt;
	gprime[1][4] = dt;
	gprime[2][5] = dt;
	gprime[3][6] = (Rprime00 * ptr->x_dot_dot + Rprime01 * ptr->y_dot_dot + Rprime02 * ptr->z_dot_dot) * dt;
	gprime[4][6] = (Rprime10 * ptr->x_dot_dot + Rprime11 * ptr->y_dot_dot + Rprime12 * ptr->z_dot_dot) * dt;
	gprime[5][6] = 0;
	for (int i = 0; i<7; i++)
		gprime[i][i] = 1;
	f32 gprimeT[7][7];
	for (int i=0;i<7;i++)
		for(int j=0; j<7; j++)
			gprimeT[i][j]=gprime[j][i];
	f32 ekfcovnew1[7][7];
	f32 ekfcovnew2[7][7];
	f32 sum=0;
	for (int i=0;i<7;i++){
		for (int j=0; j<7;j++){
			for (int k=0; k<7;k++){
				sum = sum + gprime[i][k] * ekfcov[k][j];
			}
			ekfcovnew1[i][j] = sum;
			sum = 0;
		}
	}
	for (int i=0;i<7;i++){
		for (int j=0; j<7;j++){
			for (int k=0; k<7;k++){
				sum = sum + ekfcovnew1[i][k] * gprimeT[k][j];
			}
			ekfcovnew2[i][j] = sum;
			sum = 0;
		}
	}
	for (int i=0;i<7;i++)
		for (int j=0;j<7;j++)
			ekfcov[i][j] = ekfcovnew2[i][j] + Q_load[i][j];
}
void updatefromGps(void *p)
{
	parameters *ptr = p;
	accel *position;
	accel *velocity;
	u8 fix;
	f32 hprimegpsT[7][6];
	fix = GPS_Read(position, velocity);
	if (fix == 3)
	{
		z[0] = position-> x;
		z[1] = position-> y;
		z[2] = position-> z;
		z[3] = velocity-> x;
		z[4] = velocity-> y;
		z[5] = velocity-> z;
		for (int i =0; i<6; i++)
			hprimegps[i][i] = 1;
		for (int i=0;i<7;i++)
			for(int j=0; j<7; j++)
				hprimegpsT[i][j]=hprimegps[j][i];
		f32 sum=0;
		f32 temp1[6][7];
		f32 temp2[6][6];
		f32 temp3[7][6];
		f32 temp4[7], temp5[7][7], temp6[7][7];
		for (int i=0;i<6;i++){
			for (int j=0; j<7;j++){
				for (int k=0; k<7;k++){
					sum = sum + hprimegps[i][k] * ekfcov[k][j];
				}
				temp1[i][j] = sum;
				sum = 0;
			}
		}
		for (int i=0;i<6;i++){
			for (int j=0; j<6;j++){
				for (int k=0; k<7;k++){
					sum = sum + temp1[i][k] * hprimegpsT[k][j];
				}
				temp2[i][j] = sum;
				sum = 0;
			}
		}
		for (int i=0;i<6;i++)
			for (int j=0;j<6;j++)
				toinvert[i][j] = temp2[i][j] + R_GPS[i][j];

		matrix_inverse();
		for (int i=0;i<7;i++){
			for (int j=0; j<6;j++){
				for (int k=0; k<7;k++){
					sum = sum + ekfcov[i][k] * hprimegpsT[k][j];
				}
				temp3[i][j] = sum;
				sum = 0;
			}
		}
		for (int i=0;i<7;i++){
			for (int j=0; j<6;j++){
				for (int k=0; k<6;k++){
					sum = sum + temp3[i][k] * toinvert[6+k][j];
				}
				K[i][j] = sum;
				sum = 0;
			}
		}
		for (int i=0;i<7;i++){
			for (int j=0; j<1;j++){
				for (int k=0; k<6;k++){
					sum = sum + K[i][k] *(z[k] - zfromX[k]);
				}
				temp4[i] = sum;
				sum = 0;
			}
		}

		ptr->x += temp4[0];
		ptr->y += temp4[1];
		ptr->z += temp4[2];
		ptr->x_dot += temp4[3];
		ptr->y_dot += temp4[4];
		ptr->z_dot += temp4[5];
		for (int i=0;i<7;i++){
			for (int j=0; j<7;j++){
				for (int k=0; k<6;k++){
					sum = sum + K[i][k] * hprimegps[k][j];
				}
				if (i == j)
				temp5[i][j] = 1 - sum;
				else
					temp5[i][j] = -1 * sum;
				sum = 0;
			}
		}
		for (int i=0;i<7;i++){
			for (int j=0; j<7;j++){
				for (int k=0; k<7;k++){
					sum = sum + temp5[i][k] * ekfcov[k][j];
				}
				temp6[i][j] = sum;
				sum = 0;
			}
		}
		for (int i=0;i<7;i++)
			for (int j=0; j<7;j++)
				ekfcov[i][j] = temp6[i][j];
	}

}

void updatefromMag(void *p)
{
	parameters *ptr = p;
	f32 z_mag, zfromX_mag = ptr -> psi;
	f32 diff = z_mag - zfromX_mag;
	if (diff > 180)
		zfromX_mag += 360;
	else if ( diff < -180)
		zfromX_mag -= 360;
	hprimeMag[6] = 1;
	f32 temp1[7], temp2, temp3[7][7], temp4[7][7];
	f32 sum=0;
		for (int j=0; j<7;j++){
			for (int k=0; k<7;k++){
				sum = sum + hprimeMag[k]*ekfcov[k][j];
			}
			temp1[j] = sum;
			sum = 0;
		}

		for (int i =0; i<7; i++)
			sum += temp1[i] * hprimeMag[i];
		temp2 = sum;
		sum = 0;
		temp2 += R_mag;
		temp2 = 1/temp2;
		for (int j=0; j<7;j++){
			for (int k=0; k<7;k++){
				sum = sum + ekfcov[j][k] * hprimeMag[k];
			}
			temp1[j] = sum * temp2;
			sum = 0;
		}
		ptr->psi = ptr->psi + temp1[6] * (zfromX_mag - z_mag);
		for (int i=0;i<7;i++){
			for (int j=0; j<j;j++){
					if (i == j)
						temp3[i][j] = 1 - temp1[i] * hprimeMag[j];
					else
						temp3[i][j] = -1 * temp1[i] * hprimeMag[j];
			}
		}
		for (int i=0;i<7;i++){
			for (int j=0; j<7;j++){
				for (int k=0; k<7;k++){
					sum = sum + temp3[i][k] * ekfcov[k][j];
				}
				temp4[i][j] = sum;
				sum = 0;
			}
		}
		for (int i=0;i<7;i++)
			for (int j=0;j<7;j++)
				ekfcov[i][j] = temp4[i][j];

}
