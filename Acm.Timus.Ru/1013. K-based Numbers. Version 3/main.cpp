#include <iostream>
#include <vector>
#define REP(i,n) for(long long i=0;i<n;++i)
#define REP2(i,n) for(long long i=1;i<=n;i*=2)
using namespace std;

typedef long long ll;
typedef vector<ll> row;
typedef vector<row> matrix;

ll N,K,M;

ll mult_mod(ll A,ll B,ll C)///(A*B)%C
{
    ll sol=0;
    REP2(p,B)
    {
        if(B&p)
        {
            sol=sol-C+A;
            sol%=C;
            if(sol<0)sol+=C;
        }
        A=(A+A)%C;
    }
    return sol;
}

matrix operator * (matrix A,matrix B)
{
    matrix C(2,row(2));
    REP(i,2)REP(j,2)REP(k,2)
    {
        C[i][j]=(C[i][j]-M+mult_mod(A[i][k],B[k][j],M))%M;
        if(C[i][j]<0)C[i][j]+=M;
    }
    return C;
}


matrix lgput(matrix A,ll e)
{
    matrix sol(2,row(2));
    sol[0][0]=1;
    sol[1][1]=1;
    REP2(p,e)
    {
        if(p&e)
            sol=sol*A;
        A=A*A;
    }
    return sol;
}



int main()
{
    cin>>N>>K>>M;
    matrix T(2,row(2));
    T[0][0]=K-1; T[0][1]=1;
    T[1][0]=K-1; T[1][1]=0;
    T=lgput(T,N);



    matrix F(2,row(2));
    F[0][0]=K-1;   F[0][1]=1;
    F[1][0]=1;   F[1][1]=0;
    F=T*F;
    cout<<(F[0][1])%M;
    return 0;
}