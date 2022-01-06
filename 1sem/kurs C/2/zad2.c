#include<stdio.h>

int main(void)
{
    int c,i=0;
    char tab1[10003];

    while((c=getchar())&&c!=EOF)
    {
        if(c=='(' || c=='{' || c=='[')
        {
            tab1[i]=c;
            i++;
            //printf("numer w tab to %d oraz znak to %c",i,c);
        }
        if(c==')' || c=='}' || c==']')
        {
            char tmp;
            if(c==')')
                tmp='(';
            if(c=='}')
                tmp='{';
            if(c==']')
                tmp='[';
            if(tab1[i-1]!=tmp)
            {
                printf("nie pasuje %c\n",c);
                return 0;
            }
            i--;
        }
    }
    if(i>0)
        printf("nie zamkniete");
    else
    printf("poprawny\n");

    return 0;

}
