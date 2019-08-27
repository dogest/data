#include "testlib.h"
#include <string>

constexpr int maxn = 1995;
constexpr int maxm = 44;

template <class _Tp>
	inline _Tp Min(const _Tp &x, const _Tp &y) {
		return x < y ? x : y;
	}
template <class _Tp>
	inline _Tp Max(const _Tp &x, const _Tp &y) {
		return x > y ? x : y;
	}
template <class _Tp>
	inline void chkMax(_Tp &x, const _Tp &y) {
		(x < y) && (x = y);
	}

struct Street_t {
	int u, v; bool vis;
	Street_t() : u(0), v(0), vis(false) {}
	inline bool init() {
		u = inf.readInt(0, maxm);
		v = inf.readInt(0, maxm);
		vis = false;
		return u || v;
	}
}street[maxn + 1], tmp_e;

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	for (int case_id = 1; ; ++case_id) {
		if (!tmp_e.init())
			break;
		/* end of the input */
		int curjunc = Min(tmp_e.u, tmp_e.v), cnt_e = 0, id;
		do {
			id = inf.readInt(1, maxn);
			chkMax(cnt_e, id);
			street[id] = tmp_e;
		} while (tmp_e.init());
		if (curjunc == 0)
			break;

		std::string std_str = ans.readString();
		if (std_str[0] == 'R') {
			std::string out_str = ouf.readString();
			if (out_str != std_str)
				quitf(_wa, "Expected not exist on testcase %d", case_id);
			continue;
		}

		for (int i = 1; i <= cnt_e; ++i) {
			int cur_e = ouf.readInt(1, cnt_e);
			Street_t &cur = street[cur_e];

			if (cur.vis)
				quitf(_wa, "Street %d has been visited before on testcase %d", cur_e, case_id);

			cur.vis = true;
			if (curjunc != cur.u && curjunc != cur.v)
				quitf(_wa, "Street %d does not connect to junction %d on testcase %d", cur_e, curjunc, case_id);
			curjunc ^= cur.u ^ cur.v;
		}

		ouf.readEoln();
	}
	quitf(_ok,"Good job!");
}