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
	inFile.open(filename.c_str(), std::ifstream::in);
}

void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring) {
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
	getline(inFile, line);
		for (int g = 0; g < CMAX; g++) {
		for (int h = 0; h < RMAX; h++) {
			getline(inFile, line, ' '); //Pull until space is hit
			grid[g][h] = atoi(line.c_str()); //pull values of grid in text file here
		}
	}
}

void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]) {
	int count;
	for (int i = 0; i < CMAX; i++) {
		for (int j = 0; j < RMAX; j++) {
			int neigh1 = CountType1Neighbors(current, i, j); //Get neighbors for cell
			int neigh2 = CountType2Neighbors(current, i, j);

			if (current[i][j] == 1) {						//Check what current cell value is
				if (survival[neigh1] == 1) next[i][j] = 1;	//Check if matches any survival rule
				else {
					next[i][j] = 0;							//Otherwise cell Dies
				}
			}
			else if (current[i][j] == 2) {					//Repeat if Cell is 2
				if (survival[neigh2] == 1) next[i][j] = 2;
				else {
					next[i][j] = 0;
				}
			}
			else if (neigh1 > neigh2) {						//Cell birth same process
				if (birth[neigh1] == 1) next[i][j] = 1;
				else {
					next[i][j] = 0;
				}
			}
			else if (neigh1 < neigh2) {
				if (birth[neigh2] == 1) next[i][j] = 2;
				else {
					next[i][j] = 0;
				}
			}
			else {											//Otherwise set zero
				next[i][j] = 0;
			}


		}
	}
}

void CopyGrid(const int source[][CMAX], int destination[][CMAX]) {
	for (int i = 0; i < CMAX; i++) {
		for (int j = 0; j < RMAX; j++) {
			destination[i][j] = source[i][j];		//Loop through and copy each cell to corresponding cell
		}
	}

}

int CountType2Neighbors(int grid[][CMAX], int row, int col) {
	int Total2Neighbors = 0;
	for (int ir = -1; ir <= 1; ir++) {
		for (int ic = -1; ic <= 1; ic++) {
			if (grid[(row + ir + RMAX) % RMAX][(col + ic + CMAX) % CMAX] == 2) {	//Loop through each cell wrapping on the edges
				if(((row+ir+RMAX)%RMAX) == row && ((col+ic+CMAX)%CMAX) == col){		//Check that its not the center cell
				} else {															// row + ir + RMAX % RMAX give the surrounding cells and wraps because of the + RMAX % RMAX
				Total2Neighbors++;													//Increase neighbor count otherwise
				}
			}
		}
	}
	return Total2Neighbors;
}

int CountType1Neighbors(int grid[][CMAX], int row, int col) {
	int Total1Neighbors = 0;														//Same process as for cell 2 neighbors
	for (int ir = -1; ir <= 1; ir++) {
		for (int ic = -1; ic <= 1; ic++) {
			if (grid[(row + ir + RMAX) % RMAX][(col + ic + CMAX) % CMAX] == 1) {
				if(((row+ir+RMAX)%RMAX) == row && ((col+ic+CMAX)%CMAX) == col){
				} else {
				Total1Neighbors++;
				}
			}
		}
	}
	return Total1Neighbors;
}

void ParseRequirementsString(string requirements, int reqs[]) {
	const char *buffer = requirements.c_str();										//Set the string to a char array
	char c;		
	while (c = *buffer++)															//Loop through until null
	{
		if (c == '0') {																//Check for each possible value between 0 and 9 and assign it to corresponding location
			reqs[0] = 0;
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
