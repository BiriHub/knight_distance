#include <stdio.h>
#include <stdlib.h>

/*
//
// Knight distance using the BFS algorithm
//
*/

/*
The program prints the “knight distance” of all the cells of a chessboard from a given initial cell.
The initial cell is passed as a command line argument (two integers, the row and the column of the cell).
*/



struct bfs {                    /* Breadth-first search data */
    struct bfs * prev;          /* previous element in the BFS */
    int dist;                   /* hop-distance from the starting point */
};

struct pos {                    /* position or vector on a chessboard */
    int row;
    int col;
};

const struct pos knight_moves [8] = {
    {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}
};

static int valid_pos (int r, int c) { /* static means "private" here... */
    return (r >= 0 && r < 8 && c >= 0 && c < 8);
}

int main (int argc, char * argv[]) {
    int r = 2, c = 1;           /* default initial position  */
    if (argc > 1)               /* read initial pos (row and column) */
        r = atoi(argv[1]);      /* from command line arguments       */
    if (argc > 2)
        c = atoi(argv[2]);
    if (!valid_pos(r, c))
        return EXIT_FAILURE;

    struct bfs K[8][8];         /* 8 by 8 board */

    for (int i = 0; i < 8; ++i) /* clear the board */
        for (int j = 0; j < 8; ++j) 
            K[i][j].prev = NULL;

    struct pos Q[8*8];          /* queue of board positions used in BFS */
    struct pos * head = Q;
    struct pos * tail = Q;

    tail->row = r;              /* we start from the initial positions: */
    tail->col = c;              /* enqueue(initr,c) */
    ++tail;
    K[r][c].prev = &(K[r][c]);  /* 'prev' of the start pos is itself */
    K[r][c].dist = 0;

    while (head != tail) {      /* while the queue is not empty */
        r = head->row;          /* r,c <-- dequeue() */
        c = head->col;
        ++head;
        for (int i = 0; i < 8; ++i) {
            int next_r = r + knight_moves[i].row;
            int next_c = c + knight_moves[i].col;
            if (valid_pos(next_r, next_c) && K[next_r][next_c].prev == NULL) {
                tail->row = next_r;             /* enqueue(next_r,next_c) */
                tail->col = next_c;
                ++tail;
                K[next_r][next_c].prev = &(K[r][c]);
                K[next_r][next_c].dist = K[r][c].dist + 1;
            }
        }
    }                   
    for (r = 0; r < 8; ++r) {   /* now print the distances of all the cells */
        for (c = 0; c < 8; ++c)
            printf ("%3d",K[r][c].dist);
        printf("\n");
    }
}