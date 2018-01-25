#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void wprint(char *str, int x, int y, int tcolor, int bgcolor, int isdark, int blink);
void init();
void docommand(char c,int funckey);
void play();
void display();
void move();
void food();
void gameover();
void f1();
void f2();
void f3();
void f4();
void f5();
void(*flevel[5])();


int far * scr = (int far *)0xb8000000;
int vector, end ;
int snake[50][2];
int tail;
int numfood;
char c;
int funckey = 0;
int level=1;
int score=0;
int eaten = 0;
int isnextlvl=0;
int dly;

int main() {

	
	
	
	flevel[0] = f1;
	flevel[1] = f2;
	flevel[2] = f3;
	flevel[3] = f4;
	flevel[4] = f5;
	score = 0;
	level = 1;
	init();
	dly = 100;
	food();
	flevel[0]();

	while (!end) {
		if (kbhit() && !eaten) {
			c=getch();
			funckey = 0;
			if (!c) {
				c = getch();
				funckey = 1;
			}
			docommand(c, funckey);
		}
		play();
	}
	int a;
	level = 1;
	FILE *f;
	f = fopen("hs.txt", "r+");
	fscanf(f, "%d", &a);
	if (score > a) {
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", score);
	}
	fclose(f);
	_setcursortype(_NORMALCURSOR);
	return 0;
}

void play() {
	display();
	if (!eaten)
		delay(dly);
	else
		eaten = 0;
	move();


}

void move() {
	int x, y;
	if (vector == 1) {
		x = snake[0][0];
		y = snake[0][1] + 1;
	}
	else if (vector == 2) {
		x = snake[0][0] - 1;
		y = snake[0][1];
	}
	else if (vector == 3) {
		x = snake[0][0];
		y = snake[0][1] - 1;
	}
	else if (vector == 4) {
		x = snake[0][0] + 1;
		y = snake[0][1];
	}
	if (tail == 0) {

		if (y > 79) {
			if (scr[x * 80 + 0] == (4 * 16) * 256 + ' ' || scr[x * 80 + 0] == (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[x * 80 + 0] == 7 * 16 * 256 + ' '){
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						scr[snake[i][0] * 80 + snake[i][1]] = 7 * 16 * 256 + ' ';
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = x;
				snake[0][1] = 0;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if (!isnextlvl)
					scr[x * 80 + 0] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}
		}
		else if (y < 0) {
			if (scr[x * 80 + 79] == (4 * 16) * 256 + ' ' || scr[x * 80 + 79] == (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[x * 80 + 79] == 7 * 16 * 256 + ' ') {
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						scr[snake[i][0] * 80 + snake[i][1]] = 7 * 16 * 256 + ' ';
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = x;
				snake[0][1] = 79;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if(!isnextlvl)
				scr[x * 80 + 79] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}
		}

		else if (scr[x * 80 + y] == 7 * 16 * 256 + ' ') { /////bg
			int t = 1;
			for (int i = 49;i > 0;i--) {
				if (snake[i][0] != -1 && t == 1) {
					scr[snake[i][0] * 80 + snake[i][1]] = 7 * 16 * 256 + ' ';
					t = 0;
				}
				if (snake[i][0] != -1 && t == 0) {
					snake[i][0] = snake[i - 1][0];
					snake[i][1] = snake[i - 1][1];
				}
			}
			snake[0][0] = x;
			snake[0][1] = y;

		}
		else if (x > 24) {
			if (scr[1 * 80 + y] == (4 * 16) * 256 + ' ' || scr[1 * 80 + y]== (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[1 * 80 + y] == 7 * 16 * 256 + ' ') {
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						scr[snake[i][0] * 80 + snake[i][1]] = 7 * 16 * 256 + ' ';
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = 1;
				snake[0][1] = y;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if(!isnextlvl)
				scr[1 * 80 + y] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}
		}
		else if (x == 0) {
			if (scr[24 * 80 + y] == (4 * 16) * 256 + ' ' || scr[24 * 80 + y] == (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[24 * 80 + y] == 7 * 16 * 256 + ' '){
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						scr[snake[i][0] * 80 + snake[i][1]] = 7 * 16 * 256 + ' ';
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = 24;
				snake[0][1] = y;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if(!isnextlvl)
				scr[24 * 80 + y] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}

		}
		else if (scr[x * 80 + y] == (3 + 16 * 0) * 256 + 176) {
			
			int t = 1,p=0;
			for (int i = 49;i > 0;i--) {
				if (snake[i][0] != -1 && t == 1 ) {
					t = 0;
					if (snake[i][0] == x && snake[i][1] == y) {
						p = 1;
						scr[snake[i][0] * 80 + snake[i][1]] = 7 * 16 * 256 + ' ';
					}

				}
				if (snake[i][0] != -1 && t == 0) {
					snake[i][0] = snake[i - 1][0];
					snake[i][1] = snake[i - 1][1];
				}
			}
			if (p == 0)
				gameover();
			else {
				snake[0][0] = x;
				snake[0][1] = y;
			}
		}

		 else if (scr[x * 80 + y] == (4 * 16) * 256 + ' ') {		//wall
			gameover();

		}
		else {		//ghaza
			tail += numfood;
			food();
			if (!isnextlvl)
				scr[x * 80 + y] = 7 * 16 * 256 + ' ';
			else
				isnextlvl = 0;

		}

	}
	else {
		tail--;
		if (y > 79) {
			if (scr[x * 80 + 0] == (4 * 16) * 256 + ' ' || scr[x * 80 + 0] == (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[x * 80 + 0] == 7 * 16 * 256 + ' '){
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						snake[i + 1][0] = snake[i][0];
						snake[i + 1][1] = snake[i][1];
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = x;
				snake[0][1] = 0;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if(!isnextlvl)
				scr[x * 80 + 0] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}
		}
		else if (y < 0) {
			if (scr[x * 80 + 79] == (4 * 16) * 256 + ' ' || scr[x * 80 + 79] == (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[x * 80 + 79] == 7 * 16 * 256 + ' ') {
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						snake[i + 1][0] = snake[i][0];
						snake[i + 1][1] = snake[i][1];
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = x;
				snake[0][1] = 79;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if(!isnextlvl)
				scr[x * 80 + 79] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}
		}

		else if (scr[x * 80 + y] == 7 * 16 * 256 + ' ') {
			int t = 1;
			for (int i = 49;i > 0;i--) {
				if (snake[i][0] != -1 && t == 1) {
					snake[i + 1][0] = snake[i][0];
					snake[i + 1][1] = snake[i][1];
					t = 0;
				}
				if (snake[i][0] != -1 && t == 0) {
					snake[i][0] = snake[i - 1][0];
					snake[i][1] = snake[i - 1][1];
				}
			}
			snake[0][0] = x;
			snake[0][1] = y;

		}
		else if (x > 24) {
			if (scr[1 * 80 + y] == (4 * 16) * 256 + ' ' || scr[1 * 80 + y] == (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[1 * 80 + y] == 7 * 16 * 256 + ' '){
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						snake[i + 1][0] = snake[i][0];
						snake[i + 1][1] = snake[i][1];
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = 1;
				snake[0][1] = y;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if(!isnextlvl)
				scr[1 * 80 + y] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}
		}
		else if (x == 0) {
			if (scr[24 * 80 + y] == (4 * 16) * 256 + ' ' || scr[24 * 80 + y] == (3 + 16 * 0) * 256 + 176) {		//wall
				gameover();

			}
			else if(scr[24 * 80 + y] == 7 * 16 * 256 + ' '){
				int t = 1;
				for (int i = 49;i > 0;i--) {
					if (snake[i][0] != -1 && t == 1) {
						snake[i + 1][0] = snake[i][0];
						snake[i + 1][1] = snake[i][1];
						t = 0;
					}
					if (snake[i][0] != -1 && t == 0) {
						snake[i][0] = snake[i - 1][0];
						snake[i][1] = snake[i - 1][1];
					}
				}
				snake[0][0] = 24;
				snake[0][1] = y;
			}
			else {		//ghaza
				tail += numfood;
				food();
				if(!isnextlvl)
				scr[24 * 80 + y] = 7 * 16 * 256 + ' ';
				else
					isnextlvl = 0;
			}

		}
		else if (scr[x * 80 + y] == (3 + 16 * 0) * 256 + 176) {
			gameover();
			//tail++;
		}
		else if (scr[x * 80 + y] == ((4 * 16) * 256 + ' ')) {		//wall
			gameover();

		}
		else {		//ghaza
			tail += numfood;
			food();
			if (!isnextlvl)
				scr[x * 80 + y] = 7 * 16 * 256 + ' ';
			else
				isnextlvl = 0;
			
			//tail++;

		}
		//tail--;
	}
}

void gameover() {
	//for (int y = 0;y < 500;y++)
	//	scr[y + 80] = 0;

	wprint("game over", 10,35, 4, 3, 1, 1);

	//FILE * q;
	//int x, m[300] = { 0 }, l = 0;;
	//q = fopen("go.txt", "r");
	//for (int i = 80;i < 1600;i++) {
	//		fscanf(q, "%d", &x);
	//		if (x == 3547) {
	//			m[l] = i;
	//			l++;
	//		}
	//}

	//fclose(q);
	//int w = 0;
	//while (m[w] != 0) {
	//	scr[m[w]] = 3547;
	//	w++;
	//}

	//for (int s = 0;s < 6;s++) {
		sound(1400 - 40);
		delay(200);
		sound(1400 - 80);
		delay(200);
		sound(1400 - 120);
		delay(200);
		sound(1400 - 160);
		delay(200);
		sound(1400 - 200);
		delay(200);
	//}
	nosound();

	wprint("Enter : Restart", 20, 10, 3, 5, 0, 0);
	wprint("Escape : Exit", 20, 55, 3, 5, 0, 0);
	char  c;
	int t=1;
	while (t) {

		c= getch();
		if (c == 27) {
			end = 1;
			t = 0;
		}
		else if(c==13){
			int a;
			level=1;
			FILE *f;
			f=fopen("hs.txt", "r+");
			fscanf(f, "%d", &a);
			if (score > a) {
				fseek(f, 0, SEEK_SET);
				fprintf(f, "%d", score);
			}
			fclose(f);
			score = 0;
			init();
			dly = 100;
			food();
			t = 0;
		}
	}
}

void food() {
	sound(1300);
	delay(5);
	nosound();
	eaten = 1;
	score = score + numfood*level;
	char *sscore;
	sprintf(sscore, "%d", score);
	wprint(sscore, 0, 19, 3, 1, 1, 0);
	//cout << score<<" "<<sscore<<"-";
	sscore;
	score * 3;
	if (numfood >= 9) {
		wprint("LEVEL UP:D", 14, 35, 7, 3, 1, 0);
		sound(1150);
		delay(400);
		for (int u = 0;u < 3;u++) {
			sound(1450);
			delay(400);
			sound(850);
			delay(10);
		}
		sound(1300);
		delay(200);
		sound(1170);
		delay(200);
		sound(1750);
		delay(1200);
		nosound();
		delay(1000);
		isnextlvl = 1;
		level++;
		init();
		flevel[(level - 1)%5]();
		if (level % 5 == 1) {
			dly -= 15;
		}
		char *slevel;
		sprintf(slevel, "%d", level);
		wprint(slevel, 0, 8, 3, 1, 1, 0);
		wprint(sscore, 0, 19, 3, 1, 1, 0);

	}

	numfood++;

	int rnd=0;
	time_t t;

	
	srand((unsigned)time(&t));
	rnd = rand() % 2000;
	while (scr[rnd] != 7 * 16 * 256 + ' ') {
		rnd=(rnd*7+1)%2000;
	}
	
	
	if (numfood <= 6) {
		scr[rnd] = (16 * 7 + numfood) * 256 + 2;
	}
	else{
		scr[rnd] = (16 * 7 + numfood + 3) * 256 + 2;
	}
	

}


void display() {
	if (vector == 1)                                                                                               
		scr[snake[0][0] * 80 + snake[0][1]] = (3 + 16 * 0) * 256 + '>';
	else if (vector == 2)
		scr[snake[0][0] * 80 + snake[0][1]] = (3 + 16 * 0) * 256 + '^';
	else if (vector == 3)
		scr[snake[0][0] * 80 + snake[0][1]] = (3 + 16 * 0) * 256 + '<';
	else if (vector == 4)
		scr[snake[0][0] * 80 + snake[0][1]] = (3 + 16 * 0) * 256 + 'v';
	for (int i = 1;i < 50;i++) {
		if (snake[i][0] != -1) {
			//scr[snake[i][0] * 80 + snake[i][1]] = (2 + 16 * 6) * 256 + 176;
			scr[snake[i][0] * 80 + snake[i][1]] = (3+ 16 * 0) * 256 + 176;
		}
	}

}

void docommand(char c,int funckey) {
	int far * first = (int far *) 0X0000041A;
	int far * last = (int far *) 0X0000041C;
	*last=*first;
	if (!funckey) {
		switch (c) {
		case 27:		//exit
			end = 1;
			break;
		}
	}
	else {
		switch (c) {
		case 77:		//right
			if (vector != 3)
				vector = 1;

			break;

		case 72:		//up
			if (vector != 4)
				vector = 2;

			break;

		case 75:		//left
			if (vector != 1)
				vector = 3;

			break;

		case 80:		//down
			if (vector != 2)
				vector = 4;

			break;

		}
	}

}


void wprint(char *str, int x, int y, int tcolor, int bgcolor, int isdark, int blink) {

	int i = 0;
	while (str[i] != NULL) {
		scr[x * 80 + y + i] = (tcolor + (isdark * 8) + (bgcolor * 16) + (blink * 128)) * 256 + str[i];
		i++;
	}
}


void init() {

	_setcursortype(_NOCURSOR);

	vector = 1, end = 0;
	for (int i = 0;i < 50;i++) {

		snake[i][0] = -1;
		snake[i][1] = -1;
	}
	tail = 0;

	
	snake[0][0] = 12, snake[0][1] = 40, snake[1][0] = 12, snake[1][1] = 39, snake[2][0] = 12, snake[2][1] = 38;
	for (int j = 3;j < 50;j++)
		snake[j][0] = -1, snake[j][1] = -1;

	
	
	for ( i = 0;i < 80;i++) {
		scr[i] = (16) * 256 + ' ';
	}
	for (i = 80;i < 2000;i++) {
		scr[i] = 7 * 16 * 256 + ' ';
	}


	

	wprint("LEVEL: 1   SCORE: 0      HighScore:                      press Esc to exit", 0, 1, 3, 1, 1, 0);  //highsccor copy from file && chang color of number
	FILE *f;
	int a;
	char *hs;
	f=fopen("hs.txt", "r");
	fscanf(f, "%d", &a);
	sprintf(hs, "%d", a);
	wprint(hs, 0, 37, 3, 1, 1, 0);
	hs;
	fclose(f);
	

	numfood = 0;
	
}


void f1() {
	
	//	scr[80+20+i] = (16 * 7) * 256 + 1;

	//for (int k = 0;k < 10;k++)////////////////////////////////////////////////erase please
	//	scr[5 * 80 + 4 + k] = (5 * 16) * 256 + ' ';//////////////////////////////////////////////////////
	

}

void f2() {
	
	for (int i = 0;i < 80;i++) {
		scr[80+i]= (4 * 16) * 256 + ' ';
		scr[80 * 24 + i] = (4 * 16) * 256 + ' ';
	}
	for (i = 1;i < 25;i++) {
		scr[i * 80] = (4 * 16) * 256 + ' ';
		scr[i * 80 + 79] = (4 * 16) * 256 + ' ';
	}
}
void f3() {
	scr[80] = (4 * 16) * 256 + ' ';
	scr[81] = (4 * 16) * 256 + ' ';
	scr[82] = (4 * 16) * 256 + ' ';
	scr[83] = (4 * 16) * 256 + ' ';
	scr[84] = (4 * 16) * 256 + ' ';
	scr[160] = (4 * 16) * 256 + ' ';
	scr[240] = (4 * 16) * 256 + ' ';
	scr[159] = (4 * 16) * 256 + ' ';
	scr[158] = (4 * 16) * 256 + ' ';
	scr[157] = (4 * 16) * 256 + ' ';
	scr[156] = (4 * 16) * 256 + ' ';
	scr[155] = (4 * 16) * 256 + ' ';
	scr[239] = (4 * 16) * 256 + ' ';
	scr[319] = (4 * 16) * 256 + ' ';
	scr[24 * 80] = (4 * 16) * 256 + ' ';
	scr[24 * 80 + 1] = (4 * 16) * 256 + ' ';
	scr[24 * 80 + 2] = (4 * 16) * 256 + ' ';
	scr[24 * 80 + 3] = (4 * 16) * 256 + ' ';
	scr[24 * 80 + 4] = (4 * 16) * 256 + ' ';
	scr[23 * 80] = (4 * 16) * 256 + ' ';
	scr[22 * 80] = (4 * 16) * 256 + ' ';
	scr[25 * 80 - 1] = (4 * 16) * 256 + ' ';
	scr[25 * 80 - 2] = (4 * 16) * 256 + ' ';
	scr[25 * 80 - 3] = (4 * 16) * 256 + ' ';
	scr[25 * 80 - 4] = (4 * 16) * 256 + ' ';
	scr[25 * 80 - 5] = (4 * 16) * 256 + ' ';
	scr[24 * 80 - 1] = (4 * 16) * 256 + ' ';
	scr[23 * 80 - 1] = (4 * 16) * 256 + ' ';
	for (int i = 0;i < 16;i++) {
		scr[5 * 80 + 33 + i] = (4 * 16) * 256 + ' ';
		scr[20 * 80 + 33 + i] = (4 * 16) * 256 + ' ';
	}
	for (i = 0;i < 8;i++) {
		scr[(9 + i) * 80 + 25] = (4 * 16) * 256 + ' ';
		scr[(9 + i) * 80 + 56] = (4 * 16) * 256 + ' ';
	}
	
}
void f4() {
	for (int i = 0;i < 80;i++) {
		scr[80 + i] = (4 * 16) * 256 + ' ';
		scr[80 * 24 + i] = (4 * 16) * 256 + ' ';
	}
	for (i = 1;i < 25;i++)
		scr[26+80*i] = (4 * 16) * 256 + ' ';
}

void f5() {
	for (int i = 1;i < 25;i++)
		scr[26 + 80 * i] = (4 * 16) * 256 + ' ';
	for (i = 0;i < 27;i++)
		scr[16 * 80 + i] = (4 * 16) * 256 + ' ';
	for (i = 46;i < 80;i++)
		scr[8 * 80 + i] = (4 * 16) * 256 + ' ';
	for (i = 8;i < 25;i++)
		scr[80 * i + 46] = (4 * 16) * 256 + ' ';
	for (i = 46;i < 80;i++)
		scr[24 * 80 + i] = (4 * 16) * 256 + ' ';
	for (i = 8;i < 16;i++)
		scr[80 * i + 79] = (4 * 16) * 256 + ' ';
}



