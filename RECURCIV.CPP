#include <iostream.h>
#include <conio.h>
int a[100][100]={0},b[10000]={0},c[1000]={0};
int k=0,min=10000;

void maz(int n,int x,int y);

int main(){
	clrscr();
	a[0][7]=1;a[1][0]=1;a[1][1]=1;a[1][3]=1;a[1][4]=1;a[1][5]=1;
	a[1][7]=1;a[2][0]=1;a[2][1]=1;a[2][7]=1;a[3][3]=1;a[3][4]=1;
	a[3][5]=1;a[3][6]=1;a[3][7]=1;a[4][1]=1;a[5][1]=1;a[5][2]=1;
	a[5][3]=1;a[5][4]=1;a[5][5]=1;a[5][6]=1;a[6][4]=1;a[6][5]=1;
	a[6][6]=1;a[7][0]=1;a[7][1]=1;a[7][2]=1;

	for (int i=0;i<=7;i++){
		for(int j=0;j<=7;j++){
			cout<<a[i][j]<<" ";
		}
		cout << "\n";
	}
	int n;
	cin >> n;
	maz(n-1,n-1,n-1) ;
	for (i=0;i<min;i++)
	cout << c[i]<<" ";

	cout << min;
	getch();
	return 0;
}

void maz (int n,int x, int y){
	if(x==0 && y==0 && k<min){
		min=k;
		for (int i=0;i<=min;i++)
			c[i]=b[i];

	}//end if

	// right=1  up=2  left=3  down=4
	if(x+1<n && a[x+1][y]==0){
		a[x][y]=2;
		b[k]=4;
		k++;
		maz(n,x+1,y);
		k--;
		b[k]=0;
		a[x][y]=0;
	}
	if(y+1<n && a[x][y+1]==0){
		a[x][y]=2;
		b[k]=1;
		k++;
		maz(n,x,y+1);
		k--;
		b[k]=0;
		a[x][y]=0;
	}
	if(x-1>=0 && a[x-1][y]==0){
		a[x][y]=2;
		b[k]=2;
		k++;
		maz(n,x-1,y);
		k--;
		b[k]=0;
		a[x][y]=0;
	}
	if(y-1>=0 && a[x][y-1]==0){
		a[x][y]=2;
		b[k]=3;
		k++;
		maz(n,x,y-1);
		k--;
		b[k]=0;
		a[x][y]=0;
	}

}






