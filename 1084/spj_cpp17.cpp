#include "testlib.h"
using namespace std;

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	while (!ans.seekEof())
	{
		string jans = ans.readToken();
		string pans = ouf.readToken();
		if (jans == "No")
		{
			if (jans != pans) quitf(_wa, "'No solution' format wrong!");
			jans = ans.readToken();
			pans = ouf.readToken();
			if (jans != pans) quitf(_wa, "'No solution' format wrong!");
		}
		else
		{
			stringstream sj, sp;
			sj << jans; sp << pans;
			double pa, ja;
			sj >> ja; sp >> pa;
			if (sp.fail()) quitf(_wa, "You output in a wrong format!");
			if (fabs(ja - pa) > 0.01 + 1e-8) quitf(_wa, "Except %.7f, but found %.7f!", ja, pa);
		}
	}

	quitf(_ok, "Your answer is acceptable!");
	return 0;
}
