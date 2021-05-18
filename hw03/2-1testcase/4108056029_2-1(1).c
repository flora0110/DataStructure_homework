#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node* nodepointer;
typedef struct node{
    char alph;
    nodepointer dot;
    nodepointer dash;
}
typedef struct queue* queuepointer;
typedef struct queue{
    node* nodelink;
    queuepointer link;
}queue;
queuepointer front=NULL,rear;
node* queueEmpty(){
    printf("queue is empty\n");
    node* item;
    item->alph='0';
    item->dot=NULL;
    item->dash=NULL;
    return item;
}
void addq(node* item){
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
node* build(){
    char arr[30]={'E','I','S','H','V','U','F','0',\
    'A','R','L','0','W','P','J',\
    'T','N','D','B','X','K','C','Y',\
    'M','G','Z','Q','O','0','0'};
    node* root=(node*)malloc(sizeof(node));
    root->alph='0';
    addq(root);
    node* ptr,temp;
    int n=0;
    while(front){
        temp=deleteq();
        if(arr[n]!='0'){
            ptr=(node*)malloc(sizeof(node));
            ptr->alph=arr[n++];
            temp->dot=ptr;
        }
        else{
            temp->dot=NULL;
            n++;
        }

        if(arr[n]!='0'){
            ptr=(node*)malloc(sizeof(node));
            ptr->alph=arr[n++];
            temp->dash=ptr;
        }
        else{
            temp->dash=NULL;
        }
    }
}
char* trans(char* word,node* root){
    int i;
    for(i=0;i<strlen(word);i++){

    }
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test1.txt","r");
    wptr=fopen("output2-1.txt","w");
    if(rptr==NULL|| wptr==NULL){
        printf("open error\n");
        return 0;
    }
    int n,m,i,j;
    char word[100];
    fscanf(rptr,"%d\n",&n);
    node* root=build();
    char ans[4];
    for(i=0;i<n;i++){
        fscanf(rptr,"%[A-Z]\n",&word);
        //test---------------
        printf("%d \n",strlen(word));
        for(j=0;j<strlen(word);j++){
            printf("%c",word[j]);
        }
        printf("\n");
        //------------------
        ans=trans(word,root);
    }
    fscanf(rptr,"%d\n",&m);
}
