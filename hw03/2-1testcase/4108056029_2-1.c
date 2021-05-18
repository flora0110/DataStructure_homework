#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char mose[26][5]={{'.','-'},{'-','.','.','.'},{'-','.','-','.'},{'-','.','.'},{'.'},\
    {'.','.','-','.'},{'-','-','.'},{'.','.','.','.'},{'.','.'},{'.','-','-','-'},\
    {'-','.','-'},{'.','-','.','.'},{'-','-'},{'-','.'},{'-','-','-'},\
    {'.','-','-','.'},{'-','-','.','-'},{'.','-','.'},{'.','.','.'},{'-'},\
    {'.','.','-'},{'.','.','.','-'},{'.','-','-'},{'-','.','.','-'},{'-','.','-','-'},{'-','-','.','.'}};
char* trans(char* word){
    int i,j;
    int n=0;
    char *result=(char*)malloc(400*sizeof(char));
    for(i=0;i<strlen(word);i++){
        //printf("for %d\n",strlen(mose[word[i]-65]));
        for(j=0;j<strlen(mose[word[i]-65]);j++){
            result[n++]=mose[word[i]-65][j];
            //printf("%d %c %c\n",j,mose[word[i]-65][j],result[n-1]);
        }
        result[n]='\0';
    }
    return result;
}
int indiction(char* code,char** diction,int n){
    int i,j;
    int check=0;
    for(i=0;i<n;i++){
        if(strlen(code)!=strlen(diction[i])){
            continue;
        }
        check=1;
        for(j=0;j<strlen(code);j++){
            if(code[j]!=diction[i][j]){
                check=0;
                break;
            }
        }
        if(check==1){
            return 1;
        }
    }
    return check;
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test3.txt","r");
    wptr=fopen("output2-1.txt","w");
    if(rptr==NULL|| wptr==NULL){
        printf("open error\n");
        return 0;
    }
    int n,m,i,j;
    char word[100];
    char code[400];
    fscanf(rptr,"%d\n",&n);
    char *ans=(char*)malloc(400*sizeof(char));
    char **diction=(char**)malloc(n*sizeof(char*));
    for(i=0;i<n;i++){
        fscanf(rptr,"%[A-Z]\n",&word);
        ans=trans(word);
        diction[i]=ans;

        //fprintf(wptr,"\n");
    }
    fscanf(rptr,"%d\n",&m);
    printf("\n");
    for(i=0;i<m;i++){
        fscanf(rptr,"%[.-]\n",&code);
        for(j=0;j<strlen(code);j++){
            //printf("%c",code[j]);
            fprintf(wptr,"%c",code[j]);
        }
        if(indiction(code,diction,n)){
            //printf(" is found in the dictionary.\n");
            fprintf(wptr," is found in the dictionary.\n");
        }
        else{
            //printf(" is not found in the dictionary.\n");
            fprintf(wptr," is not found in the dictionary.\n");
        }
    }
    fclose(wptr);
    fclose(rptr);
}
