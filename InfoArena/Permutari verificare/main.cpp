#include <iostream>

using namespace std;
int n,a[100],fol[100];
void gen(int x)
{
    if(x>n)
    {
        for(int i=1;i<=n;++i)cout<<a[i]<<" ";
        cout<<endl;
    }
    else
    {
        for(int i=1;i<=n;++i)
        {
            if(fol[i]==0)
            {
                fol[i]=1;
                a[x]=i;
                gen(x+1);
                fol[i]=0;
            }
        }
    }
}
int main()
{
    cin>>n;
    gen(1);
    return 0;
}
