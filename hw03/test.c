#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        printf("out\n");\
        exit(EXIT_FAILURE);\
    }
#define MAX_QUEUES 15000
struct TreeNode {
     int data;
     struct TreeNode* left;
     struct TreeNode* right;
};
typedef struct TreeNode node;
//存樹的queue
typedef struct queue* queuepointer;
typedef struct queue{
    node* nodelink;
    queuepointer link;
}queue;
