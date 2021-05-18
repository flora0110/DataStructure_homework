#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100000
#define MAX 401
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
char** arr(int rows, int cols){
    char **x;
    MALLOC(x,rows*sizeof(*x));
    int i;
    for(i=0;i<rows;i++){
        MALLOC(x[i],cols*sizeof(**x));
    }
    return x;
}
int** arrc(int rows, int cols){
    int **x;
    MALLOC(x,rows*sizeof(*x));
    int i;
    for(i=0;i<rows;i++){
        MALLOC(x[i],cols*sizeof(**x));
    }
    return x;
}
typedef struct Node* nodepointer;
typedef struct Node{
    int r;
    int c;
    int g;
    int h;
    nodepointer link;
    nodepointer parent;
}node;
nodepointer openfirst=NULL;
nodepointer openlast=NULL;
nodepointer closefirst=NULL;
nodepointer closelast=NULL;
void astar(char** maze,int sr,int sc,int fr,int fc){
    nodepointer start=(nodepointer)malloc(sizeof(node));
    start->r=sr;
    start->c=sc;
    start->g=0;
    int disr=fr-start->r,disc=fc-start->c;
    if(disr<0){
        disr=-disr;
    }
    if(disc<0){
        disc=-disc;
    }
    start->h=disr+disc;
    start->link=NULL;
    //起點弄好

    openfirst=start;//add the start node to Open
    openlast=start;

    while(1){
        node current=lowest(openfirst);


    }
    int row=sr,col=sc;
    while(maze[row][col]!='F'){
        node current = lowest(openfirst);

    }

}
nodepointer DeleteLowestInOpen(){
    int min=MAX;
    nodepointer temp,lastemp,x;
    x=openfirst;
    while(x!=NULL){
        if(((x->g) + (x->h)) <min){
            min=x->g+x->h;
            lastemp=temp;
            temp=x;
        }
        x=x->link;
    }
    if(openlast){
        lastemp->link=temp->link;
    }
    else{
        openfirst=openfirst->link;
    }
    retirn temp;
}
void AddToClose(nodepointer* y){
    if(closefirst){
        *y->link=closelast->link;
        closelast->link=*y;
    }
    else{
        *y->link=NULL;
        closefirst=*y;
    }

}
int main(){
    int i,j,k,sr,sc,fr,fc,num;
    FILE *rptr;
    rptr = fopen("test.txt","r");
    if(NULL==rptr){
        printf("Open failure");
        return 1;
    }
    else{
        fscanf(rptr,"%d\n",&num);
        printf("%d\n",num );
        char** maze = arr(num+2,num+2);//地圖
        char** mark = arr(num+2,num+2);//走過
        char** road = arr(num+2,num+2);//要印的路徑
        int** d = arrc(num+2,num+2);//距離
        for(i=0;i<num+2;i++){//弄一個大邊邊所以+2
            for(j=0;j<num+2;j++){
                if(i==0 || j==0 || i==num+1 || j==num+1){
                    //圍起每層地圖的大邊邊
                    maze[i][j]='X';
                }
                else{
                    fscanf(rptr,"%c ",&maze[i][j]);
                    if(maze[i][j]=='S'){
                        sr=i;
                        sc=j;
                    }
                    if(maze[i][j]=='F'){
                        fr=i;
                        fc=j;
                    }
                }
                road[i][j]=maze[i][j];
                mark[i][j]=maze[i][j];//road mark 複製一下
            }
        }

        free(maze);
        free(mark);
        free(road);
        free(d);
    }
    fclose(rptr);
}
