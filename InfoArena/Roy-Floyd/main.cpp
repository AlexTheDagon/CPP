#include <iostream>
#include <fstream>
#define NM 300
#define INF 100000000
using namespace std;
ifstream in("rf.in");
ofstream out("rf.out");
int dmin[NM][NM],d[NM][NM],n,m[NM][NM];
int main()
{
    in>>n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)in>>dmin[i][j];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)if(i!=j)m[i][j]=1;
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            if(i!=j)
            {
                if(dmin[i][j]==dmin[i][k]+dmin[k][j])++m[i][j];
                if(dmin[i][j]>dmin[i][k]+dmin[k][j])
                {
                    m[i][j]=1;
                    dmin[i][j]=dmin[i][k]+dmin[k][j];
                }
            }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            out<<dmin[i][j]<<" ";
        out<<'\n';
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            out<<m[i][j]<<" ";
        out<<'\n';
    }
    return 0;
}
