//
// main.cpp 
// Conway's Game of Life with edge wrapping, 
// programmable birth and survival rules
// for Type 1 and Type 2 cells
//
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Global declarations
const int RMAX = 10;		// Maximum number of rows in grid
const int CMAX = 10;		// Maximum number of columns in grid
const int MAXAGE = 8;		// Maximum number of generations any cell can survive 
const string BARS = "==========================================================";

// Function prototypes
void OpenInputFile(string filename, ifstream& inFile);
void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring);
void LoadGrid(ifstream& inFile, int grid[][CMAX]);
void PrintGrid(int grid[][CMAX]);
void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]);
void CopyGrid(const int source[][CMAX], int destination[][CMAX]);
int  CountType1Neighbors(int grid[][CMAX], int row, int col);
int  CountType2Neighbors(int grid[][CMAX], int row, int col);
void ParseRequirementsString(string requirements, int reqs[]);

int main(int argc, char* argv[])
{

  ifstream  inFile;                    // Input stream for reading grid file
  string    filename;				   // Name of grid file
  string    bstring;                   // Birth requirements as C++ string
  string    sstring;                   // Survival requirement as C++ string
  int       currentgrid[RMAX][CMAX];   // Current cell grid
  int       nextgrid[RMAX][CMAX];      // Next cell grid
  int       num;                       // Number of iterations
  int       birth[9], survival[9];     // Birth and survival look up arrays


  if (argc != 2)
  {
    cout << "Usage:  project01  <gridfile>" << endl;
    return 0;
  }
  else
    filename = argv[1];
	
  OpenInputFile(filename, inFile);     // Attempt to open grid file
  if (!inFile)
  {
    cout << "\nError: unable to open '" << filename << "' for input\nTerminating now...\n";
    return 0;
  }
  else
  {
    cout << "\nFile '" << filename << "' opened for input..." << endl;
  }

	
  LoadConstraints(inFile, num, bstring, sstring);  // Load number of iterations, birth and survival strings

  cout << "\nIterations = " << num << endl;
	
  // Exit if birth or survival requirements not specified, otherwise parse birth and survival strings
  if ((bstring[0] != 'B') || (sstring[0] != 'S'))
  {
    cout << "Error: incorrect file formatting" << endl;
    return 0; 
  }
  else	
  {
    // Initialize birth and survival requirements to zero
    for(int k=0; k<9; k++)
    {
      birth[k] = 0;
      survival[k] = 0;
    }			 
    
	// Convert bstring and sstring representations into birth and survival look up tables
    ParseRequirementsString(bstring, birth);
    ParseRequirementsString(sstring, survival);

	cout << "\nSimulation Birth/Survival Configuration\n";
    for(int k=0; k<9; k++)
    {
      cout << "birth[" << k << "] = " << birth[k] << "      survival[" 
           << k << "] = " << survival[k] << "\n";  
	}			 
  }

  	
  LoadGrid(inFile, currentgrid);              // Populate grid
  cout << "\nGrid loaded from file.\n\n";      

  cout << BARS << endl;
  cout << "Iteration = 0" << endl << endl;
  PrintGrid(currentgrid);
  cout << BARS << endl;

  for(int iteration = 1; iteration <= num; iteration++)
  {
    ComputeNextGrid(currentgrid, nextgrid, birth, survival);
    CopyGrid(nextgrid, currentgrid);
    cout << BARS << endl;
    cout << "Iteration = " << iteration << endl << endl;
    PrintGrid(currentgrid);
    cout << BARS << endl;
  } // End iterations loop

  return 0;                            // Done!!
}  // End main()


void PrintGrid(int grid[][CMAX])
// Outputs grid in desired format
{
  for(int r = 0; r < RMAX; r++)
  {
    for(int c = 0; c < CMAX; c++)
    {
      switch (grid[r][c])
      {
        case 0:  cout << ' ' << '-';   break;

        default:  cout << ' ' << grid[r][c]; break;
      }
    }
    cout << endl;
  }
}  // End PrintGrid()




/***********************************************************************/
/***********************************************************************/

//#include "project01.cpp"

/***********************************************************************/
/***********************************************************************/

/* All Support Functions Below*/

void OpenInputFile(string filename, ifstream& inFile) {
	//OpenInputFile -- Open file whose name is stored in filename

	inFile.open(filename.c_str(), std::ifstream::in);
}

void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring) {
	//LoadConstraints -- loads only simulation constraints from inFile after skipping header comment.
	//Constraints input in order num, birth string, survival string

	getline(inFile, line); //Pull first comment line
	getline(inFile, line); //Pull iterations
	num = atoi(line.c_str());
	bstring = getline(inFile, line); //Pull birth string
	sstring = getline(inFile, line); //Pull survival string
}

void LoadGrid(ifstream& inFile, int grid[][CMAX]) {
	//LoadGrid -- Loads the cell grid from inFile
	string word;
	char x;
	int f = 0;
	word.clear();

	while (inFile >> word) {
		x = inFile.get();
		while (x != ' ') {
			word = word + x;
			x = inFile.get();
		}
		f++;
		if (f > 14) {
			cout << word << endl;
		}
		word.clear();
	}
}

void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]) {
	//ComputeNextGrid -- uses  current generation to compute next generation using constraints specified in birth and survival arrays
}

void CopyGrid(const int source[][CMAX], int next[][CMAX]) {
	//CopyGrid -- copies contents of source array into destination array
}

int CountType1Neighbors(int grid[][CMAX], int row, int col);
//CountType1Neighbors -- counts the total number of LIVING Type1 neighbors for the cell at the
//grid position specified by row and col.

int CountType1Neighbors(int grid[][CMAX], int row, int col) {
	//CountType1Neighbors -- counts the total number of LIVING Type2 neighbors for the cell at the
	//grid position specified by row and col.
	int Total1Neighbors = 0;

	//rows 10 wide start at 0 end at 9
	if (row == 0) { //check for top row to wrap to bottom for neighbors
		if (col == 0) { // check for top left corner
			if (grid[9][0] == 1) Total1Neighbors++; //Top row checks
			if (grid[9][1] == 1) Total1Neighbors++;
			if (grid[9][9] == 1) Total1Neighbors++;

			if (grid[0][9] == 1) Total1Neighbors++; //Middle row checks
			if (grid[0][1] == 1) Total1Neighbors++;

			if (grid[1][0] == 1) Total1Neighbors++; //Bottom row checks
			if (grid[1][1] == 1) Total1Neighbors++;
			if (grid[1][9] == 1) Total1Neighbors++;

		}
		if (col == 9) { // check for top right corner
			if (grid[9][0] == 1) Total1Neighbors++; //Top row checks
			if (grid[9][8] == 1) Total1Neighbors++;
			if (grid[9][9] == 1) Total1Neighbors++;

			if (grid[0][8] == 1) Total1Neighbors++; //Middle row checks
			if (grid[0][0] == 1) Total1Neighbors++;

			if (grid[1][0] == 1) Total1Neighbors++; //Bottom row checks
			if (grid[1][8] == 1) Total1Neighbors++;
			if (grid[1][9] == 1) Total1Neighbors++;
		}
		//rest of top row

	}

	if (row == 9) {//check for bottom row to wrap to top for neighbors
		if (col == 0) {//check for bottom left
			if (grid[8][0] == 1) Total1Neighbors++; //Top row checks
			if (grid[8][1] == 1) Total1Neighbors++;
			if (grid[8][9] == 1) Total1Neighbors++;

			if (grid[9][9] == 1) Total1Neighbors++; //Middle row checks
			if (grid[9][1] == 1) Total1Neighbors++;

			if (grid[0][0] == 1) Total1Neighbors++; //Bottom row checks
			if (grid[0][1] == 1) Total1Neighbors++;
			if (grid[0][9] == 1) Total1Neighbors++;
		}
		if (col == 9) {//check for bottom right
			if (grid[8][0] == 1) Total1Neighbors++; //Top row checks
			if (grid[8][8] == 1) Total1Neighbors++;
			if (grid[8][9] == 1) Total1Neighbors++;

			if (grid[9][8] == 1) Total1Neighbors++; //Middle row checks
			if (grid[9][0] == 1) Total1Neighbors++;

			if (grid[0][0] == 1) Total1Neighbors++; //Bottom row checks
			if (grid[0][1] == 1) Total1Neighbors++;
			if (grid[0][9] == 1) Total1Neighbors++;
		}
		//rest of bottom row

	}
	//all non-border cell locations




	return TotalNeighbors;
}

void ParseRequirementsString(string requirements, int reqs[]) {
	const char *buffer = requirements.c_str();
	char c;
	while (c = *buffer++)
	{
		if (c == '0') {
			reqs[0] = 1;
		}
		else {
			reqs[0] = 0;
		}
		if (c == '1') {
			reqs[1] = 1;
		}
		else {
			reqs[1] = 0;
		}
		if (c == '2') {
			reqs[2] = 1;
		}
		else {
			reqs[2] = 0;
		}
		if (c == '3') {
			reqs[3] = 1;
		}
		else {
			reqs[3] = 0;
		}
		if (c == '4') {
			reqs[4] = 1;
		}
		else {
			reqs[4] = 0;
		}
		if (c == '5') {
			reqs[5] = 1;
		}
		else {
			reqs[5] = 0;
		}
		if (c == '6') {
			reqs[6] = 1;
		}
		else {
			reqs[6] = 0;
		}
		if (c == '7') {
			reqs[7] = 1;
		}
		else {
			reqs[7] = 0;
		}
		if (c == '8') {
			reqs[8] = 1;
		}
		else {
			reqs[8] = 0;
		}

	}
}
//ParseRequirementsString -- takes a birth or survival string and converts it to integer array
//assumes that the B or S appears as the first character.Order of constraints does not matter.
//For example, B13 should produce same result as B31
//
//(1's in both reqs[1] and reqs[3], zeros elsewhere)
//
//Hint: use string functions to help you scan through each character in the requirements string one
//at a time and use nested IF or SWITCH to implement logic.


