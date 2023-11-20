#include <stdio.h>
#include <stdlib.h>

/*
Knight distance using the BFS algorithm
 
The program prints the “knight distance” of all the cells of a chessboard from a given initial cell.
The initial cell is passed as a command line argument (two integers, the row and the column of the cell).
*/

// 1. Declaration of the data structures used in the program

struct bfs {                    /* Breadth-first search data */
    struct bfs * prev;          /* previous element in the BFS */
    int dist;                   /* hop-distance from the starting point */
};

struct pos {                    /* position for each cell on a chessboard */
    int row;
    int col;
};

const struct pos knight_moves [8] = {
    {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}
}; /* array of all possible moves of the knight (handled as a vector) */

// Check if the position on the matrix is valid or not
static int valid_pos (int r, int c) {
    return (r >= 0 && r < 8 && c >= 0 && c < 8);
}

//2. Main function initialization and execution
int main (int argc, char * argv[]) {
    int r = 0, c = 0;           /* default initial position  */
    if (argc > 1)               /* read initial pos (row and column) */
        r = atoi(argv[1]);      /* from command line arguments      */
    if (argc > 2)
        c = atoi(argv[2]);
    if (!valid_pos(r, c))
        return EXIT_FAILURE;

    struct bfs board[8][8];         /* 8 by 8 chessboard */

    for (int i = 0; i < 8; ++i) /* initialize the board */
        for (int j = 0; j < 8; ++j) 
            board[i][j].prev = NULL;

    // 3. BFS algorithm

    // 3.a Declaration of support queue structure
    struct pos Q[8*8];          /* support queue used in BFS */
    struct pos * head = Q;
    struct pos * tail = Q;

    tail->row = r;              /* we start from the initial positions: */
    tail->col = c;              /* enqueue(r,c) operation on the initial position */
    ++tail;
    board[r][c].prev = &(board[r][c]);  /* 'prev' of the start pos is itself */
    board[r][c].dist = 0;

    // 3.b algorithm execution
    while (head != tail) {      /* while the queue is not empty */
        r = head->row;          /* r,c <-- dequeue() */
        c = head->col;
        ++head;
        for (int i = 0; i < 8; ++i) {
            int next_r = r + knight_moves[i].row;
            int next_c = c + knight_moves[i].col;
            if (valid_pos(next_r, next_c) && board[next_r][next_c].prev == NULL) {
                tail->row = next_r;             /* enqueue(next_r,next_c) */
                tail->col = next_c;
                ++tail;
                board[next_r][next_c].prev = &(board[r][c]);
                board[next_r][next_c].dist = board[r][c].dist + 1;
            }
        }
    }     

    for (unsigned i = 0; i < 8; ++i) {   /* now print the distances of all the cells */
        for (unsigned j = 0; j < 8; ++j)
            printf ("%3d",board[i][j].dist);
        printf("\n");
    }
}