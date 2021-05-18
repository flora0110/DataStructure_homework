#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 14
#define MAX_STACK_SIZE 100
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

int min=MAX;
//找到終點道起點的最短距離min 及用回傳值確定是否可到
int bfs(char*** maze,int*** d,int sr,int sc,int sh,int n){
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
        position = deleteq();
        row = position.row;
        col = position.col;
        hei = position.hei;
        //把現在位置(已知距離)拿出來

        if(maze[hei][row][col]=='F'){//如果現在在終點
            min = d[hei][row][col];
            //記錄下min
            arrive=1;
            //檢查有沒有到終點 之後要return
            break;
        }

        //跑方向-------------------------------------------------------
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='D'){
            int upanddown=-1;
            if(maze[hei][row][col]=='U'){
                upanddown=1;
            }
            //決定是上是下

            nr = row;
            nc = col;
            nh = hei+upanddown;
            //下一個位置是哪

            if(nh>=0){
                if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]==MAX){//可以走且沒走過
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

            if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]==MAX){
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
void path(char*** maze,char*** road,char*** mark,int*** d,int sr,int sc,int sh,int n){
    element position;
    position.row = sr;//j
    position.col = sc;//k
    position.hei = sh;//i
    position.dir = 0 ;
    push(position);
    //把現在位置放入stack

    int i,j,k;
    int nr,nc,nh;//移動後位置
    int row,col,hei;//現在位置
    int found=1;//檢查是否走到死路 要先設1讓第一步可以跑

    while(top>-1){//如果stack裡還有東西就可以繼續pop出來走
        position = pop();
        push2(position);
        //走的位置先放入stack2 走道死路時才知道要怎麼走回去(消除路徑)
        row = position.row;
        col = position.col;
        hei = position.hei;
        road[hei][row][col]='*';
        mark[hei][row][col]='X';//1.不能繞回去 2.如果被倒車過(消除路徑)那再走一次也還是會到死路

        //遇到死路的倒車方法
        if(!found){
            element remind=pop2();//新的路的開頭要先記下來 倒完車要push2回去stack2
            while(top2>-1){
                element lastposition = pop2();//上一個位置
                int lr=lastposition.row;int lc=lastposition.col;int lh=lastposition.hei;int ld=lastposition.dir;

                //檢查是否已經倒到新的路開頭的上一步
                int k=0;
                for(i=ld-1;i>=0;i--){//從上一的方向開始找(因為是stack)
                    if((row == lr+move[i].vert &&col == lc+move[i].horiz&&hei == lh+move[i].hei)&&(d[lh][lr][lc]==d[hei][row][col]-1|| (d[lh][lr][lc]==d[hei][row][col]-3 && d[hei][row][col]=='T'))){
                            k=1;
                    }
                    //如果1.上一個位置可以跑到新的開頭 且 2.上一個位置的距離核心的開頭的距離差是正常的(1,T3)
                }
                if(k){
                    push2(lastposition);//是新的路開頭的上一步就不用消 加回stack2
                    push2(remind);//新的路開頭 加回stack2
                    break;
                }

                road[lastposition.hei][lastposition.row][lastposition.col]='O';//倒車消除路
            }
        }

        if(maze[hei][row][col]=='F'){//到終點
            break;
        }

        //跑方向-------------------------------------------------------------
        found=0;//先設0 如果有下一步就會變成1 否則倒車
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if (mark[nh][nr][nc]!='X' &&(d[nh][nr][nc]==d[hei][row][col]+1|| (d[nh][nr][nc]==d[hei][row][col]+3 &&markd[nh][nr][nc]=='T'))){
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
            if (mark[nh][nr][nc]!='X' && (d[nh][nr][nc]==d[hei][row][col]+1|| (d[nh][nr][nc]==d[hei][row][col]+3 && mark[nh][nr][nc]=='T'))){
                found=1;
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                if(upanddown==1) nextposition.dir=4;
                else nextposition.dir=5;
                push(nextposition);
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
    int n=0;//底層邊長
    char y;//抓第一航輸入的換行字元
    int i,j,k;

    //輸入的第一行先存在一一維陣列
    char* bottom = make1darr(MAXLEN);
    do{
        scanf("%c",&bottom[n++]);
    }while(y=getchar()!='\n');//如果抓到的不是換行字元 吃掉空格

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
                    scanf("%c",&maze[i][j][k]);//len+1~n-len*len+1~n-len都是要輸入的地圖
                    getchar();//把空格和換行吃掉
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
        if(i!=n/2){//但是最後一層不用吃喔
            getchar();//每層地圖之間有個空行 要吃掉換行符號
        }
        len++;//邊邊寬度+1
    }

    if(bfs(maze,d,sr,sc,sh,n)){//如果有路到終點
        path(maze,road,mark,d,sr,sc,sh,n);
        printf("path length: %d\n\n",min);
        printf("====outMaze====\n");
        for(i=0;i<n/2+1;i++){
            for(j=i+1;j<n+2-i-1;j++){
                for(k=i+1;k<n+2-i-1;k++){
                    printf("%c ",road[i][j][k] );
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("D\n");
        for(i=0;i<n/2+1;i++){
            for(j=0;j<n+2;j++){
                for(k=0;k<n+2;k++){
                    printf("%5d ",d[i][j][k] );
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    else printf("The maze does not have a path\n" );
    free(bottom);
    free(maze);
    free(mark);
    free(road);
    free(d);
}
