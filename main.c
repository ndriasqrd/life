#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Constants
#define GRID_SIZE 10

typedef struct cell_s {
    int state;
    int newState;
} cell;

cell new_cell() {
    cell new;
    new.state = 0;
    new.newState = 0;

    return new;
}

void print_grid(int grid_size, cell **grid) {
    for (int r = 0; r < grid_size; r++) {
        for (int c = 0; c < grid_size; c++) {
            printf("%s ", grid[r][c].state == 1 ? "*" : "-");
        }
        printf("\n");
    }
    printf("\n");
}

void do_step(cell **grid, int grid_size) {

    int aliveNeighbours = 0;

    for (int row = 0; row < grid_size; row++) {
        for (int col = 0; col < grid_size; col++) {
            aliveNeighbours = 0;

            if (row - 1 > 0) {
                aliveNeighbours += grid[row - 1][col - 1].state;
                aliveNeighbours += grid[row - 1][col].state;
                aliveNeighbours += grid[row - 1][col + 1].state;
            }

            if (row + 1 < grid_size) {
                aliveNeighbours += grid[row + 1][col - 1].state;
                aliveNeighbours += grid[row + 1][col].state;
                aliveNeighbours += grid[row + 1][col + 1].state;
            }

            if (col - 1 > 0) {
                aliveNeighbours += grid[row][col - 1].state;
            }

            if (col + 1 < grid_size) {
                aliveNeighbours += grid[row][col + 1].state;
            }

            if (aliveNeighbours < 2) {
                grid[row][col].newState = 0;
            } else if (aliveNeighbours > 3) {
                grid[row][col].newState = 0;
            } else if (aliveNeighbours == 3) {
                grid[row][col].newState = 1;
            }

        }
    }

    for (int row = 0; row < grid_size; row++) {
        for (int col = 0; col < grid_size; col++) {
            grid[row][col].state = grid[row][col].newState;
        }
    }
}

int main() {
    cell **grid = (cell **)malloc(GRID_SIZE * sizeof(cell *));

    for (int r = 0; r < GRID_SIZE; r++) {
        grid[r] = (cell*)malloc(GRID_SIZE * sizeof(cell));

        for (int c = 0; c < GRID_SIZE; c++) {
            cell new = {rand() % 2, 0};
            grid[r][c] = new;
        }
    }

    int i = 0;

    while (1) {
        printf("************************ %d ************************\n", i);
        print_grid(GRID_SIZE, grid);
        do_step(grid, GRID_SIZE);
        sleep(1);
        i++;
    }

    return 1;
}
