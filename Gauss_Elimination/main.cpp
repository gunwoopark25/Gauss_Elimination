#include "Matrix.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main()
{
	Matrix matrix3;

	matrix3.calulate();

	cout << "calculated matrix" << endl;
	matrix3.loadFinalinversematrix();

	return 0;
}