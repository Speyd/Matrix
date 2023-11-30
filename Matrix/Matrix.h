#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

extern void ClearScrean();

template <typename T>
class Matrix {

private:

	T** array;
	int line;
	int column;

public:

	Matrix(T** arrayP, const int lineP, const int columnP){
	
		ChangeArray(array, arrayP, lineP, columnP);
	
	}

	Matrix(const T** arrayP, const int lineP) : Matrix( arrayP, lineP, 0){}

	Matrix(const int lineP, const int columnP) : Matrix(nullptr, lineP, columnP) {}

	Matrix(const T** arrayP) : Matrix( arrayP, 0, 0){}

	Matrix(const Matrix& matrixP):Matrix(matrixP.array, matrixP.line, matrixP.column) {
	
		ResizeArray(array, matrixP.line, matrixP.column);
		for (int i = 0; i != matrixP.line; i++) {
			for (int l = 0; l != matrixP.column; l++) {
				array[i][l] = matrixP.array[i][l];
			}
		}
	
	}

	Matrix(Matrix&& matrixP) noexcept
		  :array{ matrixP.array }, line{ matrixP.line }, column{ matrixP.column } {

		matrixP.array = nullptr;
		matrixP.line = 0;
		matrixP.column = 0;

	}

	Matrix() : Matrix(nullptr, 0, 0) {}

	~Matrix() {

		for (size_t i{ 0 }; i != line; i++) {

			if (array[i] != nullptr) delete[] array[i];

		}

		if (array != nullptr) delete[] array;

		line = 0;
		column = 0;

	}

	Matrix& operator =(Matrix& matrixP) {

		ChangeArray(array, matrixP.array, matrixP.line, matrixP.column);
		return *this;

	}

	Matrix& operator =(Matrix&& matrixP) {

		array = matrixP.array;
		matrixP.array = nullptr;

		line = matrixP.line;
		matrixP.line = 0;

		column = matrixP.column;
		matrixP.column = 0;

		return *this;

	}

	Matrix& operator +=(Matrix& matrixP) {

		if (array != nullptr && matrixP.array != nullptr) {

			for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != line; i++) {

				for (size_t l = 0; l != column; l++) {

					if (lP < matrixP.column && iP < matrixP.line)array[i][l] += matrixP(iP, lP);

					lP++;
					if (lP == matrixP.column) {
						lP = 0;
						if (++iP == matrixP.line) break;
					}
				}
				if (iP == matrixP.line) break;
			}

		}

		return *this;

	}

	Matrix& operator -=(Matrix& matrixP) {

		if (array != nullptr && matrixP.array != nullptr) {

			for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != line; i++) {

				for (size_t l = 0; l != column; l++) {

					if (lP < matrixP.column && iP < matrixP.line)array[i][l] -= matrixP(iP, lP);

					lP++;
					if (lP == matrixP.column) {
						lP = 0;
						if (++iP == matrixP.line) break;
					}
				}
				if (iP == matrixP.line) break;
			}

		}

		return *this;

	}

	Matrix& operator *=(Matrix& matrixP) {

		if (array != nullptr && matrixP.array != nullptr) {

			for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != line; i++) {

				for (size_t l = 0; l != column; l++) {

					if (lP < matrixP.column && iP < matrixP.line)array[i][l] *= matrixP(iP, lP);

					lP++;
					if (lP == matrixP.column) {
						lP = 0;
						if (++iP == matrixP.line) break;
					}
				}
				if (iP == matrixP.line) break;
			}

		}

		return *this;

	}

	Matrix& operator /=(Matrix& matrixP) {

		if (array != nullptr && matrixP.array != nullptr) {

			for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != line; i++) {

				for (size_t l = 0; l != column; l++) {

					if (lP < matrixP.column && iP < matrixP.line)array[i][l] /= matrixP(iP, lP);

					lP++;
					if (lP == matrixP.column) {
						lP = 0;
						if (++iP == matrixP.line) break;
					}
				}
				if (iP == matrixP.line) break;
			}

		}

		return *this;

	}

	T& operator()(const int lineP, const int columnP) {

		assert((lineP >= 0 && lineP <= line - 1) and "Index out of range!");
		assert((columnP >= 0 && columnP <= column - 1) and "Index out of range!");
		return array[lineP][columnP];
	}

	T operator()(const int lineP, const int columnP)const {

		assert((lineP >= 0 && lineP <= line - 1) and "Index out of range!");
		assert((columnP >= 0 && columnP <= column - 1) and "Index out of range!");
		return array[lineP][columnP];
	}

	void ResizeArray(T**& arrayP, const int lineP, const int columnP);

	void ChangeArray(T**& oldArray, T** newArray, const int lineP, const int columnP);

	T IsMinimal(Matrix<T> &matrix);

	T IsMaximal(Matrix<T>& matrix);

	friend T operator +(const Matrix& matrix1, const Matrix& matrix2) {

		T sumT{ T() };

		int maxLine = matrix1.line > matrix2.line ? matrix1.line : matrix2.line;
		int maxColumn = matrix1.column > matrix2.column ? matrix1.column : matrix2.column;

		if (matrix1.array != nullptr || matrix2.array != nullptr) {

			for (size_t i{ 0 }; i != maxLine; i++) {

				for (size_t l{ 0 }; l != maxColumn; l++) {

					if (i < matrix1.line && l < matrix1.column)sumT += matrix1(i, l);
					if (i < matrix2.line && l < matrix2.column)sumT += matrix2(i, l);

				}

			}

		}

		return sumT;

	}

	friend T operator -(const Matrix& matrix1, const Matrix& matrix2){

		T sumT{ T() };

		if (matrix1.array != nullptr || matrix2.array != nullptr) {

			for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != matrix1.line; i++) {

				for (size_t l = 0; l != matrix1.column; l++) {

					if (lP < matrix2.column && iP < matrix2.line)sumT += matrix1(i, l) - matrix2(iP, lP);

					lP++;
					if (lP == matrix2.column) {
						lP = 0;
						if (++iP == matrix2.line) break;
					}
				}
				if (iP == matrix2.line) break;
			}

		}

		return sumT;

	}

	friend T operator *(const Matrix& matrix1, const Matrix& matrix2) {

		T sumT{ T() };

		if (matrix1.array != nullptr || matrix2.array != nullptr) {

			for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != matrix1.line; i++) {

				for (size_t l = 0; l != matrix1.column; l++) {

					if (lP < matrix2.column && iP < matrix2.line)sumT += matrix1(i, l) * matrix2(iP, lP);

					lP++;
					if (lP == matrix2.column) {
						lP = 0;
						if (++iP == matrix2.line) break;
					}
				}
				if (iP == matrix2.line) break;
			}

		}

		return sumT;

	}

	friend T operator /(const Matrix& matrix1, const Matrix& matrix2) {

		T sumT{ T() };

		if (matrix1.array != nullptr || matrix2.array != nullptr) {

			for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != matrix1.line; i++) {

				for (size_t l = 0; l != matrix1.column; l++) {

					if (lP < matrix2.column && iP < matrix2.line)sumT += matrix1(i, l) / matrix2(iP, lP);

					lP++;
					if (lP == matrix2.column) {
						lP = 0;
						if (++iP == matrix2.line) break;
					}
				}
				if (iP == matrix2.line) break;
			}

		}

		return sumT;

	}

	friend bool PrintMatrixes(vector<Matrix<T>>& matrixes);
	
	friend void PrintInfoMatrix(vector<Matrix<T>>& matrixes);

	friend void ResizeArrayDontSaveInfo(vector<Matrix<T>>& matrixes);

	friend void ResizeArraySaveInfo(vector<Matrix<T>>& matrixes);

	friend void ChangeValue(vector<Matrix<T>>& matrixes);

};

template <typename T>
void Matrix<T>::ResizeArray(T**& arrayP, const int lineP, const int columnP) {

	assert((lineP >= 0 && columnP >= 0) and "Indices less than zero");

	if (arrayP != nullptr) {

		for (size_t i{ 0 }; i != line; i++) {

			if (arrayP[i] != nullptr)delete[]arrayP[i];

		}

		delete[] arrayP;

	}

	arrayP = new T * [lineP];
	for (size_t i{ 0 }; i != lineP; i++) {

		arrayP[i] = new T[columnP];
		for (size_t l{ 0 }; l != columnP; l++)arrayP[i][l] = T();

	}

	this->line = lineP;
	this->column = columnP;

}

template <typename T>
void Matrix<T>::ChangeArray(T**& oldArray, T** newArray, const int lineP, const int columnP) {

	int tempLine{ line }, tempColumn{ column };
	if (lineP != line && columnP != column)ResizeArray(oldArray, lineP, columnP);

	if (newArray != nullptr) {

		for (size_t i{ 0 }, iP{ 0 }, lP{ 0 }; i != tempLine; i++) {

			for (size_t l{ 0 }; l != tempColumn; l++) {

				if (lP < columnP && iP < lineP)oldArray[iP][lP] = newArray[i][l];

				lP++;
				if (lP == columnP) {
					lP = 0;
					if (++iP == lineP) break;
				}
			}
			if (iP == lineP) break;
		}

	}

}

template <typename T>
T Matrix<T>::IsMinimal(Matrix<T>& matrix) {

	if (matrix.array != nullptr) {

		T minT{ matrix.line > 0 && matrix.column > 0 ? matrix(0, 0) : T() };

		for (size_t i{ 0 }; i != matrix.line; i++) {

			for (size_t l{ 0 }; l != matrix.column; l++) {

				if (minT > matrix(i, l))minT = matrix(i, l);

			}

		}

		return minT;

	}

	return T();

}

template <typename T>
T Matrix<T>::IsMaximal(Matrix<T>& matrix) {

	if (matrix.array != nullptr) {

		T maxT{ matrix.line > 0 && matrix.column > 0 ? matrix(0, 0) : T() };

		for (size_t i{ 0 }; i != matrix.line; i++) {

			for (size_t l{ 0 }; l != matrix.column; l++) {

				if (maxT < matrix(i, l))maxT = matrix(i, l);

			}

		}

		return maxT;

	}

	return T();
}