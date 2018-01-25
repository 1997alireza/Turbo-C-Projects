#include<iostream.h>
#include<conio.h>

int far* scr=(int far*)0xb8000000;

int lastx, lasty, lastatr, color, keydown;


void init();//make the home screen
int funckey(char &c);
void paint(char c,int fkey);
void pen(int jahat);
void fill(int p,int x,int y);

int main(){

	init();
	lastx=40;
	lasty=12;
	keydown=0;
	lastatr=(8-1)*256+219;

	char c;
	int fkey;
	pen(0);
	color=0;
	do{
		fkey=funckey(c);
		paint(c,fkey);



	}while(c!=27 || fkey!=0);
	return 0;
}
void paint(char c,int fkey){  scr[0]:*(scr+2)=
	if(fkey){
		switch(c){

			case 77:	//right
				if(lastx < 78)
					pen(1);
				break;

			case 72:        //up
				if(lasty > 1)
					pen(2);
				break;

			case 75:	//left
				if(lastx > 1)
					pen(3);
				break;

			case 80:	//down
				if(lasty < 19)
					pen(4);
				break;
							//end arow keys

			case 82: 		//insert
				if(keydown==0){
					keydown=1;
					scr[22*80+29]=(4+16)*256+'D';
					scr[22*80+30]=(4+16)*256+'O';
					scr[22*80+31]=(4+16)*256+'W';
					scr[22*80+32]=(4+16)*256+'N';

				}
				else{
					keydown=0;
					scr[22*80+29]=(4+16)*256+'U';
					scr[22*80+30]=(4+16)*256+'P';
					scr[22*80+31]=(4+16)*256+' ';
					scr[22*80+32]=(4+16)*256+' ';

				}
				lastatr=(8+color)*256+219;
				break;
			case 71:    	  //home
				init();
				keydown=0;

				pen(0);
				lastatr=(8-1)*256+219;
				break;

		}

	}
	else{
		if(c>=48 && c<=55){
			color=c-48-1;
			pen(0);
		}
		if(c==13 && lastatr!=(color+8)*256+219){
			scr[lasty*80+lastx]=lastatr;
			fill(lastatr,lastx,lasty);
			lastatr=(color+8)*256+219;
			pen(0);
		}
	}
}

void fill(int p,int x,int y){
	if(scr[y*80+x]!=p);
	else{
		scr[y*80+x]=(color+8)*256+219;
		if(x>=2)
			fill(p,x-1,y);
		if(x<=77)
			fill(p,x+1,y);
		if(y>=2)
			fill(p,x,y-1);
		if(y<=18)
			fill(p,x,y+1);

	}

}


void pen(int jahat){
	if(keydown==0){
		scr[lasty*80+lastx]=lastatr; //change back the last color
		switch(jahat){
			case 0:
				scr[lasty*80+lastx]=(136+color)*256+173;
				break;
			case 1:
				lastx++;
				lastatr=scr[lasty*80+lastx];
				scr[lasty*80+lastx]=(136+color)*256+173;
				break;
			case 2:
				lasty--;
				lastatr=scr[lasty*80+lastx];
				scr[lasty*80+lastx]=(136+color)*256+173;
				break;
			case 3:
				lastx--;
				lastatr=scr[lasty*80+lastx];
				scr[lasty*80+lastx]=(136+color)*256+173;
				break;
			case 4:
				lasty++;
				lastatr=scr[lasty*80+lastx];
				scr[lasty*80+lastx]=(136+color)*256+173;
				break;
		}//end switch

	}//end if
	else{
		switch(jahat){
			case 0:
				scr[lasty*80+lastx]=(136+color)*256+173;
				lastatr=(8+color)*256+219;
				break;
			case 1:
				scr[lasty*80+lastx]=(8+color)*256+219;
				lastx++;
				scr[lasty*80+lastx]=(136+color)*256+173;
				lastatr=(8+color)*256+219;
				break;
			case 2:
				scr[lasty*80+lastx]=(color+8)*256+219;
				lasty--;
				scr[lasty*80+lastx]=(136+color)*256+173;
				lastatr=(8+color)*256+219;
				break;
			case 3:
				scr[lasty*80+lastx]=(color+8)*256+219;
				lastx--;
				scr[lasty*80+lastx]=(136+color)*256+173;
				lastatr=(8+color)*256+219;
				break;
			case 4:
				scr[lasty*80+lastx]=(color+8)*256+219;
				lasty++;
				scr[lasty*80+lastx]=(136+color)*256+173;
				lastatr=(8+color)*256+219;
				break;

	}//end switch


	}//end else


}


int funckey(char &c){
	int fkey=0;
	c=getch();
	if(c==0){
		c=getch();
		fkey=1;
	}
	return fkey;

}

void init(){
	gotoxy(80,25);
	for(int i=0;i<2000;i++){   //clear screen
		scr[i]=(8-1)*256+219;
	}
	scr[0+0*80]=112*256+201;  	       //draw table
	scr[79+0*80]=112*256+187;
	scr[0+20*80]=112*256+200;
	scr[79+20*80]=112*256+188;

	for(i=1;i<79;i++){
		scr[i]=112*256+205;
		scr[i+80*20]=112*256+205;
	}
	for(i=1;i<20;i++){
		scr[i*80]=112*256+186;
		scr[(i+1)*80-1]=112*256+186;
	}					//draw table

	for(i=21*80;i<2000;i++){
		scr[i]=16*1*256+' ';
	}
	for(i=0;i<7;i++){		       	//draw row of color
		scr[22*80+2*i+4]=256*(16+8+i)+223;
		scr[23*80+(2*i)+4]=(8+i+16)*256+49+i;
	}
	scr[22*80+2]=256*(16+7)+223;
	scr[23*80+2]=256*(7+16)+48;
					//draw keys
	scr[23*80-4]=(7+16)*256+'d';
	scr[23*80-5]=(7+16)*256+'a';
	scr[23*80-6]=(7+16)*256+'o';
	scr[23*80-7]=(7+16)*256+'L';
	scr[24*80-5]=(7+16+8)*256+'3';
	scr[24*80-6]=(7+16+8)*256+'F';
	scr[23*80-11]=(7+16)*256+'e';
	scr[23*80-12]=(7+16)*256+'v';
	scr[23*80-13]=(7+16)*256+'a';
	scr[23*80-14]=(7+16)*256+'S';
	scr[24*80-12]=(7+16+8)*256+'2';
	scr[24*80-13]=(7+16+8)*256+'F';
	scr[23*80-18]=(7+16)*256+'e';
	scr[23*80-19]=(7+16)*256+'l';
	scr[23*80-20]=(7+16)*256+'e';
	scr[23*80-21]=(7+16)*256+'l';
	scr[23*80-22]=(7+16)*256+'e';
	scr[23*80-23]=(7+16)*256+'D';
	scr[24*80-19]=(7+16+8)*256+'e';
	scr[24*80-20]=(7+16+8)*256+'m';
	scr[24*80-21]=(7+16+8)*256+'o';
	scr[24*80-22]=(7+16+8)*256+'H';
	scr[24*80-27]=(7+16+8)*256+'r';
	scr[24*80-28]=(7+16+8)*256+'e';
	scr[24*80-29]=(7+16+8)*256+'t';
	scr[24*80-30]=(7+16+8)*256+'n';
	scr[24*80-31]=(7+16+8)*256+'E';
	scr[23*80-28]=(7+16)*256+'l';
	scr[23*80-29]=(7+16)*256+'l';
	scr[23*80-30]=(7+16)*256+'i';
	scr[23*80-31]=(7+16)*256+'F';
	scr[24*80-36]=(7+16+8)*256+'t';
	scr[24*80-37]=(7+16+8)*256+'r';
	scr[24*80-38]=(7+16+8)*256+'e';
	scr[24*80-39]=(7+16+8)*256+'s';
	scr[24*80-40]=(7+16+8)*256+'n';
	scr[24*80-41]=(7+16+8)*256+'I';
	scr[23*80-38]=(7+16)*256+'n';
	scr[23*80-39]=(7+16)*256+'e';
	scr[23*80-40]=(7+16)*256+'P';       //draw keys end

	scr[22*80+22]=(4+16)*256+'P';
	scr[22*80+23]=(4+16)*256+'e';
	scr[22*80+24]=(4+16)*256+'n';
	scr[22*80+25]=(4+16)*256+' ';
	scr[22*80+26]=(4+16)*256+'i';
	scr[22*80+27]=(4+16)*256+'s';
	scr[22*80+28]=(4+16)*256+' ';
	scr[22*80+29]=(4+16)*256+'U';
	scr[22*80+30]=(4+16)*256+'P';


}

