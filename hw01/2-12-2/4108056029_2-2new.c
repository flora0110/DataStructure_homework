//58failed
#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 14
#define MAX_STACK_SIZE 1000
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

int min;
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
            min = d[hei][row][col];
            //記錄下min
            arrive=1;
        }
        //跑方向-------------------------------------------------------
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='D'){
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
int pathnum=0;

void dfs(char*** maze,char*** mark,char*** road,int row,int col,int hei,int count){

    int i,j,k;

    if(count>=(min+5)){//如果跑的距離大於min+5
        return;
    }
    else{
        int i;
        int nh,nr,nc;
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if(mark[nh][nr][nc]!='X'){//這次沒跑過且可跑
                mark[nh][nr][nc]='X';//記錄跑過的路
                road[nh][nr][nc]='*';
                if(maze[nh][nr][nc]=='T'){
                    dfs(maze,mark,road,nr,nc,nh,count+3);
                }

                else{
                    dfs(maze,mark,road,nr,nc,nh,count+1);
                }
                mark[nh][nr][nc]=maze[nh][nr][nc];
                road[nh][nr][nc]=maze[nh][nr][nc];

            }
        }
        if(maze[hei][row][col]=='U'){
            if(mark[hei+1][row][col]!='X'){
                mark[hei+1][row][col]='X';
                road[hei+1][row][col]='*';
                if(maze[hei+1][row][col]=='T'){

                    dfs(maze,mark,road,row,col,hei+1,count+3);

                }
                else if(maze[hei+1][row][col]=='F'){
                    pathnum++;
                }
                else{
                    dfs(maze,mark,road,row,col,hei+1,count+1);
                }
                mark[hei+1][row][col]=maze[hei+1][row][col];
                road[hei+1][row][col]=maze[hei+1][row][col];
            }



        }
        else if(maze[hei][row][col]=='D' && hei>0){
            if(mark[hei-1][row][col]!='X'){

                mark[hei-1][row][col]='X';
                road[hei-1][row][col]='*';
                if(mark[hei-1][row][col]='T'){
                    dfs(maze,mark,road,row,col,hei-1,count+3);
                }
                else{

                    dfs(maze,mark,road,row,col,hei-1,count+1);
                }
                mark[hei-1][row][col]=maze[hei-1][row][col];
                road[hei-1][row][col]=maze[hei-1][row][col];
            }
        }

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
    FILE *wfile;
    wfile = fopen( "4108056029output.txt","w" );
    if( NULL == wfile ){
        printf( "wfile open failure" );
        return 1;
    }
    else{
        for(control=58;control<=58;control++){//for
            min = 100000;//每次記得初始化
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
                }//for
                fprintf(wfile, "test %d starts now.\n",control );
                if(bfs(maze,d,sr,sc,sh)){//如果有路到終點
                    mark[sh][sr][sc]='X';
                    pathnum=0;
                    dfs(maze,mark,road,sr,sc,sh,0);
                    printf("Sortest path : %d, Limit: %d, The number of different paths: %d\n\n",min,min+5,pathnum);
                    fprintf(wfile,"Shortest path: %d, Limit: %d, The number of different paths: %d\n\n",min,min+5,pathnum);
                }
                else fprintf(wfile,"The maze does not have a path\n" );
                free(bottom);
                free(maze);
                free(mark);
                free(road);
                free(d);
            }//else----------------------------------------------------------------------
            fclose(pfile);

        }//跑1-100的for
    }//wfile的else
    fclose(wfile);
}
