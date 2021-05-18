#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 14
#define MAX_STACK_SIZE 100000
#define MAX 455
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
char* make1darr(int n){
    char *x;
    MALLOC(x,n*sizeof(*x));
    return x;
}
char*** make3darr(int rows, int cols,int hei){
    char ***x;
    MALLOC(x,rows*sizeof(**x));
    int i,j;
    for(i=0;i<rows;i++){
        MALLOC(x[i],cols*sizeof(**x));
        for(j=0;j<hei;j++){
            MALLOC(x[i][j],hei*sizeof(***x));
        }
    }
    return x;
}

int*** make3darrint(int rows, int cols,int hei){
    int ***x;
    MALLOC(x,rows*sizeof(**x));
    int i,j;
    for(i=0;i<rows;i++){
        MALLOC(x[i],cols*sizeof(**x));
        for(j=0;j<hei;j++){
            MALLOC(x[i][j],hei*sizeof(***x));
        }
    }
    return x;
}
typedef struct{
    short int row;
    short int col;
    short int hei;
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
//六個方向----------
typedef struct{
    short int vert;
    short int horiz;
    short int hei;
}offsets;
offsets move[6];
//------------------

int min=10000;
int n;
//找到終點道起點的最短距離min 及用回傳值確定是否可到
int bfs(char*** maze,int*** d,int sr,int sc,int sh){
    rear=-1;front=-1;

    int arrive=0;//檢查有沒有到終點 之後要return
    element position;
    position.row = sr;//j
    position.col = sc;//k
    position.hei = sh;//i
    //紀錄起始位置

    addq(position);//將起點放進queue
    int i,j,k;
    for(i=0;i<n/2+1;i++){
        for(j=0;j<n+2;j++){
            for(k=0;k<n+2;k++){
                d[i][j][k]=MAX;
            }
        }
    }
    d[sh][sr][sc]=0;
    //初始化所有格子道起點的距離為MAX,起點道起點距離為0

    int nr,nc,nh;//移動後位置
    int row,col,hei;//現在位置
    while(rear!=front){
        //printf("rear: %d front: %d\n",rear,front );
        position = deleteq();
        row = position.row;
        col = position.col;
        hei = position.hei;
        //把現在位置(已知距離)拿出來

        if(maze[hei][row][col]=='F'){//如果現在在終點
            //檢查有沒有到終點 之後要return
            if(min>d[hei][row][col]){
                min = d[hei][row][col];///記錄下min
            }
            //記錄下min
            arrive=1;
        }
        //跑方向-------------------------------------------------------
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='D'){
            //printf("meet D U\n");
            //printf("%c\n",maze[hei][row][col] );
            int upanddown=-1;
            if(maze[hei][row][col]=='U'){
                //printf("meet U\n");
                upanddown=1;
            }
            //決定是上是下

            nr = row;
            nc = col;
            nh = hei+upanddown;
            //下一個位置是哪
            //printf("%d %d %d\n",nh,nr,nc);
            if(nh>=0){
                if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]>d[hei][row][col]+1){//可以走且沒走過/找到更短的路
                    d[nh][nr][nc]=d[hei][row][col]+1;//下個位置的距離是現在位置距離+1
                    if(maze[nh][nr][nc]=='T'){//遇到陷阱是+3
                        d[nh][nr][nc]=d[nh][nr][nc]+2;
                    }
                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                    addq(nextposition);//把下個位置加進去queue
                }
            }

        }
        //ODU都可以跑四方
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;

            if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]>d[hei][row][col]+1){
                d[nh][nr][nc]=d[hei][row][col]+1;
                if(maze[nh][nr][nc]=='T'){
                    d[nh][nr][nc]=d[nh][nr][nc]+2;
                }
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                addq(nextposition);
            }

        }
        //------------------------------------------------------------------------

    }
    return arrive;
}
//劃出路徑
void path(char*** maze,char*** road,char*** mark,int*** d,int sr,int sc,int sh){
    top=-1;
    top2=-1;
    element position;
    position.row = sr;//j
    position.col = sc;//k
    position.hei = sh;//i
    position.dir = 0 ;
    push(position);
    //把現在位置放入stack

    int i,j,k;
    int nr,nc,nh;//移動後位置
    int row,col,hei,dir;//現在位置
    int found=1;//檢查是否走到死路 要先設1讓第一步可以跑

    while(top>-1){//如果stack裡還有東西就可以繼續pop出來走
        position = pop();

        //走的位置先放入stack2 走道死路時才知道要怎麼走回去(消除路徑)
        row = position.row;
        col = position.col;
        hei = position.hei;
        dir = position.dir;//現在位置是怎麼來的


        //遇到死路的倒車方法
        if(!found){
            /*road[hei][row][col]='#';
            printf("now %d %d %d %d\n",row,col,hei,dir );*/
            while(top2>-1){
                element lastposition = pop2();//上一個位置
                int lr=lastposition.row;int lc=lastposition.col;int lh=lastposition.hei;int ld=lastposition.dir;

                //檢查是否已經倒到新的路開頭的上一步

                if(lr+move[dir].vert==row && lc+move[dir].horiz==col && lh+move[dir].hei==hei ){
                    push2(lastposition);//是新的路開頭的上一步就不用消 加回stack2
                    break;
                }
                road[lh][lr][lc]=maze[lh][lr][lc];//倒車消除路
                mark[lh][lr][lc]=maze[lh][lr][lc];
            }
        }
        road[hei][row][col]='*';
        mark[hei][row][col]='X';//1.不能繞回去 2.如果被倒車過(消除路徑)那再走一次也還是會到死路
        push2(position);
        if(maze[hei][row][col]=='F'){//到終點
            break;
        }

        //跑方向-------------------------------------------------------------

        found=0;//先設0 如果有下一步就會變成1 否則倒車
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if ((mark[nh][nr][nc]!='X' && ((d[nh][nr][nc]==d[hei][row][col]+1)&& mark[nh][nr][nc]!='T') || (d[nh][nr][nc]==d[hei][row][col]+3 && mark[nh][nr][nc]=='T'))){
                //現在位置和下一距離差1(3 如過下一格是T)
                found=1;
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;nextposition.dir=i;
                push(nextposition);
            }
        }
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='D'){
            int upanddown=-1;
            if(maze[hei][row][col]=='U'){
                upanddown=1;
            }
            nr = row;
            nc = col;
            nh = hei+upanddown;
            if(nh>=0){
                if ((mark[nh][nr][nc]!='X' && ((d[nh][nr][nc]==d[hei][row][col]+1)&& mark[nh][nr][nc]!='T') || (d[nh][nr][nc]==d[hei][row][col]+3 && mark[nh][nr][nc]=='T'))){

                    found=1;
                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                    if(upanddown==1) nextposition.dir=4;
                    else nextposition.dir=5;
                    push(nextposition);
                }
            }


        }
        //--------------------------------------------------------------------------------------
    }
}

int main(){
    move[0].vert=-1;
    move[0].horiz=0;
    move[0].hei=0;
    move[1].vert=0;
    move[1].horiz=1;
    move[1].hei=0;
    move[2].vert=1;
    move[2].horiz=0;
    move[2].hei=0;
    move[3].vert=0;
    move[3].horiz=-1;
    move[3].hei=0;
    move[4].vert=0;
    move[4].horiz=0;
    move[4].hei=1;
    move[5].vert=0;
    move[5].horiz=0;
    move[5].hei=-1;
    //定義跑的方向
    char y;//抓第一航輸入的換行字元
    int i,j,k;

    FILE *pfile;
    char name[50];
    int control;
    for(control=1;control<=100;control++){//for
        min=100000;
        sprintf(name,"test%d.txt",control);
        pfile = fopen(name,"r");
        if(NULL==pfile){
            printf("Open failure");
            return 1;
        }
        else{//----------------------------------------------------------------------
            printf("reading %s\n",name);
            //輸入的第一行先存在一一維陣列
            char* bottom = make1darr(MAXLEN);
            n=0;//底層邊長//改全域
            char y;
            bottom[n]=fgetc(pfile);
            while(bottom[n]!='\n'){
                fgetc(pfile);
                bottom[++n]=fgetc(pfile);
                //printf("y: %c\n",y);
            }
            char ***maze=make3darr(n/2+1,n+2,n+2);//地圖
            char ***road=make3darr(n/2+1,n+2,n+2);//要印出的路徑
            char ***mark=make3darr(n/2+1,n+2,n+2);//跑過的打X
            int ***d=make3darrint(n/2+1,n+2,n+2);//距離
            int len=0;//因為要對其所有二微陣列疊成三維振烈 所以上面的陣列會有一邊邊的寬度len
            int sr,sc,sh;//起始位置
            for(i=0;i<n/2+1;i++){//高度是n/2+1
                for(j=0;j<n+2;j++){//弄一個大邊邊所以+2
                    for(k=0;k<n+2;k++){
                        if(j==0 || k==0 || j==n+1 || k==n+1){
                            maze[i][j][k]='X';//圍起每層地圖的大邊邊
                        }
                        else if(i==0 && j==1){//一樓第一列把bottom[]複製進去
                            maze[i][j][k]=bottom[k-1];//地圖有大邊邊所以是從1開始喔
                        }
                        else if(j > len && j <= n-len && k > len && k <= n-len){
                            fscanf(pfile,"%c ",&maze[i][j][k]);//len+1~n-len*len+1~n-len都是要輸入的地圖

                        }
                        else{
                            maze[i][j][k]='X';//寬度為len的邊邊
                        }
                        if(maze[i][j][k]=='S'){//起始位置
                            sh=i;
                            sr=j;
                            sc=k;
                        }
                        road[i][j][k]=maze[i][j][k];
                        mark[i][j][k]=maze[i][j][k];//road mark 複製一下
                    }
                }
                len++;//邊邊寬度+1
            }//for-------------------------------------------------
            FILE *wfile;
            sprintf(name,"4108056029test%d_ans.txt",control);
            wfile = fopen(name,"w");
            if( NULL == wfile ){
                printf( "wfile open failure" );
                return 1;
            }
            else{
                if(bfs(maze,d,sr,sc,sh)){//如果有路到終點
                    path(maze,road,mark,d,sr,sc,sh);
                    //dfs(maze,mark,road,d,sr,sc,sh,&found);
                    fprintf(wfile,"Path length: %d\n",min);
                    fprintf(wfile,"=====outMaze=====\n");
                    for(i=0;i<n/2+1;i++){
                        for(j=i+1;j<n+2-i-1;j++){
                            for(k=i+1;k<n+2-i-1;k++){
                                fprintf(wfile,"%c ",road[i][j][k] );
                            }
                            fprintf(wfile,"\n");
                        }
                        fprintf(wfile,"\n");
                    }
                }
                else fprintf(wfile,"The maze does not have a path\n" );
            }
            free(bottom);
            free(maze);
            free(mark);
            free(road);
            free(d);
        }//else----------------------------------------------------------------------
        fclose(pfile);

    }
}
