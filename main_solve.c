#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "solve.h"

#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"

int main(int argc, char **argv)
{
    int row, col;
    int start, finish;
    // Here we check to be sure that the correct number of arguments have been
    // passed in from the command line.
    if (argc != 2)
    {
        fprintf(stderr, "\nYou must pass in a maze readin filename to this program.\n");
        return 1;
    }

    // This opens the file for reading. A return value of NULL indicates the file
    // failed to open for some reason, in which case we print out the error and
    // return an error status.
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
        perror("Failed to open file");
        return 2;
    }

    /*#########################################################
                        Start of Maze Solution
    ##########################################################*/
    // Create a linkedlist instance adding all the nodes by sequence
    LinkedList *LL = LL_create();
    
    // Read in the data declared from command line and put all the data to nodes in linkedlist
    read_data(infile, LL, row, col, start, finish);
   
    // printf("Row: %d\n", row);
    // printf("Col: %d\n", col);
    // printf("Start: %d\n", start);
    // printf("Finish: %d\n", finish);

    // Use Breadth First Search Algorithm to find the finish node from a given start node.
    // Establish the predecessors for solution reference
    // Print the solution from a within helper function (print_solution)
    // bfs(LL, start, finish, row, col);

    return 0;
}