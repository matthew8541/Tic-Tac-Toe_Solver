#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "generate.h"

/* row * col */

/* Defining struct EdgeNode as nodes within the linked list stucture LinkedList */
struct EdgeNode
{
    int key;
    EdgeNode *next;
};

/* Defining struct Node within the Linked List */
struct Node
{
    int location;
    int visit;
    EdgeNode *edge;
    Node *next;
};

/* Defining struct LinkedList as the linked list implementation of LILO Queue */
struct LinkedList
{
    Node *head;
    Node *tail;
};

/* Function, Creating a Node for each point in the maze */
int add_Edge(LinkedList *LL, int location, int edge)
{
    EdgeNode *newEdge = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (newEdge == NULL)
    {
        return -1;
    }

    // LL_Search
    Node *curr = LL->head;
    while (curr != NULL && curr->location != location)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        return -1;
    }

    newEdge->key = edge;
    if (curr->edge == NULL)
    {
        curr->edge = newEdge;
        return 0;
    }

    EdgeNode *curr_edge = curr->edge;
    while (curr_edge->next != NULL)
    {
        // If the edge integer is existed in the node, then break the method without adding the edge
        if (curr_edge->key == edge) {
            return 0;
        }
        curr_edge = curr_edge->next;
    }
    curr_edge->next = newEdge;
    return 0;
};

/* Function. Creating a LinkedList and returns the pointer to it. If fails, return NULL */
LinkedList *LL_create()
{
    LinkedList *LL = (LinkedList *)malloc(sizeof(LinkedList));

    if (LL == NULL)
    {
        return NULL;
    }
    return LL;
};

/* Function. To insert a Node within the linked list */
int LL_insert(LinkedList *LL, int location)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return -1;
    }

    newNode->location = location;
    if (LL->head == NULL)
    {
        LL->head = newNode;
        LL->tail = newNode;
        return 0;
    }

    LL->tail->next = newNode;
    LL->tail = newNode;
    return 0;
};

/* Function. To search specified data within the linked list. Returns a pointer to the Node in the location */
Node *LL_Search(LinkedList *LL, int location)
{
    Node *curr = LL->head;

    while (curr != NULL && curr->location != location)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        return NULL;
    }
    else
    {
        return curr;
    }
};

/* Function. To print out all the location for each Node and the edges within of the linked list */
void LL_print(LinkedList *LL)
{
    Node *curr = LL->head;

    if (curr == NULL)
    {
        printf("LinkedList is empty!\n");
    }

    while (curr != NULL)
    {
        printf("Node %d edges: ", curr->location);
        EdgeNode *curr_edge = curr->edge;
        if (curr_edge == NULL)
        {
            printf("empty!");
        }
        while (curr_edge != NULL)
        {
            printf("%d ", curr_edge->key);
            curr_edge = curr_edge->next;
        }
        printf("\n");
        curr = curr->next;
    }
};

/* Function. To free the memory of the linked list */
void LL_free(LinkedList *LL)
{
    Node *temp_node;
    Node *curr_node = LL->head;

    while (curr_node != NULL)
    {
        temp_node = curr_node;
        EdgeNode *temp_edge;
        EdgeNode *curr_edge = temp_node->edge;
        while (curr_edge != NULL)
        {
            temp_edge = curr_edge;
            curr_edge = curr_edge->next;
            free(temp_edge);
        }
        curr_node = curr_node->next;
        free(temp_node);
    }
    free(LL);
};

/* Defining struct for Stack used in Depth First Search */
struct StackNode
{
    int data;
    StackNode *next;
};

/* Function. Adding StackNodes to each other */
StackNode *newNode(int data)
{
    StackNode *stackNode = (StackNode *)malloc(sizeof(StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

/* Function. Checking if a node in a stack is null */
int isEmpty(StackNode *root)
{
    return !root;
}

/* Function. To push into the Stack */
void push(StackNode **root, int data)
{
    StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
    printf("%d pushed to stack\n", data);
}

/* Function. To pop from the stack */
int pop(StackNode **root)
{
    if (isEmpty(*root))
    {
        return INT_MIN;
    }
    StackNode *temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    printf("%d popped out of stack\n", popped);
    free(temp);

    return popped;
}

/* Function. To look into the Stack */
int peek(StackNode *root)
{
    if (isEmpty(root))
        return INT_MIN;
    return root->data;
}

/* Function. To print out all the data within the Node's linked list */
void stack_print(StackNode *node)
{
    StackNode *curr = node;
    int count = 0;

    if (curr == NULL)
    {
        printf("Stack is empty!\n\n");
    }

    while (curr != NULL)
    {
        printf("element %d: %d\n\n", count, curr->data);
        curr = curr->next;
        count += 1;
    }
};

/* Function. To generate a random integer between min & max input */
void shuffle(int *array, int n, int num_shuffles)
{
    srand((unsigned)time(NULL));
    for (int j = 0; j < num_shuffles; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int *filter_direction(int *outcome, int node_location, int row, int col)
{
    // The first node in the matrix
    if (node_location == 0)
    {
        outcome[0] = 1;
        outcome[1] = col;
        outcome[2] = 0;
        outcome[3] = 0;
    }
    // The last node in the matrix
    else if (node_location + 1 == row * col)
    {
        outcome[0] = 0;
        outcome[1] = 0;
        outcome[2] = -1;
        outcome[3] = -col;
    }
    // The left bottom node
    else if (node_location == col * (row - 1) ) {
        outcome[0] = 0;
        outcome[1] = 0;
        outcome[2] = 1;
        outcome[3] = -col;
    } 
    // The right upper node
    else if (node_location == col - 1) {
        outcome[0] = 0;
        outcome[1] = 0;
        outcome[2] = -1;
        outcome[3] = col;
    }
    // The first row in the matrix but the first node
    else if (node_location - col < 0)
    {
        outcome[0] = 1;
        outcome[1] = col;
        outcome[2] = -1;
        outcome[3] = 0;
    }
    // The last row in the matrix but the last node
    else if (node_location + col  >= row * col)
    {
        outcome[0] = 1;
        outcome[1] = 0;
        outcome[2] = -1;
        outcome[3] = -col;
    }
    // The first column in the matrix but the first node
    else if (node_location % col == 0)
    {
        outcome[0] = 1;
        outcome[1] = col;
        outcome[2] = 0;
        outcome[3] = -col;
    }
    // The last column in the matrix but the last node
    else if (node_location % col == col - 1)
    {
        outcome[0] = 0;
        outcome[1] = col;
        outcome[2] = -1;
        outcome[3] = -col;
    }
    // The node not boarders the edges of the matrix
    else
    {
        outcome[0] = -1;
        outcome[1] = 1;
        outcome[2] = -col;
        outcome[3] = col;
    }
    return outcome;
}

/* Function. Depth First Search to create the maze structure */
int dfs(LinkedList *LL, int startNodeNum, int *outcome, int row, int col)
{
    int finishNodeNum;
    int *directions;
    // StackNode *stack = (StackNode *)malloc(sizeof(StackNode));
    StackNode *stack = NULL;

    Node *start_node = LL_Search(LL, startNodeNum);
    start_node->visit = 1;
    push(&stack, startNodeNum);
    Node *curr_node = start_node;
    int firstPopped = -1;
    int popreference = 0;

    while (!isEmpty(stack))
    {
        printf("Start of the outer while loop\n");
        int direction;
        int popped = -1;
        
        // do-while loop is for getting valid direction from filtered_direction method 
        do
        {
            printf("Start of the inner while loop\n");
            directions = filter_direction(outcome, curr_node->location, row, col);
            printf("Before shuffle: ");
            for (int i = 0; i < 4; i++) {
                if (i != 3) {
                    printf("%d ", directions[i]);
                } else {
                    printf("%d\n", directions[i]);
                }
            }
            int length = 4;
            shuffle(directions, length, 100);
            printf("After shuffle: ");
            for (int i = 0; i < 4; i++) {
                if (i != 3) {
                    printf("%d ", directions[i]);
                } else {
                    printf("%d\n", directions[i]);
                }
            }
            printf("Direction (before filter visit): %d\n", direction);
            int count = 0;
            for (int i = 0; i < length; i++)
            {   
                Node *node = LL_Search(LL, (curr_node->location) + directions[i]);
                if (count == length-1 && node->visit == 1) {
                    printf("Ready to pop\n");
                    pop(&stack);
                    popped = 1;
                    if (stack != NULL)
                    {   
                        if (popreference == 0 ) {
                            firstPopped = curr_node->location;
                        }
                        printf("Stack isn't empty\n");
                        curr_node = LL_Search(LL, stack->data);
                        printf("Current Stack Node: %d\n", curr_node->location);
                        popreference ++;
                    }
                    else
                    {
                        if (popreference == 0 ) {
                            firstPopped = curr_node->location;
                        }
                        printf("Stack empty\n");
                        finishNodeNum = firstPopped;
                        printf("Finish Node: %d\n", finishNodeNum);
                        popreference ++;
                    }
                    break;
                }
                printf("direction %d:", count+1);
                count ++;

                if (node->visit == 0)
                {
                    printf("%d\n", directions[i]);
                    direction = directions[i];
                    printf("Direction (after filter visit): %d\n", directions[i]);
                    printf("Next Node location (currnet node location + direction): %d\n", curr_node->location + directions[i]);
                    break;
                }
                else
                {
                    printf("Skip a visited node\n");
                    continue;
                }
            }
        } while (direction == 0);
        printf("***********************\n");
        if (popped != 1) {
            printf("Current Node: %d visit: %d\n", curr_node->location, curr_node->visit);
            Node *next_node = LL_Search(LL, (curr_node->location) + direction);
            printf("Next Node: %d visit: %d\n", next_node->location, next_node->visit);
            if (next_node->visit != 1)
            {
                printf("Starting Add Edge Function\n");
                add_Edge(LL, curr_node->location, next_node->location);
                printf("Add Edge %d -> %d\n", curr_node->location, next_node->location);
                add_Edge(LL, next_node->location, curr_node->location);
                printf("Add Edge %d -> %d\n", next_node->location, curr_node->location);
            }
            curr_node = next_node;
            next_node->visit = 1;
            push(&stack, curr_node->location);
            firstPopped = -1;
            popreference = 0;
        }
    }
    return finishNodeNum;
}

void print_adjacencyList(FILE *infile, int row, int col, LinkedList *LL) {
    /* write adjacency list from node(0) to node(row * col - 1)*/
    for (int i = 0; i < row * col; i++)
    {   
        Node *curr = LL_Search(LL, i);
        printf("print node%d\n", curr->location);

        EdgeNode *curr_edge = curr->edge;
        printf("print edges:\n");
        if (curr_edge == NULL)
        {
            fprintf(infile, "\n");
        }
        while (curr_edge != NULL)
        {
            if (curr_edge->next == NULL) {
                fprintf(infile, "%d\n", curr_edge->key);
            } else {
                fprintf(infile, "%d ", curr_edge->key);
            }        
            curr_edge = curr_edge->next;
        }
        curr = curr->next;
        // fprintf(infile, "This is line %d\n", i + 1);
    }
}