#include<iostream.h>
#include<conio.h>


int main(){
	clrscr();
	cout << "Hello!\nWelcome to program A of FCP 101!\n\nplease enter a number:\n";
	int x=0;
	char c=getch();
	while(c!=27){
		cout << c;
		if(c!=13){
			x=(x*10)+(int)c-48;
		}
		else{
			cout << "\nModule of "<< x <<" by 3 is: " << x%3 << "\n\nPlease enter a number:\n";
			x=0;
		}
		c=getch();


	}


	cout << "Oops! you've presses Esc button! come back soon! Happy ending for now";
	return 0;
}