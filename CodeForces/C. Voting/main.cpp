#include <iostream>
#include <string.h>
using namespace std;
char c[200005];
int n,re,de,nrr,nrd,cnrd,cnrr,dr,dd,aux;
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>c[i];
        if(c[i]=='D')++nrd;
        else ++nrr;
    }
    cnrr=nrr;
    cnrd=nrd;
    for(int ind=1;ind<=n;++ind)
    {
        if(c[ind]=='D')
        {
            if(re>0)
            {
                --nrd;
                --re;
            }
            else
            {
                ++de;
            }
        }
        else
        {
            if(de>0)
            {
                --nrr;
                --de;
            }
            else
            {
                ++re;
            }
        }
        if(ind>n)ind=1;
    }
    if(re>0)nrd-=re;
    else nrr-=dr;
    dr=cnrr-nrr;
    dd=cnrd-nrd;
    while(nrr>0 && nrd>0)
    {
        nrd-=dd;
        nrr-=dr;

    }
    if(nrr<nrd)cout<<"D";
    else cout<<"R";
    return 0;
}
