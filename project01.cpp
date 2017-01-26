/* All Support Functions Below*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


void OpenInputFile(string filename, ifstream& inFile);
void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring);
void LoadGrid(ifstream& inFile, int grid[][CMAX]);
void PrintGrid(int grid[][CMAX]);
void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]);
void CopyGrid(const int source[][CMAX], int destination[][CMAX]);
int  CountType1Neighbors(int grid[][CMAX], int row, int col);
int  CountType2Neighbors(int grid[][CMAX], int row, int col);
void ParseRequirementsString(string requirements, int reqs[]);

void OpenInputFile(string filename, ifstream& inFile) { 

//WORKS


	//OpenInputFile -- Open file whose name is stored in filename

	inFile.open(filename.c_str(), std::ifstream::in);
}

void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring) {


//WORKS


	//LoadConstraints -- loads only simulation constraints from inFile after skipping header comment.
	//Constraints input in order num, birth string, survival string
	string line;
	getline(inFile, line); //Pull first comment line
	getline(inFile, line); //Pull iterations
	getline(inFile, line);
	num = atoi(line.c_str());
	getline(inFile, line);
	getline(inFile, bstring); //Pull birth string
	getline(inFile, line);
	getline(inFile, sstring); //Pull survival string
}

void LoadGrid(ifstream& inFile, int grid[][CMAX]) {
	//LoadGrid -- Loads the cell grid from inFile
	
}

void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]) {
	//ComputeNextGrid -- uses  current generation to compute next generation using constraints specified in birth and survival arrays
}

void CopyGrid(const int source[][CMAX], int next[][CMAX]) {
	//CopyGrid -- copies contents of source array into destination array
}

int CountType2Neighbors(int grid[][CMAX], int row, int col){


//WORKS


//CountType1Neighbors -- counts the total number of LIVING Type1 neighbors for the cell at the
//grid position specified by row and col.
int Total2Neighbors = 0;
	for(int ir = -1; ir = 1; ir++){
		for(int ic = -1; ic = 1; ic++){
			if(grid[(row+ir+RMAX)%RMAX][(col+ic+CMAX)%CMAX] == 1){
				Total2Neighbors++;
			}
		}		
	}
	



	return Total2Neighbors;
}

int CountType1Neighbors(int grid[][CMAX], int row, int col) {


//WORKS



	//CountType1Neighbors -- counts the total number of LIVING Type2 neighbors for the cell at the
	//grid position specified by row and col.
	int Total1Neighbors = 0;
	for(int ir = -1; ir = 1; ir++){
		for(int ic = -1; ic = 1; ic++){
			if(grid[(row+ir+RMAX)%RMAX][(col+ic+CMAX)%CMAX] == 1){
				Total1Neighbors++;
			}
		}		
	}
	



	return Total1Neighbors;
}

void ParseRequirementsString(string requirements, int reqs[]) {


//WORKS


	const char *buffer = requirements.c_str();
	char c;
	while (c = *buffer++)
	{
		if (c == '0') {
			reqs[0] = 1;
		}
		if (c == '1') {
			reqs[1] = 1;
		}
		if (c == '2') {
			reqs[2] = 1;
		}
		if (c == '3') {
			reqs[3] = 1;
		}
		if (c == '4') {
			reqs[4] = 1;
		}
		if (c == '5') {
			reqs[5] = 1;
		}
		if (c == '6') {
			reqs[6] = 1;
		}
		if (c == '7') {
			reqs[7] = 1;
		}
		if (c == '8') {
			reqs[8] = 1;
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
