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

set <VI> s;
int N;
int a[NM];


int main() {
	cin >> N;
	VI subSeq;
	for (int i = 1; i <= N; ++i) {
		cin >> a[i];
		if (subSeq.size() > 0 && subSeq.back() > a[i]) {
			s.insert(subSeq);
			subSeq.clear();
		}
		subSeq.push_back(a[i]);
	}
	s.insert(subSeq);
	subSeq.clear();

	set<VI>::iterator itr;
	set<VI>::iterator itr2;
	bool check = true;
	while (check) {
		check = false;
		VI vec1;
		VI vec2;
		VI split;
		for (itr = s.begin(); itr != s.end(); itr++){
			itr2 = itr;
			itr2++;
			if (itr2 == s.end()) {
				break;
			}
			vec1 = *itr;
			vec2 = *itr2;
			if (vec1.back() > vec2[0]) {
				split.clear();
				int i = 0;
				s.erase(vec1);
				while (i < vec1.size() && vec1[i] < vec2[0]) ++i;
				for (int j = i; j < vec1.size(); ++j)split.push_back(vec1[j]);
				for (int j = vec1.size() - 1; j >= i; --j)vec1.pop_back();
				
			}
		}
		
		if (split.size()) {
			s.erase(vec1);
			s.insert(split);
			s.insert(vec1);
			check = true;
		}
	}
	
	cout << s.size();


	return 0;
}