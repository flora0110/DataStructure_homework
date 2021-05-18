//git 修改1
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
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
typedef struct{
    short int row;
    short int col;
    short int dir;//記錄他跑的方向
} element;

element stack[MAX_STACK_SIZE];
int top = -1;
void stackFull(){
    fprintf(stderr, "堆疊已滿，不能再加入元素");
    exit(EXIT_FAILURE);
}
void push(element item){
    if(top >=MAX_STACK_SIZE-1){
        stackFull();
    }
    stack [++top] = item;
}
element pop(){
    if(top==-1){
        fprintf(stderr, "堆疊已空");
    }
    return stack[top--];
}
element stack2[MAX_STACK_SIZE];
int top2 = -1;
void push2(element item){
    if(top2 >=MAX_STACK_SIZE-1){
    }//
    stack2 [++top2] = item;
}
element pop2(){
    /*if(top2==-1){
        return
    }*/
    return stack2[top2--];
}
element queue[MAX_STACK_SIZE];
int rear = -1;
int front = -1;
void queueFull(){
    fprintf(stderr, "佇列已滿，不能再加入元素");
    exit(EXIT_FAILURE);
}
void addq(element item){
    if(rear==MAX_STACK_SIZE-1){
        queueFull();
    }
    queue[++rear] = item;
}
element deleteq(){
    if(front==rear){
        fprintf(stderr, "佇列已空");
    }
    return queue[++front];
}
//四個方向----------
typedef struct{
    short int vert;
    short int horiz;
}offsets;
offsets move[4];
//---------------------

int min=100000;
//找到終點道起點的最短距離min 及用回傳值確定是否可到
int bfs(char** maze,int **d,int num,int sx,int sy){
    int arrive=0;//檢查有沒有到終點 之後要return

    queue[0].row = sx; queue[0].col = sy;
    rear++;
    //將起點放進queue
    int i,j;
    for(i=0;i<num+2;i++){
        for(j=0;j<num+2;j++){
            d[i][j]=MAX;
        }
    }
    d[sx][sy]=0;
    //初始化所有格子道起點的距離為MAX,起點道起點距離為0

    element position;
    int nr,nc;//移動後位置
    int row,col;//現在位置
    while (rear!=front){
        position = deleteq();
        row = position.row;
        col = position.col;
        //把現在位置(已知距離)拿出來
        if(maze[row][col]=='F'){//如果現在在終點
            if(min>d[row][col]){
                min=d[row][col];//記錄下min
            }
            arrive=1;
        }
        //跑方向-----------------------------------------------
        for(i=0;i<4;i++){
            nr = position.row+move[i].vert;
            nc = position.col+move[i].horiz;
            //下一個位置
            if (maze[nr][nc]!='X' && d[nr][nc]>d[row][col]+1){//可以走且沒走過
                d[nr][nc]=d[row][col]+1;;//下個位置的距離是現在位置距離+1
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;
                addq(nextposition);//把下個位置加進去queue
            }
        }
        //-----------------------------------------------
    }
    return arrive;
}
//劃出路徑
void path(int **d,char **maze,char** road,char** mark,int fx,int fy,int num){
    element position;
    int i,j,k;
    stack[0].row = fx; stack[0].col = fy;stack[0].dir=0;
    top = 0;
    int nr,nc;//移動後位置
    int row,col;//現在位置
    //把現在位置放入stack
    int found=1;//檢查是否走到死路 要先設1讓第一步可以跑
    while(top>-1){//如果stack裡還有東西就可以繼續pop出來走
        position = pop();
        push2(position);//走的位置先放入stack2 走道死路時才知道要怎麼走回去(消除路徑)
        row = position.row;
        col = position.col;
        mark[row][col]='X';//1.不能繞回去 2.如果被倒車過(消除路徑)那再走一次也還是會到死路
        road[row][col]='*';

        //遇到死路的倒車方法
        if(!found){
            element remind=pop2();//新的路的開頭要先記下來 倒完車要push2回去stack2
            while(top2>-1){
                element lastposition = pop2();//上一個位置
                int lr=lastposition.row;int lc=lastposition.col;int ld=lastposition.dir;
                //檢查是否已經倒到新的路開頭的上一步
                int k=0;
                for(i=3;i>=0;i--){//從上一的方向開始找(因為是stack)
                    if((row == lr+move[i].vert &&col == lc+move[i].horiz)&&(d[lr][lc]==d[row][col]-1)){
                            k=1;
                    }
                    //如果1.上一個位置可以跑到新的開頭 且 2.上一個位置的距離核心的開頭的距離差是正常的(1)
                }
                if(k){
                    push2(lastposition);//是新的路開頭的上一步就不用消 加回stack2
                    push2(remind);//新的路開頭 加回stack2
                    break;
                }

                road[lastposition.row][lastposition.col]='O';//倒車消除路
            }
        }

        if(maze[row][col]=='S'){//到起點
            break;
        }
        //跑方向----------------------------------------------------
        found=0;//先設0 如果有下一步就會變成1 否則倒車
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            if (d[nr][nc] == d[row][col]-1){
                //現在位置和下一距離差1(3 如過下一格是T)
                found=1;
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.dir=i;
                push(nextposition);
            }
        }
        //-------------------------------------------------------
    }
}

int main(){

    move[0].vert=-1;
    move[0].horiz=0;
    move[1].vert=0;
    move[1].horiz=1;
    move[2].vert=1;
    move[2].horiz=0;
    move[3].vert=0;
    move[3].horiz=-1;
    //定義跑的方向
    int num,i,j,startx,starty,finalx,finaly;
    FILE *rptr;
    rptr = fopen("test.txt","r");
    if(NULL==rptr){
        printf("Open failure");
        return 1;
    }
    else{
        fscanf(rptr,"%d\n",&num);
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
                        startx=i;
                        starty=j;
                    }
                    if(maze[i][j]=='F'){
                        finalx=i;
                        finaly=j;
                    }
                }
                road[i][j]=maze[i][j];
                mark[i][j]=maze[i][j];//road mark 複製一下
            }
        }
        if(bfs(maze,d,num,startx,starty)){//如果有路到終點
            path(d,maze,road,mark,finalx,finaly,num);
            for(i=1;i<num+2-1;i++){
                for(j=1;j<num+2-1;j++){
                    printf("%c ",road[i][j]);
                }
                printf("\n");
            }
            printf("最短路徑為%d\n",min);
        }
        else printf("The maze does not have a path\n" );
        free(maze);
        free(mark);
        free(road);
        free(d);
    }
    fclose(rptr);
}
