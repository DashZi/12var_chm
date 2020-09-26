#include "Header.h"

MatrixProf::MatrixProf(void)
{
	n = 0;
	col = 0;
}

MatrixProf::MatrixProf(int x, int c)
{
	n = x;
	col = c;
	di.resize(n);
	ia.resize(n + 1);
	al.resize(col);
	au.resize(col);
	F.resize(n);
}

void MatrixProf::load(ifstream &matrix, ifstream &vect)
{
	for (int i = 0; i < n + 1; i++)
	{
		matrix >> ia[i];
	}
	for (int i = 0; i < n; i++)
	{
		matrix >> di[i];
	}
	for (int i = 0; i < col; i++)
	{
		matrix >> al[i];
	}
	for (int i = 0; i < col; i++)
	{
		matrix >> au[i];
	}
	for (int i = 0; i < n; i++)
	{
		vect >> F[i];
	}
}
