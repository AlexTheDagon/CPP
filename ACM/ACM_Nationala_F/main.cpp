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
#define NM (int)1e5+5

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

int N, M, X;
int fr[NM];
int maxP;
set <int> md[2][NM];

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> X;
		fr[X] ++;
	}
	for (int i = 1; i < NM; ++i) {
		md[fr[i] % 2][i % M].insert(i);
		maxP += fr[i] / 2;
	}
	for (int i = 0; i < M; ++i) {
		int A = i;
		int B = (M - i) % M;
		if (A < B) {
			vector <int> toRemoveA;
			vector <int> toRemoveB;
			if (A == B) {
				maxP += md[1][A].size() / 2;
			}
			if (A != B) {
				maxP += max(md[1][A].size(), md[1][B].size());
				for (auto x : md[1][A]) toRemoveA.push_back(x);
				for (auto x : md[1][B]) toRemoveB.push_back(x);
				for (int j = 0; j < min(toRemoveA.size(), toRemoveB.size()); ++j) {
					int xA = toRemoveA[j];
					int xB = toRemoveB[j];
					md[1][A].erase(xA);
					md[1][B].erase(xB);
					fr[xA] --;
					fr[xB] --;
					if (fr[xA]) md[0][A].insert(xA);
					if (fr[xB]) md[0][B].insert(xB);
				}
				/// Now for each pair(A,B) we only have one of the sets having cards with ODD cardinality
			}
		}
		
	}
	return 0;
}