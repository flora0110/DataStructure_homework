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


typedef struct queue *queuepointer;
typedef struct queue {
    element data;
    queuepointer link;
}queue;
queuepointer front;
queuepointer rear;

void addq(element item){
    printf("in addq\n");
    queuepointer temp;
    MALLOC(temp,sizeof(*temp));
    temp->data=item;
    temp->link=NULL;
    if(front!=NULL){
        printf("in addq if\n");
        rear->link=temp;
        printf("in addq if bottom\n");
    }
    else {
        printf("in addq else\n");
        front=temp;
    }
    printf("in addq bottom\n");
}
element deleteq(){
    queuepointer temp=front;
    element item;
    if(temp==NULL){
        fprintf(stderr, "佇列已空");
    }
    item = temp->data;
    front=temp->link;
    free(temp);
    return item;
}
/*
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
*/
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
    //rear=-1;front=-1;
    //printf("in\n");
    int arrive=0;//檢查有沒有到終點 之後要return
    element position;
    position.row = sr;//j
    position.col = sc;//k
    position.hei = sh;//i
    //紀錄起始位置

    addq(position);//將起點放進queue
    //printf("addq\n");
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
    //while(rear!=front){
    while(front!=NULL){
        //printf("while\n");
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
        //-----------------------------------------*/
        //printf("rear: %d front: %d\n",rear,front );
        position = deleteq();
        printf("deleteq\n");
        row = position.row;
        col = position.col;
        hei = position.hei;
        //把現在位置(已知距離)拿出來

        if(maze[hei][row][col]=='F'){//如果現在在終點
            printf("meet f\n");
            //檢查有沒有到終點 之後要return
            if(min>d[hei][row][col]){
                min = d[hei][row][col];///記錄下min
            }
            //記錄下min
            arrive=1;
        }
        //跑方向-------------------------------------------------------
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='D'){
            printf("meet D U\n");
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
                //------------------test------------------
                printf("updown!! \n");
                for(i=0;i<n/2+1;i++){
                    for(j=i+1;j<n+2-i-1;j++){
                        for(k=i+1;k<n+2-i-1;k++){
                            printf("%5d ",d[i][j][k] );
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
                //-----------------------------------------*/
            }

        }
        //ODU都可以跑四方
        for(i=0;i<4;i++){
            printf("in for\n");
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;

            if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]>d[hei][row][col]+1){
                printf("in if\n");
                d[nh][nr][nc]=d[hei][row][col]+1;
                if(maze[nh][nr][nc]=='T'){
                    d[nh][nr][nc]=d[nh][nr][nc]+2;
                }
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                addq(nextposition);
                printf("addq\n");
                //------------------test------------------
                printf("d!! %d \n",i);
                int h;
                for(h=0;h<n/2+1;h++){
                    for(j=h+1;j<n+2-h-1;j++){
                        for(k=h+1;k<n+2-h-1;k++){
                            printf("%5d ",d[h][j][k] );
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
                //-----------------------------------------*/
            }
            printf("bottom\n");


        }
        //------------------------------------------------------------------------
        //printf("bottom");
    }
    printf("all bottom\n");
    return arrive;
}
//劃出路徑
void path(int ***d,char ***maze,char*** road,int fr,int fc,int fh){
	int row=fr;
	int col=fc;
	int hei=fh;
	int i,j,k,nr,nc,nh;
	road[hei][row][col]='*';
	while(maze[hei][row][col]!='S'){
    	if ((d[hei][row+1][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row+1][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            //現在位置和下一距離差1 差3
            row++;
        }
        else if ((d[hei][row-1][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row-1][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            //現在位置和下一距離差1 差3
            row--;
        }
        else if ((d[hei][row][col+1]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row][col+1]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            col++;
        }
        else if ((d[hei][row][col-1]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei][row][col-1]==d[hei][row][col]-3 && maze[hei][row][col]=='T')){
            col--;
        }
    	else if(maze[hei-1][row][col]=='U' &&((d[hei-1][row][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei-1][row][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T'))){
    		hei--;
		}
		else if(maze[hei+1][row][col]=='U' &&((d[hei+1][row][col]==d[hei][row][col]-1&& maze[hei][row][col]!='T') || (d[hei+1][row][col]==d[hei][row][col]-3 && maze[hei][row][col]=='T'))){
    		hei++;
		}
    	road[hei][row][col]='*';
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
    for(control=10;control<=10;control++){//for
        front=NULL;
        MALLOC(rear,sizeof(*rear));
        //MALLOC(front,sizeof(*front));
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
            int sr,sc,sh,fr,fc,fh;//起始位置
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
                        if(maze[i][j][k]=='F'){//起始位置
                            fh=i;
                            fr=j;
                            fc=k;
                        }
                        road[i][j][k]=maze[i][j][k];
                        mark[i][j][k]=maze[i][j][k];//road mark 複製一下
                    }
                }
                len++;//邊邊寬度+1
            }//for-------------------------------------------------
            FILE *wfile;
            sprintf(name,"test%d_ans.txt",control);
            wfile = fopen(name,"w");
            if( NULL == wfile ){
                printf( "wfile open failure" );
                return 1;
            }
            else{
                if(bfs(maze,d,sr,sc,sh)){//如果有路到終點
                    //------------------test------------------
                    printf("finald!! \n");
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
                    //-----------------------------------------*/
                    //path(maze,road,mark,d,sr,sc,sh);
                    path(d,maze,road,fr,fc,fh);
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

            for(i = 0; i < n/2+1; i++) {
        		for(j=0;j<n+2;j++){
        			free(maze[i][j]);
				}
    		}
    		for(i=0;i < n/2+1; i++){
    			free(maze[i]);
			}
            free(maze);
            for(i = 0; i < n/2+1; i++) {
        		for(j=0;j<n+2;j++){
        			free(mark[i][j]);
				}
    		}
    		for(i=0;i < n/2+1; i++){
    			free(mark[i]);
			}
            free(mark);
            for(i = 0; i < n/2+1; i++) {
        		for(j=0;j<n+2;j++){
        			free(road[i][j]);
				}
    		}
    		for(i=0;i < n/2+1; i++){
    			free(road[i]);
			}
            free(road);
            for(i = 0; i < n/2+1; i++) {
        		for(j=0;j<n+2;j++){
        			free(d[i][j]);
				}
    		}
    		for(i=0;i < n/2+1; i++){
    			free(d[i]);
			}
            free(d);
        }//else----------------------------------------------------------------------
        fclose(pfile);

    }
}
