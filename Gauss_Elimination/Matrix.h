#pragma once
#include<fstream>

using namespace std;

class Matrix
{
public:

	Matrix();
	~Matrix();

	int n;
	int Size;

	double Set;
	double factor;

	double** matrix;

	void fileLoad(); //loading for reading matrix + matirx size I/O + I/O matrix element
	void calulate();
	void loadFinalinversematrix();
	void writeFile();
};

