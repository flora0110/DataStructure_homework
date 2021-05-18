#include<stdio.h>
#include<stdlib.h>
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
node* build(int l,int r,int* arr){
    node* ptr=(node*)malloc(sizeof(node));
    if(r==l){
        ptr->sum=arr[l];
        ptr->ls=arr[l];
        ptr->rs=arr[l];
        ptr->max=arr[l];
        return ptr;
    }
    else{
        int m=(l+r)/2;
        node* leftn=build(l,m,arr);
        node* rightn=build(m+1,r,arr);
        ptr->sum=leftn->sum+rightn->sum;
        ptr->ls=max(leftn->ls,leftn->sum+rightn->ls);
        ptr->rs=max(rightn->rs,rightn->sum+leftn->rs);
        ptr->max=max(max(rightn->max,leftn->max),leftn->rs+rightn->ls);
        ptr->left=leftn;
        ptr->right=rightn;
        return ptr;
    }
}
typedef struct imfor{
    int sum;
    int ls;
    int rs;
    int max;
}imfor;
imfor findinq1(int a,int b,int l,int r,node* ptr){
    imfor im;//存a到b的imfor
    if(a>b){
        im.ls=0;
        im.rs=0;
        im.max=0;
        im.sum=0;
        return im;
    }
    if(a==l && b==r){//符合就直接帶
        im.sum=ptr->sum;
        im.ls=ptr->ls;
        im.rs=ptr->rs;
        im.max=ptr->max;
        return im;
    }
    int m=(l+r)/2;
    if(b<=m){//都在左邊
        im = findinq1(a,b,l,m,ptr->left);
        return im;
    }
    if(a>m){//都在右邊
        im = findinq1(a,b,m+1,r,ptr->right);
        return im;
    }
    else{
        imfor leftim=findinq1(a,m,l,m,ptr->left);
        imfor rightim=findinq1(m+1,b,m+1,r,ptr->right);
        im.sum=leftim.sum+rightim.sum;
        im.ls=max(leftim.ls,leftim.sum+rightim.ls);
        im.rs=max(rightim.rs,rightim.sum+leftim.rs);
        im.max=max(max(rightim.max,leftim.max),leftim.rs+rightim.ls);
        return im;
    }
}
int find(int x1,int y1,int x2,int y2,int* arr,int n,node* root) {
    int i;
    int Max;
    if(y1>x2){//有交錯 
        imfor left,right,middle,leftedge,rightedge;
        left=findinq1(x1,x2-1,1,n,root);
        middle=findinq1(x2,y1,1,n,root);
        right=findinq1(y1+1,y2,1,n,root);
        leftedge=findinq1(x1,x2,1,n,root);//區間一(left)含右邊邊 
        rightedge=findinq1(y1,y2,1,n,root);
        Max=max(max(left.rs+middle.ls,middle.rs+right.ls),middle.max);
        Max=max(max(Max,left.rs+middle.sum+right.ls),max(leftedge.rs,rightedge.ls));
        return Max;
    }
    int max=arr[y1];
    int sum=arr[y1];
    for(i=y1-1;i>=x1;i--){
        if(arr[i]+sum>max){
            max=arr[i]+sum;
        }
        sum+=arr[i];
    }
    for(i=y1+1;i<=x2;i++){//y1~x2
        max+=arr[i];
    }
    sum=max;
    for(i=x2+1;i<=y2;i++){
        if(arr[i]+sum>max){
            max=arr[i]+sum;
        }
        sum+=arr[i];
    }
    return max;
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test.txt","r");//test----------------------test.txt
    wptr=fopen("output.txt","w");
    if(rptr==NULL ||wptr==NULL){
        printf("open error\n");
        return 0;
    }
    int i,j,k,q;
    int t,n,m;
    fscanf(rptr,"%d\n",&t);
    printf("t: %d\n",t);
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
        node* root;
        root=build(1,n,arr);
        fscanf(rptr,"%d\n",&m);
        printf("m: %d\n",m);
        int x1,x2,y1,y2,max;
        for(j=0;j<m;j++){
            fscanf(rptr,"%d %d %d %d\n",&x1,&y1,&x2,&y2);
            max=find(x1,y1,x2,y2,arr,n,root);
            fprintf(wptr,"%d\n",max);
        }
    }
    free(arr);
    fclose(wptr);
    fclose(rptr);
}
