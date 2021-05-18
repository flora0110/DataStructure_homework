#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *ansptr;
    FILE *testptr;
    ansptr=fopen("output3.txt","r");
    testptr=fopen("output1-1.txt","r");
    if(ansptr==NULL || testptr==NULL){
        printf("ERROR\n");
        return 0;//
    }
    int ans,test;
    while(fscanf(ansptr,"%d\n",&ans)!=EOF && fscanf(testptr,"%d\n",&test)!=EOF){
        //printf("%d %d\n",ans,test);
        if(ans!=test){
            printf("%d %d\n",ans,test);
        }
    }
    while(fscanf(ansptr,"%d\n",&ans)!=EOF || fscanf(testptr,"%d\n",&test)!=EOF){
        printf("%d %d\n",ans,test);
        /*if(ans!=test){
            printf("%d %d\n",ans,test);
        }*/
    }
}
