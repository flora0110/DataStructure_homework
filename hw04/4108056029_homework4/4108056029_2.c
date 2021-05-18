#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int check[10000];//1->fordid
int way[8];//每隔要轉的up and down
typedef struct node* nodepointer;//先弄成樹等等printf路徑
typedef struct node{
    int* data;//這格轉到
    nodepointer link[8];//轉不同方向會到
    int way[8];//個還有哪些可轉 轉多少
}node;

typedef struct queue* queuepointer;//跑bfs找最短
typedef struct queue{
    node* treenode;
    queuepointer link;
}queue;
queuepointer rear,front=NULL;
node* deleteq();
void addq(node*);

typedef struct stack* stackpointer;//存路徑
typedef struct stack{
    int *data;
    stackpointer link;
}stack;
stackpointer top=NULL;
int* pop();
void push(int*);

typedef struct stack2* stackpointer2;//太蠢反了要倒出來
typedef struct stack2{
    int *data;
    stackpointer2 link;
}stack2;
stackpointer2 top2=NULL;
int* pop2();
void push2(int*);

int check_in(int*);//回傳這個是否可以轉 1->forbid
void set_way(int*);//把way[8]弄好
int bfs();//跑最短
int* turn(int ,int*);//回傳轉一次後變成
int dfs_mark(node*);//跑樹存最短
int main(){
    FILE *rptr;
    rptr=fopen("test4.txt","r");//test-------------------------------------------test
    if(rptr==NULL){
        return 0;
    }
    int *now=(int*)malloc(4*sizeof(int));//起始狀態
    int *password=(int*)malloc(4*sizeof(int));//password
    int *diff=(int*)malloc(4*sizeof(int));//起始和答案的差
    int i,j,n;
    for(i=0;i<4;i++){
        fscanf(rptr,"%d ",&now[i]);
    }
    for(i=0;i<4;i++){
        fscanf(rptr,"%d ",&password[i]);
        diff[i]=password[i]-now[i];
    }
    set_way(diff);
    fscanf(rptr,"%d\n",&n);//幾個不能碰的
    memset(check,0,10000);//check==0 ok / check==1 forbid
    int sum=0;
    int num;
    for(i=0;i<n;i++){
        sum=0;
        for(j=0;j<4;j++){
            fscanf(rptr,"%d ",&num);
            sum+=pow(10,3-j)*num;//換成四位數
        }
        check[sum]=1;//forbid
    }
    nodepointer root=(nodepointer)malloc(sizeof(node));
    root->data=now;
    for(i=0;i<8;i++){
        root->link[i]=NULL;
    }
    for(i=0;i<8;i++){
        root->way[i]=way[i];
    }
    addq(root);
    int can=bfs(password);
    if(can){//有路
        int sum=0;
        for(i=0;i<8;i++){
            sum+=way[i];
        }
        push(root->data);
        dfs_mark(root);
        while(top){//反啦倒出來
            push2(pop());
        }
        printf("%d\n",sum);
        pop2();
        while(top2){//印答案
            for(i=0;i<4;i++){
                printf("%d",top2->data[i]);
            }
            printf("\n");
            pop2();
        }

    }
    else{
        printf("Impossible\n");
    }
}
node* deleteq(){
    if(front==NULL){
        return NULL;
    }
    queuepointer temp=front;
    node* item;
    item=temp->treenode;
    front=temp->link;
    free(temp);
    return item;
}
void addq(node* item){
    queuepointer temp;
    temp=(queue*)malloc(sizeof(queue));
    temp->treenode=(nodepointer)malloc(sizeof(node));
    temp->treenode=item;
    temp->link=NULL;
    if(front==NULL){
        front=temp;
    }
    else{
        rear->link=temp;
    }
    rear=temp;
}
int* pop(){
    if(top==NULL){
        return NULL;
    }
    stackpointer temp=top;
    int* item;
    item=temp->data;
    top=temp->link;
    free(temp);
    return item;
}
void push(int* item){
    stackpointer temp;
    temp=(stack*)malloc(sizeof(stack));
    temp->data=item;
    temp->link=top;
    top=temp;
}

int* pop2(){
    if(top2==NULL){
        return NULL;
    }
    stackpointer2 temp=top2;
    int* item;
    item=temp->data;
    top2=temp->link;
    free(temp);
    return item;
}
void push2(int* item){
    stackpointer2 temp;
    temp=(stack2*)malloc(sizeof(stack2));
    temp->data=item;
    temp->link=top2;
    top2=temp;
}
void set_way(int *diff){
    int test[4];//算出來要轉每隔多少
    test[0]=diff[0]+diff[3]-diff[2];
    test[1]=(-diff[3])+diff[2];
    test[2]=(-diff[0])+diff[1];
    test[3]=diff[0]+diff[3]-diff[1];
    int i;
    for(i=0;i<4;i++){
        if(test[i]>0){//處理正反轉
            way[i]=test[i];
            way[4+i]=10-way[i];
        }
        else{
            way[4+i]=-test[i];
            way[i]=10-way[4+i];
        }
        if(way[i]<way[i+4]){//存少的就好
            way[i+4]=0;
        }
        else{
            way[i]=0;
        }
    }
}
int check_in(int *need_check){//1->fordid
    int i;
    int sum=0;
    for(i=0;i<4;i++){
        sum+=pow(10,3-i)*need_check[i];//轉成四位數
    }
    return check[sum];
}
int bfs(int* password){
    int* now;//現在的狀態
    int* new;//轉完變成
    node* current;//現在在的node
    node* newnode;//新的(如果可走)
    int i,j;
    int nowway[8];//在現在這個點的每隔格可轉
    while(front){//queue跑廣度
        current=deleteq();
        now=current->data;
        for(i=0;i<8;i++){
            nowway[i]=current->way[i];
        }
        int can=0;//檢查走完八方是否都有路
        for(i=0;i<8;i++){
            if(nowway[i]==0){
                current->link[i]=NULL;//明明早就初始化了，但是沒這行還是會報錯
                continue;
            }
            new=turn(i,now);//轉完變成
            if(check_in(new)==0){
                newnode=(node*)malloc(sizeof(node));
                for(j=0;j<8;j++){
                    newnode->link[i]=NULL;//初始化
                }
                can=1;//有路
                newnode->data=new;
                for(j=0;j<8;j++){
                    newnode->way[j]=nowway[j];
                    if(i==j){//走了這個要--way值
                        newnode->way[j]--;
                    }
                }
                addq(newnode);//可走的丟進去~
                current->link[i]=newnode;
                if(new[0]==password[0] &&new[1]==password[1] &&new[2]==password[2] &&new[3]==password[3]){
                    newnode->way[0]=-1;//方便等等爬樹確定這是終點
                    return 1;
                }
            }
        }
        if(can==0){
            return 0;//沒路
        }
    }
}
int* turn(int w,int* now){
    int* new=(int*)malloc(4*sizeof(int));
    switch(w){
        case 0:new[0]=now[0]+1;     new[1]=now[1]+1;    new[2]=now[2];     new[3]=now[3];break;
        case 1:new[0]=now[0]+1;     new[1]=now[1]+1;    new[2]=now[2]+1;   new[3]=now[3];break;
        case 2:new[0]=now[0];       new[1]=now[1]+1;    new[2]=now[2]+1;   new[3]=now[3]+1;break;
        case 3:new[0]=now[0];       new[1]=now[1];      new[2]=now[2]+1;   new[3]=now[3]+1;break;
        case 4:new[0]=now[0]-1;     new[1]=now[1]-1;    new[2]=now[2];     new[3]=now[3];break;
        case 5:new[0]=now[0]-1;     new[1]=now[1]-1;    new[2]=now[2]-1;   new[3]=now[3];break;
        case 6:new[0]=now[0];       new[1]=now[1]-1;    new[2]=now[2]-1;   new[3]=now[3]-1;break;
        case 7:new[0]=now[0];       new[1]=now[1];      new[2]=now[2]-1;   new[3]=now[3]-1;break;
    }
    int i;
    for(i=0;i<4;i++){
        if(new[i]<0 || new[i]>9){//轉超過要繞回來
            new[i]=10-abs(new[i]);
        }
    }
    return new;
}
int dfs_mark(node* root){
    int i,j;
    if(root->way[0]==-1){//找到終點
        return 1;
    }
    for(i=0;i<8;i++){
        if(root->link[i]){
            push(root->link[i]->data);//路放進去~
            return dfs_mark(root->link[i]);
            pop();//路拿出來
        }
    }
}

