/****************************************************************************************
* Copyright 2025 Gerben den Hartog
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************************/
/****************************************************************************************
* File:         ATAN2_Approx.c
* Author:       Gerben den Hartog
* Created on:   20-02-2026
****************************************************************************************/
/*********************************************************************************************
                                    INCLUDES
*********************************************************************************************/
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

/*********************************************************************************************
                                    LOCAL PROTOTYPES
*********************************************************************************************/
int32_t Calculate_Angle(int16_t Z_Axis, int16_t X_Axis);

/*
Function to calculate an angle in degrees

Based on apporimation of TAN where TAN < 1.

*/
int32_t Calculate_Angle(int16_t Z_Axis, int16_t X_Axis)
{
	double Tan_x, Angle, result;
	int16_t x_abs = abs(X_Axis);
	int16_t z_abs = abs(Z_Axis);
	int32_t	Current_Angle;

	//Check for Zero to prevent divide by zero
	if(Z_Axis == 0 || X_Axis == 0)
	{
		if(Z_Axis == 0)
		{
			if(X_Axis > 0)
			{
				Current_Angle = 90;
			}
			else
			{
				Current_Angle = -90;
			}
		}
		else
		{
			if(Z_Axis > 0)
			{
				Current_Angle = 0;
			}
			else
			{
				Current_Angle = 180;
			}

		}

		return Current_Angle;
	}

	//Check if result will be bigger than 1
	if(x_abs <= z_abs)
	{
		Tan_x = (double)x_abs / (double)z_abs;
	}
	else
	{
		Tan_x = (double)z_abs / (double)x_abs;
	}

	//Calculate angle using tan approximation
	Angle = Tan_x*(45.0 - (Tan_x - 1.0)*(14.0 + 3.83* Tan_x));

	//Cast round and cast angle to an int32 representing the angle in .01 degrees
	Current_Angle = lrint(Angle * 100);


	/* Determine offset of the calculated angle
	 * The tan approximation only covers numbers between 0 and 1 so to make a full circle from -180 degrees to 180 degrees
	 * some calculations need to be done.
	 * If Z_axis is < 0 the camera is pointing upward otherwise the camera is pointing downward*/
	if(x_abs <= z_abs)
	{
		if(Z_Axis > 0)
		{
			if(X_Axis > 0)
			{
				//Nothing happens here angle is angle
			}
			else
			{
				//Flip angle
				Angle = -Angle;
				Current_Angle = -Current_Angle;
			}
		}
		else
		{
			if(X_Axis > 0)
			{
				Angle = 180 - Angle;
				Current_Angle = 18000 - Current_Angle;
			}
			else
			{
				//Flip angle
				Angle = -(180 - Angle);
				Current_Angle = -(18000 - Current_Angle);
			}
		}

	}
	else
	{
		if(Z_Axis > 0)
		{
			if(X_Axis > 0)
			{
				Angle = 90 - Angle;
				Current_Angle = 9000 - Current_Angle;
			}
			else
			{
				//Flip angle
				Angle = -(90 - Angle);
				Current_Angle = -(9000 - Current_Angle);
			}
		}
		else
		{
			if(X_Axis> 0)
			{
				Angle = 90 + Angle;
				Current_Angle = 9000 + Current_Angle;
			}
			else
			{
				//Flip angle
				Angle = -(90 + Angle);
				Current_Angle = -(9000 + Current_Angle);
			}
		}

	}
	
	return Current_Angle;

}

