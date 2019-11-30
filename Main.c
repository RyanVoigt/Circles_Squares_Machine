float const SPEED = 5;
float const TIME = 10;
float const ENCODER = 10;
float AENCODE(float x)
{
	int encode;
	encode = x*(360/((2*PI)*(2.1));
	return encode;
}
void TRAY_READPOSITION()
{
	motor[motorA]= SPEED;
	wait1Msec(TIME);
	motor[motorA] = 0;
}

bool CSENSOR_READ(int *Board, int arrayvalue, int arraynum)
{
	if(SensorValue[S2] == (int)colorBlue)
		//if spot has not been filled yet
		if(arrayvalue == 0)
		{
			//fill it and return a true
			Board[arraynum] = 1;
			return true;
		}
		else
			return false;
	return 0;
}

 bool TRAY_READ(int *Board, int *have)
{
	int i = 0;
	int q = 0;
	int SPEED = -SPEED;
	bool found = false;
	for(; q<=2 || !found; q++)
	{
	// switches direction of movement
		SPEED = SPEED*-1;
		for(; i<=2 || found == false; i++)
		{
			//movning the robot to the 3 squares and checking for read
			//HAS TO START IN INTIAL SQUARE
			int space = 0;
			space = i+q;
			//scanning square for colour
			found = CSENSOR_READ(Board, Board[space], space);
			if (i < 2)
			{
			motor[motorB]= SPEED;
			wait1Msec(TIME);
			motor[motorB] = 0;
			}

		}
		//moving tray to the 3 set read postions
		motor[motorA]= SPEED;
		wait1Msec(TIME);
		motor[motorA] = 0;
	}
	have[0] = i;
	have[1] = q;
	return true;
}
//moving arm across board to the 3 set spots

// moving board itself
void Y_Move (int y, int *have)
{
	float travel = 0;
	float encodeBlock = ENCODER;
	int direction = 1;
	int Ydist = abs(have[1] - y);
	if(have[1] > y)
		direction *= -1;
	travel = Ydist*direction*encodeBlock;
	nMotorEncoder[motorA] = 0;
		while (nMotorEncoder[motorA] <= travel)
		{
			motor[motorB] = 40;
		}
		motor[motorB] = 0;
}

void X_Move (int x, int *have)
{
	float travel = 0;
	float encodeBlock = AENCODE(4);
	int direction = 1;
	int Ydist = abs(have[1] - x);
	if(have[1] > x)
		direction *= -1;
	travel = Ydist*direction*encodeBlock;
	nMotorEncoder[motorB] = 0;
		while (nMotorEncoder[motorB] <= travel)
		{
			motor[motorB] = 40;
		}
		motor[motorB] = 0;
}
void DRAW()
{
	motor[motorC] = 10;
	wait1Msec(TIME);
	motor[motorC] = 0;
	motor[motorA]= SPEED;
	wait1Msec(TIME);
	motor[motorA] = 0;
	motor[motorA]= -SPEED;
	wait1Msec(TIME);
	motor[motorA] = 0;
	motor[motorC] = -10;
	wait1Msec(TIME);
	motor[motorC] = 0;
}
void RESETLOCATION()
{
	while(SensorValue[S2]==false)
		{
			motor[motorB] = 100;
		}
		motor[motorB] = 0;
	while(SensorValue[S3]==false)
		{
			motor[motorA] = 100;
		}
			motor[motorA] = 0;
}
void READBOARD(int *Board, int *have)
{
	have[1] = 0;
	TRAY_READPOSITION();
	TRAY_READ(Board, have);
}
void DISPLAYWIN(bool win)
{
	RESETLOCATION();
	if (win == true)
		displayBigTextLine(2, "                 ROBOT WINS!");
	else
		displayBigTextLine(2, "                     TIE");

	displayBigTextLine(4, "         WOULD YOU LIKE TO PLAY AGAIN");
	displayBigTextLine(6, "YES                                         NO");
}
bool PLAYAGAIN()
{

	while (!getButtonPress(buttonLeft) || !getButtonPress(buttonRight))
	{}
	if(getButtonPress(buttonLeft) == true)
	{
		return true;
	}
	else if(getButtonPress(buttonRight) == true)
	{
		return false;
	}
	return 0;
}

bool MAIN_FINAL(bool win)
{
	DISPLAYWIN(win);
	bool play = PLAYAGAIN();
	if (play == true)
		return true;
	else
		return false;
}
void WELCOMEDISPLAY
void MAIN_CONTROL(int *Board, int x, int y, int *have)
{
	Y_MOVE(y, have);
	X_MOVE(x, have);
	DRAW();
	RESETLOCATION();
	//YOU WILL NEED TO GIVE IN X VALUE 0 or 1 or 2
	//AND Y VALUES 0 or 1 or 2
}
task main()
{
int have[2];
have[0] = 0;
have[1] = 1;
X_Move(2,have);

}
	
