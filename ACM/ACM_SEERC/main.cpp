#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

#define MP make_pair
#define PB push_back;
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define NM (int)1e6+5

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)

typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int, int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;


priority_queue<PII, vector<PII> > maxQ;
priority_queue<PII, vector<PII>, greater<PII> > minQ;

int64 N;
int64 a, b, c, bo, bc;
string s;
char sc;
VII sol;
deque < pair<char, int> > stA;
deque < pair<char, int> > stB;


int main() {
	cin >> N;
	cin >> s;
	for (auto x : s) {
		if (x == 'A') ++a;
		if (x == 'B') ++b;
		if (x == 'C') ++c;
	}
	if (a < c) {
		bo += c - a;
		b -= bo;
	}
	else {
		bc += a - c;
		b -= bc;
	}
	if (b % 2) {
		cout << "NO";
		return 0;
	}
	bo += b / 2;
	bc += b / 2;
	for (int i = 1; i <= 2 * N; ++i) {
		//cout << i << '\n';
		sc = s[i - 1];
		if (sc == 'A') {
			stA.push_back({ 'A', i });
		}
		if (sc == 'B') {
			stB.push_back({ 'B', i});
		}
		if (sc == 'C') {
			pair<char, int> pci;
			if (!stB.empty() && bo) {
				pci = stB.front();
				stB.pop_front();
				sol.push_back({ pci.second, i });
				--bo;
			}
			else if (!stA.empty()) {
				pci = stA.back();
				stA.pop_back();
				sol.push_back({ pci.second, i });
			}
			else {
				cout << "NO";
				return 0;
			}
		}
	}
	
	if (stB.size() != stA.size()) {
		cout << "NO";
		return 0;
	}

	while (stA.size()) {
		sol.push_back({ stA.back().second, stB.back().second });
		if (stA.back().second > stB.back().second) {
			cout << "NO\n";
			return 0;
		}
		stA.pop_back();
		stB.pop_back();
	}



	cout << "YES\n";
	for (auto p : sol) {
		cout << p.first << " " << p.second << '\n';
	}
	return 0;
}

