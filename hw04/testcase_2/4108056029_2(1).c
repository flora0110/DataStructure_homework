#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int check[10000];
int way[8];
typedef struct node* nodepointer;
typedef struct node{
    int* data;
    nodepointer link[8];
    int way[8];
}node;
typedef struct queue* queuepointer;
typedef struct queue{
    node* treenode;
    queuepointer link;
}queue;
queuepointer rear,front=NULL;
node* deleteq();
void addq(node*);

typedef struct stack* stackpointer;
typedef struct stack{
    int *data;
    stackpointer link;
}stack;
stackpointer top=NULL;
int* pop();
void push(int*);

typedef struct stack2* stackpointer2;
typedef struct stack2{
    int *data;
    stackpointer2 link;
}stack2;
stackpointer2 top2=NULL;
int* pop2();
void push2(int*);

int check_in(int*);
void set_way(int*);
int bfs();
int* turn(int ,int*);
int dfs_mark(node*);
int updown[2];
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test4.txt","r");
    wptr=fopen("output.txt","w");
    if(rptr==NULL || wptr==NULL){
        return 0;
    }
    int *now=(int*)malloc(4*sizeof(int));//起始狀態
    int *password=(int*)malloc(4*sizeof(int));//password
    int *diff=(int*)malloc(4*sizeof(int));//起始和答案的差
    int i,j,n;
    printf("now: ");
    for(i=0;i<4;i++){
        fscanf(rptr,"%d ",&now[i]);
        printf("%d ",now[i]);
    }
    printf("\n");
    printf("password: ");
    for(i=0;i<4;i++){
        fscanf(rptr,"%d ",&password[i]);
        printf("%d",password[i] );
        diff[i]=password[i]-now[i];
    }
    printf("\n");
    set_way(diff);
    printf("way: ");
    for(i=0;i<8;i++){
        printf("%d ",way[i]);
    }
    printf("\n");
    fscanf(rptr,"%d\n",&n);//幾個不能碰的
    memset(check,0,10000);//check==0 ok / check==1 forbid
    int sum=0;
    int num;
    for(i=0;i<n;i++){
        sum=0;
        for(j=0;j<4;j++){
            fscanf(rptr,"%d ",&num);
            sum+=pow(10,3-j)*num;
        }
        check[sum]=1;
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
    if(can){
        int sum=0;
        for(i=0;i<8;i++){
            sum+=way[i];
        }
        push(root->data);
        dfs_mark(root);
        while(top){
            /*for(i=0;i<4;i++){
                printf("%d ",top->data[i]);
            }
            printf("\n");*/
            push2(pop());
        }
        printf("%d\n",sum);
        while(top2){
            for(i=0;i<4;i++){
                printf("%d ",top2->data[i]);
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
    int test[4];
    test[0]=diff[0]+diff[3]-diff[2];
    test[1]=(-diff[3])+diff[2];
    test[2]=(-diff[0])+diff[1];
    test[3]=diff[0]+diff[3]-diff[1];
    int i;
    for(i=0;i<4;i++){
        if(test[i]>0){
            way[i]=test[i];
            way[4+i]=10-way[i];
        }
        else{
            way[4+i]=-test[i];
            way[i]=10-way[4+i];
        }
        if(way[i]<way[i+4]){
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
        sum+=pow(10,3-i)*need_check[i];
    }
    return check[sum];
}
int bfs(int* password){
    int* now;
    int* new;
    node* current;
    node* newnode;
    int i,j;
    int nowway[8];
    while(front){
        current=deleteq();
        now=current->data;
        for(i=0;i<8;i++){
            nowway[i]=current->way[i];
        }
        /*printf("---------------now: ");
        for(i=0;i<4;i++){
            printf("%d ",now[i]);
        }
        printf("\n");*/
        int can=0;
        for(i=0;i<8;i++){

            //printf("nowway[%d]: %d\n",i,nowway[i]);
            if(nowway[i]==0){
                current->link[i]=NULL;
                continue;
            }

            new=turn(i,now);
            if(check_in(new)==0){
                newnode=(node*)malloc(sizeof(node));
                for(j=0;j<8;j++){
                    newnode->link[i]=NULL;
                }
                can=1;
                newnode->data=new;
                //printf("newnode address %p\n",newnode);
                //printf("newnode->way: ");
                for(j=0;j<8;j++){
                    newnode->way[j]=nowway[j];
                    if(i==j){
                        newnode->way[j]--;
                    }
                    //printf("%d ",newnode->way[j]);
                }
                //printf("\n");
                addq(newnode);
                current->link[i]=newnode;
                //way[i]--;
                /*printf("way: %d\n",i);
                printf("ok 's new: ");
                for(j=0;j<4;j++){
                    printf("%d ",new[j]);
                }
                printf("\n");*/
                if(new[0]==password[0] &&new[1]==password[1] &&new[2]==password[2] &&new[3]==password[3]){
                    /*for(j=0;j<8;j++){
                        printf("%d ",newnode->way[j]);
                    }
                    printf("\n");*/
                    newnode->way[0]=-1;
                    //printf("arrive\n");
                    return 1;
                }
            }
        }
        if(can==0){
            return 0;
        }
        //printf("\n");
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
    //printf("way: %d\n",w );
    //printf("new: ");
    for(i=0;i<4;i++){
        if(new[i]<0 || new[i]>9){
            new[i]=10-abs(new[i]);
        }
        //printf("%d ",new[i]);
    }
    //printf("\n");
    return new;
}
int dfs_mark(node* root){
    int i,j;
    /*for(i=0;i<4;i++){
        printf("%d ",root->data[i]);
    }
    printf("\n");*/

    if(root->way[0]==-1){
        return 1;
    }
    int check=0;
    for(i=0;i<8;i++){
        //printf("way %d\n",i );
        if(root->link[i]){
            //printf("can\n");
            push(root->link[i]->data);
            check=dfs_mark(root->link[i]);
            if(check){
                return 1;
            }
            pop();
        }
    }
}
