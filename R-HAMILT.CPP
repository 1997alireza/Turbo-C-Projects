#include <iostream.h>
#include <conio.h>

int b[50] = {0},p, a[50][2] = { 0 };

void hamil(int m,int n, int vertex);

int main() {
	clrscr();
	for (int y = 0;y < 50;y++)
		b[y] = 100;
	int n,m;
	char c;
	cin >> m >> n;
	p = m;
	for (int i = 0;i < n;i++) {
		c = getch();
		cout << c;
		while (c != ' ') {
			a[i][0] = 10 * a[i][0] + c - 48;
			c = getch();
			cout << c;
		}

		c = getch();
		cout << c;
		while (c != 13) {
			a[i][1] = 10 * a[i][1] + c - 48;
			c = getch();
			cout << c;
		}
		cout << "\n";
	}

	hamil(m,n,0);


	getch();
	return 0;
}


void hamil(int m,int n, int vertex) {
	if (m == 0) {
		for (int i = 0;i < n;i++) {
			if ((a[i][0] == b[0] && a[i][1] == b[p - 1]) || (a[i][1] == b[0] && a[i][0] == b[p - 1])) {
				for (int q = 0;q < p;q++) {
					cout << b[q];

				}
				cout << "\n";
			}
		}

	}
	else {
		for (int i = 1;i <= p;i++) {
			int t = 1;
			for (int j = p - 1;j >= 0;j--) {
				if (b[j] == i)
					t = 0;
			}
			if (t == 1) {
				if (vertex == 0) {
					b[m - 1] = i;
					hamil(m - 1, n, i);
					b[m - 1] = 100;
				}
				else {
					for (int j = 0;j < n;j++) {
						if ((a[j][0] == i && a[j][1] == vertex) || (a[j][1] == i && a[j][0] == vertex)) {
							b[m - 1] = i;
							hamil(m - 1, n, i);
							b[m - 1] = 100;
						}
					}
				}

			}


		}
	}//end else


}//end hamil














