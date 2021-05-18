#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node* nodepointer;
typedef struct chan_node* chan_nodepointer;
typedef struct node{
    char *state;//���I����l
    char *function;//���ܼƪ�fun
    int check;//�O�_�]�L
    chan_nodepointer next;//�ഫ���ܼ�
    chan_nodepointer rear;//�o�@�檺�̫�
}node;//���Y�ܼ�
typedef struct chan_node{
    nodepointer link;//���V���Y
    chan_nodepointer next;//���V�U�@��
}chan_node;//�ഫ���ܼ�

node *var_trans[11];//�ܼ�
node* variable_to_pointer(char* v,int n){//v is a variable//�n���ܼ�(�r��)�������V���Y������
    int i;
    for(i=0;i<n;i++){
        if(strlen(var_trans[i]->state)==strlen(v) && strncmp(var_trans[i]->state,v,strlen(v))==0){//�@�˪��B�@��
            return var_trans[i];
        }
    }
}
void build(char* chan,char *pch,int n,char *function){//chan = f(chainto)
    node* chantemp=variable_to_pointer(chan,n);//�����Y�ܼ�
    node* pchtemp=variable_to_pointer(pch,n);//���n�ഫ�����ܼƪ����Y
    chantemp->function=function;//�����Y�ܼƪ����
    chan_nodepointer new=(chan_node*)malloc(sizeof(chan_node));
    new->link=pchtemp;
    new->next=NULL;
    if(chantemp->rear==NULL){
        chantemp->next=new;
    }
    else{
        chantemp->rear->next=new;
    }
    chantemp->rear=new;
}
char ans[11][1000];//���ץ��s��
int k=0;//�O�{�b������ܼƭn�s�bans[k]
int showans(node* now){//�}�l�L�Xnow���� 0�O�L��
    if(now->function==NULL){
        strcat(ans[k],now->state);
        strcat(ans[k]," ");
        return 1;
    }
    else{//�٥i�H�i�}
        strcat(ans[k],now->function);
        strcat(ans[k],"( ");
        chan_nodepointer next=now->next;//�ҥH���ഫ�����ܼ�
        while(next!=NULL){//�S�ܼƤF�X�h
            if(next->link->check==1){//�̭Ӧb�o���Ѫk���X�{�L�F�A�O�j��
                return 0;//�L��
            }
            next->link->check=1;//�o���������L
            int c=showans(next->link);
            if(c==0){//�䤤�@�ܼƷ|�X�{loop
            	return 0;
			}
            next->link->check=0;//�_��
            next=next->next;
        }
        strcat(ans[k],") ");
        return 1;
    }
}
int main(){
    FILE *rptr;
    rptr=fopen("test.txt","r");//test---------------------------------test
    if(rptr==NULL){
        printf("open error\n");
        return 0;
    }
    int i,j;
    int n,m;
    fscanf(rptr,"%d\n",&n);
    //printf("n: %d\n",n );
    for(i=0;i<n;i++){
        var_trans[i]=(nodepointer)malloc(sizeof(node));
        var_trans[i]->state=(char*)malloc(4*sizeof(char));
        fscanf(rptr,"%s ",var_trans[i]->state);
        var_trans[i]->next=NULL;
        var_trans[i]->function=NULL;
        var_trans[i]->check=0;
        var_trans[i]->rear=NULL;
    }
    fscanf(rptr,"%d\n",&m);
    //printf("m: %d\n",m );
    char chinto[21];//chan=f(chinto)
    char chan[4];
    char *function;
    const char* delim = " ";
    for(i=0;i<m;i++){
        function = (char*)malloc(4*sizeof(char));
        fscanf(rptr,"%s = %[^(] %*c %[^)] )\n",chan,function,chinto);
        char* pch=strtok(chinto,delim);//�H�Ů��
        while(pch){
            build(chan,pch,n,function);
            pch=strtok(NULL,delim);
        }
    }
    int check=1;
    for(i=0;i<n;i++){
        var_trans[i]->check=1;
        memset(ans[i],'\0',1000);
        check=showans(var_trans[i]);
        k++;
        var_trans[i]->check=0;
        if(check==0){
            printf("No solution.\n");
            break;
        }
    }
    if(check){
        for(i=0;i<n;i++){
            for(j=0;j<strlen(var_trans[i]->state);j++){
                printf("%c",var_trans[i]->state[j]);
            }
            printf(" -> ");
            for(j=0;j<strlen(ans[i]);j++){
                printf("%c",ans[i][j]);
            }
            printf("\n");
        }
    }
    for(i=0;i<n;i++){
        free(var_trans[i]->state);
        free(var_trans[i]->function);
        free(var_trans[i]->next);
        free(var_trans[i]);
    }
    fclose(rptr);
}

