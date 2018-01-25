#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
#include <iostream.h>

int matrix [2][50],h=1,k,stage=1,length=2,w=1,d=0;  //k=random scr   //h=1 right
char key;
int far* scr=(int far *)0xb8000000;

void init (int stage,int d)
{
   for(int i=2;i<25;i++)
   {
     for(int j=0;j<80;j++)
		  *(scr+i*80+j)=0;
   }

   for(int n=50;n<80;n++)
   {
    *(scr+n)=0;
   }
   for(int y=0;y<80;y++)
   {
     *(scr+1*80+y)=15*256+196;
   }
   *(scr+2)=15*256+'S';
   *(scr+3)=15*256+'t';
   *(scr+4)=15*256+'a';
   *(scr+5)=15*256+'g';
   *(scr+6)=15*256+'e';
   *(scr+7)=15*256+':';
   *(scr+9)=15*256+(stage+48);

   *(scr+17)=15*256+'S';
   *(scr+18)=15*256+'c';
   *(scr+19)=15*256+'o';
   *(scr+20)=15*256+'r';
   *(scr+21)=15*256+'e';
   *(scr+22)=15*256+':';
   *(scr+24)=0;
   *(scr+25)=0;
   *(scr+26)=15*256+(d+48);

   *(scr+9*80+40)=97*256+ ':';
   *(scr+9*80+39)=97*256;
   matrix[0][0]=9;
   matrix[0][1]=40;
   matrix[1][0]=9;
   matrix[1][1]=39;

 if(stage==2)
  {
    for(int t=0;t<80;t++)
    {
     *(scr+2*80+t)=16*256;
     *(scr+24*80+t)=16*256;
    }
   for(int q=2;q<25;q++)
    {
     *(scr+q*80+0)=16*256;
     *(scr+q*80+79)=16*256;
    }
  }

 if(stage==3)
  {
    for(int c=0;c<80;c++)
     {
      *(scr+2*80+c)=16*256;
      *(scr+24*80+c)=16*256;
     }
      *(scr+2*80+8)=0;
      *(scr+24*80+8)=0;
      *(scr+2*80+64)=0;
      *(scr+24*80+64)=0;

   for(int r=2;r<24;r++)
     {
      *(scr+r*80+0)=16*256;
      *(scr+r*80+79)=16*256;
     }
     *(scr+12*80+0)=0;
     *(scr+12*80+79)=0;
     *(scr+13*80+0)=0;
     *(scr+13*80+79)=0;

   for(int e=7;e<14;e++)
     {
      *(scr+e*80+17)=16*256;
     }

   for(int f=22;f<40;f++)
     {
      *(scr+17*80+f)=16*256;
     }

   for(int s=60;s<70;s++)
     {
      *(scr+10*80+s)=16*256;
     }
  }
}//end function init

void food(int &number)
{
  k=rand()%1680;
  while(scr[k+240]!=0)
   {
    k=rand()%1680;
   }
  scr[k+240]=199*256+(48+number);
}//end function food

void eat(int &number,int &length,int k)
{
   d+=number;
   *(scr+26)=15*256+(d+48);
   if(d>9)
   {
    *(scr+25)=15*256+((d/10)+48);
    *(scr+26)=15*256+((d%10)+48);
   }
   if(d>99)
   {
    *(scr+24)=15*256+((d/100)+48);
    *(scr+25)=15*256+(((d/10)%10)+48);
    *(scr+26)=15*256+(((d-100)%10)+48);
   }
   for(int a=length;a<length+number;a++)
   {
    matrix[a][0]=(k+240)/80;
    matrix[a][1]=(k+240)%80;
   }
   length+=number;
   number++;
  if(number==10)
   {
    number=0;
   }
   scr[k+240]=0;
}//end function eat

void show(int length)
{
   for(int i=1;i<length;i++)
   {
    *(scr+matrix[i][0]*80+matrix[i][1])=97*256;
   }
    *(scr+matrix[0][0]*80+matrix[0][1])=97*256+':';
}//end function show

int funckey(char&key)
{
  int T=0;
  key=getch();
  if (!key){
	    T=1;
	    key=getch();
	   }
   return T; // T=1:funckey T=0:datakey
}//end function funckey

void up(int length)
{
   for(int i=length-1;i>0;i--)
   {
    matrix[i][0]=matrix[i-1][0];
    matrix[i][1]=matrix[i-1][1];
    if(matrix[0][0]>1)
      matrix[0][0]--;
   }
}//end function up

void down(int length)
{
   for(int i=length-1;i>0;i--)
   {
    matrix[i][0]=matrix[i-1][0];
    matrix[i][1]=matrix[i-1][1];
    if(matrix[0][0]<25)
      matrix[0][0]++;
   }
}//end function down

void left(int length)
{
   for(int i=length-1;i>0;i--)
   {
     matrix[i][0]=matrix[i-1][0];
     matrix[i][1]=matrix[i-1][1];
     if(matrix[0][1]>-1)
	matrix[0][1]--;
   }
}//end function left

void right(int length)
{
  for(int i=length-1;i>0;i--)
   {
    matrix[i][0]=matrix[i-1][0];
    matrix[i][1]=matrix[i-1][1];
    if(matrix[0][1]<80)
      matrix[0][1]++;
   }
}//end function right

void docommand(int &number,int T,char key,int length,int k)
{
 if(w==1){
	  if(T==1)
	  {
	     switch(key){

		case 72:if(h!=2)
			h=0;
			break;

		case 75:if(h!=1)
			h=3;
			break;

		case 77:if(h!=3)
			h=1;
			break;

		case 80:if(h!=0)
			h=2;
			break;
		     }

	  }
	   *(scr+matrix[length-1][0]*80+matrix[length-1][1])=0;

	      if(h==0)
	      {                                //up
	       up(length);
		 for(int j=0;j<length-1;j++)
		 {
		  if(matrix[j][0]==1)
		  matrix[j][0]=24;
		 }
	      }

	      if(h==3)
	      {                                //left
	       left(length);
		 for(int j=0;j<length-1;j++)
		 {
		  if(matrix[j][1]==-1)
		  matrix[j][1]=79;
		 }
	      }

	      if(h==1)
	      {                                //right
	       right(length);
		 for(int j=0;j<length-1;j++)
		 {
		  if(matrix[j][1]==80)
		  matrix[j][1]=0;
		 }
	      }

	      if(h==2)
	      {                                //down
	       down(length);
		 for(int j=0;j<length-1;j++)
		 {
		  if(matrix[j][0]==25)
		  matrix[j][0]=2;
		 }
	      }
  if(*(scr+matrix[0][0]*80+matrix[0][1])==16*256||*(scr+matrix[0][0]*80+matrix[0][1])==96*256)
  {
  *(scr+50)=132*256+'G';
  *(scr+51)=132*256+'A';
  *(scr+52)=132*256+'M';
  *(scr+53)=132*256+'E';
  *(scr+55)=132*256+'O';
  *(scr+56)=132*256+'V';
  *(scr+57)=132*256+'E';
  *(scr+58)=132*256+'R';
  *(scr+59)=132*256+'!';

  *(scr+68)=15*256+'"';
  *(scr+69)=143*256+'S';
  *(scr+70)=15*256+'"';
  *(scr+71)=15*256+':';
  *(scr+73)=15*256+'R';
  *(scr+74)=15*256+'E';
  *(scr+75)=15*256+'S';
  *(scr+76)=15*256+'T';
  *(scr+77)=15*256+'A';
  *(scr+78)=15*256+'R';
  *(scr+79)=15*256+'T';

  w=0;
  }
  if((matrix[0][0]*80+matrix[0][1])==k+240)
   {
     if(number==0&&stage<4)
     {
      init(++stage,d);
     }
     if(number==0&&stage==4)
     {
      w=0;
      *(scr+50)=132*256+'C';
      *(scr+51)=132*256+'O';
      *(scr+52)=132*256+'N';
      *(scr+53)=132*256+'G';
      *(scr+54)=132*256+'R';
      *(scr+55)=132*256+'A';
      *(scr+56)=132*256+'T';
      *(scr+57)=132*256+'U';
      *(scr+58)=132*256+'L';
      *(scr+59)=132*256+'A';
      *(scr+60)=132*256+'T';
      *(scr+61)=132*256+'I';
      *(scr+62)=132*256+'O';
      *(scr+63)=132*256+'N';
      *(scr+64)=132*256+'S';
      *(scr+65)=132*256+'!';

     }
     eat(number,length,k);
     if(w==1)
     food(number);
   }
 }
  show(length);
}//end function docommand

void main()
{
  int number=1,T;

  _setcursortype(_NOCURSOR);
  srand(time(NULL));
  init(stage,d);
  food(number);
  if(kbhit())
    T=funckey(key);

  while(key!=27 || T!=0)
   {
      if(stage==1)
      {
	 delay(140);
      }
      if(stage==2)
      {
	 delay(100);
      }
      if(stage==3)
      {
	 delay(60);
      }

    docommand(number,T,key,length,k);
    if(kbhit())
      T=funckey(key);
   }
}//end function main





