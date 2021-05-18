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

int pathnum=0;
int min=100000;
int step=0;
void path(char*** maze,char*** mark,char*** road,int sr,int sc,int sh,int n,int pnum){
    step=0;
    min=100000;
    pathnum=0;
    top=-1;
    int i,j,k;
    /*//------------------test------------------
    printf("maze!! \n");
    for(i=0;i<n/2+1;i++){
        for(j=i+1;j<n+2-i-1;j++){
            for(k=i+1;k<n+2-i-1;k++){
                printf("%c ",maze[i][j][k] );
            }
            printf("\n");
        }
        printf("\n");
    }
    //-----------------------------------------*/
    element position;
    int row,col,hei,dir;
    int nr,nc,nh;
    int countp=0;
    int found=1;
    int inproad=0;
    position.row = sr;//j
    position.col = sc;//k
    position.hei = sh;//i
    push(position);
    while(top>-1){
        //printf("----------------------------------------------------\n",maze[0][3][1] );
        position=pop();
        row = position.row;
        col = position.col;
        hei = position.hei;
        dir = position.dir;


        if(!found){
            //printf("dead road\n" );
            while(top2>-1){
                element lastposition = pop2();//上一個位置
                int lr=lastposition.row;int lc=lastposition.col;int lh=lastposition.hei;int ld=lastposition.dir;
                //printf("last %d %d %d is %c\n",lh,lr,lc,maze[lh][lr][lc] );
                //檢查是否已經倒到新的路開頭的上一步
                if(lr+move[dir].vert==row && lc+move[dir].horiz==col && lh+move[dir].hei==hei ){

                    push2(lastposition);//是新的路開頭的上一步就不用消 加回stack2
                    break;
                }
                road[lh][lr][lc]=maze[lh][lr][lc];//倒車消除路
                mark[lh][lr][lc]=maze[lh][lr][lc];
                if(maze[lh][lr][lc]=='T'){
                    step=step-3;
                }
                else step--;
                if(maze[lh][lr][lc]=='P'){
                    countp--;
                }
                /*//------------------test------------------
                road[lh][lr][lc]='&';
                printf("reroad!! \n");
                for(i=0;i<n/2+1;i++){
                    for(j=i+1;j<n+2-i-1;j++){
                        for(k=i+1;k<n+2-i-1;k++){
                            printf("%c ",road[i][j][k] );
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
                road[lh][lr][lc]=maze[lh][lr][lc];
                printf("countp %d\n\n",countp );
                printf("remark!! \n");
                for(i=0;i<n/2+1;i++){
                    for(j=i+1;j<n+2-i-1;j++){
                        for(k=i+1;k<n+2-i-1;k++){
                            printf("%c ",mark[i][j][k] );
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
                printf("countp %d\n\n",countp );
                printf("step %d\n\n",step );
                //-----------------------------------------*/
            }
        }
        mark[hei][row][col]='X';
        road[hei][row][col]='*';
        if(maze[hei][row][col]=='T'){
            step=step+3;
        }
        else step++;
        if(maze[hei][row][col]=='P'){
            inproad=1;
            countp++;
        }
        if(countp==pnum){
            inproad=0;
        }
        push2(position);

        printf("now %d %d %d\n",hei,row,col );
        //------------------test------------------
        road[hei][row][col]='@';
        printf("road!! \n");
        for(i=0;i<n/2+1;i++){
            for(j=i+1;j<n+2-i-1;j++){
                for(k=i+1;k<n+2-i-1;k++){
                    printf("%c ",road[i][j][k] );
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("countp %d\n\n",countp );
        printf("mark!! \n");
        for(i=0;i<n/2+1;i++){
            for(j=i+1;j<n+2-i-1;j++){
                for(k=i+1;k<n+2-i-1;k++){
                    printf("%c ",mark[i][j][k] );
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("countp %d\n\n",countp );
        printf("step %d\n\n",step );
        road[hei][row][col]='*';
        //-----------------------------------------*/
        if(maze[hei][row][col]=='F' && countp==pnum){
            pathnum++;
            if(min>step){
                min=step;

            }
            printf("finally------------------------------------------------\n" );
            //------------------test------------------
            printf("road!! \n");
            for(i=0;i<n/2+1;i++){
                for(j=i+1;j<n+2-i-1;j++){
                    for(k=i+1;k<n+2-i-1;k++){
                        printf("%c ",road[i][j][k] );
                    }
                    printf("\n");
                }
                printf("\n");
            }
            printf("countp %d pnum %d\n",countp,pnum );
            printf("step %d\n\n",step );
            printf("pathnum %d\n",pathnum );
            //--------------------------------------------------

            //
        }
        //run----------------------------------------------
        found=0;
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if(inproad){
                if(mark[nh][nr][nc]!='X' && maze[nh][nr][nc]=='P'){
                    found=1;
                    //printf("push %d %d %d\n",nh,nr,nc );

                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;nextposition.dir=i;
                    push(nextposition);
                }
            }
            else{
                if(mark[nh][nr][nc]!='X'){
                    found=1;
                    //printf("push %d %d %d\n",nh,nr,nc );

                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;nextposition.dir=i;
                    push(nextposition);
                }
            }

        }
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='P'){
            if(inproad){
                if(mark[nh][nr][nc]!='X' && maze[hei+1][row][col]=='P'){
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei+1;nextposition.dir=4;
                    push(nextposition);
                }
            }
            else{
                if(mark[hei+1][row][col]!='X'){
                    //printf("push %d %d %d\n",hei+1,row,col );
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei+1;nextposition.dir=4;
                    push(nextposition);
                }
            }




        }
        if((maze[hei][row][col]=='D'  || maze[hei][row][col]=='P')&& hei>0){
            if(inproad){
                if(mark[nh][nr][nc]!='X' && maze[hei-1][row][col]=='P'){
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei-1;nextposition.dir=5;
                    push(nextposition);
                }
            }
            else{
                if(mark[hei-1][row][col]!='X'){
                    //printf("push %d %d %d\n",hei+1,row,col );
                    found=1;
                    element nextposition;
                    nextposition.row=row;nextposition.col=col;nextposition.hei=hei-1;nextposition.dir=5;
                    push(nextposition);
                }
            }
        }
    }

}


/*

int bfs(char*** maze,int*** d,int sr,int sc,int sh,int n,int pnum){
    printf("rear : %d\n",rear );
    rear=-1;front=-1;
    int countp;
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
        //------------------test------------------
        printf("d!! \n");
        for(i=0;i<n/2+1;i++){
            for(j=i+1;j<n+2-i-1;j++){
                for(k=i+1;k<n+2-i-1;k++){
                    printf("%5d ",d[i][j][k] );
                }
                printf("\n");
            }
            printf("\n");
        }
        //-----------------------------------------
        position = deleteq();
        row = position.row;
        col = position.col;
        hei = position.hei;
        //把現在位置(已知距離)拿出來
        //----------------test--------------------
        if(maze[hei][row][col]=='F' && countp!=pnum){//如果現在在終點
            printf("p is not enough\n");
        }
        //---------------------------------------
        if(maze[hei][row][col]=='F' && countp==pnum){//如果現在在終點
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
                if (maze[nh][nr][nc]!='X' && (d[nh][nr][nc]>d[hei][row][col]+1 || maze[nh][nr][nc]=='P')){//可以走且沒走過/找到更短的路
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
        else if(maze[hei][row][col]=='P'){
            countp++;
            for(i=-1;i<=1;i=i+2){
                nr = row;
                nc = col;
                nh = hei+i;
                //下一個位置是哪
                if(nh>=0){
                    if (maze[nh][nr][nc]!='X' && (d[nh][nr][nc]>d[hei][row][col]+1 || maze[nh][nr][nc]=='P')){//可以走且沒走過/找到更短的路
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
        }
        //ODU都可以跑四方
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;

            if (maze[nh][nr][nc]!='X' && (d[nh][nr][nc]>d[hei][row][col]+1 || maze[nh][nr][nc]=='P')){
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
*/
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

    FILE *pfile;
    char name[50];
    int control;
    for(control=2;control<=2;control++){//for
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
            int n=0;
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
            int pnum=0;
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
                        if(maze[i][j][k]=='P'){
                            pnum++;
                        }
                        road[i][j][k]=maze[i][j][k];
                        mark[i][j][k]=maze[i][j][k];//road mark 複製一下
                    }
                }
                len++;//邊邊寬度+1
            }//for
            /*
            printf("PNUM %d\n",pnum );
            //------------------test------------------
            printf("maze!! \n");
            for(i=0;i<n/2+1;i++){
                for(j=i+1;j<n+2-i-1;j++){
                    for(k=i+1;k<n+2-i-1;k++){
                        printf("%c ",maze[i][j][k] );
                    }
                    printf("\n");
                }
                printf("\n");
            }
            //-----------------------------------------*/
            FILE *wfile;
            wfile = fopen( "4108056029output.txt","a" );
            if( NULL == wfile ){
                printf( "wfile open failure" );
                return 1;
            }
            else{
                fprintf(wfile, "test%d Starts now.\n",control );

                /*if(bfs(maze,d,sr,sc,sh,n,pnum)){//如果有路到終點

                    //------------------test------------------
                    printf("d!! \n");
                    for(i=0;i<n/2+1;i++){
                        for(j=i+1;j<n+2-i-1;j++){
                            for(k=i+1;k<n+2-i-1;k++){
                                printf("%5d ",d[i][j][k] );
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }
                    printf("min %d\n",min );
                    //-----------------------------------------
*/
                if(1){
                    //printf("min %d\n",min );
                    mark[sh][sr][sc]='X';
                    pathnum=0;
                    path(maze,mark,road,sr,sc,sh,n,pnum);
                    printf("Shortest path: %d, The number of different paths: %d\n\n",min-1,pathnum);
                    fprintf(wfile,"Shortest path: %d, The number of different paths: %d\n\n",min-1,pathnum);
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
