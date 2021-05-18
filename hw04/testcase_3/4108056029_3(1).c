#include <stdio.h>
#include <stdlib.h>
typedef struct position{
    int row;
    int col;
    int mirror;
}position;
typedef struct Orien{
    int row;
    int col;
}Orien;
Orien orien[4];
void mark(char**,int**,int,int,int,int,int,int,int,int,int);
//void mark(char** ans,int** see,int seen,int v,int z,int g,int monsta,int row,int col,int mirror)
int n;
int main(){
    FILE* rptr;
    FILE* wptr;
    rptr=fopen("test4.txt","r");
    wptr=fopen("output.txt","w");
    if(rptr==NULL ||wptr==NULL){
        printf("error\n");
        return 0;
    }
    orien[0].row=1;
    orien[0].col=0;
    orien[1].row=0;
    orien[1].col=-1;
    orien[2].row=-1;
    orien[2].col=0;
    orien[3].row=0;
    orien[3].col=1;
    int v,z,g;
    fscanf(rptr,"%d %d %d\n",&v,&z,&g);
    fscanf(rptr,"%d\n",&n);
    int** see=(int**)malloc((n*4)*sizeof(int*));
    int i,j;
    for(i=0;i<n*4;i++){
        see[i]=(int*)malloc(4*sizeof(int));
        fscanf(rptr,"%d ",&see[i][0]);
        if(i<n){
            see[i][1]=1;
            see[i][2]=i+1;
            see[i][3]=0;
        }
        else if(i<2*n){
            see[i][1]=n;
            see[i][2]=i-n+1;
            see[i][3]=2;
        }
        else if(i<3*n){
            see[i][1]=i-2*n+1;
            see[i][2]=1;
            see[i][3]=3;
        }
        else{
            see[i][1]=i-n*3+1;
            see[i][2]=n;
            see[i][3]=1;
        }
    }
    char **maze=(char**)malloc((n+2)*sizeof(char*));
    char **ans=(char**)malloc((n+2)*sizeof(char*));
    for(i=0;i<n+2;i++){
        maze[i]=(char*)malloc((n+2)*sizeof(char));
        ans[i]=(char*)malloc((n+2)*sizeof(char));
        for(j=0;j<n+2;j++){
            if(i==0 || j==0 || i==n+1 || j==n+1){
                maze[i][j]='x';
            }
            else{
                fscanf(rptr,"%c",&maze[i][j]);
            }
            ans[i][j]=maze[i][j];
            //printf("%d %d %c\n",i,j,maze[i][j]);
        }
        if(i!=0 &&i!=n+1){
            fgetc(rptr);
        }
    }
    //test---------------
    for(i=0;i<n+2;i++){
        for(j=0;j<n+2;j++){
            //printf("%d %d %c\n",i,j,maze[i][j]);
            printf("%c",maze[i][j]);
        }
        printf("\n");
    }
    //-------------------*/
    mark(ans,see,0,v,z,g,see[0][0],1,1,0,0);
    fclose(rptr);
    fclose(wptr);
}
void show(char** ans,int v,int z,int g,int monsta,int seen){
    if(seen!=11) return;
    //printf("-------------------------------------------------------------------seen %d\n",seen );
    printf("v: %d   z: %d   g: %d   monsta: %d\n",v,z,g,monsta);
    int i,j;
    for(i=0;i<n+2;i++){
        for(j=0;j<n+2;j++){
            printf("%c",ans[i][j]);
        }
        printf("\n");
    }
}
void mark(char** ans,int** see,int seen,int v,int z,int g,int monsta,int row,int col,int mirror,int dir){
    int i,j;
    /*if(seen==11 || seen==12) printf("---------in mark %d\n",seen);
    if(seen==11 || seen==12) printf("v: %d   z: %d   g: %d   monsta: %d\n",v,z,g,monsta);
    if(seen==11 || seen==12) printf("now at %d %d\n",row,col );
    for(i=0;i<n+2;i++){
        for(j=0;j<n+2;j++){
            if(i==row && j==col){
                if(seen==11 || seen==12) printf("*");
            }
            else {if(seen==11 || seen==12) printf("%c",ans[i][j]);}
        }
        if(seen==11 || seen==12) printf("\n");
    }*/
    char origin=ans[row][col];
    if(v<0||z<0||g<0||monsta<0 || monsta>see[seen][0]){
        //printf("--------------------------------------v<0||z<0||g<0||monsta<0\n");
        return;
    }
    if(ans[row][col]=='x' && monsta!=0){
        //printf("--------------------------------------!front and monsta!=0\n");
        return;
    }
    if(ans[row][col]=='x' && monsta==0){
        //printf("----------------------------------------to next seen %d\n",seen );
        if(seen==4*n-1){
            printf("-----------------------ans----------------------\n");
            for(i=0;i<n+2;i++){
                for(j=0;j<n+2;j++){
                    printf("%c",ans[i][j]);
                }
                printf("\n");
            }
            return;
        }
        mark(ans,see,seen+1,v,z,g,see[seen+1][0],see[seen+1][1],see[seen+1][2],0,see[seen+1][3]);
        return;
    }
    /*if(seen==12){
        printf("dir %d ans[row][col]= %c\n",dir,ans[row][col] );
    }*/
    if(ans[row][col]=='\\'){
        mirror=1;
        switch (dir) {
            case 0: dir=3;break;      case 1: dir=2;break;     case 2: dir=1;break;    case 3: dir=0;break;
        }
    }
    else if(ans[row][col]=='/'){
        mirror=1;
        switch (dir) {
            case 0: dir=1;break;  case 1: dir=0;break;  case 2: dir=3;break;  case 3: dir=2;break;
        }
    }
    int nextrow=row+orien[dir].row,nextcol=col+orien[dir].col,nextmonsta=monsta;
    //int nextv=v,nextz=z,nextg=g;
    if(ans[row][col]=='Z'||ans[row][col]=='G'||ans[row][col]=='V'){
        if(ans[row][col]=='Z') nextmonsta--;
        if(mirror==1 && ans[row][col]=='G') nextmonsta--;
        else if(mirror==0 && ans[row][col]=='V') nextmonsta--;
        mark(ans,see,seen,v,z,g,nextmonsta,nextrow,nextcol,mirror,dir);
    }
    else if(ans[row][col]=='.'){
        ans[row][col]='Z';
        //show(ans,v,z,g,monsta,seen);
        mark(ans,see,seen,v,z-1,g,monsta-1,nextrow,nextcol,mirror,dir);
        if(mirror==1){
            ans[row][col]='G';
            //show(ans,v,z,g-1,monsta-1,seen);
            mark(ans,see,seen,v,z,g-1,monsta-1,nextrow,nextcol,mirror,dir);
            ans[row][col]='V';
            //show(ans,v-1,z,g,monsta,seen);
            mark(ans,see,seen,v-1,z,g,monsta,nextrow,nextcol,mirror,dir);
        }
        else if(mirror==0){
            ans[row][col]='G';
            //show(ans,v,z,g-1,monsta-1,seen);
            mark(ans,see,seen,v,z,g-1,monsta,nextrow,nextcol,mirror,dir);
            ans[row][col]='V';
            //show(ans,v-1,z,g,monsta,seen);
            mark(ans,see,seen,v-1,z,g,monsta-1,nextrow,nextcol,mirror,dir);
        }
    }
    else mark(ans,see,seen,v,z,g,monsta,nextrow,nextcol,mirror,dir);
    ans[row][col]=origin;
    /*printf("return to origin\n");
    printf("---------in mark %d\n",seen);
    printf("v: %d   z: %d   g: %d   monsta: %d\n",v,z,g,monsta);
    for(i=0;i<n+2;i++){
        for(j=0;j<n+2;j++){
            if(i==row && j==col){
                printf("*");
            }
            else printf("%c",ans[i][j]);
        }
        printf("\n");
    }*/
    return;
}
