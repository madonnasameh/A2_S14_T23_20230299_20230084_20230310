#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <unordered_set>
#include <set>
#include <cctype>
#include <algorithm>

using namespace std;

/////////////////////////////////////////////////////////////////// Number 1 ///////////////////////////////////////////////////

void printBoard1(const vector<vector<char>> &board)
{
    for (size_t i = 0; i < board.size(); ++i)
    {
        for (size_t j = 0; j < board.size() - i - 1; ++j)
        {
            cout << "  ";
        }
        for (char cell : board[i])
        {
            cout << (cell == ' ' ? '.' : cell) << " ";
        }
        cout << endl;
    }
}

bool checkWin(const vector<vector<char>> &board, char player)
{
    for (size_t i = 0; i < board.size(); ++i)
    {
        for (size_t j = 0; j + 2 < board[i].size(); ++j)
        {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player)
                return true;
        }
    }

    if (board[2][1] == player && board[1][0] == player && board[0][0] == player)
        return true;
    if (board[2][3] == player && board[1][2] == player && board[0][0] == player)
        return true;

    for (size_t col = 0; col < board[2].size(); ++col)
    {
        if (col < board[1].size() && board[2][col] == player && board[1][col] == player && board[0][0] == player)
            return true;
    }

    return false;
}

bool getUserInput(int &row, int &col, const vector<vector<char>> &board)
{
    cout << "Enter your move (row, col) starting from base (1-indexed): ";
    cin >> row >> col;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter numeric values for row and column.\n";
        return false;
    }

    row = 3 - row;
    col -= 1;

    if (row < 0 || row >= board.size() || col < 0 || col >= board[row].size() || board[row][col] != ' ')
    {
        cout << "Invalid move. Try again.\n";
        return false;
    }

    return true;
}

int game1()
{
    vector<vector<char>> board = {
        {' '},
        {' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}};

    string player1Name, player2Name;
    cout << "Enter name for Player 1 (X): ";
    cin >> player1Name;
    cout << "Enter name for Player 2 (O): ";
    cin >> player2Name;

    char currentPlayer = 'X';
    int moves = 0;

    while (moves < 9)
    {
        printBoard1(board);

        cout << "It's " << (currentPlayer == 'X' ? player1Name : player2Name) << "'s turn (" << currentPlayer << ")\n";

        int row, col;

        while (!getUserInput(row, col, board))
        {

        }

        board[row][col] = currentPlayer;
        moves++;

        if (checkWin(board, currentPlayer))
        {
            printBoard1(board);
            cout << "Player " << (currentPlayer == 'X' ? player1Name : player2Name) << " wins\n";
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    if (moves == 9)
    {
        cout << "It's a draw!\n";
    }

    return 0;
}

/////////////////////////////////////////////////////////////////// Number 2 ///////////////////////////////////////////////////

int boardd[6][7];
int input;
string playerNamee[2]; 
int currentPlayerr = 1;
bool GameEnds = false;

void InitializeBoards()
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            boardd[i][j] = 0;
}

bool HandleInput(int input)
{
    for (int i = 5; i >= 0; i--)
    {
        if (boardd[i][input] == 0)
        {
            boardd[i][input] = currentPlayerr;
            return true; 
        }
    }
    cout << "Column is full! Try another column.\n";
    return false; 
}

bool CheckWinner()
{
    // Check horizontal
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            if (boardd[i][j] == currentPlayerr && boardd[i][j + 1] == currentPlayerr &&
                boardd[i][j + 2] == currentPlayerr && boardd[i][j + 3] == currentPlayerr)
                return true;

    // Check vertical
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 7; j++)
            if (boardd[i][j] == currentPlayerr && boardd[i + 1][j] == currentPlayerr &&
                boardd[i + 2][j] == currentPlayerr && boardd[i + 3][j] == currentPlayerr)
                return true;

    // Check diagonal (\ direction)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            if (boardd[i][j] == currentPlayerr && boardd[i + 1][j + 1] == currentPlayerr &&
                boardd[i + 2][j + 2] == currentPlayerr && boardd[i + 3][j + 3] == currentPlayerr)
                return true;

    // Check diagonal (/ direction)
    for (int i = 3; i < 6; i++)
        for (int j = 0; j < 4; j++)
            if (boardd[i][j] == currentPlayerr && boardd[i - 1][j + 1] == currentPlayerr &&
                boardd[i - 2][j + 2] == currentPlayerr && boardd[i - 3][j + 3] == currentPlayerr)
                return true;

    return false;
}

void draw()
{
    cout << "  ";
    for (int j = 0; j < 7; j++)
        cout << j + 1 << "   ";
    cout << endl;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (boardd[i][j] == 0)
                cout << "|   ";
            else if (boardd[i][j] == 1)
                cout << "| X ";
            else if (boardd[i][j] == 2)
                cout << "| O ";
        }
        cout << "|\n";
    }
    cout << "-------------------------------\n";
}

int game2()
{
    cout << "Enter name for Player 1 (X): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, playerNamee[0]);

    cout << "Enter name for Player 2 (O): ";
    getline(cin, playerNamee[1]);

    InitializeBoards();
    GameEnds = false;
    currentPlayerr = 1; 

    while (!GameEnds)
    {
        draw();
        cout << playerNamee[currentPlayerr - 1] << "'s turn (" << (currentPlayerr == 1 ? 'X' : 'O') << "): ";

        if (!(cin >> input) || input < 1 || input > 7)
        {
            cin.clear();                                         
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Enter a number between 1 and 7.\n";
            continue;
        }

        if (!HandleInput(input - 1))
        {
            continue; 
        }

        if (CheckWinner())
        {
            draw();
            cout << playerNamee[currentPlayerr - 1] << " wins!\n";
            GameEnds = true;
        }
        else
        {
            currentPlayerr = (currentPlayerr == 1 ? 2 : 1); 
        }
    }

    cout << "Thanks for playing!\n";
    return 0;
}
/////////////////////////////////////////////////////////////////// Number 3 ///////////////////////////////////////////////////

class Player
{
public:
    string name;
    char symbol; 

    Player(string n, char s) : name(n), symbol(s) {}
};

class TicTacToee
{
private:
    vector<vector<char>> board; 
    Player *player1;
    Player *player2;
    Player *currentPlayer;

    void displayBoard()
    {
        cout << "    0   1   2   3   4" << endl;
        cout << "  ---------------------" << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << i << " | ";
            for (int j = 0; j < 5; j++)
            {
                cout << board[i][j];
                if (j < 4)
                    cout << " | ";
            }
            cout << " |" << endl;
            cout << "  ---------------------" << endl;
        }
    }

    int countThreeInARow(char symbol)
    {
        int count = 0;

        // Check horizontally
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol)
                {
                    count++;
                }
            }
        }

        // Check vertically
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol)
                {
                    count++;
                }
            }
        }

        // Check diagonally
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol)
                {
                    count++;
                }
                if (board[i][j + 2] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j] == symbol)
                {
                    count++;
                }
            }
        }

        return count;
    }

    int getValidIntegerInput(const string &prompt)
    {
        int value;
        while (true)
        {
            cout << prompt;
            cin >> value;

            if (cin.fail() || value < 0 || value > 4)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 0 and 4." << endl;
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
    }

public:
    TicTacToee(string name1, string name2)
    {
        player1 = new Player(name1, 'X');                      
        player2 = new Player(name2, 'O');                      
        currentPlayer = player1;                               
        board = vector<vector<char>>(5, vector<char>(5, ' ')); 
    }

    void playGame()
    {
        int row, col;
        int moves = 0;

        while (moves < 24)
        { 
            displayBoard();
            cout << "Turn for " << currentPlayer->name << " (" << currentPlayer->symbol << ")." << endl;
            row = getValidIntegerInput("Enter row (0-4): ");
            col = getValidIntegerInput("Enter column (0-4): ");

       
            if (board[row][col] == ' ')
            {
                board[row][col] = currentPlayer->symbol;
                moves++;
            }
            else
            {
                cout << "Invalid move. Cell already occupied. Try again." << endl;
                continue;
            }

            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }

        displayBoard();

        int countX = countThreeInARow('X');
        int countO = countThreeInARow('O');
        cout << "Player X has " << countX << " three-in-a-row sequences." << endl;
        cout << "Player O has " << countO << " three-in-a-row sequences." << endl;

        if (countX > countO)
        {
            cout << "Player X wins!" << endl;
        }
        else if (countO > countX)
        {
            cout << "Player O wins!" << endl;
        }
        else
        {
            cout << "It's a draw!" << endl;
        }
    }
};

int game3()
{
    string player1Name, player2Name;

    cout << "Enter name for Player 1 (X): ";
    cin >> player1Name;
    cout << "Enter name for Player 2 (O): ";
    cin >> player2Name;

    TicTacToee game(player1Name, player2Name);
    game.playGame();

    return 0;
}

/////////////////////////////////////////////////////////////////// Number 4 ///////////////////////////////////////////////////
unordered_set<string> loadWords()
{
    unordered_set<string> wordList;
    string filename;

    cout << "Enter the name of the dictionary file: ";
    cin >> filename;

    ifstream file(filename);
    string word;

    if (!file)
    {
        cerr << "Error: Unable to open dictionary file: " << filename << endl;
        exit(1);
    }

    while (file >> word)
    {
        if (word.length() == 3)
        {
            wordList.insert(word);
        }
    }

    return wordList;
}

void displayBoard(char **grid)
{
    cout << "  1 2 3" << endl;

    for (int i = 0; i < 3; ++i)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j)
        {
            cout << (grid[i][j] == ' ' ? '.' : grid[i][j]) << " ";
        }
        cout << endl;
    }
}

string extractWord(char **grid, int startX, int startY, int dx, int dy)
{
    string word;
    for (int i = 0; i < 3; ++i)
    {
        word += grid[startX + i * dx][startY + i * dy];
    }
    return word;
}

bool isWordFormed(char **grid, const unordered_set<string> &wordList)
{
    for (int i = 0; i < 3; ++i)
    {
        if (wordList.count(extractWord(grid, i, 0, 0, 1)) ||
            wordList.count(extractWord(grid, 0, i, 1, 0)))
        {
            return true;
        }
    }

    return wordList.count(extractWord(grid, 0, 0, 1, 1)) ||
           wordList.count(extractWord(grid, 0, 2, 1, -1));
}

int getValidInput(const string &prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        }
        else
        {
            return value;
        }
    }
}

char getValidLetter(const string &prompt)
{
    char letter;
    while (true)
    {
        cout << prompt;
        cin >> letter;

        if (isdigit(letter))
        {
            cout << "Invalid input. Please enter a letter (not a number).\n";
            continue;
        }

        return letter;
    }
}

int game4()
{
    string player1, player2;
    cout << "Enter the name of Player 1: ";
    cin >> player1;
    cout << "Enter the name of Player 2: ";
    cin >> player2;

    char **grid = new char *[3];
    for (int i = 0; i < 3; ++i)
    {
        grid[i] = new char[3]{' ', ' ', ' '};
    }

    unordered_set<string> wordList = loadWords();
    int turnCount = 0;

    cout << "Welcome to Word Tic-Tac-Toe\n";
    displayBoard(grid);

    while (turnCount < 9)
    {
        int row, col;
        char letter;

        string currentPlayer = (turnCount % 2 == 0) ? player1 : player2;
        char symbol = (turnCount % 2 == 0) ? 'X' : 'O';

        cout << currentPlayer << "'s turn (" << symbol << ").\n";

        row = getValidInput("Enter row (1:3) ", 1, 3);
        col = getValidInput("Enter column (1:3) ", 1, 3);

        if (grid[row - 1][col - 1] != ' ')
        {
            cout << "Cell already occupied. Try again.\n";
            continue;
        }

        letter = getValidLetter("Enter a letter: ");

        grid[row - 1][col - 1] = letter;
        displayBoard(grid);

        if (isWordFormed(grid, wordList))
        {
            cout << currentPlayer << " is the winner!\n";

            for (int i = 0; i < 3; ++i)
            {
                delete[] grid[i];
            }
            delete[] grid;

            return 0;
        }

        ++turnCount;
    }

    cout << "It's a draw! No valid word formed.\n";

    for (int i = 0; i < 3; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}

/////////////////////////////////////////////////////////////////// Number 5 ///////////////////////////////////////////////////
int board[3][3];                          
string playerNames[2];                    
int currentPlayer = 1;                    
set<int> usedNumbers;                    
vector<int> oddNumbers = {1, 3, 5, 7, 9}; 
vector<int> evenNumbers = {2, 4, 6, 8};   
bool GameEnd = false;                    

bool isValidName(const string &name)
{
    return !name.empty() && all_of(name.begin(), name.end(), ::isalpha);
}

void InitializeBoard()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = 0;

    usedNumbers.clear();
    oddNumbers = {1, 3, 5, 7, 9};
    evenNumbers = {2, 4, 6, 8};
}

void DrawBoard()
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                cout << " . ";
            else
                cout << " " << board[i][j] << " "; 
            if (j < 2)
                cout << "|";
        }
        cout << "\n";
        if (i < 2)
            cout << "---+---+---\n";
    }
    cout << "\n";
}

bool CheckWin()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] + board[i][1] + board[i][2] == 15)
            return true;
        if (board[0][i] + board[1][i] + board[2][i] == 15)
            return true;
    }

    if (board[0][0] + board[1][1] + board[2][2] == 15)
        return true;
    if (board[0][2] + board[1][1] + board[2][0] == 15)
        return true;

    return false;
}

bool IsInteger(const string &input)
{
    return !input.empty() && all_of(input.begin(), input.end(), ::isdigit);
}

bool HandleInput(int cell, int number)
{
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;

    if (cell < 1 || cell > 9 || board[row][col] != 0)
    {
        cout << "Invalid input! Choose an empty cell (1-9).\n";
        return false;
    }

    if ((currentPlayer == 1 && find(oddNumbers.begin(), oddNumbers.end(), number) == oddNumbers.end()) ||
        (currentPlayer == 2 && find(evenNumbers.begin(), evenNumbers.end(), number) == evenNumbers.end()))
    {
        cout << "Invalid input! Player " << currentPlayer << " must choose a "
             << (currentPlayer == 1 ? "odd" : "even") << " number.\n";
        return false;
    }

    if (usedNumbers.count(number))
    {
        cout << "Invalid input! Number already used.\n";
        return false;
    }

    board[row][col] = number;
    usedNumbers.insert(number);

    if (currentPlayer == 1)
        oddNumbers.erase(remove(oddNumbers.begin(), oddNumbers.end(), number), oddNumbers.end());
    else
        evenNumbers.erase(remove(evenNumbers.begin(), evenNumbers.end(), number), evenNumbers.end());

    return true;
}

int game5()
{
    while (true)
    {
        cout << "Enter name for Player 1 (Odd numbers): ";
        getline(cin, playerNames[0]);
        if (!isValidName(playerNames[0]))
        {
            cout << "Invalid name. Please enter a valid name (letters only).\n";
            continue;
        }

        cout << "Enter name for Player 2 (Even numbers): ";
        getline(cin, playerNames[1]);
        if (!isValidName(playerNames[1]))
        {
            cout << "Invalid name. Please enter a valid name (letters only).\n";
            continue;
        }

        break;
    }

    InitializeBoard();
    GameEnd = false;
    currentPlayer = 1;

    DrawBoard();

    while (!GameEnd)
    {
        string cellInput, numberInput;
        int cell, number;
        bool validInput = false;

        while (!validInput)
        {
            cout << playerNames[currentPlayer - 1] << "'s turn (" << (currentPlayer == 1 ? "Odd" : "Even") << "):\n";
            cout << "Available numbers: ";
            if (currentPlayer == 1)
            {
                for (int num : oddNumbers)
                    cout << num << " ";
            }
            else
            {
                for (int num : evenNumbers)
                    cout << num << " ";
            }
            cout << "\n";

            DrawBoard();

            cout << "Enter cell (1-9): ";
            cin >> cellInput;

            if (!IsInteger(cellInput))
            {
                cout << "Invalid input! Please enter a valid number for the cell.\n";
                continue;
            }

            cell = stoi(cellInput);

            cout << "Enter number: ";
            cin >> numberInput;

            if (!IsInteger(numberInput))
            {
                cout << "Invalid input! Please enter a valid number.\n";
                continue;
            }

            number = stoi(numberInput);

            validInput = HandleInput(cell, number);
            if (!validInput)
                cout << "Please try again.\n";
        }

        DrawBoard();

        if (CheckWin())
        {
            cout << playerNames[currentPlayer - 1] << " wins!\n";
            GameEnd = true;
        }
        else if (usedNumbers.size() == 9)
        {
            cout << "It's a draw!\n";
            GameEnd = true;
        }
        else
        {
            currentPlayer = 3 - currentPlayer; // Switch player
        }
    }

    cout << "Thanks for playing!\n";
    return 0;
}

/////////////////////////////////////////////////////////////////// Number 6 ///////////////////////////////////////////////////

char grid[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void displayGrid()
{
    cout << "    1   2   3\n"; 
    cout << "  -------------\n";
    for (int i = 0; i < 3; i++) 
    {
        cout << i + 1 << " | ";     
        for (int j = 0; j < 3; j++) 
        {
            cout << grid[i][j] << " | "; 
        }
        cout << "\n  -------------\n"; 
    }
}

bool checkLoss(char mark)
{
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][0] == mark && grid[i][1] == mark && grid[i][2] == mark)
            return true;
    }
    for (int i = 0; i < 3; i++)
    {
        if (grid[0][i] == mark && grid[1][i] == mark && grid[2][i] == mark)
            return true;
    }
    if (grid[0][0] == mark && grid[1][1] == mark && grid[2][2] == mark)
        return true;
    if (grid[0][2] == mark && grid[1][1] == mark && grid[2][0] == mark)
        return true;

    return false;
}

bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == ' ')
                return false;
        }
    }
    return true; 
}

void getMove(int &row, int &col)
{
    while (true)
    {
        cout << "Enter your move (row and column): ";
        if (!(cin >> row >> col)) 
        {
            cout << "Invalid input. Please enter two integers for row and column.\n";
            cin.clear();                                        
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }

        row--;
        col--;

        if (row < 0 || row >= 3 || col < 0 || col >= 3)
        {
            cout << "Invalid move. Row and column must be between 1 and 3.\n";
            continue;
        }

        if (grid[row][col] != ' ')
        {
            cout << "Invalid move. The cell is already occupied. Try again.\n";
            continue;
        }

        break; 
    }
}

void game6()
{
    string player1, player2;
    cout << "Enter the name of Player 1 (X): ";
    cin >> player1;
    cout << "Enter the name of Player 2 (O): ";
    cin >> player2;

    string currentPlayer = player1;
    char currentMark = 'X';

    while (true)
    {
        displayGrid();

        cout << currentPlayer << " (" << currentMark << "), it's your turn!\n";

        int row, col;
        getMove(row, col);

        grid[row][col] = currentMark;

        if (checkLoss(currentMark))
        {
            displayGrid();
            cout << currentPlayer << " (" << currentMark << ") loses! Game over.\n";
            break; 
        }

        if (checkDraw())
        {
            displayGrid();
            cout << "It's a draw! Game over.\n";
            break; 
        }

        if (currentPlayer == player1)
        {
            currentPlayer = player2;
            currentMark = 'O';
        }
        else
        {
            currentPlayer = player1;
            currentMark = 'X';
        }
    }
}

/////////////////////////////////////////////////////////////////// Number 7 ///////////////////////////////////////////////////

class TicTacToe
{
private:
    vector<vector<char>> board;
    string player1Name, player2Name;
    char player1Token, player2Token;
    int player1Tokens, player2Tokens;

public:
    TicTacToe(string name1, string name2)
    {
        board = vector<vector<char>>(4, vector<char>(4, '.'));
        player1Name = name1;
        player2Name = name2;
        player1Token = 'X';
        player2Token = 'O';
        player1Tokens = 2; 
        player2Tokens = 2;
    }

    void displayBoard()
    {
        cout << "   0   1   2   3\n"; 
        for (int i = 0; i < 4; ++i)
        {
            cout << i << " "; 
            for (int j = 0; j < 4; ++j)
            {
                cout << "[" << board[i][j] << "] ";
            }
            cout << endl;
        }
    }

    bool isMoveValid(int row, int col)
    {
        if (row < 0 || row >= 4 || col < 0 || col >= 4 || board[row][col] != '.')
        {
            return false; 
        }
        return true;
    }

    bool moveToken(int player, int row, int col)
    {
        if (!isMoveValid(row, col))
        {
            return false;
        }

        char token = (player == 1) ? player1Token : player2Token;
        board[row][col] = token;

        if (player == 1)
        {
            --player1Tokens;
        }
        else
        {
            --player2Tokens;
        }
        return true;
    }

    bool checkWin(char token)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                // Horizontal check
                if (j < 2 && board[i][j] == token && board[i][j + 1] == token && board[i][j + 2] == token)
                {
                    return true;
                }
                // Vertical check
                if (i < 2 && board[i][j] == token && board[i + 1][j] == token && board[i + 2][j] == token)
                {
                    return true;
                }
                // Diagonal check (top-left to bottom-right)
                if (i < 2 && j < 2 && board[i][j] == token && board[i + 1][j + 1] == token && board[i + 2][j + 2] == token)
                {
                    return true;
                }
                // Diagonal check (top-right to bottom-left)
                if (i < 2 && j > 1 && board[i][j] == token && board[i + 1][j - 1] == token && board[i + 2][j - 2] == token)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isGameOver()
    {
        return player1Tokens == 0 || player2Tokens == 0 || checkWin(player1Token) || checkWin(player2Token);
    }

    bool getValidInput(int &row, int &col)
    {
        while (true)
        {
            if (cin >> row >> col)
            {
                if (row >= 0 && row < 4 && col >= 0 && col < 4)
                {
                    return true; 
                }
                else
                {
                    cout << "Invalid input! Row and column must be between 0 and 3. Try again: ";
                }
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter integers only for row and column. Try again: ";
            }
        }
    }

    void playGame7()
    {
        int currentPlayer = 1; 
        int row, col;

        while (!isGameOver())
        {
            displayBoard();
            cout << (currentPlayer == 1 ? player1Name + " [X]" : player2Name + " [O]")
                 << "'s turn. Enter your move (row and column): ";

            if (getValidInput(row, col) && moveToken(currentPlayer, row, col))
            {
                if (checkWin(currentPlayer == 1 ? player1Token : player2Token))
                {
                    displayBoard();
                    cout << (currentPlayer == 1 ? player1Name : player2Name)
                         << " wins!" << endl;
                    return;
                }
                currentPlayer = (currentPlayer == 1) ? 2 : 1; 
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }
        }

        displayBoard();
        cout << "Game Over! It's a draw!" << endl;
    }
};

int game7()
{
    string player1, player2;

    cout << "Enter Player 1's name: ";
    getline(cin, player1); 

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Player 2's name: ";
    getline(cin, player2); 

    TicTacToe game(player1, player2);
    game.playGame7();

    return 0;
}

/////////////////////////////////////////////////////////////////// Number 8 ///////////////////////////////////////////////////
const int SZ = 3;

class Grid
{
public:
    vector<vector<char>> cells;
    char champ;
    bool done;

    Grid() : cells(SZ, vector<char>(SZ, ' ')), champ(' '), done(false) {}

    void show()
    {
        for (int r = 0; r < SZ; r++)
        {
            for (int c = 0; c < SZ; c++)
            {
                cout << cells[r][c];
                if (c < SZ - 1)
                    cout << " | ";
            }
            cout << endl;
            if (r < SZ - 1)
                cout << "---------\n";
        }
    }

    bool place(int r, int c, char p)
    {
        if (r < 1 || r > SZ || c < 1 || c > SZ || cells[r - 1][c - 1] != ' ')
            return false;

        cells[r - 1][c - 1] = p;
        checkWin(p);
        return true;
    }

    void checkWin(char p)
    {
        for (int i = 0; i < SZ; i++)
        {
            if (cells[i][0] == p && cells[i][1] == p && cells[i][2] == p)
            {
                champ = p;
                done = true;
            }
            if (cells[0][i] == p && cells[1][i] == p && cells[2][i] == p)
            {
                champ = p;
                done = true;
            }
        }
        if (cells[0][0] == p && cells[1][1] == p && cells[2][2] == p)
        {
            champ = p;
            done = true;
        }
        if (cells[0][2] == p && cells[1][1] == p && cells[2][0] == p)
        {
            champ = p;
            done = true;
        }
    }

    bool isFull()
    {
        for (int r = 0; r < SZ; r++)
        {
            for (int c = 0; c < SZ; c++)
            {
                if (cells[r][c] == ' ')
                    return false;
            }
        }
        done = true;
        return true;
    }
};

class BigGrid
{
public:
    vector<vector<Grid>> grids;
    char champ;

    BigGrid() : grids(SZ, vector<Grid>(SZ)), champ(' ') {}
    void show()
    {
        cout << "         1              2              3\n";
        cout << "     1   2   3      1   2   3      1   2   3";
        cout << endl;
        

        for (int r = 0; r < SZ; r++)
        {
            for (int sr = 0; sr < SZ; sr++)
            {
                if (sr == 0)
                    cout << "  " << r + 1 << " "; 
                else
                    cout << "    ";

                for (int c = 0; c < SZ; c++)
                {
                    for (int sc = 0; sc < SZ; sc++)
                    {
                        if (sr == 0 && sc == 0)
                            cout << sr + 1 << " ";
                        else if (sr == 1 && sc == 0)
                            cout << sr + 1 << " ";
                        else if (sr == 2 && sc == 0)
                            cout << sr + 1 << " ";
                        else
                            cout << "  ";

                        cout << grids[r][c].cells[sr][sc];
                        if (sc < SZ - 1)
                            cout << " ";
                    }

                    if (c < SZ - 1)
                        cout << " || ";
                }

                cout << endl;
            }

            if (r < SZ - 1)
                cout << "     ==========     ===========    ===========\n";
        }
    }

    bool move(int gr, int gc, int cr, int cc, char p)
    {
        if (grids[gr - 1][gc - 1].done)
        {
            cout << "This grid is done!\n";
            return false;
        }

        if (grids[gr - 1][gc - 1].place(cr, cc, p))
        {
            checkWin();
            return true;
        }
        else
        {
            cout << "Invalid move, try again.\n";
            return false;
        }
    }

    void checkWin()
    {
        for (int i = 0; i < SZ; i++)
        {
            if (grids[i][0].champ != ' ' && grids[i][0].champ == grids[i][1].champ && grids[i][1].champ == grids[i][2].champ)
                champ = grids[i][0].champ;
            if (grids[0][i].champ != ' ' && grids[0][i].champ == grids[1][i].champ && grids[1][i].champ == grids[2][i].champ)
                champ = grids[0][i].champ;
        }
        if (grids[0][0].champ != ' ' && grids[0][0].champ == grids[1][1].champ && grids[1][1].champ == grids[2][2].champ)
            champ = grids[0][0].champ;
        if (grids[0][2].champ != ' ' && grids[0][2].champ == grids[1][1].champ && grids[1][1].champ == grids[2][0].champ)
            champ = grids[0][2].champ;
    }

    bool isOver()
    {
        return champ != ' ';
    }

    void declare()
    {
        if (champ != ' ')
            cout << "Player " << champ << " wins the Ultimate Tic Tac Toe!\n";
    }
};

int safeInput(const string &msg)
{
    int x;
    while (true)
    {
        cout << msg;
        cin >> x;
        if (!cin.fail() && x >= 1 && x <= SZ)
        {
            return x;
        }
        cout << "Invalid input. Please enter a number between 1 and " << SZ << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
int game8()
{
    BigGrid game;
    string player1, player2;

    cout << "Enter Player 1's name (X): ";
    cin >> player1;
    cout << "Enter Player 2's name (O): ";
    cin >> player2;

    char turn = 'X';
    string currentPlayerName = player1; 

    while (!game.isOver())
    {
        game.show();
        cout << currentPlayerName << " (" << turn << ")'s turn.\n";

        int gr = safeInput("Enter grid row (1-3): ");
        int gc = safeInput("Enter grid column (1-3): ");
        int cr = safeInput("Enter cell row (1-3): ");
        int cc = safeInput("Enter cell column (1-3): ");

        if (game.move(gr, gc, cr, cc, turn))
        {
            turn = (turn == 'X') ? 'O' : 'X';
            currentPlayerName = (currentPlayerName == player1) ? player2 : player1;
        }
    }

    game.show();
    game.declare();

    return 0;
}

/////////////////////////////////////////////////////////////////// Main Menu ///////////////////////////////////////////////////

int main()
{
    int choice;

    while (true)
    {
        cout << "Select a game variant:\n";
        cout << "1. Pyramid Tic-Tac-Toe\n";
        cout << "2. Four-in-a-row\n";
        cout << "3. 5 x 5 Tic Tac Toe\n";
        cout << "4. Word Tic-Tac-Toe\n";
        cout << "5. Numerical Tic-Tac-Toe\n";
        cout << "6. Misere Tic-Tac-Toe\n";
        cout << "7. 4 x 4 Tic-Tac-Toe\n";
        cout << "8. Ultimate Tic-Tac-Toe\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 9)
        {
            cin.clear();                                         
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please select a valid choice (1-9).\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Starting Pyramid Tic-Tac-Toe...\n";
            game1();
            break;
        case 2:
            cout << "Starting Four-in-a-row...\n";
            game2();
            break;
        case 3:
            cout << "Starting 5 x 5 Tic Tac Toe...\n";
            game3();
            break;
        case 4:
            cout << "Starting Word Tic-Tac-Toe...\n";
            game4();
            break;
        case 5:
            cout << "Starting Numerical Tic-Tac-Toe...\n";
            game5();
            break;
        case 6:
            cout << "Starting Misere Tic-Tac-Toe...\n";
            cout << "The goal is to avoid forming three marks in a row, column, or diagonal.\n";
            game6();
            break;
        case 7:
            cout << "Starting 4 x 4 Tic-Tac-Toe...\n";
            game7();
            break;
        case 8:
            cout << "Starting Ultimate Tic-Tac-Toe...\n";
            game8();
            break;
        case 9:
            cout << "Thank you for playing!\n";
            exit(0);
        default:
            cout << "Something went wrong! Exiting...\n";
            return 0;
        }
    }

    return 0;
}
