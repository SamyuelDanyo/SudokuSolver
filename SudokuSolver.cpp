//
//  SudokuSolver.cpp
//    Decimal implemented.
//


#include <cstdlib>														//  Includes
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

using namespace std;													// Namespace


#define DEC_DIMENSIONS 81												// Definitions
#define HEX_DIMENSIONS 256
#define DEC 1
#define HEX 2



void printBoard(vector<vector<int>>& vec);								// Function prototypes
string fileHandler(string filename);
int lengthCheck(string str);
vector<vector<int>> fillBoard(string str);
int isFull(vector<vector<int>>& vec);
array<int, 9> possibleEntries(vector<vector<int>> vec,int i, int j);
int solve(vector<vector<int>> board);

int puzzleType;  //1-->DEC 2-->											// Global Variables
int difficulty = 0;

int main(int argc, const char * argv[]) {

	string str, file, a;
	
	vector<vector<int>> board;
	
	//Open Fetch and Close File
	cout<<"Enter input sudoku file";
	cin>>file;
	str = fileHandler(file);

	//Length Checking
	if(!lengthCheck(str))
		return 0;
		
	
	//Initialising board
	board = fillBoard(str);
	
	//Printing board
	printBoard(board);

	//Solve Board
	cout<<"Solve sudoku?(y/n):"<<endl;
	
	cin>>a;
	if (a=="y") {
		solve(board);
	}
	else
		return 0;
	
	return 0;
}

int solve(vector<vector<int>> board)
{
	int x,y,i,j;
	string str;
	array<int, 9> possibilities;
	
	difficulty++;
	y=0;
	x=0;
	
	if (isFull(board))
	{
		for (i=0; i<=20; i++) {
			cout<<endl;
		}
		cout<<"Solution:"<<endl;
		printBoard(board);
		cout<<"The puzzle used, "<<difficulty<<" iterations."<<endl;
		return 0;
	}
	else
	{
		for (i=0; i<=8; i++) {
			for (j=0; j<=8; j++) {
				if(board[i][j]==0)
				{
					y=i;
					x=j;
					break;
				}
			}
		}
		
		
		possibilities = possibleEntries(board, y, x);
		
		for (i=0; i<=8; i++) {
			if (possibilities[i]!=0) {
				board[y][x]=possibilities[i];
				solve(board);
				
			}
		}
		board[y][x] = 0;
	}
	return 0;
}

void printBoard(vector<vector<int>>& vec)
{
	int i,j;
	
	for (j=0;j<=12;j++)
		cout<<"---";
	cout<<endl;
	
	for (i=0; i<=8; i++)
	{
	
		for (j=0; j<=8; j++)
		{
			if (vec[i][j]!=0)
				cout<<"| "<<vec[i][j]<<" ";
			else
				cout<<"|   ";
			if (((j+1)%3==0)&&(j!=8))
				cout <<"|";
			
		}
		cout <<"|"<< endl;
		if (((i+1)%3==0))
		{
			for (j=0;j<=12;j++)
				cout<<"---";
		}
		cout<<endl;
	}

}

string fileHandler(string filename)
{
	fstream inputStream;
	string str;

	inputStream.open(filename);
	inputStream >> str;
	cout << "File:\n";
	cout << str<<endl;
	inputStream.close();
	
	return str;
}

int lengthCheck(string str)
{
	
	unsigned long length;
	
	
	length = str.length();
	
	cout<<"The length of the file is "<<length<<" characters"<<endl;
	
	if (length == DEC_DIMENSIONS)
	{
		cout<<"Decimal-Sudoku puzzle found"<<endl;
		puzzleType = DEC;
		return 1;
	}
	else if (length == HEX_DIMENSIONS)
	{
		cout<<"Hexadecimal-Sudoku puzzle Found!"<<endl;
		puzzleType = HEX;
		return 1;
	}
	else
	{
		cout<<"Error! Sudoku puzzle not found!"<<endl<<"Check input file."<<endl;
		return 0;
	}
}

vector<vector<int>> fillBoard(string str)
{
	int i, j, strCounter,number;
	char buffer;
	vector<vector<int>> board;
	
	strCounter = 0;
	//FOR DEC DO PART FOR HEX
	
		for (i=0; i<=8; i++)
		{
			vector<int> row;
		
			for (j=0; j<=8; j++)
			{
				if (str!=".")
				{
					buffer = str[strCounter];
					number = atoi(&buffer);
					row.push_back(number);
				}
				else
					row.push_back(0);
			
				strCounter++;
			}
			board.push_back(row);
		}
		return board;
	
}

int isFull(vector<vector<int>>& vec)
{
	int i,j;
	for (i=0; i<=8; i++)
    {
		for (j=0; j<=8; j++)
		{
			if (vec[i][j]==0)
				return 0;
		}
	}
	return 1;
}

array<int, 9> possibleEntries(vector<vector<int>> vec,int yi, int xj)
{
	int i, j,r,c;
	
	array<int, 9> possibleNumbers;
	
	
	for (i=0; i<=8; i++)		//If element = 1 : Possible # else: Not possible #
		possibleNumbers[i]=1;	//Initialization -> All numbers possible
	
	//Horizontal
	for (j=0;j<=8; j++)
    {
		if (vec[yi][j]!=0) {
			possibleNumbers[vec[yi][j] - 1]=0;	// # not possible
		}
	}
	
	//Vertical
	for (i=0; i<=8; i++)
    {
		if (vec[i][xj]) {
			possibleNumbers[vec[i][xj] - 1]=0;	// # not possible
		}
	}

	//3X3 Subsquare
	if (yi<=2)
		r = 0;
	else if (yi<=5)
		r = 3;
	else
		r = 6;
	if (xj<=2)
		c = 0;
	else if (xj<=5)
		c = 3;
	else
		c = 6;
	
	
	for (i = r; i<=r+2; i++)
	{
		for (j=c; j<=c+2; j++)
		{
			if (vec[i][j]!=0)
			{
				possibleNumbers[(vec[i][j]-1)]=0; // # not possible
			}
		}
	}
	for (i=0; i<=8; i++) {
		if (possibleNumbers[i]!=0) {
			possibleNumbers[i]=i+1;
		}
	}
	return possibleNumbers;
}