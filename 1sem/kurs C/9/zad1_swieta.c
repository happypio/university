#include<stdio.h>
#include<stdlib.h>
typedef struct Array2D {
    unsigned int width, height;
    int *t;
} Array2D;

void print(Array2D *array) {
    for (unsigned int y = 0; y < array->height; y++) {
        for (unsigned int x = 0; x < array->width; x++)
            printf(" %i", array->t[y*array->width+x]);
        printf("\n");
    }
    printf("\n");
}
void resize(Array2D *array, unsigned int width, unsigned int height)
{
    if(width==0||height==0){
        array-> t=NULL;
    }
    else{
        if(width>=array->width){
            array->t=(int*)realloc(array->t,(width*height-1)*sizeof(int));
            int przeskok=width-array->width;
            int dlugosc=array->width-1;
                for(int unsigned i=0;i<width*height;i++)
                {
                    if(przeskok==0){
                        dlugosc=array->width-1;
                        przeskok=width-array->width;
                    }
                    if(dlugosc<0){
                        for(int unsigned j=width*height-1;j>i;j--){
                            array->t[j]=array->t[j-1];
                        }
                        array->t[i]=0;
                        przeskok--;
                    }
                    dlugosc--;
                }
        }
        if(width<array->width){
            int przeniesienie=0;
            int przeskok=-width+array->width;
            int dlugosc=width-1;
            for(int unsigned i=0;i<array->width*array->height;i++)
                {
                    if(dlugosc<0){
                        dlugosc=width-1;
                        przeniesienie+=przeskok;
                    }
                    if(i+przeniesienie<array->width*array->height)
                    array->t[i]=array->t[i+przeniesienie];
                    //printf("%d \n",dlugosc);
                    dlugosc--;
                }
            array->t=(int*)realloc(array->t,(width*height-1)*sizeof(int));
            //print(array);
        }
        if(height>array->height){
            //if(array->height>0)
                for(int unsigned i=array->height*width;i<height*width;i++)
                    array->t[i]=0;
            //else
                //for(int unsigned i=array->height;i<height*width;i++)
                //array->t[i]=0;
        }
    }
    array->height=height;
    array->width=width;

}
int main(void)
{
    Array2D a = {3,3,(int*)malloc(9*sizeof(int))};
    for(int i=0;i<9;i++) a.t[i] = i+1;
    print(&a);
    //resize(&a,5,2); print(&a);
    resize(&a,4,3); print(&a);
    resize(&a,5,2); print(&a);
    resize(&a,2,3); print(&a);
    resize(&a,4,5); print(&a);
    resize(&a,4,0);
    resize(&a,4,1); print(&a);
    free(a.t);
    return 0;
}
