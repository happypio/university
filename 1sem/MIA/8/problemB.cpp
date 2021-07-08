#include<iostream>
using namespace std;
int main()
{
    string slowo;
    cin>>slowo;
    int ostatni=-1;
    for(int i='z'-'a';i>=0;i--){
        for(int j=0;j<slowo.size();j++){
            if(slowo[j]==i+'a')
                if(j>ostatni){
                    cout<<slowo[j];
                    ostatni=j;
            }
        }
    }
    return 0;
}
