#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_QUEUES 15000
struct TreeNode {
     int data;
     struct TreeNode* left;
     struct TreeNode* right;
};
typedef struct TreeNode node;
typedef struct queue* queuepointer;
typedef struct queue{
    node* nodelink;
    queuepointer link;
}queue;
queuepointer front=NULL,rear;

node* queueEmpty(){
    printf("queue is empty\n");
    node* item;
    item->data=-1;
    item->left=NULL;
    item->right=NULL;
    return item;
}
void addq(node* item){
    //printf("in addq\n");
    queuepointer temp;
    temp=(queuepointer)malloc(sizeof(queue));
    temp->nodelink=item;
    temp->link=NULL;
    if(front){
        rear->link=temp;
    }
    else
        front=temp;
    rear=temp;
    if(front==NULL){
        printf("front is null\n");
    }
}

node* deleteq(){
    queuepointer temp=front;
    node* item;
    if(!temp){
        return queueEmpty();
    }
    item = temp->nodelink;
    front=temp->link;
    free(temp);
    return item;
}

typedef struct Nodenum{
    double num;
    node* fromnode;
    int no;
    int p;
}Nodenum;


typedef struct queue2* queuepointer2;
typedef struct queue2{
    Nodenum data;
    queuepointer2 link;
}queue2;

//typedef struct queue2* queuepointer2;
queuepointer2 front2[MAX_QUEUES],rear2[MAX_QUEUES];
Nodenum queueEmpty2(){
    printf("queue is empty\n");
    Nodenum item;
    item.num=-1;
    item.fromnode=NULL;
    item.no=-1;
    return item;
}
void addq2(Nodenum item,int i){
    queuepointer2 temp;
    temp=(queuepointer2)malloc(sizeof(queue2));
    temp->data=item;
    temp->link=NULL;
    if(front2[i]){
        rear2[i]->link=temp;
    }
    else
        front2[i]=temp;
    rear2[i]=temp;
}

Nodenum deleteq2(int i){
    queuepointer2 temp=front2[i];
    Nodenum item;
    if(!temp){
        return queueEmpty2();
    }
    item = temp->data;
    front2[i]=temp->link;
    free(temp);
    return item;
}

Nodenum minno(int i){
    int min=15001;
    Nodenum temp;
    queuepointer2 now=front2[i];
    while(now){
        if(now->data.num<min){
            min=now->data.num;
            temp=now->data;
            now=now->link;
        }
    }
    return temp;
}
Nodenum maxno(int i){
    int max=-1;
    Nodenum temp;
    queuepointer2 now=front2[i];
    while(now){
        if(now->data.num>max){
            temp=now->data;
            now=now->link;
        }
    }
    return temp;

}
void postorder(node* ptr){
    if(ptr){
        printf("%d\n",ptr->data);
        postorder(ptr->left);
        postorder(ptr->right);
    }
}
int main(){
    int i,j;
    char c;
    //node* Root;
    node* root;
    root=(node*)malloc(sizeof(node));
    c=getc(stdin);
    int n=0;
    //printf("[: %c\n",c);
    int test=1;
    if(c=='['){//???????????????
        //printf("[: %c\n",c);
        c=getc(stdin);//??????
        if(c=='0'){
            printf("root: %c\n",c);
            c=getc(stdin);
            //struct TreeNode root;
            printf("??\n");
            root->data=test++;
            //printf("ready to addq\n");
            addq(root);
            //printf("out addq\n");
            n++;
        }
        while(front){
            //printf("in while\n" );
            struct TreeNode* current;//????????????????????????
            current=deleteq();
            if(c==']'){//??????
                break;
            }
            c=getc(stdin);
            if(c=='0'){
                printf("left: %c\n",c);
                //struct TreeNode newnode;//??????
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                //current.left=&newnode;
                current->left=newnode;
                newnode->data=test++;
                newnode->left=NULL;
                newnode->right=NULL;
                //printf("root's data %d\n",current.data);
                addq(newnode);
                printf("out addq\n");
                n++;
            }
            else if(c=='n'){
                current->left=NULL;
                scanf("%*[ull]");//??????ull
            }
            c=getc(stdin);//???','
            if(c==']'){
                break;
            }
            c=getc(stdin);
            if(c=='0'){
                printf("right: %c\n",c);
                //struct TreeNode newnode;//??????
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                current->right=newnode;
                newnode->left=NULL;
                newnode->right=NULL;
                newnode->data=test++;
                addq(newnode);
                n++;
            }
            else{
                current->right=NULL;
                scanf("%*[ull]");
            }
            c=getc(stdin);//eat ','or']'
        }//-----------------------------------------------?????????
        printf("root's data %d\n",root->data);
        postorder(root);
        printf("bulid tree finish\n");
    }
    else{//????????????[??????
        printf("input error\n");
    }
    printf("start to find\n");
    int lleaf,rleaf;
    //Nodenum nodenum[n][n];
    double den=0;//??????????????????????????????
    double leafden=0;//???????????????????????????????????????
    front=NULL;
    addq(root);
    int nownum=-1;//????????????
    int leafnum=0;//??????????????????????????????
    int k=0;
    //------------------------------------
    while(front){
        struct TreeNode* nowcheck=deleteq();
        nownum++;
        printf("now check %d\n",nownum );
        den=0;
        if(nowcheck->left){
            addq(nowcheck->left);//????????????????????????
            den++;
        }
        if(nowcheck->right){
            addq(nowcheck->right);
            den++;
        }

        Nodenum nodenum;
        nodenum.num=(double)nowcheck->data/(den+1+k);
        nodenum.fromnode=nowcheck;
        nodenum.no=nownum;//????????????
        printf("nowcheck->data : %d\n",nowcheck->data);
        printf("nowcheck->data/(den+1+%d) : %f to %d\n",k,nodenum.num,nownum);
        //nodenum.no=nownum;
        addq2(nodenum,nownum);//???????????????/???+1 ???????????? addq2 queue2[nownum] ?????????????????????????????????
        //nodenum[nownum][nowno].num=nowcheck.data/(den+1);//????????????/den+1
        //nodenum[nownum][nowno].fromnode=&nowcheck;
        if(nowcheck->left){
            leafnum++;//?????????????????????
            Nodenum leftnum;//???????????????
            leftnum.num=nowcheck->data/(den+1+k);//?????????????????????
            leftnum.fromnode=nowcheck;//?????????nownum
            leftnum.no=nownum;
            printf("nowcheck->data/(den+1) : %f to %d\n",leftnum.num,leafnum);
            //leftnum.no=nodenum.no+1;//????????????????????????
            addq2(leftnum,leafnum);
            //nodenum[1][0].num=nowcheck.data/(den+1);
            //??????????????????????????????
            leafden=0;
            if(nowcheck->left->left){
                leafden++;
            }
            if(nowcheck->left->right){
                leafden++;
            }
            //???????????????
            leftnum.no=leafnum;
            leftnum.num=(double)nowcheck->left->data/(leafden+2);
            leftnum.fromnode=nowcheck->left;//????????????
            printf("leftnum.num : %f to %d\n",leftnum.num,nownum);
            addq2(leftnum,nownum);
        }
        if(nowcheck->right){
            leafnum++;//?????????????????????
            Nodenum rightnum;//???????????????
            rightnum.num=nowcheck->data/(den+1+k);//?????????????????????
            rightnum.fromnode=nowcheck;//?????????nownum
            rightnum.no=nownum;
            printf("nowcheck->data/(den+1) : %f to %d\n",rightnum.num,leafnum);
            addq2(rightnum,leafnum);

            //??????????????????????????????
            leafden=0;
            if(nowcheck->right->left){
                leafden++;//??????
            }
            if(nowcheck->right->right){
                leafden++;
            }
            //???????????????
            rightnum.no=leafnum;
            rightnum.num=(double)nowcheck->right->data/(leafden+2);
            rightnum.fromnode=nowcheck->right;//????????????
            printf("rightnum.num : %f to %d\n",rightnum.num,nownum);
            addq2(rightnum,nownum);
        }
        k=1;
    }
    printf("finish find\n");
    printf("start to mark\n");
    int min=15001;
    int mark[nownum];
    int p[nownum];
    //int pro[nownum];
    for(i=0;i<nownum;i++){
        mark[i]=0;
        p[i]=0;
    }
    for(i=0;i<nownum;i++){
        Nodenum minnodenum=minno(i);
        printf("min to protect %d: %d\n", i,minnodenum.no);
        mark[minnodenum.no]++;
    }

    int ans=0;
    for(i=nownum-1;i>=0;i--){
        if(p[i]==0){//????????????
            Nodenum marknode=maxno(i);//-1 ?????? ??????????????????????????????????????????????????????????????????
            if(marknode.fromnode->data!=-1){//???????????????
                ans++;
                marknode.fromnode->data=-1;
            }
            p[i]=1;
        }
    }
}
