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
//���Ӥ�V----------
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
        inproad=1;//�}�l�n�����Op����
        countp++;
    }
    if(pnum==countp){//����p����
        inproad=0;//���}p��
    }
    if(maze[hei][row][col]=='F' && pnum==countp){//����I�ӥB������p
        pathnum++;//���|�ƥ[�@
        if(min>step){
            min=step;//���N�̤p
        }
        return;
    }
    else{//�}�l�]���Ӥ�V
        int nh,nr,nc;
        for(i=0;i<4;i++){
            nr = row+move[i].vert;
            nc = col+move[i].horiz;
            nh = hei+move[i].hei;
            if(mark[nh][nr][nc]!='X' && !(inproad && maze[nh][nr][nc]!='P')){//�o���S�]�L�B�i�] + p�n�s��]
                mark[nh][nr][nc]='X';//�O���]�L����
                road[nh][nr][nc]='*';
                if(maze[nh][nr][nc]=='T'){
                    dfs(maze,mark,road,nr,nc,nh,inproad,step+3,countp);
                }
                else{
                    dfs(maze,mark,road,nr,nc,nh,inproad,step+1,countp);//printf("���� %d %d %d step %d\n",hei,row,col,step );
                }
                mark[nh][nr][nc]=maze[nh][nr][nc];//�]���o���n�٭�
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
    //�w�q�]����V
    char y;//��Ĥ@���J������r��
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
            //��J���Ĥ@����s�b�@�@���}�C
            char* bottom = make1darr(MAXLEN);
            n=0;//�����
            char y;
            bottom[n]=fgetc(pfile);
            while(bottom[n]!='\n'){
                fgetc(pfile);
                bottom[++n]=fgetc(pfile);
                //printf("y: %c\n",y);
            }
            char ***maze=make3darr(n/2+1,n+2,n+2);//�a��
            char ***road=make3darr(n/2+1,n+2,n+2);//�n�L�X�����|
            char ***mark=make3darr(n/2+1,n+2,n+2);//�]�L����X
            int ***d=make3darrint(n/2+1,n+2,n+2);//�Z��
            int len=0;//�]���n���Ҧ��G�L�}�C�|���T�����P �ҥH�W�����}�C�|���@���䪺�e��len
            int sr,sc,sh;//�_�l��m
            pnum=0;//�����
            for(i=0;i<n/2+1;i++){//���׬On/2+1
                for(j=0;j<n+2;j++){//�ˤ@�Ӥj����ҥH+2
                    for(k=0;k<n+2;k++){
                        if(j==0 || k==0 || j==n+1 || k==n+1){
                            maze[i][j][k]='X';//��_�C�h�a�Ϫ��j����
                        }
                        else if(i==0 && j==1){//�@�ӲĤ@�C��bottom[]�ƻs�i�h
                            maze[i][j][k]=bottom[k-1];//�a�Ϧ��j����ҥH�O�q1�}�l��
                        }
                        else if(j > len && j <= n-len && k > len && k <= n-len){
                            fscanf(pfile,"%c ",&maze[i][j][k]);//len+1~n-len*len+1~n-len���O�n��J���a��

                        }
                        else{
                            maze[i][j][k]='X';//�e�׬�len������
                        }
                        if(maze[i][j][k]=='S'){//�_�l��m
                            sh=i;
                            sr=j;
                            sc=k;
                        }
                        if(maze[i][j][k]=='P'){
                            pnum++;
                        }
                        road[i][j][k]=maze[i][j][k];
                        mark[i][j][k]=maze[i][j][k];//road mark �ƻs�@�U
                    }
                }
                len++;//����e��+1
            }//for
            FILE *wfile;
            wfile = fopen( "output.txt","a" );
            if( NULL == wfile ){
                printf( "wfile open failure" );
                return 1;
            }
            else{
                fprintf(wfile, "test %d starts now.\n",control );
                mark[sh][sr][sc]='X';
                pathnum=0;//����
                min=100000;
                //printf("pnum %d\n",pnum );
                dfs(maze,mark,road,sr,sc,sh,0,0,0);
                if(pathnum>0){
                    //printf("Shortest path: %d, The number of different paths: %d\n\n",min,pathnum);
                    fprintf(wfile,"Shortest path: %d, The number of different paths: %d\n\n",min,pathnum);
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

