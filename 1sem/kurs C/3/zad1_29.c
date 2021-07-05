#include<stdio.h>
#include<ctype.h>

int main(void)
{
    int c,kropka=0,przecinek=0,litera=0;
    while((c=getchar())!=EOF)
    {
        if(c=='.')
        {
            kropka=1;
            litera=1;
        }
        if(c==',')
            przecinek=1;
        if(isalpha(c)&&litera)
        {
            c=toupper(c);
            litera=0;
        }
        if(c!=' '&&c!='.'&&kropka)
            kropka=0;
        if(c!=' '&&c!=','&&przecinek)
            przecinek=0;

        if(c!=' '&&(kropka||przecinek))
            {
                putchar(c);
                putchar(' ');
            }
        else
            if(c==' '&&kropka==0&&przecinek==0)
                putchar(c);
            else
                if(c!=' ')
                    putchar(c);


    }

    return 0;
}
