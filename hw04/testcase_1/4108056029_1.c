#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node* nodepointer;
typedef struct chan_node* chan_nodepointer;
typedef struct node{
    char *state;//此點的鳴子
    char *function;//此變數的fun
    int check;//是否跑過
    chan_nodepointer next;//轉換的變數
    chan_nodepointer rear;//這一行的最後
}node;//標頭變數
typedef struct chan_node{
    nodepointer link;//指向標頭
    chan_nodepointer next;//指向下一個
}chan_node;//轉換的變數

node *var_trans[11];//變數
node* variable_to_pointer(char* v,int n){//v is a variable//要把變數(字串)換成指向標頭的指標
    int i;
    for(i=0;i<n;i++){
        if(strlen(var_trans[i]->state)==strlen(v) && strncmp(var_trans[i]->state,v,strlen(v))==0){//一樣長且一樣
            return var_trans[i];
        }
    }
}
void build(char* chan,char *pch,int n,char *function){//chan = f(chainto)
    node* chantemp=variable_to_pointer(chan,n);//找到標頭變數
    node* pchtemp=variable_to_pointer(pch,n);//找到要轉換成的變數的標頭
    chantemp->function=function;//此標頭變數的函數
    chan_nodepointer new=(chan_node*)malloc(sizeof(chan_node));
    new->link=pchtemp;
    new->next=NULL;
    if(chantemp->rear==NULL){
        chantemp->next=new;
    }
    else{
        chantemp->rear->next=new;
    }
    chantemp->rear=new;
}
char ans[11][1000];//答案先存著
int k=0;//記現在到哪個變數要存在ans[k]
int showans(node* now){//開始印出now的解 0是無解
    if(now->function==NULL){
        strcat(ans[k],now->state);
        strcat(ans[k]," ");
        return 1;
    }
    else{//還可以展開
        strcat(ans[k],now->function);
        strcat(ans[k],"( ");
        chan_nodepointer next=now->next;//所以有轉換成的變數
        while(next!=NULL){//沒變數了出去
            if(next->link->check==1){//者個在這條解法中出現過了，是迴圈
                return 0;//無解
            }
            next->link->check=1;//這條路中走過
            int c=showans(next->link);
            if(c==0){//其中一變數會出現loop
            	return 0;
			}
            next->link->check=0;//復原
            next=next->next;
        }
        strcat(ans[k],") ");
        return 1;
    }
}
int main(){
    FILE *rptr;
    rptr=fopen("test5.txt","r");//test---------------------------------test
    if(rptr==NULL){
        printf("open error\n");
        return 0;
    }
    int i,j;
    int n,m;
    fscanf(rptr,"%d\n",&n);
    printf("n: %d\n",n );
    for(i=0;i<n;i++){
        var_trans[i]=(nodepointer)malloc(sizeof(node));
        var_trans[i]->state=(char*)malloc(4*sizeof(char));
        fscanf(rptr,"%s ",var_trans[i]->state);
        var_trans[i]->next=NULL;
        var_trans[i]->function=NULL;
        var_trans[i]->check=0;
        var_trans[i]->rear=NULL;
    }
    fscanf(rptr,"%d\n",&m);
    printf("m: %d\n",m );
    char chinto[21];//chan=f(chinto)
    char chan[4];
    char *function;
    const char* delim = " ";
    for(i=0;i<m;i++){
        function = (char*)malloc(4*sizeof(char));
        fscanf(rptr,"%s = %[^(] %*c %[^)] )\n",chan,function,chinto);
        char* pch=strtok(chinto,delim);//以空格切
        while(pch){
            build(chan,pch,n,function);
            pch=strtok(NULL,delim);
        }
    }
    int check=1;
    for(i=0;i<n;i++){
        var_trans[i]->check=1;
        memset(ans[i],'\0',1000);
        check=showans(var_trans[i]);
        k++;
        var_trans[i]->check=0;
        if(check==0){
            printf("no solution\n");
            break;
        }
    }
    if(check){
        for(i=0;i<n;i++){
            for(j=0;j<strlen(var_trans[i]->state);j++){
                printf("%c",var_trans[i]->state[j]);
            }
            printf(" -> ");
            for(j=0;j<strlen(ans[i]);j++){
                printf("%c",ans[i][j]);
            }
            printf("\n");
        }
    }
    for(i=0;i<n;i++){
        free(var_trans[i]->state);
        free(var_trans[i]->function);
        free(var_trans[i]->next);
        free(var_trans[i]);
    }
    fclose(rptr);
}
