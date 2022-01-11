#include <stdio.h>
#include <assert.h>
#include "pomoku.h"

#define MAX_BOARD_SIZE (20)
#define DEFAULT_BOARD_SIZE (15)

static int s_board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
static size_t s_valid_row_size;
static size_t s_valid_column_size;
static int s_player_score[2];

void init_game(void)
{
    size_t i;
    size_t j;
    s_valid_row_size = DEFAULT_BOARD_SIZE;
    s_valid_column_size = DEFAULT_BOARD_SIZE;

    for (i = 0; i < s_valid_row_size; i++) {
        for (j = 0; j < s_valid_column_size; j++) {
            s_board[i][j] = -1;
        }
    }

    s_player_score[0] = 0;
    s_player_score[1] = 0;
}

size_t get_row_count(void)
{
    return s_valid_row_size;
}

size_t get_column_count(void)
{
    return s_valid_column_size;
}


int get_score(const color_t color)
{
    if (color != 0 && color != 1) {
        return -1;
    }

    return s_player_score[color];
}

int get_color(const size_t row, const size_t col)
{
    return s_board[row][col];
}

int is_placeable(const size_t row, const size_t col)
{

    if (row < s_valid_row_size && col < s_valid_column_size && s_board[row][col] == -1) {
        return 1;
    } else {
        return 0;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    int valid_location;

    if (color != 1 && color != 0) {
        return 0;
    }

    valid_location = is_placeable(row, col);

    if (valid_location) {
        s_board[row][col] = color;
        counting_stone(color, row, col);
        printf("score is : %d \n", s_player_score[color]);
        return valid_location;
    } else {
        return valid_location;
    }
}

void counting_stone(const color_t color, const size_t row, const size_t col)
{
    int horizontal_score;
    int vertical_score;
    int left_diagonal_score;
    int right_diagonal_score;
    int total_score;

    horizontal_score = check_horizontal_chaining(color, row, col);
    vertical_score = check_vertical_chaining(color, row, col);
    left_diagonal_score = check_left_diagonal_chaining(color, row, col);
    right_diagonal_score = check_right_diagonal_chaining(color, row, col);
    total_score = horizontal_score + vertical_score + left_diagonal_score + right_diagonal_score;

    printf("horizontal_score is : %d \n", horizontal_score);
    printf("vertical_score is : %d \n", vertical_score);
    printf("left_diagonal_score is : %d \n", left_diagonal_score);
    printf("right_diagonal_score is : %d \n", right_diagonal_score);
    printf("total_score is : %d \n", total_score);

    s_player_score[color] += total_score;
}

int check_horizontal_chaining(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 1;
    chaining_stone_count += check_west_recursive(color, row, col);
    chaining_stone_count += check_east_recursive(color, row, col);

    if (chaining_stone_count < 5) {
        return 0;
    } else {
        return chaining_stone_count % 5 + 1;
    }
}

int check_west_recursive(const color_t color, const size_t row, size_t col)
{
    int chaining_stone_count = 0;

    if (col == 0 || s_board[row][col - 1] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_west_recursive(color, row, col - 1);
    return ++chaining_stone_count;
}

int check_east_recursive(const color_t color, const size_t row, size_t col)
{
    int chaining_stone_count = 0;

    if (col >= get_column_count() - 1 || s_board[row][col + 1] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_west_recursive(color, row, col + 1);
    return ++chaining_stone_count;
}

int check_vertical_chaining(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 1;
    chaining_stone_count += check_north_recursive(color, row, col);
    chaining_stone_count += check_south_recursive(color, row, col);

    if (chaining_stone_count < 5) {
        return 0;
    } else {
        return chaining_stone_count % 5 + 1;
    }
}

int check_north_recursive(const color_t color, size_t row, const size_t col)
{
    int chaining_stone_count = 0;

    if (row == 0 || s_board[row - 1][col] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_north_recursive(color, row - 1, col);
    return ++chaining_stone_count;
}

int check_south_recursive(const color_t color, size_t row, const size_t col)
{
    int chaining_stone_count = 0;

    if (row >= get_row_count() - 1 || s_board[row + 1][col] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_south_recursive(color, row + 1, col);
    return ++chaining_stone_count;
}

int check_left_diagonal_chaining(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 1;
    chaining_stone_count += check_north_west_recursive(color, row, col);
    chaining_stone_count += check_south_east_recursive(color, row, col);

    if (chaining_stone_count < 5) {
        return 0;
    } else {
        return chaining_stone_count % 5 + 1;
    }
}

int check_north_west_recursive(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 0;

    if (row == 0 || col == 0 || s_board[row - 1][col - 1] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_north_west_recursive(color, row - 1, col - 1);
    return ++chaining_stone_count;
}

int check_south_east_recursive(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 0;

    if (row >= get_row_count() - 1 || col >= get_column_count() - 1 || s_board[row + 1][col + 1] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_south_east_recursive(color, row + 1, col + 1);
    return ++chaining_stone_count;
}

int check_right_diagonal_chaining(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 1;
    chaining_stone_count += check_north_east_recursive(color, row, col);
    chaining_stone_count += check_south_west_recursive(color, row, col);

    if (chaining_stone_count < 5) {
        return 0;
    } else {
        return chaining_stone_count % 5 + 1;
    }
}

int check_north_east_recursive(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 0;

    if (row == 0 || col >= get_column_count() - 1 || s_board[row - 1][col + 1] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_north_east_recursive(color, row - 1, col + 1);
    return ++chaining_stone_count;
}

int check_south_west_recursive(const color_t color, size_t row, size_t col)
{
    int chaining_stone_count = 0;

    if (row >= get_row_count() - 1 || col == 0 || s_board[row + 1][col - 1] != (int)color) {
        return chaining_stone_count;
    }

    chaining_stone_count = check_south_west_recursive(color, row + 1, col - 1);
    return ++chaining_stone_count;
}
