#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
void rotateX(double t, double x, double y, double z, double & x2, double & y2, double &z2);
void rotateY(double t, double x, double y, double z, double & x2, double & y2, double & z2);
void rotateZ(double t, double x, double y, double z, double & x2, double & y2, double & z2);
void getKey(char & c, int & fkey);
void doCommand(char c, int fkey);
void init();
void clearPage();
void drawPage();
int cmx, cmy, contuneP = 1, color, xDeg = 0, yDeg = 0, zDeg = 0;
double scale = 1.0;
double P = 3.14159265358979323846264338;
double tempDots[128][3];
int length = 30;
int NOR/*Number of rotates*/ = 0,accuracy=0;
int rotates[10000];
double tdot[128][3];
int dots[128][3] =
{
	{ 0,18,0 },{ -5,17,0 },{ -7,22,0 },{ -8,14,0 },{ -12,11,0 },{ -24,12,0 },{ -32,14,0 },{ -36,19,0 },{ -38,25,0 },
	{ -118,24,0 },{ -112,22,0 },{ -104,21,0 },{ -96,19,0 },{ -88,15,0 },{ -82,10,0 },{ -79,0,0 },{ -78,-6,0 },{ -78,-9,0 },{ -80,-13,0 },{ -72,-12,0 },{ -64,-12,0 },{ -56,-12,0 },
	{ -48,-13,0 },{ -40,-13,0 },{ -32,-14,0 },{ -25,-16,0 },{ -18,-17,0 },{ -14,-18,0 },{ -8,-22,0 },{ -5,-26,0 },{ -3,-30,0 },{ -2,-33,0 },{ 0,-36,0 } /* end left and center & z=0*/

	,{ 5,17,0 },{ 7,22,0 },{ 8,14,0 },{ 12,11,0 },{ 24,12,0 },{ 32,14,0 },{ 36,19,0 },{ 38,25,0 },
	{ 118,24,0 },{ 112,22,0 },{ 104,21,0 },{ 96,19,0 },{ 88,15,0 },{ 82,10,0 },{ 79,0,0 },{ 78,-6,0 },{ 78,-9,0 },{ 80,-13,0 },{ 72,-12,0 },{ 64,-12,0 },{ 56,-12,0 },
	{ 48,-13,0 },{ 40,-13,0 },{ 32,-14,0 },{ 25,-16,0 },{ 18,-17,0 },{ 14,-18,0 },{ 8,-22,0 },{ 5,-26,0 },{ 3,-30,0 },{ 2,-33,0 } /*end right & z=0*/

	,{ 0,18,length },{ -5,17,length },{ -7,22,length },{ -8,14,length },{ -12,11,length },{ -24,12,length },{ -32,14,length },{ -36,19,length },{ -38,25,length },
	{ -118,24,length },{ -112,22,length },{ -104,21,length },{ -96,19,length },{ -88,15,length },{ -82,10,length },{ -79,0,length },{ -78,-6,length },{ -78,-9,length },{ -80,-13,length },{ -72,-12,length },{ -64,-12,length },{ -56,-12,length },
	{ -48,-13,length },{ -40,-13,length },{ -32,-14,length },{ -25,-16,length },{ -18,-17,length },{ -14,-18,length },{ -8,-22,length },{ -5,-26,length },{ -3,-30,length },{ -2,-33,length },{ 0,-36,length } /* end left and center & z=length*/

	,{ 5,17,length },{ 7,22,length },{ 8,14,length },{ 12,11,length },{ 24,12,length },{ 32,14,length },{ 36,19,length },{ 38,25,length },
	{ 118,24,length },{ 112,22,length },{ 104,21,length },{ 96,19,length },{ 88,15,length },{ 82,10,length },{ 79,0,length },{ 78,-6,length },{ 78,-9,length },{ 80,-13,length },{ 72,-12,length },{ 64,-12,length },{ 56,-12,length },
	{ 48,-13,length },{ 40,-13,length },{ 32,-14,length },{ 25,-16,length },{ 18,-17,length },{ 14,-18,length },{ 8,-22,length },{ 5,-26,length },{ 3,-30,length },{ 2,-33,length } /*end right & z=length*/
};
int lines[2500][2] =
{
	{ 0,1 },{ 1,2 },{ 2,3 },{ 3,4 },{ 4,5 },{ 5,6 },{ 6,7 },{ 7,8 },{ 8,9 },{ 9,10 },{ 10,11 },{ 11,12 },{ 12,13 },{ 13,14 },{ 14,15 },{ 15,16 },{ 16,17 },{ 17,18 },
	{ 18,19 },{ 19,20 },{ 20,21 },{ 21,22 },{ 22,23 },{ 23,24 },{ 24,25 },{ 25,26 },{ 26,27 },{ 27,28 },{ 28,29 },{ 29,30 },{ 30,31 },{ 31,32 },
	{ 0,33 },{ 33,34 },{ 34,35 },{ 35,36 },{ 36,37 },{ 37,38 },{ 38,39 },{ 39,40 },{ 40,41 },{ 41,42 },{ 42,43 },{ 43,44 },{ 44,45 },{ 45,46 },{ 46,47 },
	{ 47,48 },{ 48,49 },{ 49,50 },{ 50,51 },{ 51,52 },{ 52,53 },{ 53,54 },{ 54,55 },{ 55,56 },{ 56,57 },{ 57,58 },{ 58,59 },{ 59,60 },{ 60,61 },{ 61,62 },{ 62,63 },
	{ 63,32 }, /*end of z=0*/

{ 64 + 0,1 + 64 },{ 64 + 1,2 + 64 },{ 64 + 2,3 + 64 },{ 64 + 3,4 + 64 },{ 64 + 4,5 + 64 },{ 64 + 5,6 + 64 },{ 64 + 6,7 + 64 },{ 64 + 7,8 + 64 },{ 64 + 8,9 + 64 },{ 64 + 9,10 + 64 },{ 64 + 10,11 + 64 },{ 64 + 11,12 + 64 },{ 64 + 12,13 + 64 },{ 64 + 13,14 + 64 },{ 64 + 14,15 + 64 },{ 64 + 15,16 + 64 },{ 64 + 16,17 + 64 },{ 64 + 17,18 + 64 },
{ 64 + 18,19 + 64 },{ 64 + 19,20 + 64 },{ 64 + 20,21 + 64 },{ 64 + 21,22 + 64 },{ 64 + 22,23 + 64 },{ 64 + 23,24 + 64 },{ 64 + 24,25 + 64 },{ 64 + 25,26 + 64 },{ 64 + 26,27 + 64 },{ 64 + 27,28 + 64 },{ 64 + 28,29 + 64 },{ 64 + 29,30 + 64 },{ 64 + 30,31 + 64 },{ 64 + 31,32 + 64 },
{ 64 + 0,33 + 64 },{ 64 + 33,34 + 64 },{ 64 + 34,35 + 64 },{ 64 + 35,36 + 64 },{ 64 + 36,37 + 64 },{ 64 + 37,38 + 64 },{ 64 + 38,39 + 64 },{ 64 + 39,40 + 64 },{ 64 + 40,41 + 64 },{ 64 + 41,42 + 64 },{ 64 + 42,43 + 64 },{ 64 + 43,44 + 64 },{ 64 + 44,45 + 64 },{ 64 + 45,46 + 64 },{ 64 + 46,47 + 64 },
{ 64 + 47,48 + 64 },{ 64 + 48,49 + 64 },{ 64 + 49,50 + 64 },{ 64 + 50,51 + 64 },{ 64 + 51,52 + 64 },{ 64 + 52,53 + 64 },{ 64 + 53,54 + 64 },{ 64 + 54,55 + 64 },{ 64 + 55,56 + 64 },{ 64 + 56,57 + 64 },{ 64 + 57,58 + 64 },{ 64 + 58,59 + 64 },{ 64 + 59,60 + 64 },{ 64 + 60,61 + 64 },{ 64 + 61,62 + 64 },{ 64 + 62,63 + 64 },
{ 64 + 63,32 + 64 }, /*end of z=length*/

{ 0,64 } ,{ 1,65 } ,{ 2,66 },{ 3,67 },{ 4,68 },{ 5,69 },{ 6,70 },{ 7,71 },{ 8,72 },{ 9,73 },{ 10,74 },{ 11,75 },{ 12,76 },{ 13,77 },{ 14,78 },{ 15,79 },{ 16,80 },{ 17,81 },{ 18,82 },{ 19,83 },
{ 20,84 },{ 21,85 },{ 22,86 },{ 23,87 },{ 24,88 },{ 25,89 },{ 26,90 },{ 27,91 },{ 28,92 },{ 29,93 },{ 30,94 },{ 31,95 },{ 32,96 },{ 33,97 },{ 34,98 },{ 35,99 },{ 36,100 },{ 37,101 },{ 38,102 },
{ 39,103 },{ 40,104 },{ 41,105 },{ 42,106 },{ 43,107 },{ 44,108 },{ 45,109 },{ 46,110 },{ 47,111 },{ 48,112 },{ 49,113 },{ 50,114 },{ 51,115 },{ 52,116 },{ 53,117 },{ 54,118 },{ 55,119 },{ 56,120 },{ 57,121 },
{ 58,122 },{ 59,123 },{ 60,124 },{ 61,125 },{ 62,126 },{ 63,127 } /*end of connect 2page*/
};
int numLine = 189;


void main()
{
	int device = DETECT, mode;
	initgraph(&device, &mode, "c:\\TURBOC3\\BGI");
	cleardevice();
	init();
	char c;
	int fkey;
	while (contuneP)
	{
		getKey(c, fkey);
		doCommand(c, fkey);
	}
	closegraph();

}
void doCommand(char c, int fkey)
{
	clearPage();
	if (!fkey)
	{
		switch (c)
		{
		case 27:  //esc
			contuneP = 0;
			break;

		case 'a':	//chang accuracy
			accuracy = 1;
			break;
		case 's':  //zoomOut
			scale /= 1.01;
			break;
		case 'S':  //zoomIn
			scale *= 1.01;
			break;
		case 'x':  //rotateX + //41
			if (accuracy == 0)
			{
				if (NOR == 0)
				{
					rotates[0] = 41;
					NOR++;
				}
				else if (rotates[NOR - 1] % 41 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 41) + 1) * 41;
					if (rotates[NOR - 1] / 41 == 36)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if(mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if(mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = 41;
					NOR++;
				}
			}
			else//////////////////////////////////////////////////////////////53
			{
				accuracy = 0;
				if (NOR == 0)
				{
					rotates[0] = 53;
					NOR++;
				}
				else if (rotates[NOR - 1] % 53 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 53) + 1) * 53;
					if ((rotates[NOR - 1] / 53)%41==0 || (rotates[NOR - 1] / 53) % 43==0 || (rotates[NOR - 1] / 53) % 47==0 || (rotates[NOR - 1] / 53) % 53==0 || (rotates[NOR - 1] / 53) % 59==0 || (rotates[NOR - 1] / 53) % 61==0 )
						rotates[NOR - 1] = ((rotates[NOR - 1] / 53) + 1) * 53;
					if (rotates[NOR - 1] / 53 == 720)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = 53;
					NOR++;
				}
			}
		
			break;
		case 'X':  //rotateX - //-1
			
			if (accuracy == 0)
			{
				if (NOR == 0)
				{
					rotates[0] = -41;
					NOR++;
				}
				else if (rotates[NOR - 1] % 41 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 41) - 1) * 41;
					if (rotates[NOR - 1] / 41 == -36)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = -41;
					NOR++;
				}
			}
			else//////////////////////////////////////////////////////////////53
			{
				accuracy = 0;
				if (NOR == 0)
				{
					rotates[0] = -53;
					NOR++;
				}
				else if (rotates[NOR - 1] % 53 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 53) - 1) * 53;
					if ((rotates[NOR - 1] / 53) % 41 == 0 || (rotates[NOR - 1] / 53) % 43 == 0 || (rotates[NOR - 1] / 53) % 47 == 0 || (rotates[NOR - 1] / 53) % 53 == 0 || (rotates[NOR - 1] / 53) % 59 == 0 || (rotates[NOR - 1] / 53) % 61 == 0)
						rotates[NOR - 1] = ((rotates[NOR - 1] / 53) - 1) * 53;
					if (rotates[NOR - 1] / 53 == -720)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = -53;
					NOR++;
				}
			}

			break;
		case 'y':  //rotateY + //43
			if (accuracy == 0)
			{
				if (NOR == 0)
				{
					rotates[0] = 43;
					NOR++;
				}
				else if (rotates[NOR - 1] % 43 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 43) + 1) * 43;
					if (rotates[NOR - 1] / 43 == 36)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = 43;
					NOR++;
				}
			}
			else//////////////////////////////////////////////////////////////59
			{
				accuracy = 0;
				if (NOR == 0)
				{
					rotates[0] = 59;
					NOR++;
				}
				else if (rotates[NOR - 1] % 59 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 59) + 1) * 59;
					if ((rotates[NOR - 1] / 59) % 41==0 || (rotates[NOR - 1] / 59) % 43==0 || (rotates[NOR - 1] / 59) % 47==0 || (rotates[NOR - 1] / 59) % 53==0 || (rotates[NOR - 1] / 59) % 59==0 || (rotates[NOR - 1] / 59) % 61==0)
						rotates[NOR - 1] = ((rotates[NOR - 1] / 59) + 1) * 59;
					if (rotates[NOR - 1] / 59 == 720)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = 59;
					NOR++;
				}
			}

			break;
		case 'Y':  //rotateY - //-2
			if (accuracy == 0)
			{
				if (NOR == 0)
				{
					rotates[0] = -43;
					NOR++;
				}
				else if (rotates[NOR - 1] % 43 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 43) - 1) * 43;
					if (rotates[NOR - 1] / 43 == -36)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = -43;
					NOR++;
				}
			}
			else//////////////////////////////////////////////////////////////59
			{
				accuracy = 0;
				if (NOR == 0)
				{
					rotates[0] = -59;
					NOR++;
				}
				else if (rotates[NOR - 1] % 59 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 59) - 1) * 59;
					if ((rotates[NOR - 1] / 59) % 41 == 0 || (rotates[NOR - 1] / 59) % 43 == 0 || (rotates[NOR - 1] / 59) % 47 == 0 || (rotates[NOR - 1] / 59) % 53 == 0 || (rotates[NOR - 1] / 59) % 59 == 0 || (rotates[NOR - 1] / 59) % 61 == 0)
						rotates[NOR - 1] = ((rotates[NOR - 1] / 59) - 1) * 59;
					if (rotates[NOR - 1] / 59 == -720)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = -59;
					NOR++;
				}
			}

			break;
			
		case 'z':  //rotateZ + //3
			if (accuracy == 0)
			{
				if (NOR == 0)
				{
					rotates[0] = 47;
					NOR++;
				}
				else if (rotates[NOR - 1] % 47 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 47) + 1) * 47;
					if (rotates[NOR - 1] / 47 == 36)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = 47;
					NOR++;
				}
			}
			else//////////////////////////////////////////////////////////////61
			{
				accuracy = 0;
				if (NOR == 0)
				{
					rotates[0] = 61;
					NOR++;
				}
				else if (rotates[NOR - 1] % 61 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 61) + 1) * 61;
					if ((rotates[NOR - 1] / 61) % 41==0 || (rotates[NOR - 1] / 61) % 43==0 || (rotates[NOR - 1] / 61) % 47==0 || (rotates[NOR - 1] / 61) % 53==0 || (rotates[NOR - 1] / 61) % 59==0 || (rotates[NOR - 1] / 61) % 61==0)
						rotates[NOR - 1] = ((rotates[NOR - 1] / 61) + 1) * 61;
					if (rotates[NOR - 1] / 61 == 720)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = 61;
					NOR++;
				}
			}

			break;
			
		case 'Z':  //rotateZ - //-3
			if (accuracy == 0)
			{
				if (NOR == 0)
				{
					rotates[0] = -47;
					NOR++;
				}
				else if (rotates[NOR - 1] % 47 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 47) - 1) * 47;
					if (rotates[NOR - 1] / 47 == -36)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 61 == 0)
						mod = 61;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 61)
								rotateZ((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = -47;
					NOR++;
				}
			}
			else//////////////////////////////////////////////////////////////61
			{
				accuracy = 0;
				if (NOR == 0)
				{
					rotates[0] = -61;
					NOR++;
				}
				else if (rotates[NOR - 1] % 61 == 0)
				{
					rotates[NOR - 1] = ((rotates[NOR - 1] / 61) - 1) * 61;
					if ((rotates[NOR - 1] / 61) % 41 == 0 || (rotates[NOR - 1] / 61) % 43 == 0 || (rotates[NOR - 1] / 61) % 47 == 0 || (rotates[NOR - 1] / 61) % 53 == 0 || (rotates[NOR - 1] / 61) % 59 == 0 || (rotates[NOR - 1] / 61) % 61 == 0)
						rotates[NOR - 1] = ((rotates[NOR - 1] / 61) - 1) * 61;
					if (rotates[NOR - 1] / 61 == -720)
					{
						rotates[NOR - 1] = 0;
						NOR--;
						for (int j = 0;j < 128;j++)
						{
							tdot[j][0] = dots[j][0];
							tdot[j][1] = dots[j][1];
							tdot[j][2] = dots[j][2];

						}
						for (int i = 0;i < NOR - 1;i++)
						{
							if (rotates[i] % 41 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 41) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 43 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 43) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 47 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 47) * 10, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 53 == 0)
								for (int j = 0;j < 128;j++)
									rotateX((rotates[i] / 53) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 59 == 0)
								for (int j = 0;j < 128;j++)
									rotateY((rotates[i] / 59) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
							else if (rotates[i] % 61 == 0)
								for (int j = 0;j < 128;j++)
									rotateZ((rotates[i] / 61) * 0.5, tdot[j][0], tdot[j][1], tdot[j][2], tdot[j][0], tdot[j][1], tdot[j][2]);
						}
					}
				}
				else
				{
					int mod;
					if (rotates[NOR - 1] % 43 == 0)
						mod = 43;
					else if (rotates[NOR - 1] % 47 == 0)
						mod = 47;
					else if (rotates[NOR - 1] % 41 == 0)
						mod = 41;
					else if (rotates[NOR - 1] % 59 == 0)
						mod = 59;
					else if (rotates[NOR - 1] % 53 == 0)
						mod = 53;
					if (NOR == 1)
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, dots[i][0], dots[i][1], dots[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					else
					{
						for (int i = 0;i < 128;i++)
						{
							if (mod == 43)
								rotateY((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 47)
								rotateZ((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 41)
								rotateX((rotates[NOR - 1] / mod) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 59)
								rotateY((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
							else if (mod == 53)
								rotateX((rotates[NOR - 1] / mod) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tdot[i][0], tdot[i][1], tdot[i][2]);
						}
					}
					rotates[NOR] = -61;
					NOR++;
				}
			}

			break;
			
		case 'c':  //change color
			color++;
			if (color == 16)
				color = 1;
			setcolor(color);
			break;
		case 'C':  //change Color
			color++;
			if (color == 16)
				color = 1;
			setcolor(color);
			break;
		}
	}
	else // is funcKey
	{
		switch (c)
		{
		case 77:  //right
			cmx++;
			break;
		case 72:  //up
			cmy--;
			break;
		case 75:  //left
			cmx--;
			break;
		case 80:  //down
			cmy++;
			break;
		}
	}
	drawPage();
}
void drawPage()
{
	if (NOR == 0)
	{
		for (int i = 0;i < 128;i++)
		{
			tempDots[i][0] = dots[i][0];
			tempDots[i][1] = dots[i][1];
			tempDots[i][2] = dots[i][2];
			tempDots[i][0] *= scale;
			tempDots[i][1] *= scale;
			tempDots[i][2] *= scale;
		}
	}
	else if (NOR == 1)
	{
		for (int i = 0;i < 128;i++)
		{
			
			if (rotates[NOR - 1] % 41 == 0)
				rotateX((rotates[NOR - 1] / 41) * 10, dots[i][0], dots[i][1], dots[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 43 == 0)
				rotateY((rotates[NOR - 1] / 43) * 10, dots[i][0], dots[i][1], dots[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if(rotates[NOR - 1] % 47 == 0)
				rotateZ((rotates[NOR - 1] / 47) * 10, dots[i][0], dots[i][1], dots[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 53 == 0)
				rotateX((rotates[NOR - 1] / 53) * 0.5, dots[i][0], dots[i][1], dots[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 59 == 0)
				rotateY((rotates[NOR - 1] / 59) * 0.5, dots[i][0], dots[i][1], dots[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 61 == 0)
				rotateZ((rotates[NOR - 1] / 61) * 0.5, dots[i][0], dots[i][1], dots[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);

			tempDots[i][0] *= scale;
			tempDots[i][1] *= scale;
			tempDots[i][2] *= scale;
		}
	}
	else
	{
		for (int i = 0;i < 128;i++)
		{
			
			if (rotates[NOR - 1] % 41 == 0)
				rotateX((rotates[NOR - 1] / 41) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 43 == 0)
				rotateY((rotates[NOR - 1] / 43) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 47 == 0)
				rotateZ((rotates[NOR - 1] / 47) * 10, tdot[i][0], tdot[i][1], tdot[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 53 == 0)
				rotateX((rotates[NOR - 1] / 53) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 59 == 0)
				rotateY((rotates[NOR - 1] / 59) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);
			else if (rotates[NOR - 1] % 61 == 0)
				rotateZ((rotates[NOR - 1] / 61) * 0.5, tdot[i][0], tdot[i][1], tdot[i][2], tempDots[i][0], tempDots[i][1], tempDots[i][2]);

			tempDots[i][0] *= scale;
			tempDots[i][1] *= scale;
			tempDots[i][2] *= scale;
		}
	}

	for (int i = 0;i < numLine;i++)
	{
		int x1 = tempDots[lines[i][0]][0] + cmx;
		int y1 = tempDots[lines[i][0]][1] + cmy;
		int x2 = tempDots[lines[i][1]][0] + cmx;
		int y2 = tempDots[lines[i][1]][1] + cmy;
		line(x1, y1, x2, y2);
	}

}
void init()
{
	for (int i = 0;i < 128;i++)
		for (int j = 0; j < 3;j++)
			tempDots[i][j] = dots[i][j];
	cmx = 320;
	cmy = 240;
	color = 3;
	for (i = 0;i < 10000;i++)
		rotates[i] = 0;
	setcolor(color);
	drawPage();
}
void clearPage()
{
	setcolor(0);
	for (int i = 0;i < numLine;i++)
	{
		int x1 = tempDots[lines[i][0]][0] + cmx;
		int y1 = tempDots[lines[i][0]][1] + cmy;
		int x2 = tempDots[lines[i][1]][0] + cmx;
		int y2 = tempDots[lines[i][1]][1] + cmy;
		line(x1, y1, x2, y2);
	}
	setcolor(color);
}
void getKey(char & c, int & fkey)
{
	c = getch();
	fkey = 0;
	if (!c)
	{
		fkey = 1;
		c = getch();
	}
}
void rotateX(double t, double x, double y, double z, double & x2, double & y2, double & z2)
{
	t = t / 180 * P;
	x2 = x;
	y2 = y*cos(t) - z*sin(t);
	z2 = y*sin(t) + z*cos(t);
}
void rotateY(double t, double x, double y, double z, double & x2, double & y2, double & z2)
{
	t = t / 180 * P;
	x2 = x*cos(t) + z*sin(t);
	y2 = y;
	z2 = z*cos(t) - x*sin(t);
}
void rotateZ(double t, double x, double y, double z, double & x2, double & y2, double & z2)
{

	t = t / 180 * P;
	x2 = x*cos(t) - y*sin(t);
	y2 = x*sin(t) + y*cos(t);
	z2 = z;
}
