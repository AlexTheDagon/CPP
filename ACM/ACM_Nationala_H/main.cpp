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
#define KM (long long)1e18+5

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

int64 dim[NM];
int64 N, K;

int main() {
	
	cin >> N >> K;
	dim[1] = dim[2] = 1;
	for (int i = 3; i <= 90; ++i) {
		dim[i] = dim[i - 2] + dim[i - 1];
		//if (dim[i] > KM) cout << i << " ";
		//cout << dim[i] << '\n';
	}
	
	while (N > 89) N -= 2;

	while (N > 2) {
		if (K > dim[N - 2]) {
			K -= dim[N - 2];
			N--;
		}
		else N -= 2;
	}
	if (N == 1) cout << "N";
	else cout << "A";
	/*string s1 = "N";
	string s2 = "A";
	for (int i = 1; i < 10; ++i) {
		string s3 = s1 + s2;
		cout << s1 << " " << s2 << '\n';
		s1 = s2;
		s2 = s3;
	}*/
	return 0;
}