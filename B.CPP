#include<iostream.h>
#include<conio.h>

int main(){
	clrscr();
	cout << "Hello!\nWelcome to program B of FCP 101!\n\nPlease enter the first operand:\n";
	char z,c=getch();
	int t=1,x=0,y=0;
	while (c!=27){
		cout << c;
		if(t==1){
			if(c!=13)
				x=(x*10)+(int)c-48;
			else{
				cout<<"\nplease enter the operation you want:\n";
				t++;
			}

		}
		else if(t==2){
			z=c;
			cout << "\nplease enter the second operand:\n";
			t++;

		}
		else if(t==3){
			if(c!=13)
				y=(y*10)+(int)c-48;
			else{
				if(z=='+')
					cout << "\nOK! the result is:\n"<<x+y<<"\n\n";
				else if(z=='-')
					cout << "\nOK! the result is:\n"<<x-y<<"\n\n";
				else if(z=='*')
					cout << "\nOK! the result is:\n"<<x*y<<"\n\n";
				else if(z=='/')
					cout << "\nOK! the result is:\n"<<x/y<<"\n\n";
				else{
					cout<<"\nthe given operation is not allowed please change it and try again.\n\n";

				}
				t=1;
				x=0;
				y=0;
				cout<<"please enter the first operand:\n";

			}

		}
		c=getch();

	}



	return 0;
}
