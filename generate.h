#ifndef MY_LinkedList_H
#define MY_LinkedList_H

/*********************************************************
Linked List: Adjacency List
***********************************************************/
/* Defining struct EdgeNode as nodes within the linked list stucture LinkedList */
typedef struct EdgeNode EdgeNode;

/* Defining struct Node within the Linked List */
typedef struct Node Node;

/* Defining struct LinkedList as the linked list implementation of LILO Queue */
typedef struct LinkedList LinkedList;

/* Function. Creating a Node for the maze and to hold the linkedlist of edges */
int add_Edge(LinkedList *LL, int location, int edge);

/* Function. Creating a LinkedList and returns the pointer to it. If fails, return NULL */
LinkedList *LL_create();

/* Function. To insert data within the linked list */
int LL_insert(LinkedList *LL, int location);

/* Function. To search specified data within the linked list. Returns a pointer to the data */
Node *LL_Search(LinkedList *LL, int data);

/* Function. To print out all the data within each node of the linked list */
void LL_print(LinkedList *LL);

/* Function. To print out all the edges for each node in the maze */
void Node_print(Node *node);

/* Function. To free the memory of the linked list */
void LL_free(LinkedList *LL);

/*********************************************************
Stack: DFS
***********************************************************/
/* Defining struct for Stack used in Depth First Search */
typedef struct StackNode StackNode;

/* Function. To check if the stack is empty of not */
int isEmpty(StackNode *root);

/* Function. To push the node to the stack */
void push(StackNode **root, int data);

/* Function. To pop the node out of the stack */
int pop(StackNode **root);

/* Function. To peek the node thru the stack */
int peek(StackNode *root);

/* Function. To print all the node in the stack */
void stack_print(StackNode *node);

/*********************************************************
Random: DFS
***********************************************************/
/* Function. To generate a random integer between min & max input */
void shuffle(int *array, int n, int num_shuffles);

/*********************************************************
DFS
***********************************************************/
/* Function. Depth First Search to create the maze structure */
int dfs(LinkedList *LL, int startNodeNum, int *outcome, int row, int col);

/*********************************************************
Print Ajacency List: DFS
***********************************************************/
/* Function. To write in to the file of all the information of the maze */
void print_adjacencyList(FILE *infile, int row, int col, LinkedList *LL);

#endif