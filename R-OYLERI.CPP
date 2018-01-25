#include <iostream.h>
#include <conio.h>

int b[52] = {0},m, a[50][2] = { 0 };

void oyler(int n, int vertex);

int main() {
	clrscr();
	int n;
	for (int l = 0;l < 52;l++)
		b[l] = n;
	char c;
	cin >> n;
	m = n;
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

	oyler(n, 0);



	getch();
	return 0;
}

void oyler(int n, int vertex) {
	if (n == 0) {
		for (int i = m-1;i >= 0;i--) {
			cout << b[i];
		}
		cout << "\n";
	}
	else {
		for (int i = 0;i < m;i++) {
			int t = 1;
			for (int j = m - 1;j >= 0;j--) {
				if (b[j] == i)
					t = 0;
			}

			if (t == 1) {
				if (vertex == 0) {
					b[n - 1] = i;
					oyler(n - 1, a[i][0]);
					oyler(n - 1, a[i][1]);
					b[n - 1] = m;
				}
				else {
					if (a[i][0] == vertex) {
						b[n - 1] = i;
						oyler(n - 1, a[i][1]);
						b[n - 1] = m;
					}
					if (a[i][1] == vertex) {
						b[n - 1] = i;
						oyler(n - 1, a[i][0]);
						b[n - 1] = m;
					}
				}
			}
		}

	}
}















