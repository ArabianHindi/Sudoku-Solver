#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define RESET 0
int sudokuSolver();
int findEmptyCell();
int isValid();
void printGrid();
void init();
void flush_cells();
void play();
void check();
void clearsudoku();
void generate();

int grid[9][9] = {
		{0, 0, 5, 3, 0, 0, 0, 0, 0},
		{8, 0, 0, 0, 0, 0, 0, 2, 0},
		{0, 7, 0, 0, 1, 0, 5, 0, 0},
		{4, 0, 0, 0, 0, 5, 3, 0, 0},
		{0, 1, 0, 0, 7, 0, 0, 0, 6},
		{0, 0, 3, 2, 0, 0, 0, 8, 0},
		{0, 6, 0, 5, 0, 0, 0, 0, 9},
		{0, 0, 4, 0, 0, 0, 0, 3, 0},
		{0, 0, 0, 0, 0, 9, 7, 0, 0}
};



int row, col;
//this variable was used just to keep track of number of recursive calls
long int totalNumOfCalls = 0;
void play()
{

	int i, j, n, s;
	int k, l;
	int total_row[9];
	int total_col[9];
	printf("'enter the inputs of a soduko,and check whether its correct or not'\n");
	printf("\n input no of 'rows x column' \n");

	scanf("\n%d", &k);
	scanf("\t%d", &l);

	printf("values\n");
	for (i = 0; i < k; i++)
	{

		total_row[i] = 0;
		for (j = 0; j < l; j++)
		{
			if (grid[i][j] == 0)
			{
				scanf("%d", &grid[i][j]);
				system
				("cls");
				printGrid();
			}
			total_row[i] = total_row[i] + grid[i][j];

		}
	}
	for (i = 0; i < k; i++)
	{
		printf("\n");
		for (j = 0; j < l; j++)
		{
			printf(" \t %d ", grid[i][j]);
		}
	}
	check();


}

int main(void) {



	int i, j, solution = 0;
	char ch{};
	system("cls");
	while (ch != 'e')
	{

		printf("You can change the puzzle before running the program \nby changing the values in the \"grid\" array\n\n");
		printf("The Entered Sudoku puzzle is: \n");
		printGrid();
		printf("Press \n'a' to confirm and solve\n,'e' to exit\n,'b' to play\n,'c' to creat a new buzzle\n, 'd' to gnreate a random ssudoku and play it\n");
		scanf("%c", &ch);
		if (ch == 'e')
			exit(0);
		else if (ch == 'a')
		{
			system("cls");
			solution = sudokuSolver();
			if (solution)
			{
				printf("\nThe Solved Sudoku is: \n\n");
				printGrid();
			}
			clearsudoku();
		}
		else if (ch == 'b')
		{
			play();
			clearsudoku();
		}
		else if (ch == 'c')
		{
			init();
		}
		else if (ch == 'd')
		{
			generate();
		}
	}
}
int findEmptyCell() {
	int i, j;
	for (i = row; i <= 8; i++)
		for (j = 0; j <= 8; j++) {
			if (grid[i][j] == 0)
			{
				row = i; col = j;
				return 1;
			}
		}
	return 0;
}
int isValid(int cellRow, int cellCol, int num) {
	int i, j, trow, tcol, trow1, tcol1;
	int rowStart = (cellRow / 3) * 3;
	int colStart = (cellCol / 3) * 3;
	// to check the presence of number in row and column
	for (j = 0; j <= 8; j++) {
		if (grid[cellRow][j] == num)
			return 0;
		if (grid[j][cellCol] == num)
			return 0;
	}
	// to check the presence of number in 3X3 box
	for (i = rowStart; i <= rowStart + 2; i++)
		for (j = colStart; j <= colStart + 2; j++)
			if (grid[i][j] == num)return 0;
	return 1;
}
int sudokuSolver()
{
	int digit;
	int prevRow, prevCol; // for backtracking
	totalNumOfCalls++;
	if (!findEmptyCell())
		return 1;
	for (digit = 1; digit <= 9; digit++) {
		if (isValid(row, col, digit)) {
			grid[row][col] = digit;
			prevRow = row; prevCol = col;
			if (sudokuSolver())
				return 1;
			//while backtracking assigning previous values to row and col
			row = prevRow; col = prevCol;
			grid[row][col] = RESET;
		}
	}
	return 0;
}
void printGrid() {

	int i, j;

	printf("\t-------------------------\n");
	for (i = 0; i < 9; i++) {
		printf("\t");
		for (j = 0; j < 9; j++)
		{
			if (j == 0)
				printf("| ");
			if (grid[i][j] == 0)
				printf(". ");
			else
				printf("%d ", grid[i][j]);
			if ((j + 1) % 3 == 0)
				printf("| ");
		}
		if ((i + 1) % 3 == 0)
			printf("\n\t-------------------------");
		printf("\n");
	}

}
void init()
{
	int row, column;
	printf("Enter the desired sudoku and enter 0 for unknown entries\n");
	flush_cells();
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 9; column++)
		{
			scanf("%d", &grid[row][column]);
			system("cls");
			printGrid();
		}
	}
}
void check()
{
	int i, j, n;
	int total_row[9], total_col[9];
	for (i = 0; i < 9; i++)
	{
		total_row[i] = 0;
		for (j = 0; j < 9; j++)
		{
			total_row[i] = total_row[i] + grid[i][j];
		}
	}
	for (j = 0; j < 9; j++)
	{
		total_col[j] = 0;
		for (i = 0; i < 9; i++)
		{
			total_col[j] = total_col[j] + grid[i][j];
		}
	}

	for (n = 0; n < 9; n++)
	{
		if ((total_col[n]) != 45)

			printf("\n incorrect i/p's col_%d ", n + 1);
		else if ((total_row[n]) != 45)
			printf(" incorrect i/p's row_%d ", n + 1);
		else if (total_row[n] && 45 && total_col[n])
			printf("\n correct i/p for both %d row and col ", n + 1);
		else if (total_row[n] && 45)
			printf("\n correct i/p for %d row ", n + 1);
		else if (45 && total_col[n])
			printf("\n correct i/p for %d col ", n + 1);
	}
}
void flush_cells()
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			grid[i][j] = 0;
		}
	}
}
void clearsudoku()
{
	flush_cells();
	grid[0][2] = 5;
	grid[0][3] = 3;
	grid[1][0] = 8;
	grid[1][7] = 2;
	grid[2][1] = 7;
	grid[2][4] = 1;
	grid[2][6] = 5;
	grid[3][0] = 4;
	grid[3][5] = 5;
	grid[3][6] = 3;
	grid[4][1] = 1;
	grid[4][4] = 7;
	grid[4][8] = 6;
	grid[5][2] = 3;
	grid[5][3] = 2;
	grid[5][7] = 8;
	grid[6][1] = 6;
	grid[6][3] = 5;
	grid[6][8] = 9;
	grid[7][2] = 4;
	grid[7][7] = 3;
	grid[8][5] = 9;
	grid[8][6] = 7;
}
void generate()
{
	int i, randnum, n, m;
	int row, column;
	flush_cells();
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 9; column++)
		{
			n = rand() % 10;
			m = rand() % 10;
			randnum = rand() % 9;
			if (isValid(n, m, randnum))
				grid[n][m] = randnum;

		}
	}
	printGrid();
}
