#include<iostream>
using namespace std;
int tab[100][100];
int main()
{
    int n,k=0;
    cin>>n;
    for(int i=0;i<n;i++)
        if(i%2==0)
            for(int j=0;j<=i;j++)
            {
                tab[i-j][j]=k;
                k++;
            }
            else
            for(int j=i;j>=0;j--)
        {
            tab[i-j][j]=k;
            k++;
        }
    for(int i=n-1;i>=0;i--)
        if(i%2==1)
            for(int j=0;j<i;j++){
                tab[n-1-j][n-1-i+j+1]=k;
                k++;
            }
        else
            for(int j=i-1;j>=0;j--){
             tab[n-1-j][n-1-i+j+1]=k;
                k++;
        }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<tab[i][j]<<" ";
        cout<<endl;
    }

    return 0;
}
