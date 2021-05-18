#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char mose[3][5]={{'.','-','a','v'},{'-','.','.','.'},{'-','.','-','a'}};
int main(){
    int i,j;
    /*for(i=0;i<3;i++){
        printf("%d %d\n",i,strlen(mose[i]));
        printf("%p\n",&mose[i]);
        for(j=0;j<strlen(mose[i]);j++){
            printf("%p\n",&mose[i][j]);
            //printf("%p\n",&mose[i*4+j]);
            printf("%c\n",mose[i][j]);
        }
    }*/
    for(i=0;i<10;i++){
        printf("is %d\n",i );
        if(i==3){
            continue;
        }
        printf("is %d\n",i );
    }
}
