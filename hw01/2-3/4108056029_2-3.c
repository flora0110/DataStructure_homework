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
//六個方向----------
typedef struct{
    short int vert;
    short int horiz;
    short int hei;
}offsets;
offsets move[6];
//------------------

int min;
int pathnum;
int pnum;
int n;
void dfs(char*** maze,char*** mark,char*** road,int row,int col,int hei,int inproad,int step,int countp){
    int i,j,k;
    if(maze[hei][row][col]=='P'){
        inproad=1;//開始要走都是p的路
        countp++;
    }
    if(pnum==countp){//走完p的路
        inproad=0;//離開p路
    }
    if(maze[hei][row][col]=='F' && pnum==countp){//到終點而且有走完p
        pathnum++;//路徑數加一
        if(min>step){
            min=step;//取代最小
        }
        return;
    }
    else{//開始跑六個方向
        int nh,nr,nc;
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if(mark[nh][nr][nc]!='X' && !(inproad && maze[nh][nr][nc]!='P')){//這次沒跑過且可跑 + p要連續跑
                mark[nh][nr][nc]='X';//記錄跑過的路
                road[nh][nr][nc]='*';
                if(maze[nh][nr][nc]=='T'){
                    dfs(maze,mark,road,nr,nc,nh,inproad,step+3,countp);
                }
                else{
                    dfs(maze,mark,road,nr,nc,nh,inproad,step+1,countp);//printf("走完 %d %d %d step %d\n",hei,row,col,step );
                }
                mark[nh][nr][nc]=maze[nh][nr][nc];//跑完這條要還原
                road[nh][nr][nc]=maze[nh][nr][nc];
            }
        }
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='P'){
            if(mark[hei+1][row][col]!='X' && !(inproad && maze[hei+1][row][col]!='P')){
                mark[hei+1][row][col]='X';
                road[hei+1][row][col]='*';
                if(maze[hei+1][row][col]=='T'){
                    dfs(maze,mark,road,row,col,hei+1,inproad,step+3,countp);

                }

                else{
                    dfs(maze,mark,road,row,col,hei+1,inproad,step+1,countp);
                }
                mark[hei+1][row][col]=maze[hei+1][row][col];
                road[hei+1][row][col]=maze[hei+1][row][col];
            }



        }
        if((maze[hei][row][col]=='D'|| maze[hei][row][col]=='P') && hei>0 ){
            if(mark[hei-1][row][col]!='X' && !(inproad && maze[hei-1][row][col]!='P')){
                mark[hei-1][row][col]='X';
                road[hei-1][row][col]='*';
                if(maze[hei-1][row][col]=='T'){
                    dfs(maze,mark,road,row,col,hei-1,inproad,step+3,countp);
                }
                else{
                    dfs(maze,mark,road,row,col,hei-1,inproad,step+1,countp);
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
    for(control=1;control<=100;control++){//for
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
            n=0;//改全域
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
            pnum=0;//改全域
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
            FILE *wfile;
            wfile = fopen( "4108056029output.txt","a" );
            if( NULL == wfile ){
                printf( "wfile open failure" );
                return 1;
            }
            else{
                fprintf(wfile, "test %d starts now.\n",control );
                mark[sh][sr][sc]='X';
                pathnum=0;//全域
                min=100000;
                //printf("pnum %d\n",pnum );
                dfs(maze,mark,road,sr,sc,sh,0,0,0);
                if(pathnum>0){
                    printf("Shortest path: %d, The number of different paths: %d\n\n",min,pathnum);
                    fprintf(wfile,"Shortest path: %d, The number of different paths: %d\n\n",min,pathnum);
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
