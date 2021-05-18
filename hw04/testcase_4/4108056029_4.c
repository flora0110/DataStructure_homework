#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct all{
    int *ori;//an array to save which obj it has original
    int *chan_to;//and all ori will equal to chan_to
}All;
int at_where(char**,char*,int*);//will return the position that the obj at
int pass(All*,int*,int,int,int);//will add new obj which the origin obj equal to
int main(){
    FILE* rptr;
    rptr=fopen("test8.txt","r");//------------------test
    if(rptr==NULL){
        printf("error\n");
        return 0;
    }
    int n,i,j;
    fscanf(rptr,"%d\n",&n);
    char* token;
    const char* delim = " ";
    All* all=(All*)malloc(300*sizeof(All));//to save n equaltion
    int alln=0;//how many all it has
    char **obj=(char**)malloc(18000*sizeof(char*));//a string array to save every obj at a position
    int objn=0;//num of obj
    int flyat,pigat;//whereh fly at in obj array and where pig at
    int* ori;//a array to save which obj it origin have
    int* chan_to;//and which obj it can add
    for(i=0;i<n;i++){
        char str[300];
        fgets(str,300,rptr);
        token = strtok(str,delim);//chop by ' '
        int chan=0;//whether it is at chan_to part
        ori=(int*)malloc(18000*sizeof(int));
        chan_to=(int*)malloc(18000*sizeof(int));
        int orin=0,chan_ton=0;//how many obj in ori and chan_to
        int isthat=0;//whether ut has appear that
        while( token != NULL ){
            if('Z'>=token[0] && token[0]>='A'){//is obj
                if(token[strlen(token)-1]=='\n') token[strlen(token)-1]='\0';//to make every obj same
                int at=at_where(obj,token,&objn);//show the position
                if(chan==0){//ori part
                    ori[orin++]=at;//put the position of obj in ori
                }
                else if(chan==1){
                    chan_to[chan_ton++]=at;//put the position of obj in chan_to
                }
                if (strlen(token)==3 && strncmp("FLY",token,strlen(token))==0) flyat=at;
                else if (strlen(token)==4 && strncmp("PIGS",token,strlen(token))==0) pigat=at;

            }
            if((strlen(token)==3 && strncmp("are",token,strlen(token))==0)||\
                (strlen(token)==3 && strncmp("can",token,strlen(token))==0) && isthat==0 ||\
                (strlen(token)==4 && strncmp("have",token,strlen(token))==0)){//can without that in front of it
                chan=1;
            }
            if(strlen(token)==4 && strncmp("that",token,strlen(token))==0){
                isthat=1;
            }
            if(strlen(token)==3 && strncmp("can",token,strlen(token))==0 && isthat==1){
                isthat=0;//after can apear isthat ture back to 0
            }
            token=strtok(NULL,delim);//chop str
        }
        ori[orin]=-1;
        chan_to[chan_ton]=-1;//end sign
        all[alln].ori=ori;
        all[alln++].chan_to=chan_to;//save to all
    }
    int *test=(int*)malloc((objn+1)*sizeof(int));
    memset(test,0,objn+1);//set test to all 0
    test[pigat]=1;//start from pig
    int allcheck=pass(all,test,alln,flyat,pigat);//1-> add 0-> no add 2->can fly
    while(allcheck!=0 && allcheck!=2){
        allcheck=pass(all,test,alln,flyat,pigat);
    }
    if(allcheck==2){
        printf("All pigs can fly\n");
    }
    else{
        for(i=0;i<objn;i++){
            for(j=0;j<objn;j++){
                test[j]=0;
                if(j==i) test[j]=1;//turn to other obj start
            }
            allcheck=pass(all,test,alln,flyat,pigat);
            while(allcheck!=0 && allcheck!=2){
                allcheck=pass(all,test,alln,flyat,pigat);
            }
            if(allcheck==2) {//some pig can fly
                break;
            }
        }
        if(allcheck==2){//if there is a obj it are  pig and can fly
            printf("Some pigs can fly\n");
        }
        else{
            printf("No pigs can fly\n");
        }
    }
}
int pass(All all[300],int* test,int alln,int flyat,int pigat){//if not chan-> 0 if found fly ->2
    int i,j,allcheck=0;//whether it has add(1)
    for(i=0;i<alln;i++){
        int check=1;
        for(j=0;all[i].ori[j]!=-1;j++){
            if(test[all[i].ori[j]]==0) {//not meet the conditions
                check=0;
                break;
            }
        }
        if(check){
            for(j=0;all[i].chan_to[j]!=-1;j++){
                if(test[all[i].chan_to[j]]==0) allcheck=1;//it is 0 original
                test[all[i].chan_to[j]]=1;//add new obj
            }
        }
    }
    if(test[flyat]==1 && test[pigat]==1){//pig can fly
        return 2;
    }
    else {
        return allcheck;//add or not
    }
}
int at_where(char** obj,char* token,int* objn){
    int i,j,check=0;
    char *new=(char*)malloc(300*sizeof(char));
    for(i=0;i<strlen(token);i++){
        new[i]=token[i];
    }
    new[i]='\0';
    for(i=0;i<*objn;i++){
        if(strcmp(obj[i],token)==0 && strncmp(obj[i],token,strlen(token))==0){
            check=1;
            return i;
        }
    }
    if(!check){//not in obj array
        obj[(*objn)++]=new;
        return (*objn)-1;
    }
}
