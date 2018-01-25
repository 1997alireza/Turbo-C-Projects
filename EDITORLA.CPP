#include <iostream.h>
#include <conio.h>

int xcursor,overWrite,lang;
char c;
int PT[10][10] = { {1,2,3,4,5,6,7,8,9,10}, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 } };
int far *scr = (int far*)0xb8000000;
int iskbfree = 1;


void wprint(char str[], int x, int y, int tcolor, int bgcolor, int isdark, int blink);
void(*func[10])();
void f0();
void f1();
void f2();
void f3();
void f4();
void f5();
void f6();
void f7();
void f8();
void f9();
void init();
int getEvent();
void display();


enum language
{
	EN = 0, FA = 1
};

struct stack
{
	char a[1000];
	int last;
	void init()
	{
		last = -1;
	}
	int isfull()
	{
		return last == 999;
	}
	int isempty()
	{
		return last == -1;
	}
	void push(char x)
	{
		if (!isfull() && x != 0)
		{
			
			
			last++;	
			a[last] = x;
		}
	}
	int pop()
	{
		if (!isempty())
		{
			return a[last--];
		}
		else
		{
			return 0;
		}
	}
}p,q;

void main() {
	

	init();
	int currentstate = 0;
	while (currentstate>=0 && currentstate<=9)
	{
		func[currentstate]();
		display();
		int event = getEvent();
		currentstate = PT[currentstate][event];


	}

}

void display()
{
	wprint("                                         ",9,20,7,0,1,0);
	gotoxy(xcursor+20+1,10);

	for (int i = 0;i < xcursor;i++)
	{
		scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + p.a[p.last - i];
	}
	for (i = q.last;i >= 0;i--) {
		if(q.last-i+xcursor<40)
			scr[9*80+20+xcursor+q.last-i]= 15 * 256 + q.a[i];
	}
	if (xcursor > p.last)
		scr[9 * 80 + 18] = (8) * 256 + '<';
	else
		scr[9 * 80 + 18] = (10) * 256 + '<';
	if(40-xcursor>q.last)
		scr[9 * 80 + 62] = (8) * 256 + '>';
	else
		scr[9 * 80 + 62] = (10) * 256 + '>';

}

int getEvent()
{
	int far *KB = (int far*)0x00400017;
	int t = 1;
	while (t) {
		if ((*KB == 9 || *KB == 9 + 16 || *KB == 9 + 32 || *KB == 9 + 64 || *KB == 9 + 16 + 32 || *KB == 9 + 16 + 64 || *KB == 9 + 32 + 64 || *KB == 9 + 16 + 32 + 64) && iskbfree) 
		{
			iskbfree = 0;
			return 8;
		}
		else if ((*KB == 0 || *KB == 0 + 16 || *KB == 0 + 32 || *KB == 0 + 64 || *KB == 0 + 16 + 32 || *KB == 0 + 16 + 64 || *KB == 0 + 32 + 64 || *KB == 0 + 16 + 32 + 64) && !iskbfree)
		{
			iskbfree = 1;
		}
		else if(kbhit()){
			char cTemp = getch();
			if (!cTemp)
			{
				cTemp = getch();
				switch (cTemp)
				{
				case 83: return 1;//del
				case 77: return 3;//right
				case 75: return 4;//left
				case 82: return 5;//insert
				case 71: return 6;//home
				case 79: return 7;//end
				}
			}
			else	//data key
			{
				if (cTemp == 8)//BKSP
					return 2;
				else if (cTemp == 27)
				{
					return 9;
				}
				else if (cTemp >= 32 && cTemp <= 126)//harf
				{
					c = cTemp;
					return 0;
				}
			}
		}
	}
}

void init()
{
	for (int j = 0;j < 2000;j++)
	{
		scr[j] = 0;
	}
	overWrite = 0;
	xcursor = 0;
	lang = EN;
	c = 0;
	func[0] = f0;
		func[1] = f1;
		func[2] = f2;
		func[3] = f3;
		func[4] = f4;
		func[5] = f5;
		func[6] = f6;
		func[7] = f7;
		func[8] = f8;
		func[9] = f9;
		display();
		scr[9 * 80 + 19] = (11 ) * 256 + 179;
		scr[9 * 80 + 61] = (11 ) * 256 + 179;
		for (int i = 0;i < 41;i++)
		{
			scr[8 * 80 + 20+i] = (11 ) * 256 + 196;
			scr[10 * 80 + 20 + i] = (11) * 256 + 196;
		}
		scr[8 * 80 + 19] = (11) * 256 + 218;
		scr[10 * 80 + 19] = (11) * 256 + 192;
		scr[8 * 80 + 61] = (11) * 256 + 191;
		scr[10 * 80 + 61] = (11) * 256 + 217;
		scr[9 * 80 + 62] = (8) * 256 + '>';
		scr[9 * 80 + 18] = (8) * 256 + '<';
		for (i = 0;i < 10;i++)
		{
			scr[(6+i) * 80 + 15] = 4 * 256 + 186;
			scr[(6+i) * 80 + 65] = 4 * 256 + 186;
		}
		for (i = 16;i < 65;i++)
		{
			scr[5 * 80 + i] = 4 * 256 + 205;
			scr[16 * 80 + i] = 4 * 256 + 205;
		}
		scr[5 * 80 + 15] = 4 * 256 + 201;
		scr[16 * 80 + 15] = 4 * 256 + 200;
		scr[5 * 80 + 65] = 4 * 256 + 187;
		scr[16 * 80 + 65] = 4 * 256 + 188;
		wprint("press Esc to exit", 14, 18, 1, 0, 0, 0);
		wprint(" EN ", 14, 60, 7, 1, 1, 0);


}


void wprint(char str[], int x, int y, int tcolor, int bgcolor, int isdark, int blink) {

	int i = 0;
	while (str[i] != NULL) {
		scr[x * 80 + y + i] = (tcolor + (isdark * 8) + (bgcolor * 16) + (blink * 128)) * 256 + str[i];
		i++;
	}
}

void f0()
{
	xcursor = 0;
	p.init();
	q.init();
}
void f1()
{

	if (xcursor < 40)
		xcursor++;
	p.push(c);
	
	if (overWrite == 1 && q.last>=0)
		q.last--;
}
void f2()
{
	
	q.pop();
}
void f3()
{
	
	if (xcursor > 0)
		xcursor--;
	p.pop();
}
void f4()
{
	
	if (xcursor < 40 && !q.isempty())
		xcursor++;
	
	p.push(q.pop());

}
void f5()
{
	if (xcursor > 0)
		xcursor--;
	
	q.push(p.pop());
}
void f6()
{
	
	overWrite = !overWrite;
}
void f7()
{
	
	xcursor = 0;
	while (!p.isempty())
	{
		
		q.push(p.pop());
	}
}
void f8()
{
	xcursor = p.last + q.last + 2;
	if (xcursor > 40)
		xcursor = 40;
	while (!q.isempty())
	{
		
		p.push(q.pop());

	}
}
void f9()
{
	if (lang)
	{
		lang = 0;
		wprint(" EN ", 14, 60, 7, 1, 1, 0);
	}
	else
	{
		lang = 1;
		wprint(" FA ", 14, 60, 7, 1, 1, 0);
	}



}