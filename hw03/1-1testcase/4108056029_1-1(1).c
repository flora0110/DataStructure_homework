#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        printf("out\n");\
        exit(EXIT_FAILURE);\
    }
int max(int a,int b){
    if(a>b){
        return a;
    }
    else return b;
}
typedef struct Treenode* nodepointer;
typedef struct Treenode{
    int sum;
    int ls;
    int rs;
    int max;
    nodepointer left;
    nodepointer right;
}node;
node build(int l,int r,int* arr){
    printf("in build\n");
    node ptr;
    node* ptrn=&ptr;
    //ptrn=(node*)malloc(sizeof(node));
    //node* ptrn=(node*)malloc(sizeof(node));
    //printf("ptr\n");
    if(r==l){
        //ptrn=(node*)malloc(sizeof(node));
        //printf("in if\n");
        ptrn->sum=arr[l];
        ptrn->ls=arr[l];
        ptrn->rs=arr[l];
        ptrn->max=arr[l];
        printf("leaf : %d %d : %d\n",l,r,ptrn->sum);
        return ptr;
    }
    else{
        //printf("inelse \n" );
        printf("%d %d\n",l,r );
        //ptrn=(node*)malloc(sizeof(node));
        printf("in else\n");
        int m=(l+r)/2;
        printf("in left\n");
        node leftn=build(1,m,arr);
        printf("in right\n");
        node rightn=build(m+1,r,arr);
        ptrn->sum=leftn.sum+rightn.sum;
        printf("left: %d right: %d\n",leftn.sum,rightn.sum );
        ptrn->ls=max(leftn.ls,leftn.sum+rightn.ls);
        ptrn->rs=max(rightn.rs,rightn.sum+leftn.rs);
        ptrn->max=max(max(rightn.max,leftn.max),leftn.rs+rightn.ls);
        printf("node : %d %d : %d\n",l,r,ptrn->sum);
        ptrn->left=&leftn;
        ptrn->right=&rightn;
        /*
        ptrn->sum=leftn->sum+rightn->sum;
        printf("left: %d right: %d\n",leftn->sum,rightn->sum );
        ptrn->ls=max(leftn->ls,leftn->sum+rightn->ls);
        ptrn->rs=max(rightn->rs,rightn->sum+leftn->rs);
        ptrn->max=max(max(rightn->max,leftn->max),leftn->rs+rightn->ls);
        printf("node : %d %d : %d\n",l,r,ptrn->sum);
        ptrn->left=leftn;
        ptrn->right=rightn;*/
        return ptr;
    }
}
void modify(int x,int value,int l,int r,node* ptr){
    if(l==r){
        ptr->sum=value;
        ptr->ls=value;
        ptr->rs=value;
        ptr->max=value;
        return;
    }
    int m=(r+l)/2;
    if(x<m){
        modify(x,value,l,m,ptr->left);
    }
    else{
        modify(x,value,m+1,r,ptr->right);
    }
    ptr->sum=ptr->left->sum+ptr->right->sum;
    ptr->ls=max(ptr->left->ls,ptr->left->sum+ptr->right->ls);
    ptr->rs=max(ptr->right->rs,ptr->right->sum+ptr->left->rs);
    ptr->max=max(max(ptr->right->max,ptr->left->max),ptr->left->rs+ptr->right->ls);
}
typedef struct imfor{
    int sum;
    int ls;
    int rs;
    int max;
}imfor;
imfor find(int a,int b,int l,int r,node* ptr){
    imfor im;
    if(a==r && b==r){
        im.sum=ptr->sum;
        im.ls=ptr->ls;
        im.rs=ptr->rs;
        im.max=ptr->max;
        return im;
    }
    int m=(l+r)/2;
    if(b<m){
        im = find(a,b,l,m,ptr->left);
    }
    if(a>m){
        im = find(a,b,m+1,r,ptr->right);
    }
    else{
        imfor leftim=find(a,m,l,m,ptr->left);
        imfor rightim=find(m,b,m,r,ptr->right);
        im.sum=leftim.sum+rightim.sum;
        im.ls=max(leftim.ls,leftim.sum+rightim.ls);
        im.rs=max(rightim.rs,rightim.sum+leftim.rs);
        im.max=max(max(rightim.max,leftim.max),leftim.rs+rightim.ls);
    }
    return im;
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test1.txt","r");
    wptr=fopen("output1-1.txt","w");
    if(rptr==NULL ||wptr==NULL){
        printf("open error\n");
        return 0;
    }
    int i,j;
    int t,n,m;
    fscanf(rptr,"%d\n",&t);
    printf("t: %d\n",t);
    node* root;
    int* arr;
    for(i=0;i<t;i++){
        fscanf(rptr,"%d\n",&n);
        printf("n: %d\n",n);
        arr=(int*)malloc((n+1)*sizeof(int));
        arr[0]=0;
        for(j=1;j<n;j++){
            fscanf(rptr,"%d ",&arr[j]);
        }
        fscanf(rptr,"%d\n",&arr[j]);
        //test-----------------------------
        printf("----test----\n");
        for(j=1;j<=n;j++){
            printf("%d \n",arr[j]);
        }
        printf("------------\n");
        //---------------------------------*/
        //int a[8]={1,2,3,4,5,6,7,8};
        root=build(1,n,arr,n);
        fscanf(rptr,"%d\n",&m);
        printf("m: %d\n",m);
        char c;
        int n1,n2;
        for(j=0;j<m;j++){
            fscanf(rptr,"%c ",&c);
            fscanf(rptr,"%d %d\n",&n1,&n2);
            if(c=='M'){
                printf("%c %d %d\n",c,n1,n2);
                //modify(n1,n2,1,n,root);
            }
            else if(c=='P'){
                printf("%c %d %d\n",c,n1,n2);
                //imfor ans=find(n1,n2,1,n,root);
                //printf("max %d\n",ans.max);
            }
        }

    }
}
