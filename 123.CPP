#include<iostream.h>
#include<conio.h>

void main(){

	int t=0,x;
	int far* screen = (int far*)0XB8000000;

	for(int i=0;i<2080;i=i+80){
		for(int z=35;z<=44;z++)
			screen[i-80+z]=' ';




		screen[i+35]=212*256+'A';
		screen[i+36]=212*256+'l';
		screen[i+37]=212*256+'i';
		screen[i+38]=212*256+' ';
		screen[i+39]=212*256+'j';
		screen[i+40]=212*256+'a';
		screen[i+41]=212*256+'f';
		screen[i+42]=212*256+'a';
		screen[i+43]=212*256+'r';
		screen[i+44]=212*256+'i';
		for (int l=0;l<10000;l++){
			for (int k=0;k<1000;k++)
				2*2;
		}

	}


}

