#include<iostream.h>
#include<conio.h>

void pali(int x, int y, int font, int bground);
void clear(int x, int y);
int far* screen = (int far*)0XB8000000;


int main(){
	clrscr();
	pali(35,0,0,0);
	int x=35,y=0,font=0,bground=0,check=0;
	char c=getch(),d;
	while(c!=27){
		if(c==0){
				d=getch();
				if(d==77 && x<70){
					clear(x,y);
					x++;
					pali(x,y,font,bground);
					check=1;

				}
				else if(d==72 && y>0){
					clear(x,y);
					y--;
					pali(x,y,font,bground);
					check=1;
				}
				else if(d==75 && x>0){
					clear(x,y);
					x--;
					pali(x,y,font,bground);
					check=1;
				}
				else if(d==80 && y<24){
					clear(x,y);
					y++;
					pali(x,y,font,bground);
					check=1;
				}


			}//if
			else if(c==9){
				font++;
				if(font==8)
					font=0;
				pali(x,y,font,bground);

			}
			else if(c==32){
				bground++;
				if(bground==8)
					bground=0;
				pali(x,y,font,bground);
			}
			c=getch();


		}



	return 0;
}

void pali(int x, int y, int font, int bground){


	screen[(y*80)+x+0]=(136+font+(16*bground))*256+'A';
	screen[(y*80)+x+1]=(136+font+(16*bground))*256+'l';
	screen[(y*80)+x+2]=(136+font+(16*bground))*256+'i';
	screen[(y*80)+x+3]=(136+font+(16*bground))*256+' ';
	screen[(y*80)+x+4]=(136+font+(16*bground))*256+'J';
	screen[(y*80)+x+5]=(136+font+(16*bground))*256+'a';
	screen[(y*80)+x+6]=(136+font+(16*bground))*256+'f';
	screen[(y*80)+x+7]=(136+font+(16*bground))*256+'a';
	screen[(y*80)+x+8]=(136+font+(16*bground))*256+'r';
	screen[(y*80)+x+9]=(136+font+(16*bground))*256+'i';

}
void clear(int x, int y){
	screen[(y*80)+x+0]=' ';
	screen[(y*80)+x+1]=' ';
	screen[(y*80)+x+2]=' ';
	screen[(y*80)+x+3]=' ';
	screen[(y*80)+x+4]=' ';
	screen[(y*80)+x+5]=' ';
	screen[(y*80)+x+6]=' ';
	screen[(y*80)+x+7]=' ';
	screen[(y*80)+x+8]=' ';
	screen[(y*80)+x+9]=' ';


}