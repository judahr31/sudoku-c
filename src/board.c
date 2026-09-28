#include "board.h"

#include <stdlib.h>

int board_coordinates_in_range(int row, int column) {
    return row >= 0 && row < SUDOKU_SIZE &&
           column >= 0 && column < SUDOKU_SIZE;
}

SudokuBoard *board_create(void) {
    /* STUDENT TODO 1: Implement the complete board constructor. */
    SudokuBoard *board = malloc(sizeof(*board));
    if (board == NULL) {
        return NULL;
    }
    board->cells = calloc(SUDOKU_CELL_COUNT, sizeof(int));
    if (board->cells == NULL) {
        free(board);
        return NULL;
    }
    return board;
}

SudokuBoard *board_clone(const SudokuBoard *source) {
    /* STUDENT TODO 3: Return a separate board with independent cell storage. */
    if (source == NULL || source->cells == NULL) {
        return NULL;
    }
    SudokuBoard *board = board_create();
    if (board == NULL) {
        return NULL;
    }
    if (board_copy(board, source) == 1) {
        return board;
    } else {
        board_destroy(&board);
        return NULL;
    }
}

void board_destroy(SudokuBoard **board_ptr) {
    /* STUDENT TODO 1: Release a board and clear the caller's pointer. */
    if (board_ptr == NULL || (*board_ptr) == NULL) {
        return;
    }
    free((*board_ptr)->cells);
    free(*board_ptr);
    *board_ptr = NULL;
    return;
}

int *board_cell(SudokuBoard *board, int row, int column) {
    /* STUDENT TODO 2: Return the mutable cell pointer for this coordinate. */
    if (board == NULL || board->cells == NULL || !board_coordinates_in_range(row, column)) {
        return NULL;
    }
    int index = row * SUDOKU_SIZE + column;
    return board->cells + index;
}

const int *board_cell_const(const SudokuBoard *board, int row, int column) {
    /* STUDENT TODO 2: Return the read-only cell pointer for this coordinate. */
    if (board == NULL || board->cells == NULL || !board_coordinates_in_range(row, column)) {
        return NULL;
    }
    int index = row * SUDOKU_SIZE + column;
    return board->cells + index;
}

void board_clear(SudokuBoard *board) {
    int *cursor;
    int *end;

    if (board == NULL || board->cells == NULL) {
        return;
    }

    cursor = board->cells;
    end = board->cells + SUDOKU_CELL_COUNT;

    while (cursor < end) {
        *cursor = SUDOKU_EMPTY;
        cursor++;
    }
}

int board_copy(SudokuBoard *destination, const SudokuBoard *source) {
    if (destination == NULL || destination->cells == NULL ||
        source == NULL || source->cells == NULL) {
        return 0;
    }

    for (size_t index = 0; index < SUDOKU_CELL_COUNT; index++) {
        destination->cells[index] = source->cells[index];
    }

    return 1;
}

int board_equal(const SudokuBoard *first, const SudokuBoard *second) {
    if (first == NULL || first->cells == NULL ||
        second == NULL || second->cells == NULL) {
        return 0;
    }

    for (size_t index = 0; index < SUDOKU_CELL_COUNT; index++) {
        if (first->cells[index] != second->cells[index]) {
            return 0;
        }
    }

    return 1;
}
