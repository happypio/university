#include<stdio.h>
int t[12][12],temp[12][12],koniec[12][12],kolumny[12][12],git=0,m,n,stopp=0,makabra=0,zera[12][12];
void minusowanie()
{
    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
            temp[i][j]=-10;
    return;
}
void rekurencja(int row, int index,int suma,int niezmienione)
{

    //printf("%d ",suma);
    if(git==1||makabra==1)
        return;
    if(row==n){
        for(int i=0;i<m;i++){
            /*for(int j=0;j<m;j++)
                printf("%d ",kolumny[n-1][j]);
            printf("\n");*/
            if(kolumny[n-1][i]!=0)
                return;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                koniec[i][j]=temp[i][j];
                //if(temp[i][j]==0)
                    //return;
            }
            //git=1;
        }
        git=1;
        return;
    }
    if(index==m){
        /*for(int i=0;i<m;i++)
            printf("%d ",temp[row][i]);
        printf("\n");*/
        if(suma==0){
            rekurencja(row+1,0,0,0);
        }
        return;
    }
    if(suma>(m-index)*9||suma<(-(m-index)*9)){
            stopp=suma;
        return;
    }
    if(row>0)
        kolumny[row][index]=kolumny[row-1][index]+t[row][index];
    else
        kolumny[row][index]=t[row][index];
    if(row>0){
        if(kolumny[row][index]>(n-row)*9||kolumny[row][index]<(-(n-row)*9)){
                int sumyy=0,sumiczki=0;
                for(int j=0;j<n;j++){
                    if(zera[j][index])
                        sumyy+=zera[j][index];
                    else
                        sumiczki+=9;
                }
                //printf("%d %d %d\n",sumyy,index,row);
                if(sumyy>sumiczki||sumyy<-sumiczki)
                    makabra=1;
            return;
        }
    }
    if(t[row][index]==0){
        int i=-9,k=9;
            if((9-suma)-(m-index)*9>-9)
                i=(9-suma)-(m-index)*9;
            else
                i=-9;

            if((m-index)*9-(9+suma)<9)
                k=(m-index)*9-(9+suma);
            else
                k=9;
            //printf("%d %d\n",i,k);
        for(;i<=k;i++){
            //if(i!=0){
            temp[row][index]=i;
            if(row>0)
                kolumny[row][index]=kolumny[row-1][index]+temp[row][index];
            else
                kolumny[row][index]=temp[row][index];
            if(row>0)
                if(kolumny[row-1][index]>(n-row)*9||kolumny[row-1][index]<(-(n-row)*9))
                    return;
            if(niezmienione==m-1)
                zera[row][index]=temp[row][index];
            rekurencja(row,index+1,suma+i,niezmienione-1);
            if(stopp!=0)
                if(suma+i>stopp)
                    i=30;
            stopp=0;
        }
        return;
    }
    //temp[row][index]=t[row][index];
    rekurencja(row,index+1,suma+t[row][index],niezmienione+1);
    return;
}
int main(void)
{
    //minusowanie();
    scanf("%d %d",&m,&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            scanf("%d",&t[i][j]);
        getchar();
    }
    rekurencja(0,0,0,0);
    printf("\n");
    if(git==0)
        printf("Nie da sie\n");
    else
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(t[i][j]!=0)
                    printf("%d ",t[i][j]);
                else
                    printf("%d ",koniec[i][j]);
            }
            printf("\n");
        }
    //for(int i=0;i<n;i++)
        //printf("%d\n",zera[i][9]);
    return 0;
}
