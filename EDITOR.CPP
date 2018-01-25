#include <iostream.h>
#include <conio.h>
#include <dos.h>

void wprint(char str[], int x, int y, int tcolor, int bgcolor, int isdark, int blink);
void(*func[10])();

int xcursor,overWrite,lang;
unsigned char c;
int PT[10][10] = { {1,2,3,4,5,6,7,8,9,10}, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 }, { 1,2,3,4,5,6,7,8,9,10 } };
int far *scr = (int far*)0xb8000000;
int iskbfree = 1, EOO = 0;
char convertC[58][2] =
 {
	{ 'h' , 144 },
	{ 'H',141 },
	{ 'm', 143 },
	{ 'M', 142 },
	{ 'f', 146 },
	{ 'F', 146 },
	{ '\\', 148 },
	{ 'j', 150 },
	{ 'J', 150 },
	{ 'e', 152 },
	{ 'E', 152 },
	{ '[', 154 },
	{ ']', 156 },
	{ 'p', 158 },
	{ 'P', 158 },
	{ 'o', 160 },
	{ 'O', 160 },
	{ 'n', 162 },
	{ 'N', 162 },
	{ 'b', 163 },
	{ 'B', 163 },
	{ 'v', 164 },
	{ 'V', 164 },
	{ 'c', 165 },
	{ 'C', 166 },
	{ 's', 167 },
	{ 'S', 167 },
	{ 'a', 169 },
	{ 'A', 169 },
	{ 'w', 171 },
	{ 'W', 171 },
	{ 'q', 173 },
	{ 'Q', 173 },
	{ 'x', 175 },
	{ 'X', 175 },
	{ 'z', 224 },
	{ 'Z', 224 },
	{ 'u', 225 },
	{ 'U', 225 },
	{ 'y', 229 },
	{ 'Y', 229 },
	{ 't', 233 },
	{ 'T', 233 },
	{ 'r', 235 },
	{ 'R', 235 },
	{ ';', 237 },
	{ '\'',239 },
	{ 'g', 241 },
	{ 'G', 241 },
	{ 'l', 244 },
	{ 'L', 244 },
	{ 'k', 246 },
	{ 'K', 246 },
	{ ',', 248 },
	{ 'i', 249 },
	{ 'I', 249 },
	{ 'd', 253 },
	{ 'D', 253 }
};
unsigned char rightchar[35][4] =
{
	{144,145,144,145},
	{141,141,141,141},
	{143,143,143,143},
	{142,142,142,142},
	{146,146,147,147},
	{148,148,149,149},
	{150,150,151,151},
	{152,152,153,153},
	{154,154,155,155},
	{156,156,157,157},
	{158,158,159,159},
	{160,160,161,161},
	{162,162,162,162},
	{163,163,163,163},
	{164,164,164,164},
	{165,165,165,165},
	{166,166,166,166},
	{167,167,168,168},
	{169,169,170,170},
	{171,171,172,172},
	{173,173,174,174},
	{175,175,175,175},
	{224,224,224,224},
	{225,226,228,227},
	{229,230,232,231},
	{233,233,234,234},
	{235,235,236,236},
	{237,237,238,238},
	{239,239,240,240},
	{241,241,243,243},
	{244,244,245,245},
	{246,246,247,247},
	{248,248,248,248},
	{249,249,251,250},
	{253,252,254,254}
};
unsigned char tohead[26] = {142,146,148,150,152,154,156,158,160,167,169,171,173,175,224,225,229,233,235,237,239,241,244,246,249,253};
int numOfPersian = 0, wasNumber = 0;
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
void warning();

enum language
{
	EN = 0, FA = 1
};

struct stack
{
	unsigned char a[100];
	int last;
	void init()
	{
		last = -1;
	}
	int isfull()
	{
		return last == 99;
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
		//else
			//warning();
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

	for (int i = 0;i < xcursor;i++)
	{
		if (p.a[p.last - i] < 140)
			scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + p.a[p.last - i];
		else
		{
			int left, right;
			if (i == 0) 
			{
				right = 0;
				for (int j = 0;j <= 25 && right == 0;j++)
				{
					if (q.last>=0 && tohead[j] == q.a[q.last])
						right = 1;
				}

				left = 0;
				if (p.a[p.last - i - 1]>141)
					left = 1;

				int line;
				int t = 0;
				for (line = 0;t == 0;line++)
					if (rightchar[line][0] == p.a[p.last - i])
						t = 1;
				line--;
				if (left == 0 && right == 0)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][0];
				else if (left == 0 && right == 1)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][1];
				else if (left == 1 && right == 0)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][2];
				else if (left == 1 && right == 1)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][3];
			}

			//else if (i == xcursor - 1)
			else if (i == p.last)
			{
				right = 0;
				for (int j = 0;j <= 25 && right == 0;j++)
				{
					if (tohead[j] == p.a[p.last - i + 1])
						right = 1;
				}
				int line;
				int t = 0;
				for (line = 0;t == 0;line++)
					if (rightchar[line][0] == p.a[p.last - i])
						t = 1;
				line--;
				if (right == 1)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][1];
				else
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][0];

			}

			else
			{
				right = 0;
				for (int j = 0;j <= 25 && right == 0;j++)
				{
					if (tohead[j] == p.a[p.last - i + 1])
						right = 1;
				}

				left = 0;
				if (p.a[p.last - i - 1]>141)
					left = 1;

				int line;
				int t = 0;
				for (line = 0;t == 0;line++)
					if (rightchar[line][0] == p.a[p.last - i])
						t = 1;
				line--;
				if (left == 0 && right == 0)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][0];
				else if (left == 0 && right == 1)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][1];
				else if (left == 1 && right == 0)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][2];
				else if (left == 1 && right == 1)
					scr[9 * 80 + 20 + xcursor - i - 1] = 15 * 256 + rightchar[line][3];
			}
		}
	}
	for (i = q.last;i >= 0;i--) {
		if ((q.last - i + xcursor < 40)&&(q.isempty()) ||(q.last - i + xcursor <= 40)&&(!q.isempty())) {
			if (q.a[i] < 140)
				scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + q.a[i];
			else
			{
				int left, right;
				if (i == q.last) 
				{
					right = 0;
					for (int j = 0;j <= 25 && right == 0;j++)
					{
						if (tohead[j] == q.a[i - 1])
							right = 1;
					}
					left = 0;
					if (p.last>=0 && p.a[p.last]>141)
						left = 1;
					
					int line;
					int t = 0;
					for (line = 0;t == 0;line++)
						if (rightchar[line][0] == q.a[i])
							t = 1;
					line--;
					if (left == 0 && right == 0)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][0];
					else if (left == 0 && right == 1)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][1];
					else if (left == 1 && right == 0)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][2];
					else if (left == 1 && right == 1)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][3];
				}

				else if (i == 0) 
				{
					left = 0;
					if (q.a[i + 1]>141)
						left = 1;

					int line;
					int t = 0;
					for (line = 0;t == 0;line++)
						if (rightchar[line][0] == q.a[i])
							t = 1;
					line--;
					if(left==1)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][2];
					else
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][0];
				}

				else
				{
					right = 0;
					for (int j = 0;j <= 25 && right == 0;j++)
					{
						if (tohead[j] == q.a[i - 1])
							right = 1;
					}

					left = 0;
					if (q.a[i + 1]>141)
						left = 1;

					int line;
					int t = 0;
					for (line = 0;t == 0;line++)
						if (rightchar[line][0] == q.a[i])
							t = 1;
					line--;
					if (left == 0 && right == 0)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][0];
					else if (left == 0 && right == 1)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][1];
					else if (left == 1 && right == 0)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][2];
					else if (left == 1 && right == 1)
						scr[9 * 80 + 20 + xcursor + q.last - i] = 15 * 256 + rightchar[line][3];
				}

			}
		}
	}


	if (xcursor > p.last)
		scr[9 * 80 + 18] = (8) * 256 + 17;
	else
		scr[9 * 80 + 18] = (10) * 256 + 17;
	if(40-xcursor>=q.last)
		scr[9 * 80 + 62] = (8) * 256 + 16;
	else
		scr[9 * 80 + 62] = (10) * 256 + 16;
	
	if (!overWrite || EOO == 1 || q.isempty())
		gotoxy(xcursor + 20 + 1, 10);
	else
	{
		gotoxy(1,1);
		scr[9 * 80 + xcursor + 20 ] += (128+16*5) * 256;
	}
	
}

int getEvent()
{
	int far *KB = (int far*)0x00400017;
	int t = 1;
	while (t) {
		if ((*KB == 9 || *KB == 9 + 16 || *KB == 9 + 32 || *KB == 9 + 64 || *KB == 9 + 16 + 32 || *KB == 9 + 16 + 64 || *KB == 9 + 32 + 64 || *KB == 9 + 16 + 32 + 64 || *KB == 9 + 128 || *KB == 9 + 16 + 128 || *KB == 9 + 32 + 128 || *KB == 9 + 64 + 128 || *KB == 9 + 16 + 32 + 128 || *KB == 9 + 16 + 64 + 128 || *KB == 9 + 32 + 64 + 128 || *KB == 9 + 16 + 32 + 64 + 128 ) && iskbfree) 
		{
			iskbfree = 0;
			return 8;
		}
		else if ((*KB == 0 || *KB == 0 + 16 || *KB == 0 + 32 || *KB == 0 + 64 || *KB == 0 + 16 + 32 || *KB == 0 + 16 + 64 || *KB == 0 + 32 + 64 || *KB == 0 + 16 + 32 + 64 || *KB == 0 + 128 || *KB == 0 + 16 + 128 || *KB == 0 + 32 + 128 || *KB == 0 + 64 + 128 || *KB == 0 + 16 + 32 + 128 || *KB == 0 + 16 + 64 + 128 || *KB == 0 + 32 + 64 + 128 || *KB == 0 + 16 + 32 + 64 + 128 ) && !iskbfree)
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
					if (lang == EN) 
					{
						c = cTemp;
					}
					else 
					{
						if (cTemp >= 48 && cTemp <= 57)
							c = cTemp - 48 + 128;
						else
						{
							int chech = 0;
							for (int j = 0;j < 58;j++)
							{
								if (convertC[j][0] == cTemp)
								{
									c = convertC[j][1];
									chech = 1;
								}
							}
							if (chech == 0)
								c = cTemp;
						}
					}
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
		scr[9 * 80 + 62] = (8) * 256 + 16;
		scr[9 * 80 + 18] = (8) * 256 + 17;
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
	if (lang == EN)
	{
		
		if (!p.isfull())
		{
			EOO = 0;
			if (xcursor < 40)
				xcursor++;

			p.push(c);
			if (overWrite == 1 && q.last >= 0)
				q.last--;
		}
		else
			warning();
	}
	else if (c >= 128 && c <= 137)
	{
		if (!p.isfull())
		{
			EOO = 0;
			//numOfPersian++;//||
			wasNumber = 1;
			if (xcursor < 40)
				xcursor++;
			p.push(c);

			if (overWrite == 1 && q.last >= 0 /*&& q.a[q.last]>=128 && q.a[q.last]<=137*/)//||
				q.last--;
		}
		else
			warning();
	}
	else
	{
		
		if (!q.isfull() || (overWrite && p.last == -1 && EOO == 0))
		{
			/*if (wasNumber == 1)
			{
				while (p.a[p.last] >= 128 && p.a[p.last] <= 137)
				{
					q.push(p.pop());
					xcursor--;
					numOfPersian++;//||
				}
				wasNumber = 0;
			}*/
			numOfPersian++;
			if (overWrite == 1 && p.last >= 0 && EOO == 0)
			{
				if (q.last >= 0)
					q.last--;
				q.push(c);
				q.push(p.pop());
				if (xcursor > 0)
					xcursor--;

			}
			else if (overWrite && p.last == -1 && EOO == 0)
			{
				if (q.last >= 0)
					q.last--;
				q.push(c);
				EOO = 1;
			}
			else if (overWrite && EOO)
			{
				q.push(c);
			}
			else
			{
				q.push(c);
			}
		}
		else
			warning();
	}
}
void f2()//delete
{
	/*//wasNumber = 0;//||
	numOfPersian = 0;
	if (lang == EN)
		q.pop();
	else
	{
		if (xcursor > 0)
			xcursor--;
		p.pop();
	}*/
	q.pop();
}
void f3()//bksp
{
	/*wasNumber--;
	if (numOfPersian > 0)//||
		numOfPersian--;
	if (lang == EN)
	{
		if (xcursor > 0)
			xcursor--;
		p.pop();
	}
	else
		q.pop();*/
	if (xcursor > 0)
		xcursor--;
	p.pop();
}
void f4()//right
{
	wasNumber = 0;
	numOfPersian = 0;
	if (EOO)
		EOO = 0;

	else if (!p.isfull())
	{

		if (xcursor < 40 && !q.isempty())
			xcursor++;
		p.push(q.pop());
	}
	else
		warning();

}
void f5()//left
{
	wasNumber = 0;
	numOfPersian = 0;
	if (!q.isfull())
	{
		if (overWrite && p.last == -1 && EOO == 0 && lang == FA)
		{
			EOO = 1;
		}

		if (xcursor > 0)
			xcursor--;

		q.push(p.pop());
	}
	else
		warning();
}
void f6()
{
	if (!overWrite)
		wprint("insert", 14, 50, 5, 0, 1, 0);
	else
		wprint("      ", 14, 50, 0, 0, 0, 0);
	overWrite = !overWrite;
}
void f7()//home
{
	wasNumber = 0;
	numOfPersian = 0;
	if (q.last + p.last + 2 <= 100)
	{
		xcursor = 0;
		while (!p.isempty())
		{

			q.push(p.pop());
		}
	}
	else
	{
		warning();
	}
}
void f8()//end
{
	wasNumber = 0;
	numOfPersian = 0;
	if (q.last + p.last + 2 <= 100)
	{
		xcursor = p.last + q.last + 2;
		if (xcursor > 40)
			xcursor = 40;
		while (!q.isempty())
		{

			p.push(q.pop());

		}
		if (EOO)
			EOO = 0;
	}
	else
		warning();
}
void f9()
{
	if (lang)
	{
		/*if (overWrite && !EOO && numOfPersian!=0)//||
			numOfPersian++;
		if (numOfPersian + p.last <= 100)
		{
			for (;numOfPersian > 0;numOfPersian--)
			{
				p.push(q.pop());
				if (xcursor < 40)
					xcursor++;
			}
		}
		else
			warning();*/
		lang = 0;
		wprint(" EN ", 14, 60, 7, 1, 1, 0);
	}
	else
	{
		lang = 1;
		wprint(" FA ", 14, 60, 7, 1, 1, 0);
	}
	numOfPersian = 0;


}

void warning()
{

	wprint("there is not enough space", 11, 28, 4, 0, 0, 1);

	sound(2400);
	delay(200);
	nosound();
	delay(50);
	sound(2400);
	delay(200);
	nosound();
	delay(50);
	sound(2400);
	delay(200);
	nosound();
	delay(50);
	sound(2400);
	delay(200);
	nosound();
	delay(50);
	sound(2400);
	delay(200);
	nosound();
	delay(50);
	wprint("                         ", 11, 28, 0, 0, 0, 0);
	int far * first = (int far *) 0X0000041A;
	int far * last = (int far *) 0X0000041C;
	*last = *first;
}