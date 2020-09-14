void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* add your functions here */

/* Q1 */
int is_complete(char board[9][9]);

/* Q2 */

int make_move(char position[3], char digit, char board[9][9]);
int digittest(char digit);
int boundtest(int row, int column);
int rowtest(int rowmove, char digit, char board[9][9]);
int columntest(int columnmove, char digit, char board[9][9]);
int squaretest(int rowmove, int columnmove, char digit, char board[9][9]);

/* Q3 */
int save_board(char filename[100], char board[9][9]);

/* Q4 */
int solve_board(char board[9][9]);
int find_element(char board[9][9], int& row, int& column);
