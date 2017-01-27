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

	string line;
	for(int z = 0; z < 9; z++){
	getline(inFile, line);
	}
	for(int g = 0; g < CMAX; g++){
		for(int h = 0; h < RMAX; h++){
			getline(inFile, line, ' ');
			grid[g][h] = atoi(line.c_str()); //pull values of grid in text file here
		}
	}
}

void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]) {
	//ComputeNextGrid -- uses  current generation to compute next generation using constraints specified in birth and survival arrays
	int neigh1 = 0;
	int neigh2 = 0;
	int maxBirth = birth[0];
	int minBirth = birth[0];
	int maxSurv = survival[0];
	int minSurv = survival [0];

	for(int t = 1; t < 10; t++){
		if(minBirth > birth[t]){
			minBirth = birth[t];
		} else if(maxBirth < birth[t]){
			maxBirth = birth[t];
		}
	}

	for(int r = 1; r < 10; r++){
		if(minSurv > survival[r]){
			minSurv = survival[r];
		} else if(maxSurv < survival[r]){
			maxSurv = survival[r];
		}
	}
	

	for(int i = 0; i < CMAX; i++){
		for(int j = 0; j < RMAX; j++){
			neigh1 = CountType1Neighbors(current, i, j);
			neigh2 = CountType2Neighbors(current, i, j);


			if(current[i][j] == 1){
				if(neigh1 >= minSurv && neigh1 <= maxSurv){
					next[i][j] = 1;
				} else {
					next[i][j] = 0;
				}
			}
			
			if(current[i][j] == 2){
				if(neigh2 >= minSurv && neigh2 <= maxSurv){
					next[i][j] = 2;
				} else {
					next[i][j] = 0;
				}
			}
			
			if(current[i][j] == 0){
				if(neigh1 > neigh2){
					if(neigh1 >= minBirth && neigh1 <= maxBirth){
					next[i][j] = 1;
				} else {
					next[i][j] = 0;
				}
				if(neigh1 < neigh2){
					if(neigh2 >= minBirth && neigh2 <= maxBirth){
					next[i][j] = 2;
				} else {
					next[i][j] = 0;
				}
			}
	
			
		}
	}

}

void CopyGrid(const int source[][CMAX], int next[][CMAX]) { 


//NEEDS TO BE TESTED



	//CopyGrid -- copies contents of source array into destination array
	
	for(int i = 0; i < CMAX; i++){
		for(int j = 0; j < RMAX; j++){
			next[i][j] = source[i][j];
		}
	}

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
