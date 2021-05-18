#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	short int vert,horiz;
}offsets;
offsets move[4];
//////////////////////////////////////////////////////
typedef struct
{
	short int row,col;//dir�O���q����
}element;
element position;
//////////////////////////////////////////////////////
element queue[1000];
int rear = -1;
int front = -1;
void queueFull(){
    fprintf(stderr, "queue is full");
    exit(EXIT_FAILURE);
}
void addq(element item){
    if(rear==100000-1){
        queueFull();
    }
    queue[++rear] = item;
}
element deleteq(){
    if(front==rear){
        fprintf(stderr, "queue is empty");
    }
    return queue[++front];
}
int bfs(char *maze,int *d,int n)////maze�O���l�a��  d �O��bfs���̵u���|
{
	printf("haha\n");
	int row,col,nr,nc,i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			d[i*n+j]=401;
			if(maze[i*n+j]=='F')
			{
				d[i*n+j] = 0;
			}
		}
	}

	while(front!=rear){
		printf("haha\n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{

				printf("%3d ", d[i*n+j]);
			}
			printf("\n");
		}
		printf("\n");
		position = deleteq();
		row=position.row;
		col=position.col;
		if(maze[row*n+col] == 'F')//�������I
			return 1;
		for(i=0;i<4;i++)
		{
			nr=row+move[i].vert;
			nc=col+move[i].horiz;
			if(maze[nr*n+nc] != 'X' && d[nr*n+nc] > d[row*n+col]+1)//�J��X�Χ��u���|
			{
				d[nr*n+nc]=  d[row*n+col]+1;
				position.row = nr;
				position.col = nc;
				addq(position);
			}
		}
	}

	return 0;
}
//	maze[1*n+2];
//maze[1][2]=maze[7]
//bfs(&maze[0][0]);
FILE *p1;
//////////////////////////////////////////////////
int main() {
	char a[1000]={};//Ū��
	int x=0,i,j=1,n=0,row=0,col=0;//i,j forŪ���� ; nŪ�Ĥ@��
	char maze[n+2][n+2],mark[n+2][n+2];//maze�O���l�a��  mark�O�аO����
	int num_maze[n+2][n+2];//num_maze�O��bfs���̵u���|
	p1=fopen("test.txt","r");
	if(p1==NULL)
	{
		printf("p1 error");
	}
		fscanf(p1,"%d\n",&n);//Ū�Ĥ@��:n
	printf("n:%d\n",n);
	for(i=0; i<n*n ;i++)//�@���@��Ū
	{
		a[i]=fgetc(p1);
		printf("%c ", a[i]);
		fgetc(p1);//��Ū�Ů�
		if(i%n==n-1){
			fgetc(p1);//��Ū����
			printf("\n");
		}

	}
	printf("----------------\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{

			printf("%c ", a[i*n+j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("----------------\n");
	char ans[n+2][n+2];
	for(i =0;i<n+2;i++)//����
	{
		for( j=0;j<n+2;j++)
		{
			if(i == 0  || i == n+1 || j == 0  || j == n+1 )
			{
				mark[i][j] = 'X';
				maze[i][j] = 'X';
			}
			else
			{
				mark[i][j] = a[x];
				maze[i][j] = a[x];
				x++;
				//if(maze[0][2]!='X'){
				//	printf("in a %d ,%d %d\n",x,i,j);
				//}
			}
			//if(maze[0][2]!='X'){
			//	printf("%d %d\n",i,j);
			//}
			//printf("%c----------------1\n", maze[0][2]);
			printf("%c ", maze[i][j]);
			ans[i][j]=maze[i][j];
		}
		//printf("%c----------------2\n", maze[0][2]);
		printf("\n");
	}
	//printf("%c------------------3\n", maze[0][2]);
	printf("\n");
	for(i=0;i<n+2;i++)
	{
		for(j=0;j<n+2;j++)
		{

			printf("%c ", ans[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0; i<n+2 ;i++)//���_�I
	{
		for( j=0;j<n+2;j++)
		{
			if(mark[i][j]== 'S')
			{

				mark[i][j] = '*';
				maze[i][j] = '*';
				position.row = i;
				position.col = j;
				row = position.row;
				col = position.col;
				addq(position);
				printf("rear %d ",rear);
			}
		}
	}


	if(bfs(&maze[0][0],&num_maze[0][0],n+2)==1){
		for(i=0;i<n+2;i++)
		{
			for(j=0;j<n+2;j++)
			{

				printf("%3d ", num_maze[i][j]);
			}
			printf("\n");
		}
	}
	else{
		printf("not exit");
	}








	return 0;
}
