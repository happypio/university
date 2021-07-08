#include<iostream>
#include<queue>
using namespace std;
long long sum_pref[5005],dp[5005][5005];
int main()
{
    int n,m,k,p;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>p;
        sum_pref[i]=sum_pref[i-1]+p;
    }
    for(int i=1;i<=k;i++)
        for(int j=m;j<=n;j++){
            dp[i][j]=sum_pref[j]-sum_pref[j-m];
            dp[i][j]+=dp[i-1][j-m];
            dp[i][j]=max(dp[i][j-1],dp[i][j]);
        }
    cout<<dp[k][n];

    return 0;
}
