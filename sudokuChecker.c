/**
 * Name: sudokuChecker.c
 * Authors:  Teresa Condon, Kieran Losh
 * Date: 2/16/17
  *
 * ========================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
  * holds checks for threads
  */
typedef struct
{
    int row;
    int col;
    // pointer does not allow modify
        int (* board)[9];
          } checks;

// function prototypes
void * checkRows(void * checks);
void * checkCols(void * checks);
void * checkSquare(void * checks);

int sudokuChecker(void)
{
  //works
   int board[9][9] = {
            {6, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 4, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
        };

    // all subsections access board
    checks * check0 = (checks *) malloc(sizeof (checks));
    check0->row = 0;
    check0->col = 0;
    check0->board = board;

    // First 3x3
    checks * check1 = (checks *) malloc(sizeof(checks));
    check1->row = 0;
    check1->col = 0;
    check1->board = board;

    // Second 3x3
    checks * check2 = (checks *) malloc(sizeof(checks));
    check2->row = 0;
    check2->col = 3;
    check2->board = board;

    // Third 3x3
    checks * check3 = (checks *) malloc(sizeof(checks));
    check3->row = 0;
    check3->col = 6;
    check3->board = board;

    // Fourth 3x3
    checks * check4 = (checks *) malloc(sizeof(checks));
    check4->row = 3;
    check4->col = 0;
    check4->board = board;

    // Fifth 3x3
    checks * check5 = (checks *) malloc(sizeof(checks));
    check5->row = 3;
    check5->col = 3;
    check5->board = board;

    // Sixth 3x3
    checks * check6 = (checks *) malloc(sizeof(checks));
    check6->row = 3;
    check6->col = 6;
    check6->board = board;

    // Seventh 3x3
    checks * check7 = (checks *) malloc(sizeof(checks));
    check7->row = 6;
    check7->col = 0;
    check7->board = board;

    // Eighth 3x3
    checks * check8 = (checks *) malloc(sizeof(checks));
    check8->row = 6;
    check8->col = 3;
    check8->board = board;

    // Ninth 3x3
    checks * check9 = (checks *) malloc(sizeof(checks));
    check9->row = 6;
    check9->col = 6;
    check9->board = board;

    // check
    pthread_t thread_rows, thread_cols, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;    void * all_rows;
    void * all_cols;
    void * square1;
    void * square2;
    void * square3;
    void * square4;
    void * square5;
    void * square6;
    void * square7;
    void * square8;
    void * square9;

    // start checks using same board
    pthread_create(&thread_rows, NULL, checkRows, (void *) check0);
    pthread_create(&thread_cols, NULL, checkCols, (void *) check0);
    pthread_create(&thread1, NULL, checkSquare, (void *) check1);
    pthread_create(&thread2, NULL, checkSquare, (void *) check2);
    pthread_create(&thread3, NULL, checkSquare, (void *) check3);
    pthread_create(&thread4, NULL, checkSquare, (void *) check4);
    pthread_create(&thread5, NULL, checkSquare, (void *) check5);
    pthread_create(&thread6, NULL, checkSquare, (void *) check6);
    pthread_create(&thread7, NULL, checkSquare, (void *) check7);
    pthread_create(&thread8, NULL, checkSquare, (void *) check8);
    pthread_create(&thread9, NULL, checkSquare, (void *) check9);

    // Wait for checks
    pthread_join(thread_rows, &all_rows);
    pthread_join(thread_cols, &all_cols);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);

    // then combine
        if (    (int) all_rows == 1 &&
            (int) all_cols == 1 &&
            (int) square1 == 1 &&
            (int) square2 == 1 &&
            (int) square3 == 1 &&
            (int) square4 == 1 &&
            (int) square5 == 1 &&
            (int) square6 == 1 &&
            (int) square7 == 1 &&
            (int) square8 == 1 &&
            (int) square9 == 1 ) {
        printf("The Sudoku Puzzle is solved!\n");
    }
    else {
        printf("The Sudoku Puzzle is NOT solved.\n");
    }

    return 0;
}

/**
 * Checks each row if it contains all digits 1-9.
 */
void * checkRows(void * checks) {
    checks * data = (checks *) malloc(sizeof (checks));
    int startRow = data->row;
    // allows modify startRow w/o board modify
    int startCol = data->col;
    for (int i = startRow; i < 9; ++i) {
        int row[10] = {0};
        for (int j = startCol; j < 9; ++j) {
            int val = data->board[i][j];
            if (row[val] != 0) {
              // > digit
                return (void *) 0;
            }
            else{
                row[val] = 1;
            }
        }
    }
    return (void *) 1;
}
void * checkCols(void * checks) {
    checks * data = (checks *) malloc(sizeof (checks));
    int startRow = data->row;
    int startCol = data->col;
    for (int i = startCol; i < 9; ++i) {
        int col[10] = {0};
        for (int j = startRow; j < 9; ++j) {
            int val = data->board[j][i];
            if (col[val] != 0) {
                return (void *) 0;
            }
            else{
                col[val] = 1;
            }
        }
    }
    return (void *) 1;
}

/**
 * Checks if a square of size 3x3 contains all numbers from 1-9.
  */
void * checkSquare(void * checks) {
    checks * data = (checks *) malloc(sizeof (checks));
    int startRow = data->row;
    int startCol = data->col;
    int subsection[10] = {0};
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            int val = data->board[i][j];
            if (subsection[val] != 0) {
                return (void *) 0;
            }
            else{
                subsection[val] = 1;
            }
        }
    }
    return (void *) 1;
}
