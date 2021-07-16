#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "generate.h"

int main(int argc, char **argv)
{
    int row, col;
    // Here we check to be sure that the correct number of arguments have been
    // passed in from the command line.
    if (argc != 4)
    {
        fprintf(stderr, "\nYou must pass your row, col, and filename to this program.\n");
        return 1;
    }

    // Switch char to int
    row = atoi(argv[1]);
    col = atoi(argv[2]);
    printf("%d\n", row);
    printf("%d\n", col);

    // Test for adding node to the linklist and to add edge node to the node in the linkedlist
    LinkedList *adjacencyList = LL_create();
    for (int i = 0; i < row * col; i++)
    {
        LL_insert(adjacencyList, i);
        // add_Edge(adjacencyList, i, 100);
    }

    // Generate a starting point
    int nodeTotalNum[row * col];
    int startNode;
    int finishNode;
    int outcome[4];

    for (int i = 0; i < row * col; i++) {
        nodeTotalNum[i] = i;
    }
    shuffle(nodeTotalNum, row * col, 100);
    startNode = nodeTotalNum[0];
    printf("Starting Node: %d\n", startNode);

    // Generate random road mapping position.
    int nums[4] = {1, -1, col, -col};
    shuffle(nums, 4, 100);
    // printf("Random Direction: %d\n", nums[0]);
    printf("Starting DFS...\n");
    
    finishNode = dfs(adjacencyList, startNode, outcome, row, col);
    
    // Prints out the adjacency list
    LL_print(adjacencyList);

    // This opens the file for reading. A return value of NULL indicates the file
    // failed to open for some reason, in which case we print out the error and
    // return an error status.
    FILE *infile = fopen(argv[3], "w");
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open the file:\t%s\n", argv[3]);
        perror("Failed to open file");
        return 2;
    }

    // Show row and col in the first line of the txt file
    fprintf(infile, "%d %d\n", row, col);
    
    // Show the start and end node location in the second line of the txt file
    fprintf(infile, "%d %d\n", startNode, finishNode);

    print_adjacencyList(infile, row, col, adjacencyList);

    /* close the file*/
    fclose(infile);
    return 0;
}