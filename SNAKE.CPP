#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

void wprint(char *str, int x, int y, int tcolor, int bgcolor, int isdark ,int blink);
void init(int level, int score);
void docommand();
void play();
void display();

int far * scr = (int far *)0xb8000000;
int vector=1, end=0;
int snake[50][2] = { -1 };

int main() {
	clrscr();
	init(0,0);

	while (1) {
		if (kbhit) {
			docommand();
			if (end)
				return 0;
		}
		play();
	}

}

void play() {
	display();


}

void display() {
	if (vector == 1)
		scr[snake[0][0] * 80 + snake[0][1]] = (4 + 16 * 6) * 256 + '>';
	else if (vector == 2)
		scr[snake[0][0] * 80 + snake[0][1]] = (4 + 16 * 6) * 256 + '^';
	else if (vector == 3)
		scr[snake[0][0] * 80 + snake[0][1]] = (4 + 16 * 6) * 256 + '<';
	else if (vector == 4)
		scr[snake[0][0] * 80 + snake[0][1]] = (4 + 16 * 6) * 256 + 'v';
	for (int i = 1;i < 50;i++) {
		if (snake[i][0] != -1) {
			scr[snake[i][0] * 80 + snake[i][1]] = (2 + 16 * 6) * 256 + '�';
		}
	}

}

void docommand() {
	char c = getch();
	int funckey = 0;
	if (!c) {
		c = getch();
		funckey = 1;
	}
	if (!funckey) {
		switch (c){
		case 27:		//exit
			 end=1;
			 break;
		}
	}
	else {
		switch (c){
		case 77:		//right
			vector = 1;

			break;

		case 72:		//up
			vector = 2;

			break;

		case 75:		//left
			vector = 3;

			break;

		case 80:		//down
			vector = 4;

			break;

		}
	}

}


void wprint(char *str, int x, int y, int tcolor, int bgcolor, int isdark, int blink) {

	int i = 0;
	while (str[i] != NULL) {
		scr[x * 80 + y + i] = (tcolor+(isdark*8)+(bgcolor*16)+(blink*128))*256 + str[i];
		i++;
	}
}


void init(int level , int score) {
	snake[0][0] = 12, snake[0][1] = 40, snake[1][0]=12, snake[1][1]=39, snake[2][0]=12, snake[2][1] =38 ;
	for (int j = 3;j < 50;j++)
		snake[j][0] = -1, snake[j][1] = -1;


	char *slevel,* sscore;
	for (int i = 0;i < 80;i++) {
		scr[i] = (16) * 256 + ' ';
	}
	for (i = 80;i < 2000;i++) {
		scr[i] = 7 * 16 * 256 + ' ';
	}

	sprintf(slevel, "%d", level);
	sprintf(sscore, "%d", score);

	wprint("LEVEL: 1   SCORE: 0   HighScore: 0", 0, 1, 3, 1, 1, 0);  //highsccor copy from file && chang color of number
	wprint(slevel, 0, 8, 3, 1, 1, 0);
	wprint(sscore, 0, 19, 3, 1, 1, 0);

	for (i = 24 * 80;i < 2000;i++) {
		scr[i] = 16*256 + ' ';
	}
	
}




