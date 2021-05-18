#include<stdio.h>
#include<stdlib.h>
typedef struct Treenode* nodepointer;
int max(int a,int b){
    if(a>b){
        return a;
    }
    else return b;
}
typedef struct Treenode{
    int sum;
    int lm;//左邊數來連續最大 
    int rm;
    int max;//區間內連續最大
    nodepointer left;
    nodepointer right;
}node;
node* build(int l,int r,int* arr){
    node* ptr=(node*)malloc(sizeof(node));
    if(r==l){
        ptr->sum=arr[l];
        ptr->lm=arr[l];
        ptr->rm=arr[l];
        ptr->max=arr[l];
        return ptr;
    }
    else{
        int m=(l+r)/2;
        node* leftn=build(l,m,arr);
        node* rightn=build(m+1,r,arr);
        ptr->sum=leftn->sum+rightn->sum;
        ptr->lm=max(leftn->lm,leftn->sum+rightn->lm);
        ptr->rm=max(rightn->rm,rightn->sum+leftn->rm);
        ptr->max=max(max(rightn->max,leftn->max),leftn->rm+rightn->lm);
        ptr->left=leftn;
        ptr->right=rightn;
        return ptr;
    }
}
void modify(int x,int value,int l,int r,node* ptr){
    if(l==r){
        ptr->sum=value;
        ptr->lm=value;
        ptr->rm=value;
        ptr->max=value;
        return;
    }
    int m=(r+l)/2;
    if(x<=m){
        modify(x,value,l,m,ptr->left);
    }
    else{
        modify(x,value,m+1,r,ptr->right);
    }
    ptr->sum=ptr->left->sum+ptr->right->sum;
    ptr->lm=max(ptr->left->lm,ptr->left->sum+ptr->right->lm);
    ptr->rm=max(ptr->right->rm,ptr->right->sum+ptr->left->rm);
    ptr->max=max(max(ptr->right->max,ptr->left->max),ptr->left->rm+ptr->right->lm);
    return;
}
typedef struct imfor{
    int sum;
    int lm;
    int rm;
    int max;
}imfor;
imfor find(int a,int b,int l,int r,node* ptr){
    imfor im;//存a到b的imfor
    if(a==l && b==r){//符合就直接帶
        im.sum=ptr->sum;
        im.lm=ptr->lm;
        im.rm=ptr->rm;
        im.max=ptr->max;
        return im;
    }
    int m=(l+r)/2;
    if(b<=m){//都在左邊
        im = find(a,b,l,m,ptr->left);
        return im;
    }
    if(a>m){//都在右邊
        im = find(a,b,m+1,r,ptr->right);
        return im;
    }
    else{
        imfor leftim=find(a,m,l,m,ptr->left);
        imfor rightim=find(m+1,b,m+1,r,ptr->right);
        im.sum=leftim.sum+rightim.sum;
        im.lm=max(leftim.lm,leftim.sum+rightim.lm);
        im.rm=max(rightim.rm,rightim.sum+leftim.rm);
        im.max=max(max(rightim.max,leftim.max),leftim.rm+rightim.lm);
        return im;
    }
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test.txt","r");//test---------------------------------------------test.txt
    wptr=fopen("output.txt","w");
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
        fscanf(rptr,"%d\n",&arr[n]);
        root=build(1,n,arr);
        fscanf(rptr,"%d\n",&m);
        printf("m: %d\n",m);
        char c;
        int n1,n2;
        for(j=0;j<m;j++){
            fscanf(rptr,"%c ",&c);
            fscanf(rptr,"%d %d\n",&n1,&n2);
            if(c=='M'){
                modify(n1,n2,1,n,root);
            }
            else if(c=='P'){
                imfor ans=find(n1,n2,1,n,root);
                fprintf(wptr,"%d\n",ans.max);
            }
        }

    }
    free(arr);
    fclose(wptr);
    fclose(rptr);
}
