void TRAY_READPOSITION(bool x)
{
	if (x ==false)
	{
		motor[motorA]= SPEED;
		wait1Msec(TIME);
		motor[motorA] = 0;
	}
	else if ( x ==true)
	{	
		motor[motorA]= SPEED;
		wait1Msec(TIME);
		motor[motorA] = 0;
	}
}
bool CSENSOR_READ(int Board[] int arrayvalue, int arraynum)
{
	if(SensorValue[S2] == (int)colorRed)
		//if spot has not been filled yet
		if(arraynum = 0)
		{
			//fill it and return a ture
			Board[arraynum] = 1;
			return(true);
		}
	else
		return(false)
	
}
bool TRAY_READ(int Board[])
{
	int i = 0
	bool found = false
	while(int q = 0; q<=2 || found ==false)
	{		
		while (int i = 0; i<=3 || found == false)
		{
			//movning the robot to the 3 squares and checking for read
			motor[motorB]= SPEED;
			wait1Msec(TIME);
			motor[motorB] = 0;
			int space = 0;
			space = i+q
			//scanning square for colour
			found = CSENSOR_READ(Board[], Board[space], space)	
		}
		//button sensor
			while(SensorValue[S2]==false)
			{
				motor[motorB] = 100;
			}
			motor[motorB] = 0;
		//moving tray to the 3 set read postions
		motor[motorA]= SPEED;
		wait1Msec(TIME);
		motor[motorA] = 0;
	}
}

void TRAY_DRAW(int spot)
{
	
}
