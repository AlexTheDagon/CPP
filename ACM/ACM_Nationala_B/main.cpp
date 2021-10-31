#include <iostream>
#include <fstream>
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

ifstream in("date.in");
ofstream out("date.out");

priority_queue<PII, vector<PII> > maxQ;
priority_queue<PII, vector<PII>, greater<PII> > minQ;

int cmin[NM];
int main() {
	int N;
	string s;
	cin >> N >> s;
	int flip = 0;
	int sol = 0;
	for (int i = N - 1; i >= 0; --i) {
		/// Do we need to flip 
		if ((flip % 2 == 1 && s[i] == 'A') || (flip % 2 == 0 && s[i] == 'B')) {
			if (i == 0) ++sol;
			else {
				if (s[i] == s[i - 1]) {
					++sol;
					flip++;
				}
				else ++sol;
			}
		}
	}
	cout << sol;
	return 0;
}