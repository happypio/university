#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char slowo[1000000];
typedef struct Node {
int count;
struct Node* edges[26];
} Node;
void dodaj(char slowo[],int unsigned i, Node* wezel)
{
    if(i>=strlen(slowo))
    {
        printf("%d\n",wezel->count-1);
        return;
    }
    if(wezel->edges[slowo[i]-'a']==NULL)
        wezel->edges[slowo[i]-'a']=(Node*)calloc(sizeof(Node),1);
    wezel->edges[slowo[i]-'a']->count+=1;
    //printf("%d %c\n",wezel->edges[slowo[i]-'a']->count,slowo[i]);
    dodaj(slowo,i+1,wezel->edges[slowo[i]-'a']);
}
int main(void)
{
    Node *root = (Node*)calloc(sizeof(Node),1);
    while(scanf("%s",slowo)!=EOF){
        dodaj(slowo,0,root);
    }
    return 0;
}
