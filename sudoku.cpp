#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {
  
  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/* Q1 
   Function to return true if board complete, false if board incomplete */
int is_complete(char board[9][9]) {
  int row;
  int column;
  
  for (row = 0 ; row < 9 ; row++)
    for (column = 0 ; column < 9 ; column++)
      {char number = board[row][column];
       if (number > '9' || number < '1')
	 return false;
      }
  return true;
}

/* Q2 */ 

/* Function to make move, given position and digit */
int make_move(char position[3], char digit, char board[9][9]) {
  int rowmove = position[0];
  int columnmove = position[1];

  rowmove -= 'A';
  columnmove -= '1';

  if (!digittest(digit)) {
    return false; }
    
  if(!boundtest(rowmove, columnmove)) {
    return false; }
  
  if(!rowtest(rowmove, digit, board)) {
    return false; }
  
  if(!columntest(columnmove, digit, board)) {
    return false; }
  
  if(!squaretest(rowmove, columnmove, digit, board)) {
    return false; }
  
  board[rowmove][columnmove] = digit;
  return true;
  
}

/* Function to test whether digit is between 1 and 9 */
int digittest(char digit) {
  if (digit < '1' || digit > '9')
    return false;
  return true;
}

/* Function to test whether position is within board */
int boundtest(int row, int column) {
  if ((row < 0 || row > 8) || (column < 0 || column > 8))
    return false;
  return true;
}

/* Function to test whether digit is already in row */
int rowtest(int rowmove, char digit, char board[9][9]) {
  int column;
  
  for (column = 0 ; column < 9 ; column++) {
    if (board[rowmove][column] == digit)
      return false;
  }
  return true;
}

/* Function to test whether digit is already in column */
int columntest(int columnmove, char digit, char board[9][9]) {
  int row;
  
  for (row = 0 ; row < 9 ; row++) {
    if (board[row][columnmove] == digit)
      return false;
  }
  return true;
}

/* Function to test whether digit is already in 3x3 square */
int squaretest(int rowmove, int columnmove, char digit, char board[9][9]) {
  int remainderrow = rowmove % 3;
  int remaindercolumn = columnmove % 3;
  int topleftrow = rowmove - remainderrow;
  int topleftcolumn = columnmove- remaindercolumn;
  int column, row;

  for (row = 0; row < 3 ; row++) 
    for (column = 0 ; column < 3 ; column++) {
      if (board[topleftrow+row][topleftcolumn+column] == digit)
	return false;
    }
  return true;
}  


/* Q3 */

/* Function to save board */
int save_board(char filename[100], char board[9][9]) {
  ofstream out_stream;
  
  out_stream.open(filename);

  if (out_stream.fail())
    return false;
  
  for(int row = 0 ; row < 9 ; row++) {
    for(int column = 0 ; column < 9 ; column ++)
      out_stream.put(board[row][column]);
    out_stream << endl;
  }
  out_stream.close();

  return true;
}

/* Q4 */

/* Function to attempt to recursively solve sudoku. 
   Includes variable count to measure difficulty of sudoku*/
int solve_board(char board[9][9]) {

  int row, column;
  static int count = 0;
  count++;
  
  if (is_complete(board)) {
    cout << "Calls: " << count << endl;
    count = 0;
    return true; }

  if (find_element(board, row, column)) {
    for (char digit = '1' ; digit <= '9' ; digit++) {
      char position[3];
      position[0] = row + 'A';
      position[1] = column + '1';

      if (make_move(position, digit, board)) {
	if (solve_board(board))
	  return true;
	board[row][column] = '.';
      }
    }
  }
  return false;
}

/* Function to find empty element in board */
int find_element(char board[9][9], int &row, int &column) {
  
  for (row = 0 ; row < 9 ; row ++)
    for (column = 0 ; column < 9 ; column ++)
      if (board[row][column] == '.'){
	return true;}

  return false;
}
