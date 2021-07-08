#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
    srand(time(NULL));
    int m=rand()%11,n=rand()%11,nb=rand()%9;
    cout<<m<<" "<<n<<" "<<nb<<endl;
    for(int i=0;i<nb;i++){
        int w=rand()%10 +1,h=rand()%10 +1;
        cout<<w<<" "<<h<<endl;
        for(int j=0;j<h;j++){
            for(int k=0;k<w;k++){
                int znak=rand()%2;
                if(znak==0)
                    cout<<"#";
                else
                    cout<<".";
            }
            cout<<endl;
        }
    }
    int ntest=rand()%9;
    for(int i=0;i<ntest;i++){
        for(int j=0;j<nb;j++){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    return 0;
}

