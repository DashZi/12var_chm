#include "Header.h"

Matrix::Matrix(int x, ifstream &vect) // считывание матрицы
{
	this->n = x;
	col = 0;
	vector<vector<real>> B(n);
	for (int i = 0; i < n; i++)
	{
		vector<real> buf(n);
		B[i] = buf;
	}
	matrix = B;
	F.resize(n);
	for (int i = 0; i < n; i++)
	{
		vect >> F[i];
	}
}

void Matrix::setMatrix(vector< vector<real> > A, int x, vector<real> B)
{
	n = x;
	matrix = A;
	F = B;
}

void Matrix::getCol() // подсчет значащих элементов в нижнем и верхнем треугольнике матрицы
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			if (matrix[i][j] != 0 || matrix[j][i] != 0)
				col++;
		}
}

void Matrix::ToProf(MatrixProf* M) // перевод матрицы в профильный формат
{
	getCol();
	vector <real> bdi(n);
	vector <int> bia(n + 1);
	vector <real> bau(col);
	vector <real> bal(col);
	int s = 0;
	int flag;
	for (int i = 0; i < n; i++)
	{
		bdi[i] = matrix[i][i];
		bia[i] = s;
		flag = 0;
		for (int j = 0; j < i; j++)
		{
			if (matrix[i][j] != 0 || matrix[j][i] != 0)
			{
				flag = 1;
			}
			if (flag == 1)
			{
				bal[s] = matrix[j][i];
				bau[s] = matrix[i][j];
				s++;
			}
		}
	}
	bia[n] = s;
	M->setProf(n, col, bdi, bia, bal, bau, F);
}

void MatrixProf::Direct_y() // прямой ход Ly=B
{
	for (int i = 0; i < n; i++)
	{
		int j = i - (ia[i + 1] - ia[i]);
		dubl sum = 0;
		for (int k = ia[i]; k < ia[i + 1]; k++, j++)
		{
			sum += F[j] * al[k];
		}
		F[i] = (F[i] - sum) / di[i];
	}
}

void MatrixProf::Reverse_y() // обратный ход Ux=y
{
	for (int i = n - 1; i >= 0; i--)
	{
		int j = i - (ia[i + 1] - ia[i]);
		for (int k = ia[i]; k < ia[i + 1]; k++, j++)
		{
			F[j] -= F[i] * au[k];
		}
	}
}

vector <real> MatrixProf::SLAU() // функция, которая решает СЛАУ
{
	LUDec();
	Direct_y();
	Reverse_y();
	return F;
}

void MatrixProf::setProf(int bn, int bcol, vector<real> bdi, vector<int> bia, vector<real> bal, vector<real> bau, vector<real> bF) // сет функция
{
	di.resize(bn);
	ia.resize(bn + 1);
	al.resize(bcol);
	au.resize(bcol);
	F.resize(bn);
	n = bn;
	col = bcol;
	di = bdi;
	ia = bia;
	al = bal;
	au = bau;
	F = bF;
}

vector<real> Matrix::Gauss() // метод гауса
{
	for (int i = 1; i < n; i++)
		for (int j = i; j < n; j++)
		{
			real m = matrix[j][i - 1] / matrix[i - 1][i - 1];
			for (int k = 0; k < n; k++)
				matrix[j][k] = matrix[j][k] - m * matrix[i - 1][k];
			F[j] = F[j] - m * F[i - 1];
		}
	for (int k = n - 1; k >= 0; k--)
	{
		dubl buf = 0;
		for (int j = k + 1; j < n; j++)
		{
			buf += matrix[k][j] * F[j];
		}
		F[k] = F[k] - buf;
		F[k] = F[k] / matrix[k][k];
	}
	return F;
}
