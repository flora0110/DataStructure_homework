#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
void find(char*,int);
long long check(char*,int);
char mose[26][5]={{'.','-'},{'-','.','.','.'},{'-','.','-','.'},{'-','.','.'},{'.'},\
    {'.','.','-','.'},{'-','-','.'},{'.','.','.','.'},{'.','.'},{'.','-','-','-'},\
    {'-','.','-'},{'.','-','.','.'},{'-','-'},{'-','.'},{'-','-','-'},\
    {'.','-','-','.'},{'-','-','.','-'},{'.','-','.'},{'.','.','.'},{'-'},\
    {'.','.','-'},{'.','.','.','-'},{'.','-','-'},{'-','.','.','-'},{'-','.','-','-'},{'-','-','.','.'}};
typedef struct node* nodepointer;
typedef struct node{
    int data;//有多少單字的摩斯密碼是這個組合
    nodepointer dot;//指向現在的組合加一個點的組合
    nodepointer dash;
}node;
nodepointer root;//字典樹
void trans(char* word){//把單字加到樹
    int i,j;
    nodepointer temp=root;
    for(i=0;i<strlen(word);i++){
        for(j=0;j<strlen(mose[word[i]-65]);j++){
            if(mose[word[i]-65][j]=='.'){
                if(temp->dot==NULL){
                    nodepointer new;
                    MALLOC(new,sizeof(node));
                    new->dot=NULL;
                    new->dash=NULL;
                    new->data=0;
                    temp->dot=new;
                }
                temp=temp->dot;
            }
            else if(mose[word[i]-65][j]=='-'){
                if(temp->dash==NULL){
                    nodepointer new;
                    MALLOC(new,sizeof(node));
                    new->dot=NULL;
                    new->dash=NULL;
                    new->data=0;
                    temp->dash=new;
                }
                temp=temp->dash;
            }
        }
    }
    temp->data++;//是這個組合的單字加一
}
int *step;//是否有走過
long long *arrive;//現在到這個點時後面會有的組合
void find(char* code,int now){
    nodepointer temp=root;
    int orinow=now;
    do{
        if(code[now]=='.'){
            temp=temp->dot;
            now++;
        }
        else if(code[now]=='-'){
            temp=temp->dash;
            now++;
        }
        if(!temp){
            break;
        }
        if(temp->data!=0){//有字典內的字和code prefix
            arrive[orinow]+=(temp->data)*check(code,now);//現在者個點的組合數現在+之後的
        }
    }while(now<strlen(code));
}

long long check(char* code,int now){//找組合數
    if(now==strlen(code)){//到最後一個了
        return 1;
    }
    if(step[now]==0){
        return arrive[now];//走過了，已經知道
    }
    else{
        find(code,now);//去找看看字典內是否有符合的，已知道在這個點的組合數(arrive[now])
    }
    step[now]=0;//標記走過
    return arrive[now];
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test.txt","r");//test--------------test.txt
    wptr=fopen("output.txt","w");
    if(rptr==NULL|| wptr==NULL){
        printf("open error\n");
        return 0;
    }
    clock_t start,end; // 儲存時間用的變數
    start = clock(); // 計算開始時間
    int n;
    int i,j;
    root=(nodepointer)malloc(sizeof(node));
    root->data=0;
    root->dot=NULL;
    root->dash=NULL;

    char *code=(char*)malloc(100001*sizeof(char));
    fscanf(rptr,"%[-.]\n",code);
    fscanf(rptr,"%d\n",&n);
    int coden=strlen(code);

    step=(int*)malloc(coden*sizeof(int));//(全域)是否有走過
    arrive=(long long*)malloc(coden*sizeof(long long));//(全域)現在到這個點時後面會有的組合
    for(i=0;i<coden;i++){
        arrive[i]=0;//初始化
    }
    for(i=0;i<coden;i++){
        step[i]=1;//初始化(未走過=1)
    }
    char *word=(char*)malloc(21*sizeof(char));
    for(i=0;i<n;i++){
        fscanf(rptr,"%[A-Z]\n",word);
        trans(word);
    }
    check(code,0);
    printf("output: %lld\n",arrive[0]);
    fprintf(wptr,"output: %lld\n",arrive[0]);

    free(code);
    free(word);
    free(step);
    free(arrive);
    fclose(rptr);
    fclose(wptr);
    end=clock();
    double diff = end - start;
    printf("\n %f ms",diff);
    printf(" %f sec",diff/CLOCKS_PER_SEC );
}
