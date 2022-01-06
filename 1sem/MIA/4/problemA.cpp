#include<iostream>
#include<vector>

using namespace std;
int licz=0;

void liczenie (vector<int>drzewo[], bool dojscie[],int x,int spruce[])
{
    dojscie[x]=1;
    for(int unsigned i=0;i<drzewo[x].size();i++)
    {
        if(!dojscie[drzewo[x][i]])
        {
            liczenie(drzewo,dojscie,drzewo[x][i],spruce);
            if(licz==1)
                spruce[x]++;
            licz=0;

        }
    }
    if(drzewo[x].size()==0)
    licz=1;

}

int main()
{
    ios_base::sync_with_stdio(false);
    int n,a;
    cin>>n;
    vector<int> drzewo[n+1];
    int spruce[n+1]={0};
    bool dojscie[n+1]={0};
    for(int i=2;i<=n;i++)
        {
            cin>>a;
            drzewo[a].push_back(i);
        }

    liczenie(drzewo,dojscie,1,spruce);
    for(int i=1;i<=n;i++)
    {
       if(drzewo[i].size()>0&&spruce[i]<3)
       {
        cout<<"No"<<endl;
       return 0;
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}
