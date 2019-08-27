#include "testlib.h"
#define MAXN 1010

int n,A[MAXN],B[MAXN],usr[MAXN];
int usrans,stdans;

inline int mymin(int a,int b){return a<b?a:b;}

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	n=inf.readInt();
	for (int i=1;i<=n;i++) A[i]=inf.readInt();
	for (int i=1;i<=n;i++) B[i]=inf.readInt();
	usrans=ouf.readInt();
	stdans=ans.readInt();
	if (usrans!=stdans)
	{
		quitf(_wa, "Wrong Answer. Expected = %d, Found = %d", stdans, usrans);
	}
	else
	{
		bool f=false;
		for (int i=1;i<=n;i++) usr[i]=ouf.readInt(1,n);
		for (int i=1;i<=n&&!f;i++)
			for (int j=i+1;j<=n&&!f;j++)
				if (mymin(B[usr[j]],A[usr[i]])>mymin(B[usr[i]],A[usr[j]]))
					f=true;
		if (f) quitf(_wa, "Incorrect sequence.");
		else quitf(_ok, "Acceptable answer.");
	}
	return 0;
}
