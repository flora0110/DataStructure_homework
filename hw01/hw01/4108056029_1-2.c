#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100000
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
//找到終點到起點的最短距離 min及用回傳值確定是否可到
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
            break;
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
void path(int **d,char **maze,char** road,int fx,int fy,int num){
	int row=fx;
	int col=fy;
	int i,j,nr,nc;
	road[row][col]='*';
	while(maze[row][col]!='S'){
		for(i=0;i<4;i++){
        	nr = row+move[i].vert;
        	nc = col+move[i].horiz;
        	if (d[nr][nc] == d[row][col]-1){
            	//現在位置和下一距離差1
            	row=nr;
    			col=nc;
    			break;
        	}
    	}
    	road[row][col]='*';
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
            path(d,maze,road,finalx,finaly,num);
            for(i=1;i<num+2-1;i++){
                for(j=1;j<num+2-1;j++){
                    printf("%c ",road[i][j]);
                }
                printf("\n");
            }
            printf("最短路徑為%d\n",min);
        }
        else printf("The maze does not have a path\n" );
        for(i = 0; i < num+2; i++) {
        	free(maze[i]);
    	}
        free(maze);
        for(i = 0; i < num+2; i++) {
        	free(mark[i]);
    	}
        free(mark);
        for(i = 0; i < num+2; i++) {
        	free(road[i]);
    	}
        free(road);
        free(d);
    }
    fclose(rptr);
}
