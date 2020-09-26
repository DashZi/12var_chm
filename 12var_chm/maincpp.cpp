#include "Header.h"

void main()
{
	setlocale(LC_CTYPE, "Russian");
	ifstream size("size.txt");
	ifstream matr("matrix.txt");
	ifstream vect("vector.txt");
	ofstream proffile("prof.txt");
	int n, col;
	size >> n >> col;
	MatrixProf myM(n, col);
	vector<real> X(n);
	vector<real> Y(n);
	int flag = 0;
	///////////////////////////////////
}