#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define UNASSIGNED 0

using namespace std;

class Sudoku {
private:
  int grid[9][9];
  int solnGrid[9][9];
  int guessNum[9];
  int gridPos[81];
  int difficultyLevel;
  bool grid_status;

public:
  Sudoku ();
  Sudoku (string, bool row_major=true);
  void createSeed();
  void printGrid();
  bool solveGrid();
  string getGrid();
  void countSoln(int &number);
  void genPuzzle();
  bool verifyGridStatus();
  void printSVG(string);
  int calculateDifficulty();
  int  branchDifficultyScore();
};

// Generate random number
int genRandNum(int maxLimit)
{
  return rand()%maxLimit;
}

// Create seed grid
void Sudoku::createSeed()
{ 
  this->solveGrid();
  
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->solnGrid[i][j] = this->grid[i][j];    //saving the soln grid
    }
  }
}


Sudoku::Sudoku()
{

  // initialize difficulty level
  this->difficultyLevel = 0;

 
  for(int i=0;i<81;i++)
  {
    this->gridPos[i] = i;
  }
// shuffling pos array
  random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);

  for(int i=0;i<9;i++)
  {
    this->guessNum[i]=i+1;
  }
// shuffling no array
  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

  // Initialising the grid
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->grid[i][j]=0;
    }
  }

  

void Sudoku::printGrid()
{
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(grid[i][j] == 0)
	cout<<".";
      else
	cout<<grid[i][j];
      cout<<"|";
    }
    cout<<endl;
  }

  cout<<endl;
}


bool FindUnassignedLocation(int grid[9][9], int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == UNASSIGNED)
                return true;
        }
    }

    return false;
}

bool UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
        }
    }

    return false;
}

bool isSafe(int grid[9][9], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row%3 , col - col%3, num);
}

bool Sudoku::solveGrid()
{
    int row, col;

    if (!FindUnassignedLocation(this->grid, row, col))
       return true; 

  
    for (int num = 0; num < 9; num++)
    {
        
        if (isSafe(this->grid, row, col, this->guessNum[num]))
        {
         
            this->grid[row][col] = this->guessNum[num];

            if (solveGrid())
                return true;

            
            this->grid[row][col] = UNASSIGNED;
        }
    }

    return false; //  backtracking

}

void Sudoku::countSoln(int &number)
{
  int row, col;

  if(!FindUnassignedLocation(this->grid, row, col))
  {
    number++;
    return ;
  }


  for(int i=0;i<9 && number<2;i++)
  {
      if( isSafe(this->grid, row, col, this->guessNum[i]) )
      {
        this->grid[row][col] = this->guessNum[i];
        countSoln(number);
      }

      this->grid[row][col] = UNASSIGNED;
  }

}



void Sudoku::genPuzzle()
{
  for(int i=0;i<81;i++)
  {
    int x = (this->gridPos[i])/9;
    int y = (this->gridPos[i])%9;
    int temp = this->grid[x][y];
    this->grid[x][y] = UNASSIGNED;

    // If more than 1 solution , replace the removed cell back.
    int check=0;
    countSoln(check);
    if(check!=1)
    {
      this->grid[x][y] = temp;
    }
  }
}



int Sudoku::branchDifficultyScore()
{
   int emptyPositions = -1;
   int tempGrid[9][9];
   int sum=0;

   for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      tempGrid[i][j] = this->grid[i][j];
    }
  }

   while(emptyPositions!=0)
   {
     vector<vector<int> > empty; 

     for(int i=0;i<81;i++)
     {
        if(tempGrid[(int)(i/9)][(int)(i%9)] == 0)
        {
       	  vector<int> temp;
	  temp.push_back(i);
	
	  for(int num=1;num<=9;num++)
	  {
	    if(isSafe(tempGrid,i/9,i%9,num))
	    {
	      temp.push_back(num);
	    }
	  }

	  empty.push_back(temp);
        }
      
     }

     if(empty.size() == 0)
     { 
       cout<<"Hello: "<<sum<<endl;
       return sum;
     } 

     int minIndex = 0;

     int check = empty.size();
     for(int i=0;i<check;i++)
     {
       if(empty[i].size() < empty[minIndex].size())
	  minIndex = i;
     }

     int branchFactor=empty[minIndex].size();
     int rowIndex = empty[minIndex][0]/9;
     int colIndex = empty[minIndex][0]%9;

     tempGrid[rowIndex][colIndex] = this->solnGrid[rowIndex][colIndex];
     sum = sum + ((branchFactor-2) * (branchFactor-2)) ;

     emptyPositions = empty.size() - 1;
   }

   return sum;

}


int  Sudoku::calculateDifficulty()
{
  int B = branchDifficultyScore();
  int emptyCells = 0;

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
	if(this->grid[i][j] == 0)
	   emptyCells++;
    }
  } 

  this->difficultyLevel = B*100 + emptyCells;
  return this->difficultyLevel; 
}


int main(int argc, char const *argv[])
{
  srand(time(NULL));
   // will generate the puzzle switch case is only for difficulty scores
  Sudoku *puzzle = new Sudoku();

  puzzle->createSeed();

  puzzle->genPuzzle();
  
  int n;
  int val = puzzle->calculateDifficulty();
  cout<<"Enter the value for difficulty of sudoku"<<"\n1.Easy \n2.Medium \n3.Difficult\n";
  cin>>n;
  char ans;
  switch(n)
  {
  	default: cout<<"Value entered is out of range";
  	case 1: 
  while(val>400 && val<100)
  {
   Sudoku *puzzle = new Sudoku();

  puzzle->createSeed();

  puzzle->genPuzzle();

  int val = puzzle->calculateDifficulty();
  }
  puzzle->printGrid();
  break;
  case 2:   while(val>600 && val<400)
  {
   Sudoku *puzzle = new Sudoku();

  puzzle->createSeed();

  puzzle->genPuzzle();

  int val = puzzle->calculateDifficulty();
  }
  puzzle->printGrid();
  break;
  
  
  case 3:   while(val<600 && val>900)
  {
   Sudoku *puzzle = new Sudoku();

  puzzle->createSeed();

  puzzle->genPuzzle();

  int val = puzzle->calculateDifficulty();
  }
  puzzle->printGrid();
  break;
  }
  return 0;
}
