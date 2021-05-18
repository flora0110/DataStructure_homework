#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int check[10000];//1->fordid
int way[8];//�C�j�n�઺up and down
typedef struct node* nodepointer;//���˦��𵥵�printf���|
typedef struct node{
    int* data;//�o�����
    nodepointer link[8];//�ण�P��V�|��
    int way[8];//���٦����ǥi�� ��h��
}node;

typedef struct queue* queuepointer;//�]bfs��̵u
typedef struct queue{
    node* treenode;
    queuepointer link;
}queue;
queuepointer rear,front=NULL;
node* deleteq();
void addq(node*);

typedef struct stack* stackpointer;//�s���|
typedef struct stack{
    int *data;
    stackpointer link;
}stack;
stackpointer top=NULL;
int* pop();
void push(int*);

typedef struct stack2* stackpointer2;//�����ϤF�n�˥X��
typedef struct stack2{
    int *data;
    stackpointer2 link;
}stack2;
stackpointer2 top2=NULL;
int* pop2();
void push2(int*);

int check_in(int*);//�^�ǳo�ӬO�_�i�H�� 1->forbid
void set_way(int*);//��way[8]�˦n
int bfs();//�]�̵u
int* turn(int ,int*);//�^����@�����ܦ�
int dfs_mark(node*);//�]��s�̵u
int main(){
    FILE *rptr;
    rptr=fopen("test4.txt","r");//test-------------------------------------------test
    if(rptr==NULL){
        return 0;
    }
    int *now=(int*)malloc(4*sizeof(int));//�_�l���A
    int *password=(int*)malloc(4*sizeof(int));//password
    int *diff=(int*)malloc(4*sizeof(int));//�_�l�M���ת��t
    int i,j,n;
    for(i=0;i<4;i++){
        fscanf(rptr,"%d ",&now[i]);
    }
    for(i=0;i<4;i++){
        fscanf(rptr,"%d ",&password[i]);
        diff[i]=password[i]-now[i];
    }
    set_way(diff);
    fscanf(rptr,"%d\n",&n);//�X�Ӥ���I��
    memset(check,0,10000);//check==0 ok / check==1 forbid
    int sum=0;
    int num;
    for(i=0;i<n;i++){
        sum=0;
        for(j=0;j<4;j++){
            fscanf(rptr,"%d ",&num);
            sum+=pow(10,3-j)*num;//�����|���
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
    if(can){//����
        int sum=0;
        for(i=0;i<8;i++){
            sum+=way[i];
        }
        push(root->data);
        dfs_mark(root);
        while(top){//�ϰխ˥X��
            push2(pop());
        }
        printf("%d\n",sum);
        pop2();
        while(top2){//�L����
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
    int test[4];//��X�ӭn��C�j�h��
    test[0]=diff[0]+diff[3]-diff[2];
    test[1]=(-diff[3])+diff[2];
    test[2]=(-diff[0])+diff[1];
    test[3]=diff[0]+diff[3]-diff[1];
    int i;
    for(i=0;i<4;i++){
        if(test[i]>0){//�B�z������
            way[i]=test[i];
            way[4+i]=10-way[i];
        }
        else{
            way[4+i]=-test[i];
            way[i]=10-way[4+i];
        }
        if(way[i]<way[i+4]){//�s�֪��N�n
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
        sum+=pow(10,3-i)*need_check[i];//�ন�|���
    }
    return check[sum];
}
int bfs(int* password){
    int* now;//�{�b�����A
    int* new;//�৹�ܦ�
    node* current;//�{�b�b��node
    node* newnode;//�s��(�p�G�i��)
    int i,j;
    int nowway[8];//�b�{�b�o���I���C�j��i��
    while(front){//queue�]�s��
        current=deleteq();
        now=current->data;
        for(i=0;i<8;i++){
            nowway[i]=current->way[i];
        }
        int can=0;//�ˬd�����K��O�_������
        for(i=0;i<8;i++){
            if(nowway[i]==0){
                current->link[i]=NULL;//�������N��l�ƤF�A���O�S�o���٬O�|����
                continue;
            }
            new=turn(i,now);//�৹�ܦ�
            if(check_in(new)==0){
                newnode=(node*)malloc(sizeof(node));
                for(j=0;j<8;j++){
                    newnode->link[i]=NULL;//��l��
                }
                can=1;//����
                newnode->data=new;
                for(j=0;j<8;j++){
                    newnode->way[j]=nowway[j];
                    if(i==j){//���F�o�ӭn--way��
                        newnode->way[j]--;
                    }
                }
                addq(newnode);//�i������i�h~
                current->link[i]=newnode;
                if(new[0]==password[0] &&new[1]==password[1] &&new[2]==password[2] &&new[3]==password[3]){
                    newnode->way[0]=-1;//��K��������T�w�o�O���I
                    return 1;
                }
            }
        }
        if(can==0){
            return 0;//�S��
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
        if(new[i]<0 || new[i]>9){//��W�L�n¶�^��
            new[i]=10-abs(new[i]);
        }
    }
    return new;
}
int dfs_mark(node* root){
    int i,j;
    if(root->way[0]==-1){//�����I
        return 1;
    }
    for(i=0;i<8;i++){
        if(root->link[i]){
            push(root->link[i]->data);//����i�h~
            return dfs_mark(root->link[i]);
            pop();//�����X��
        }
    }
}

