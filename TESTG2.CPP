#include<graphics.h>
#include<iostream.h>
#include <conio.h>
#include <dos.h>
#include <math.h>

void rotatex(double T,double x, double y, double z, double &x2, double &y2, double &z2);
void rotatey(double T, double x, double y, double z, double &x2, double &y2, double &z2);
void rotatez(double T, double x, double y, double z, double &x2, double &y2, double &z2);
void getkey(char &c, int &funckey);
void docommand(char c, int funckey);
void init();
void clearPage();
void draw();
void rotate(double tx, double ty, double tz, double x, double y, double z, int &x2, int &y2, int &z2);

int cmx , cmy, end = 0,numline;
double dots[50][3] = { {0,-100,0},{60,-40,60},{-60,-40,60} ,{-60,-40,-60},{60,-40,-60},{-120,-40,-120},{120,-40,-120},{120,-40,120},{-120,-40,120},{0,-20,-170},{170,-20,0},{0,-20,170},{-170,-20,0},{-50,-20,-120},{50,-20,-120},{120,-20,-50},{120,-20,50},{50,-20,120},{-50,-20,120},{-120,-20,50},{-120,-20,-50},{ 0,100,0 },{ 60,40,60 },{ -60,40,60 } ,{ -60,40,-60 },{ 60,40,-60 },{ -120,40,-120 },{ 120,40,-120 },{ 120,40,120 },{ -120,40,120 },{ 0,20,-170 },{ 170,20,0 },{ 0,20,170 },{ -170,20,0 },{ -50,20,-120 },{ 50,20,-120 },{ 120,20,-50 },{ 120,20,50 },{ 50,20,120 },{ -50,20,120 },{ -120,20,50 },{ -120,20,-50 } };
int Pdots[50][3];
int lines[2500][2] = { {0,1},{21,22},{0,2},{21,23},{0,3} ,{21,24},{0,4},{21,25},{1,2},{22,23},{2,3},{23,24},{3,4},{24,25},{4,1}, {25,22},{5,6},{26,27},{6,7},{27,28},{7,8},{28,29},{8,5},{29,26},{9,14},{30,35},{9,13},{30,34},{10,15},{31,36},{10,16},{31,37},{11,17} ,{32,38},{11,18},{32,39},{12,19} ,{33,40},{12,20},{33,41},{5,5 + 21},{13,13 + 21},{9,9 + 21},{14,14 + 21},{6,6 + 21},{15,15 + 21},{10,10 + 21},{16,16 + 21},{7,7 + 21},{11,11 + 21},{17,17 + 21 },{18,18 + 21},{8,8 + 21},{19,19 + 21},{12,12 + 21},{20,20 + 21} };
int color;
double scale,p=3.1415926535;
int tX, tY, tZ;

void main(){
	int mode, device;
	device=DETECT;
	initgraph(&device,&mode,"c:\\TURBOC3\\BGI");
	cleardevice();
	
	char c;
	int funckey;
	init();
	while (!end) {
		getkey(c,funckey);
		docommand(c, funckey);

	}
	closegraph();
}



void docommand(char c, int funckey) {

	clearPage();

	if (!funckey) {
		switch (c) {
		case 's':		//double zoomout
			scale /= 2;
			
			break;
		case 'S':		//double zoomin
			scale *= 2;
			
			break;
		case 'x':
			for (int i = 0;i < 50;i++) {
				rotatex(-5, dots[i][0], dots[i][1], dots[i][2], dots[i][0], dots[i][1], dots[i][2]);
			}
			

			break;
		case 'y':
			for (i = 0;i < 50;i++) {
				rotatey(-5, dots[i][0], dots[i][1], dots[i][2], dots[i][0], dots[i][1], dots[i][2]);
			}


			break;
		case 'z':
			for (i = 0;i < 50;i++) {
				rotatez(-5, dots[i][0], dots[i][1], dots[i][2], dots[i][0], dots[i][1], dots[i][2]);
			}


			break;
		case 'X':
			for (i = 0;i < 50;i++) {
				rotatex(5, dots[i][0], dots[i][1], dots[i][2], dots[i][0], dots[i][1], dots[i][2]);
			}


			break;
		case 'Y':
			for (i = 0;i < 50;i++) {
				rotatey(5, dots[i][0], dots[i][1], dots[i][2], dots[i][0], dots[i][1], dots[i][2]);
			}

			break;
		case 'Z':
			for (i = 0;i < 50;i++) {
				rotatez(5, dots[i][0], dots[i][1], dots[i][2], dots[i][0], dots[i][1], dots[i][2]);
			}

			break;
		case 27	:	//Esc
			end = 1;
			break;
		case 'c':
			color++;
			if (color == 16)
				color = 1;
			setcolor(color);
			break;
		}
	}
	else {
		switch (c){
		case 77	:	//right
			cmx++;
			break;
		case 72	:	//up
			cmy--;
			break;
		case 75	:	//left
			cmx--;
			break;
		case 80	:	//down
			cmy++;
			break;
		}

	}

	draw();

}


void draw() {
	for (int i = 0;i < 50;i++) {
		/*rotatex(tX, dots[i][0], dots[i][1], dots[i][2], Pdots[i][0], Pdots[i][1], Pdots[i][2]);
		rotatey(tY, Pdots[i][0], Pdots[i][1], Pdots[i][2], Pdots[i][0], Pdots[i][1], Pdots[i][2]);
		rotatez(tZ, Pdots[i][0], Pdots[i][1], Pdots[i][2], Pdots[i][0], Pdots[i][1], Pdots[i][2]);*/

		//rotate(tX, tY, tZ, dots[i][0], dots[i][1], dots[i][2], Pdots[i][0], Pdots[i][1], Pdots[i][2]);

		for (int j = 0;j < 3;j++) {
			Pdots[i][j] = dots[i][j]*scale;
		}

	}
	for ( i = 0;i < numline;i++) {
		line(Pdots[lines[i][0]][0]+cmx,Pdots[lines[i][0]][1]+cmy,Pdots[lines[i][1]][0]+cmx,Pdots[lines[i][1]][1]+cmy);
	}
}

void clearPage() {
	setcolor(0);

		for (int i = 0;i < numline;i++) {
			line(Pdots[lines[i][0]][0] + cmx, Pdots[lines[i][0]][1] + cmy, Pdots[lines[i][1]][0] + cmx, Pdots[lines[i][1]][1] + cmy);
		}

	
	setcolor(color);
}

void init() {
	for (int i = 0;i < 50;i++) {
		for (int j = 0;j < 3;j++) {
			Pdots[i][j] = dots[i][j];
		}
	}
	cmx = 320, cmy = 240;
	numline = 56;
	color = 1;
	setcolor(color);
	scale = 1.0;
	tX = 0, tY = 0, tZ = 0;
	draw();


}

void getkey(char &c, int &funckey) {
	c = getch();
	funckey = 0;
	if (!c) {
		c = getch();
		funckey = 1;
	}
}


void rotatex(double T, double x, double y, double z, double &x2, double &y2, double &z2) {
	T = (T / 180)*p;
	x2 = x;
	y2 = y*cos(T) - z*sin(T);
	z2 = y*sin(T) + z*cos(T);
}

void rotatey(double T, double x, double y, double z, double &x2, double &y2, double &z2) {
	T = (T / 180)*p;
	x2 = x*cos(T) + z*sin(T);
	y2 = y;
	z2 = z*cos(T) - x*sin(T);
}

void rotatez(double T, double x, double y, double z, double &x2, double &y2, double &z2) {
	T = (T / 180)*p;
	x2 = x*cos(T) - y*sin(T);
	y2 = x*sin(T) + y*cos(T);
	z2 = z;
}
void rotate(double tx, double ty, double tz, double x, double y, double z, int &x2, int &y2, int &z2)
{
	tx = (tx / 180)*p;
	ty = (ty / 180)*p;
	tz = (tz / 180)*p;
	x2 = x*cos(ty)*cos(tz) - y*sin(tz)*cos(ty) + z*sin(ty);
	y2 = x*(sin(tx)*sin(ty)*cos(tz) + cos(tx)*sin(tz)) + y*(-sin(tx)*sin(ty)*sin(tz) + cos(tx)*cos(tz)) + z*(-sin(tx)*cos(ty));
	z2 = x*(-sin(ty)*cos(tx)*cos(tz) + sin(tx)*sin(tz)) + y*(sin(ty)*cos(tx)*sin(tz) + sin(tx)*cos(tz)) + z*(cos(tx)*cos(ty));
}
