/****************************  codes.c  ****************************

	ACM Regional Programming Contest, Fall 1998

	Immediate Decodability Problem

	Read sets of binary codes until EOF.  If any code in a set 
	is a prefix of another code in the set (e.g., the leading 
	digits of one code equal the digits of another code), the 
	set is not immediately decodable.  Otherwise, the set is 
	decodable.  Print the result of each test.

	Programmed by Julie Gwynn.
*/
#include <stdio.h>
#include <string.h>
#define DATA "codes.dat"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAXCODES 9
#define MAXSIZE 12

void main(void)
{
	char c[MAXCODES] [MAXSIZE];
	int n, len, pfx, nset = 0;  int m1, m2;
	int i, j, k;
	FILE *fp;
	void prt();

	if((fp = fopen(DATA, "r")) == NULL)
	     {  puts("Can't open data file");  exit();  }
	while((n = getset(fp, c)) != EOF) {
	     nset++;
	     pfx = 0;
	     for(i = 0; i < n; ++i) {
		  for(j = 0; j < n; ++j) {
		       if(i == j)  continue;
		       len = MIN(strlen(c[i])-1, strlen(c[j])-1);
		       k = 0;
		       while(c[i][k] == c[j][k] && k < len)
			    k++;
		       if(k == len) {	/* match -- NOT decodable */
			    pfx = 1;
			    break ;
		       }
		  }
		  if(pfx == 1)
		       break;
	     }
	     if(pfx == 0)
		  printf("Set %d is immediately decodable\n", nset);
	     else
		  printf("Set %d is not immediately decodable\n", nset);
	}
}
int getset(FILE *fp, char c[][MAXSIZE])
{
	int n = 0, m;

	if(fgets(c[n], MAXSIZE, fp) == NULL)
	     n = EOF;
	else
	     while(c[n][0] != '9') {
		  n++;
		  fgets(c[n], MAXSIZE, fp);
	     }
	return n;
}

