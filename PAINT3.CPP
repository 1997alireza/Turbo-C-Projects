#include <stdafx>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void load();
int preprocessor();
int name_exist();
int C_character();
void go_end();
void C_math();
int C_name();
int C_number();
int C_intigerAndFloat();
void tokenize();
int C_akolad();
void check();
void go_end2();
int C_expression();

struct tokenize {
	char str[30];
	int type;
	int attribute;
	int line;
	int use;

	struct token *next;
	struct token *back;

}*temp, *first, *help, *help1, *help2;

int akolad[100][3];
int hlpakolad[100][3];

char table[20][20][20]; //////esm no' meghdar
int tp = 0;
int error = 0;
int enter = 1;

int main()
{
	first = (struct tokenize *)malloc(sizeof(struct tokenize));
	first->next = NULL;
	first->back = NULL;

	load();
	temp = first;
	tokenize();
	temp = first;

	//C_akolad();
	//C_if();

	/*hile (temp->str[0] != '?'){
	temp=temp->next;
	}
	temp=temp->back;
	temp=temp->back;
	printf ("%s" , temp->str); */

	//check();
	/*C_if();
	temp=temp->next;
	temp=temp->next;
	printf ("%s" , temp->str);
	C_intigerAndFloat();*/


	while (strcmp(temp->str, "?") != 0) {
		printf(" %s", temp->str);
		temp = temp->next;
	}
	printf("\n");

	temp = first;
	preprocessor();
	check();

	return 0;
}


void load() {
	char token[100];
	FILE *fp, *fhp;
	fp = fopen("totaldata.txt", "r+");
	temp = first;
	while (!feof(fp)) {
		fhp = fopen("help.txt", "r+");
		fgets(token, 80, fp);
		fputs(token, fhp);
		rewind(fhp);
		while (!feof(fhp)) {
			fscanf(fhp, "%s", temp->str);
			help = temp;
			temp->next = malloc(sizeof(struct tokenize));
			temp = temp->next;
			temp->back = help;
			temp->next = NULL;
		}
		temp = temp->back;
		temp->str[0] = '\n';
		temp = temp->next;
		fclose(fhp);
		fclose(fopen("help.txt", "w"));
	}
	temp->str[0] = '?';
	fclose(fp);
}

void tokenize() {
	temp = first;
	////////////keywords////////////
	while (strcmp(temp->str, "?") != 0) {

		help1 = temp->back;
		help2 = temp->next;

		if (strcmp(temp->str, "main") == 0) {
			temp->type = 1;
			temp->attribute = 0;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "if") == 0) {
			temp->type = 1;
			temp->attribute = 1;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "else") == 0) {
			temp->type = 1;
			temp->attribute = 2;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "int") == 0) {

			temp->type = 1;
			temp->attribute = 3;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "float") == 0) {
			temp->type = 1;
			temp->attribute = 4;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "char") == 0) {
			temp->type = 1;
			temp->attribute = 5;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "bool") == 0) {
			temp->type = 1;
			temp->attribute = 6;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "void") == 0) {
			temp->type = 1;
			temp->attribute = 7;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "NULL") == 0) {
			temp->type = 1;
			temp->attribute = 8;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "while") == 0) {
			temp->type = 1;
			temp->attribute = 9;
			temp->line = enter;
		}

		////////////operators////////////
		else if (strcmp(temp->str, "+") == 0) {
			temp->type = 2;
			temp->attribute = 1;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "-") == 0) {
			temp->type = 2;
			temp->attribute = 2;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "/") == 0) {
			temp->type = 2;
			temp->attribute = 3;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "*") == 0) {
			temp->type = 2;
			temp->attribute = 4;
			temp->line = enter;
		}
		else if (strcmp(temp->str, ">") == 0) {
			temp->type = 2;
			temp->attribute = 5;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "<") == 0) {
			temp->type = 2;
			temp->attribute = 6;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "==") == 0) {
			temp->type = 2;
			temp->attribute = 7;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "!=") == 0) {
			temp->type = 2;
			temp->attribute = 8;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "&&") == 0) {
			temp->type = 2;
			temp->attribute = 9;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "||") == 0) {
			temp->type = 2;
			temp->attribute = 10;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "=") == 0) {
			temp->type = 2;
			temp->attribute = 11;
			temp->line = enter;
		}

		////////////punc////////////
		else if (strcmp(temp->str, "(") == 0) {
			temp->type = 6;
			temp->attribute = 1;
			temp->line = enter;
		}
		else if (strcmp(temp->str, ")") == 0) {
			temp->type = 6;
			temp->attribute = 2;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "{") == 0) {
			temp->type = 6;
			temp->attribute = 3;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "}") == 0) {
			temp->type = 6;
			temp->attribute = 4;
			temp->line = enter;
		}
		else if (strcmp(temp->str, ",") == 0) {
			temp->type = 6;
			temp->attribute = 5;
			temp->line = enter;
		}
		else if (strcmp(temp->str, ";") == 0) {
			temp->type = 6;
			temp->attribute = 6;
			temp->line = enter;
		}
		else if (strcmp(temp->str, "'") == 0) {
			temp->type = 6;
			temp->attribute = 7;
			temp->line = enter;
		}

		/////////number///////////
		else if (C_number() == 1) {
			temp->type = 4;
			temp->attribute = 1;
			temp->line = enter;
		}
		else if (C_number() == 0) {
			temp->type = 4;
			temp->attribute = 2;
			temp->line = enter;
		}
		////////////char//////////////

		else if ((strcmp(help1->str, "'") == 0) && (strcmp(help2->str, "'") == 0) && (strlen(temp->str) == 1)) {
			temp->type = 5;
			temp->attribute = 0;
			temp->line = enter;
		}

		////////////n////////////
		else if (strcmp(temp->str, "\n") == 0) {
			temp->type = 7;
			temp->attribute = 0;
			temp->line = enter;
			enter++;
		}

		///////////id////////////
		else {
			temp->type = 3;
			temp->attribute = 0;
			temp->line = enter;

		}
		temp = temp->next;
	}
}

int preprocessor() {
	FILE *fp1, *fp2, *fp3;
	char ch;
	fp1 = fopen("variables.h", "r");
	fp2 = fopen("mytext.txt", "r");
	fp3 = fopen("totaldata.txt", "w");

	while (1) {
		ch = fgetc(fp1);
		if (ch == EOF) break;
		else putc(ch, fp3);
	}
	putc('\n', fp3);
	while (1) {
		ch = fgetc(fp2);
		if (ch == EOF) break;
		else putc(ch, fp3);
	}
	putc(' ', fp3);
	fclose(fp1);
	fclose(fp2);
}

int C_character() {
	while (strcmp(temp->str, ";") != 0 && strcmp(temp->str, "\n") != 0) {
		temp = temp->next;
		if (temp->type == 3) {
			temp = temp->next;
			if (strcmp(temp->str, "=") == 0) {
				temp = temp->next;
				if (strcmp(temp->str, "'") == 0) {
					temp = temp->next;
					if (temp->type == 5 && temp->attribute == 0) {
						temp = temp->next;
						if (strcmp(temp->str, "'") == 0) {
							temp = temp->next;
							printf("OK");
						}
						else {
							printf("%d : formate kollie character ' c ' ast\n", temp->line);
							go_end();
							error = 1;
						}
					}
					else if (strcmp(temp->str, ";") == 0) {
						error = 1;
						printf("%d : Ba'd az = bayad az ' c ' estefade shawad.\n", temp->line);
					}
					else {
						printf("%d : Ba'd az = bayad az ' c ' estefade shawad.\n", temp->line);
						go_end();
						error = 1;
					}
				}
				else {
					printf("% d : Ba'd az = bayad az ' c ' estefade shawad.\n", temp->line);
					go_end();
					error = 1;
				}

			}
			else if (strcmp(temp->str, ";") == 0) {
				go_end();
			}
			else {
				printf("%d : ba'd id ; ya = lazem ast", temp->line);
				go_end();
				error = 1;
			}
		}
		else {
			error = 1;
			printf("%d : there is no id", temp->line);
			go_end();
		}
	}
}

int C_intigerAndFloat() {
	while (strcmp(temp->str, ";") != 0 && strcmp(temp->str, "\n") != 0) {
		temp = temp->next;
		if (temp->type == 3) {
			temp = temp->next;
			if (strcmp(temp->str, "=") == 0) {
				temp = temp->next;
				if (temp->type == 3 || temp->type == 4) {
					temp = temp->next;
					if (temp->type == 2 && temp->attribute <= 4 && temp->attribute >= 1) {
						temp = temp->next;
						if (temp->type == 3 || temp->type == 4) {
							temp = temp->next;
							if (strcmp(temp->str, ";") == 0) {
								printf("OK");
								go_end();
							}
							else if (strcmp(temp->str, ",") == 0) {
								continue;
							}
							else {
								printf("bayad ; miamad");
								go_end();
								error = 1;
							}
						}
						else if (strcmp(temp->str, ";") == 0) {
							go_end();
							error = 1;
							printf("OK");
						}
						else {
							error = 1;
							go_end();
							printf("ba'd operator bayad id ya adad bashad");
						}
					}
					else if (strcmp(temp->str, ";") == 0) {
						printf("OK");
					}
				}
				else {
					printf("ba'd = ya bayad addad bashad ya moteghayer!!");
					error = 1;
					go_end();
				}
			}
			else if (strcmp(temp->str, ";") == 0) {
				go_end();
				printf("OK");
				error = 1;
			}
			else if (strcmp(temp->str, ",") == 0) {
				continue;
			}
			else {
				printf("ba'd id ; ya = lazem asst");
				go_end();
				error = 1;
			}
		}
		else {
			error = 1;
			printf("there is no id");
			go_end();
		}
	}
}

int C_if() {

	int ak = 0, ak2 = 0;
	temp = temp->next;

	if (strcmp(temp->str, "(") == 0) {
		temp = temp->next;
		if (temp->type == 3) {
			temp = temp->next;
			if (temp->type == 2) {
				temp = temp->next;
				if (temp->type == 3 || temp->type == 4) {
					temp = temp->next;
					if (strcmp(temp->str, ")") == 0) {
						printf("OK");
					}
					else {
						printf("ba'd shart if ')' lazem ast");
						error = 1;
						go_end2();
					}
				}
				else {
					printf("ba'd opertator id ya num miayad");
					error = 1;
					go_end2();
				}
			}
			else {
				printf("dar if ba'd id aval operatir lazem ast");
				error = 1;
				go_end2();
			}
		}
		else {
			printf("shart if ba id shoroo mishavad");
			error = 1;
			go_end2();
		}

	}
	else {
		printf("ba'd if bayad '(' bashad");
		error = 1;
		go_end2();
	}


	////////////////////////////////////////////////////

	if (temp->type == 6 && temp->attribute == 2)
		temp = temp->next;
	help1 = temp;
	if (temp->str[0] == '{') {

		while (ak == 0 && strcmp(temp->str, "?") != 0) {
			temp = temp->next;
			if (temp->str[0] == '}' && ak2 == 0)
			{
				ak = 1;
			}
			else if (temp->str[0] == '{') {
				ak2++;
			}
			else if (temp->str[0] == '}' && ak2 != 0) {
				ak2--;
			}
		}

		if (ak == 1) {
			printf("OK");
		}
		else
			printf("%d AKOLAD baste nashode ast", help1->line);
		error = 1;
	}
	else {
		printf("dar if ba'd ')' baya '{' bashad");
		error = 1;
		go_end2();
	}

	temp = help1;

}

/*int C_akolad (){
temp=first;
int i=0 , j=0 ,k , h1=0 , h2=0 ,r;


while (strcmp(temp->str , "?") != 0){

if (strcmp(temp->str , "{")==0){
akolad[i][0]=temp;
akolad[i][1]= 1;
i++;
}
else if (strcmp(temp->str , "}")==0){
akolad[i][0]=temp;
akolad[i][1]= 2;
i++;
}
temp=temp->next;
}
j=i;
while (j>1){
k=0;
if (akolad[k][1]==1 && akolad[k+1][1]==2){
h1=0;
h2=0;
while (h1<j){
if (h1!=k && h1!=k+1){
hlpakolad[h2][1]=akolad[h1][1];
hlpakolad[h2][0]=akolad[h1][0];
j--;
j--;
h2++;
h1++;
}
else {
h1++;
}
}
}
else {
k++;
}
k=0;
while (j>k){
akolad[k][0]=hlpakolad[k][0];
akolad[k][1]=hlpakolad[k][1];
k++;
}


}

if (j>0)
printf ("Akolad");
for (r=0 ; r<j ; r++){
printf ("%d\n" , akolad[r][1]);
}

}

*/


int C_number() {
	int flt = 0, j = 0, i;
	for (i = 0; i<strlen(temp->str); i++) {
		if ((temp->str[i] >= 48 && temp->str[i] <= 57) || (temp->str[i] == 46)) {
			if (temp->str[i] == 46)
				flt++;// agar az 1 bishtar shavad aslan addad nist

			j++;
		}
	}
	if (j != strlen(temp->str))
		return -1; //addad nabood
	else if (flt == 1 && j == strlen(temp->str))
		return 0; //ashari bood
	return 1;
}

int C_name() {
	int j = 0, k = 0, i;
	for (i = 0; i<strlen(temp->str); i++) {
		if ((temp->str[i] >= 65 && temp->str[i] <= 90) || (temp->str[i] >= 97 && temp->str[i] <= 122) || (temp->str[i] >= 48 && temp->str[i] <= 57)) {
			if (temp->str[i] >= 48 && temp->str[i] <= 57)
				k++;
			j++;
		}
	}
	if (j != strlen(temp->str) || k == j) //k=j baraye emsi ke kolan addade
		return 0; //esmet ghalate
	return 1;
}

void C_math() {
	if (!temp->str == '=') {
		return 2; //mosavi nadidam
	}
}

void go_end() {
	while (temp->str[0] != ';') {
		temp = temp->next;
	}
	//temp=temp->next;
}

int name_exist() {
	int i;
	for (i = 0; i<tp; i++) {
		if (strcmp(table[i][0], temp->str) == 0)
			return 1;
	}
	return 0;
}

void go_end2() {

	while (strcmp(temp->str, "\n") != 0 && strcmp(temp->str, "{") != 0) {

		temp = temp->next;
	}
}
int C_expression() {
	//temp=temp->next;
	while (strcmp(temp->str, ";") != 0) {
		if (temp->type == 3) {
			temp = temp->next;
			if (temp->type == 2 && temp->attribute == 11) {
				temp = temp->next;
				if (temp->type == 3 || temp->type == 4) {
					if (strcmp(temp->str, "min") == 0 || strcmp(temp->str, "max") == 0) {
						temp = temp->next;
						if (temp->type == 6 && temp->attribute == 1) {
							temp = temp->next;
							if (temp->type == 4 || temp->type == 3) {
								temp = temp->next;
								if (temp->type == 6 && temp->attribute == 5) {
									temp = temp->next;
									if (temp->type == 4 || temp->type == 3) {
										temp = temp->next;
										if (temp->type == 6 && temp->attribute == 2) {
											temp = temp->next;
										}
										else {
											printf("sakhtare dorost min/max(num,num) ast1!\n ");
											go_end();
											error = 1;
										}
									}
									else {
										printf("sakhtare dorost min/max(num,num) ast!2\n ");
										go_end();
										error = 1;
									}
								}
								else {
									printf("sakhtare dorost min/max(num,num) ast!3\n ");
									go_end();
									error = 1;
								}
							}
							else {
								printf("sakhtare dorost min/max(num,num) ast!4\n ");
								go_end();
								error = 1;
							}
						}
						else {
							printf("sakhtare dorost min/max(num,num) ast!5\n ");
							go_end();
							error = 1;
						}
					}
					/*else if(strcmp(temp->str , "true") == 0 || strcmp(temp->str , "false") == 0){
					temp=temp->next;
					}*/
					else {
						temp = temp->next;
						if ((temp->type == 2 && temp->attribute <= 4 && temp->attribute >= 1) || temp->attribute == 11) {
							temp = temp->next;
							if (temp->type == 3 || temp->type == 4) {
								temp = temp->next;
							}
							else {
								//printf("Ba'd az id/num op id/num bayad ; byayad!\n");
								printf("Ba'd az operator hatman bayad id/num byayad.\n");
								go_end();
								error = 1;
							}
						}
						else if (temp->type == 6 && temp->attribute == 6) {

							break;
						}
						else {
							printf("Ba'd az number va id bayad operator biayad!\n");
							error = 1;
							go_end();
						}
					}
				}
				else if (strcmp(temp->str, "'") == 0) {
					temp = temp->next;
					if (temp->type == 5) {
						temp = temp->next;
						if (strcmp(temp->str, "'") == 0) {
							temp = temp->next;
						}
						else {
							printf("sakhtare tArife char, ' c ' ast!\n");
							error = 1;
							go_end();
						}
					}
					else {
						printf("sakhtare tArife char, ' c ' ast!\n");
						error = 1;
						go_end();
					}
				}
				else {
					printf("Ba'de mosawi ya id ya max//min ya number ya 'c' miAyad!\n");
					go_end();
					error = 1;
				}
			}
			else {
				printf("Ba'd az id hatman = miAyad.\n");
				error = 1;
				go_end();
			}
		}
		else {
			printf("Dar shoroE expression hatman id miAyad!\n");
			go_end();
			error = 1;
		}
	}
}



void check() {

	temp = first;

	while (strcmp(temp->str, "?") != 0) {

		if (strcmp(temp->str, "}") == 0 || strcmp(temp->str, "{") == 0 || strcmp(temp->str, "\n") == 0 || strcmp(temp->str, " ") == 0) {
			//printf ("SSSS");
		}
		else if (strcmp(temp->str, "if") == 0) {
			C_if();
		}
		else if (strcmp(temp->str, "int") == 0) {
			//printf ("TTTT");
			C_intigerAndFloat();
		}
		else if (strcmp(temp->str, "float") == 0) {
			C_intigerAndFloat();
		}
		else if (strcmp(temp->str, "char") == 0) {
			C_character();
		}
		else {
			//printf ("DDDD");
			C_expression();
			//printf("   %s   " , temp->str );


		}
		temp = temp->next;
	}
}
