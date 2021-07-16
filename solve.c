#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "solve.h"
#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"

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
    int p;
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
        if (curr_edge->key == edge)
        {
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
struct QueueNode
{
    int data;
    QueueNode *next;
};

/* Function. Adding StackNodes to each other */
QueueNode *newNode(int data)
{
    QueueNode *queueNode = (QueueNode *)malloc(sizeof(QueueNode));
    queueNode->data = data;
    queueNode->next = NULL;
    return queueNode;
}

/* Function. Checking if a node in a stack is null */
int isEmpty(QueueNode *root)
{
    return !root;
}

/* Function. To push into the Stack */
void push(QueueNode **root, int data)
{
    QueueNode *queueNode = newNode(data);
    queueNode->next = *root;
    *root = queueNode;
    printf("%d pushed to queue\n", data);
}

/* Function. To pop from the stack */
int pop(QueueNode **root)
{
    int popped;
    if (isEmpty(*root))
    {
        printf("Queue is empty\n");
        return INT_MIN;
    }
    QueueNode *temp = *root;

    // O
    if ((*root)->next == NULL)
    {
        popped = (*root)->data;
        printf("%d popped out of queue\n", popped);
        *root = NULL;
        free(temp);
        return popped;
    }

    // O O O....
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    // O O
    popped = temp->next->data;
    temp->next = NULL;

    printf("%d popped out of queue\n", popped);
    free(temp->next);

    return popped;
}

/* Function. To look into the Stack */
int peek(QueueNode *root)
{
    if (isEmpty(root))
        return INT_MIN;
    return root->data;
}

/* Function. To print out all the data within the Node's linked list */
void queue_print(QueueNode **node)
{
    QueueNode *curr = *node;
    int count = 0;

    if (curr == NULL)
    {
        printf("Queue is empty!\n");
    }

    while (curr != NULL)
    {
        printf("element %d: %d\n", count, curr->data);
        curr = curr->next;
        count += 1;
    }
    printf("\n");
};

void ReverseArray(int arr[], int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

/* Function to print out solution of the maze */
void print_solution(Node *finishNode, LinkedList *LL)
{
    // printf("Maze Solution: \n");
    Node *curr_node = finishNode;
    int size = 1;
    while (curr_node->p != -1)
    {
        // printf("%d ", curr_node->location);
        curr_node = LL_Search(LL, curr_node->p);
        size++;
    }
    printf("\n");

    printf("Array Size: %d\n", size);

    int solution[size];
    curr_node = finishNode;
    int i = 1;
    // printf("ReverseSolution: \n");
    solution[0] = curr_node->location;
    printf("%d ", solution[0]);
    while (curr_node->p != -1)
    {

        solution[i] = curr_node->p;
        
        // printf("%d ", solution[i]);
        curr_node = LL_Search(LL, curr_node->p);
        i++;
    }
    printf("\n");

    // Reverse the order of the array
    ReverseArray(solution, size);

    printf("Solution: \n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", solution[i]);
    }
}

/* Function. Depth First Search to create the maze structure */
int bfs(LinkedList *LL, int startNodeNum, int finishNodeNum, int row, int col)
{
    // QueueNode *queue = (QueueNode *)malloc(sizeof(QueueNode));
    QueueNode *queue = NULL;

    Node *start_node = LL_Search(LL, startNodeNum);
    start_node->p = -1;
    push(&queue, startNodeNum);
    // queue_print(&queue);
    Node *curr_node = start_node;

    while (!isEmpty(queue))
    {
        queue_print(&queue);
        printf("Enter bfs outer while loop...\n");
        int queueNum = pop(&queue);
        // queue_print(&queue);
        // printf("queue first num: %d\n", queueNum);

        curr_node = LL_Search(LL, queueNum);
        EdgeNode *neighbor = curr_node->edge;
        printf("current Node: %d\nneighbors:\n", curr_node->location);
        // Check every edge of the current node
        while (neighbor != NULL)
        {
            // printf("Enter bfs inner while loop...\n");
            int neighborNum = neighbor->key;
            printf("neighbor: %d ", neighborNum);
            // Current node's neighbor (A neighbor of the node just popped)
            Node *neighborNode = LL_Search(LL, neighborNum);
            int isVisit = neighborNode->visit;
            // if the neighbor is unvisited, then it should be the next node to be enqueued
            if (isVisit == 0)
            {
                printf("not visited\n");
                push(&queue, neighborNum);
                // If we found the finish node, then the bfs method terminates
                if (neighbor->key == finishNodeNum)
                {
                    neighborNode = LL_Search(LL, neighbor->key);
                    neighborNode->p = curr_node->location;
                    printf("Final node found: %d\n", neighborNode->location);
                    print_solution(neighborNode, LL);
                    return 1;
                }
                // Put predecessor reference of the current node's nighbor to the current node
                neighborNode->p = curr_node->location;
            }
            // if this neighbor is visited, then search for another available neighbor
            else
            {
                printf("visited and skipped\n");
            }
            // Search next edges of the current node
            neighbor = neighbor->next;
        }
        // Mark the current node as visited
        curr_node->visit = 1;
    }
    printf("BFS failed\n");
    return 0;
}

/* Read data from text file and add node to adjacency list and add edges to the nodes */
void read_data(FILE *infile, LinkedList *LL, int row, int col, int start, int finish)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int index = 0;
    // Read line by line by getline method
    while ((read = getline(&line, &len, infile)) != -1)
    {
        // Split string into char
        char *charInt = strtok(line, " ");
        // Index 0 reads in row, and col
        if (index == 0)
        {
            // Utilize innerIndex to judge which one is row/col
            int innerIndex = 0;
            while (charInt)
            {
                if (innerIndex == 0)
                {
                    row = atoi(charInt);
                }
                else
                {
                    col = atoi(charInt);
                }
                charInt = strtok(NULL, " ");
                innerIndex++;
            }
        }
        // Index 1 reads in start and finish 1-d index
        else if (index == 1)
        {
            // Utilize inner index to see which one is start/finish
            int innerIndex = 0;
            while (charInt)
            {
                if (innerIndex == 0)
                {
                    start = atoi(charInt);
                }
                else
                {
                    finish = atoi(charInt);
                }
                charInt = strtok(NULL, " ");
                innerIndex++;
            }
        }
        // Starting from index 2, the function start to reads the node and its edges.
        else if (index > 1)
        {
            // Print out row/col/start/finish reading in from index 0 & 2 iterations.
            if (index == 2)
            {
                printf("Row: %d\n", row);
                printf("Col: %d\n", col);
                printf("Start: %d\n", start);
                printf("Finish: %d\n", finish);
            }

            // Create node instance to the adjacency list
            LL_insert(LL, index - 2);
            printf("Node: %d\n", index - 2);
            printf("Edges: ");
            // Loop all the chars from one line string and tranform them into integers, which is stored into edges
            while (charInt)
            {
                // printf("charInt: %s", charInt);
                printf("%d ", atoi(charInt));
                // atoi() tranforms char into int and add the integer to the edges
                add_Edge(LL, index - 2, atoi(charInt));
                charInt = strtok(NULL, " ");
            }
            printf("\n");
        }
        index++;
    }

    if (line)
        free(line);

    printf("Row: %d\n", row);
    printf("Col: %d\n", col);
    printf("Start: %d\n", start);
    printf("Finish: %d\n", finish);

    LL_print(LL);
    // Use Breadth First Search Algorithm to find the finish node from a given start node.
    // Establish the predecessors for solution reference
    // Print the solution from a within helper function (print_solution)
    // bfs(LL, start, finish, row, col);
    bfs(LL, start, finish, row, col);

    fclose(infile);
}
