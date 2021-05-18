//58failed
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
    short int dir;//�O���L�]����V
} element;
element queue[MAX_STACK_SIZE];
int rear = -1;
int front = -1;
void queueFull(){
    fprintf(stderr, "��C�w���A����A�[�J����");
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
        fprintf(stderr, "��C�w��");
    }
    return queue[++front];
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
int n;
//�����I�D�_�I���̵u�Z��min �ΥΦ^�ǭȽT�w�O�_�i��
int bfs(char*** maze,int*** d,int sr,int sc,int sh){
    rear=-1;front=-1;

    int arrive=0;//�ˬd���S������I ����nreturn
    element position;
    position.row = sr;//j
    position.col = sc;//k
    position.hei = sh;//i
    //�����_�l��m

    addq(position);//�N�_�I��iqueue
    int i,j,k;
    for(i=0;i<n/2+1;i++){
        for(j=0;j<n+2;j++){
            for(k=0;k<n+2;k++){
                d[i][j][k]=MAX;
            }
        }
    }
    d[sh][sr][sc]=0;
    //��l�ƩҦ���l�D�_�I���Z����MAX,�_�I�D�_�I�Z����0

    int nr,nc,nh;//���ʫ��m
    int row,col,hei;//�{�b��m
    while(rear!=front){
        //printf("rear: %d front: %d\n",rear,front );
        position = deleteq();
        row = position.row;
        col = position.col;
        hei = position.hei;
        //��{�b��m(�w���Z��)���X��

        if(maze[hei][row][col]=='F'){//�p�G�{�b�b���I
            //�ˬd���S������I ����nreturn
            if(min>d[hei][row][col]){
                min = d[hei][row][col];///�O���Umin
            }
            min = d[hei][row][col];
            //�O���Umin
            arrive=1;
        }
        //�]��V-------------------------------------------------------
        if(maze[hei][row][col]=='U' || maze[hei][row][col]=='D'){
            int upanddown=-1;
            if(maze[hei][row][col]=='U'){
                //printf("meet U\n");
                upanddown=1;
            }
            //�M�w�O�W�O�U

            nr = row;
            nc = col;
            nh = hei+upanddown;
            //�U�@�Ӧ�m�O��
            if(nh>=0){
                if (maze[nh][nr][nc]!='X' && d[nh][nr][nc]>d[hei][row][col]+1){//�i�H���B�S���L/����u����
                    d[nh][nr][nc]=d[hei][row][col]+1;//�U�Ӧ�m���Z���O�{�b��m�Z��+1
                    if(maze[nh][nr][nc]=='T'){//�J�쳴���O+3
                        d[nh][nr][nc]=d[nh][nr][nc]+2;
                    }
                    element nextposition;
                    nextposition.row=nr;nextposition.col=nc;nextposition.hei=nh;
                    addq(nextposition);//��U�Ӧ�m�[�i�hqueue
                }
            }

        }
        //ODU���i�H�]�|��
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

int dfs(char*** maze,char*** mark,char*** road,int row,int col,int hei,int limit){
    int count=0;
    int i,j,k;

    if(limit<0 || maze[hei][row][col]=='X' ||mark[hei][row][col]=='X'){//�p�G�]���Z���j��min+5
        return 0;
    }
    if(maze[hei][row][col]=='F'&&limit>=0){
        return 1;
    }
    road[hei][row][col]='*';
    mark[hei][row][col]='X';//�O���]�L����
    int nh,nr,nc;
    if(maze[hei][row][col]=='T'){
        limit-=3;
    }
    else{
        limit--;
    }
    //printf("limit %d\n", limit);
    for(i=0;i<4;i++){
        //printf("%d limit %d\n",i, limit);
        nr = row+move[i].vert;
        nc = col+move[i].horiz;
        nh = hei+move[i].hei;
        if(maze[hei][row][col]=='T'){
            count+=dfs(maze,mark,road,nr,nc,nh,limit);
        }
        else{
            count+=dfs(maze,mark,road,nr,nc,nh,limit);
        }
    }
    if(maze[hei][row][col]=='U'){
        if(maze[hei][row][col]=='T'){
            count+=dfs(maze,mark,road,row,col,hei+1,limit);
        }
        else{
            count+=dfs(maze,mark,road,row,col,hei+1,limit);
        }
    }
    else if(maze[hei][row][col]=='D' && hei>0){
        if(maze[hei][row][col]=='T'){
            count+=dfs(maze,mark,road,row,col,hei-1,limit);
        }
        else{
            count+=dfs(maze,mark,road,row,col,hei-1,limit);
        }
    }
    mark[hei][row][col]=maze[hei][row][col];
    road[hei][row][col]=maze[hei][row][col];
    return count;
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
    FILE *wfile;
    wfile = fopen( "output.txt","w" );
    if( NULL == wfile ){
        printf( "wfile open failure" );
        return 1;
    }
    else{
        for(control=1;control<=100;control++){//for
            min = 100000;//�C���O�o��l��
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
                n=0;//���h���//�����
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
                            road[i][j][k]=maze[i][j][k];
                            mark[i][j][k]=maze[i][j][k];//road mark �ƻs�@�U
                        }
                    }
                    len++;//����e��+1
                }//for
                fprintf(wfile, "test %d starts now.\n",control );
                if(bfs(maze,d,sr,sc,sh)){//�p�G��������I
                    pathnum=0;
                    int pathnum=dfs(maze,mark,road,sr,sc,sh,min+5);
                    printf("Sortest path : %d, Limit: %d, The number of different paths: %d\n\n",min,min+5,pathnum);
                    fprintf(wfile,"Shortest path: %d, Limit: %d, The number of different paths: %d\n\n",min,min+5,pathnum);
                }
                else fprintf(wfile,"The maze does not have a path\n" );
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

        }//�]1-100��for
    }//wfile��else
    fclose(wfile);
}

