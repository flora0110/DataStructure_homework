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
//�|�Ӥ�V----------
typedef struct{
    short int vert;
    short int horiz;
}offsets;
offsets move[4];
//---------------------

int min=100000;
//�����I��_�I���̵u�Z�� min�ΥΦ^�ǭȽT�w�O�_�i��
int bfs(char** maze,int **d,int num,int sx,int sy){
    int arrive=0;//�ˬd���S������I ����nreturn

    queue[0].row = sx; queue[0].col = sy;
    rear++;
    //�N�_�I��iqueue
    int i,j;
    for(i=0;i<num+2;i++){
        for(j=0;j<num+2;j++){
            d[i][j]=MAX;
        }
    }
    d[sx][sy]=0;
    //��l�ƩҦ���l�D�_�I���Z����MAX,�_�I�D�_�I�Z����0

    element position;
    int nr,nc;//���ʫ��m
    int row,col;//�{�b��m
    while (rear!=front){
        position = deleteq();
        row = position.row;
        col = position.col;
        //��{�b��m(�w���Z��)���X��
        if(maze[row][col]=='F'){//�p�G�{�b�b���I
            if(min>d[row][col]){
                min=d[row][col];//�O���Umin
            }
            arrive=1;
        }
        //�]��V-----------------------------------------------
        for(i=0;i<4;i++){
            nr = position.row+move[i].vert;
            nc = position.col+move[i].horiz;
            //�U�@�Ӧ�m
            if (maze[nr][nc]!='X' && d[nr][nc]>d[row][col]+1){//�i�H���B�S���L
                d[nr][nc]=d[row][col]+1;;//�U�Ӧ�m���Z���O�{�b��m�Z��+1
                element nextposition;
                nextposition.row=nr;nextposition.col=nc;
                addq(nextposition);//��U�Ӧ�m�[�i�hqueue
            }
        }
        //-----------------------------------------------
    }
    return arrive;
}
//���X���|
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
            	//�{�b��m�M�U�@�Z���t1
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
    //�w�q�]����V
    int num,i,j,startx,starty,finalx,finaly;
    FILE *rptr;
    rptr = fopen("test.txt","r");
    if(NULL==rptr){
        printf("Open failure");
        return 1;
    }
    else{
        fscanf(rptr,"%d\n",&num);
        //char** maze = arr(num+2,num+2);//�a��
        char maze[25][25];
        char** mark = arr(num+2,num+2);//���L
        char** road = arr(num+2,num+2);//�n�L�����|
        int** d = arrc(num+2,num+2);//�Z��
        for(i=0;i<num+2;i++){//�ˤ@�Ӥj����ҥH+2
            for(j=0;j<num+2;j++){
                if(i==0 || j==0 || i==num+1 || j==num+1){
                    //��_�C�h�a�Ϫ��j����
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
                mark[i][j]=maze[i][j];//road mark �ƻs�@�U
            }
        }
        printf("----------------------\n");
        for(i=0;i<num+2;i++){
        	for(j=0;j<num+2;j++){
        		printf("%c ",maze[i][j]);
			}
			printf("\n");
		}
		printf("---------------------\n");
        /*if(bfs(maze,d,num,startx,starty)){//�p�G��������I
            path(d,maze,road,finalx,finaly,num);
            for(i=1;i<num+2-1;i++){
                for(j=1;j<num+2-1;j++){
                    printf("%c ",road[i][j]);
                }
                printf("\n");
            }
            printf("�̵u���|��%d\n",min);
        }
        else printf("The maze does not have a path\n" );*/
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
