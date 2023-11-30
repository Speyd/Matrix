#include "Matrix.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#pragma region Special_Abilities

void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\tMatrix" << endl;
}

void Enter() {
	string enter;
	cin.ignore();
	do {
		cout << "Press enter to continue: "; getline(cin, enter);
	} while (!enter.empty());
}
#pragma endregion

bool PrintMatrixes(vector<Matrix<int>>& matrixes) {

	if (matrixes.size() != 0) {

		for (size_t i = 0; i != matrixes.size(); i++) {

			cout << i + 1 << "-th matrix have " << matrixes[i].line
				 << " line and " << matrixes[i].column << " column" << endl;

		}

		return 1;

	}
	else {

		cout << "Matrix list empty!" << endl;
		return 0;
	}

}

template <typename T>
int ChoiceMatrix(vector<Matrix<T>>& matrixes) {

	int index{ 1 }; size_t size{ matrixes.size() };

	do {

		if (index >= 1 && index <= size)cout << "Enter your choice: ";
		else cout << "There is no such choice!\nEnter your choice again: ";

		cin >> index;

		ClearScrean();
		PrintMatrixes(matrixes);

	} while (index < 1 || index > size);

	return --index;

}

void PrintInfoMatrix(vector<Matrix<int>>& matrixes) {

	if (PrintMatrixes(matrixes) == true) {

		int index{ ChoiceMatrix(matrixes) };
		ClearScrean();

		for (size_t i{ 0 }; i != matrixes[index].line; i++) {

			for (size_t l{ 0 }; l != matrixes[index].column; l++)cout << matrixes[index](i, l) << " | ";
			cout << endl << endl;

		}


	}
}

template <typename T>
void WritingValues(Matrix<T>& tempMatrix, const int line, const int column) {

	int choice{ 0 };

	do {

		ClearScrean();
		cout << "[1] - Add manually\n[2] - Add random\n[0] - Don't add" << endl;
		if (choice >= 0 && choice <= 2)cout << "Enter your choice: ";
		else cout << "There is no such choice!\nEnter your choice again: ";

		cin >> choice;

	} while (choice < 0 || choice > 2);

	if (choice != 0) {

		T value = T();
		for (size_t i = 0; i != line; i++) {

			for (size_t l = 0; l != column; l++) {

				if (choice == 1) {

					ClearScrean();
					cout << i + 1 << " line| " << l + 1 << " column| Enter value: "; cin >> value;

					tempMatrix(i, l) = value;
				}
				else if (choice == 2)tempMatrix(i, l) = T(rand() % (100 - 1 + 1) + 1);

			}

		}

	}

}

template <typename T>
Matrix<T> AddMatrix() {

	int line{ 0 }, column{ 0 }, choice{ 0 };

	cout << "Enter line: "; cin >> line;
	cout << "Enter column: "; cin >> column;
	Matrix<T> tempMatrix{ line < 0 ? 0 : line, line == 0? 0:column < 0 ? 0 : column };
	
	WritingValues(tempMatrix, line, column);

	return tempMatrix;
}

template <typename T>
void DeleteMatrix(vector<Matrix<T>>& matrixes) {

	if (PrintMatrixes(matrixes) == true) {

		int index{ ChoiceMatrix(matrixes) };
		ClearScrean();

		matrixes.erase(matrixes.begin() + index);
		cout << "Delete was successful!" << endl;


	}
}

void ResizeArrayDontSaveInfo(vector<Matrix<int>>& matrixes) {

	if (PrintMatrixes(matrixes) == true) {

		int index{ ChoiceMatrix(matrixes) }, line{ 0 }, column{ 0 };

		ClearScrean();
		cout << "Enter new line: "; cin >> line;
		cout << "Enter new column: "; cin >> column;
		
		matrixes[index].ResizeArray(matrixes[index].array, line, column);
	}
}

void ResizeArraySaveInfo(vector<Matrix<int>>& matrixes) {

	if (PrintMatrixes(matrixes) == true) {

		int index{ ChoiceMatrix(matrixes) }, line{ 0 }, column{ 0 };

		ClearScrean();
		cout << "Enter new line: "; cin >> line;
		cout << "Enter new column: "; cin >> column;
		
		Matrix<int> tempMatrix{ matrixes[index] };
		matrixes[index].ChangeArray(matrixes[index].array, tempMatrix.array, line, column);
	}
}

void ChangeValue(vector<Matrix<int>>& matrixes) {

	if (PrintMatrixes(matrixes) == true) {

		int index{ ChoiceMatrix(matrixes) }, choice{ 0 };

		do {

			ClearScrean();
			cout << "[1] - Change all value in matrix\n"
				 <<"[2] - Change some value in matrix\n[0] - Exit" << endl;

			if(choice >= 0 && choice <= 2)cout << "Enter your choice: ";
			else cout << "There is no such choice!\nEnter your choice again: ";

			cin >> choice;

		} while (choice < 0 || choice > 2);

		ClearScrean();

		if (choice == 1)WritingValues(matrixes[index], matrixes[index].line, matrixes[index].column);
		else if (choice == 2) {

			double choiceIndex{ 1 };
			int SumBordes{ matrixes[index].line + matrixes[index].column };

			do {

				ClearScrean();
				for (size_t i{ 0 }; i != matrixes[index].line; i++) {

					for (size_t l{ 0 }; l != matrixes[index].column; l++)cout << matrixes[index](i, l) << " | ";
					cout << endl << endl;

				}

				if(choiceIndex >= 1 && choiceIndex <= SumBordes)cout << "Enter number value: ";
				else cout << "There is no such number!\nEnter number value again: ";

				cin >> choiceIndex;

			} while (choiceIndex < 1 || choiceIndex > SumBordes);

			int line{ int(ceil(choiceIndex / matrixes[index].line)) - 1};
			int column{int( (matrixes[index].column - 1) + choiceIndex - int(ceil(choiceIndex / matrixes[index].line)) * matrixes[index].column )};
			
			ClearScrean();
			cout << "Enter new value(line: " << line + 1 << " | column: " << column + 1 << "): ";
			cin >> matrixes[index](line,column);

		}

	}

}

void ArithmeticOperations(vector<Matrix<int>>& matrixes) {


	if (PrintMatrixes(matrixes) == true) {

		int index[2]{ 0, 0 }, choice{ 0 }, choiceInfo{ 0 };

		for (size_t i = 0; i != 2; i++) {

			ClearScrean();
			PrintMatrixes(matrixes);

			cout << "Now you write the number of the matrix with which"
				<< " you will perform arithmetic operations";

			if (i == 0)cout << " actions into it" << endl;
			else cout << endl;

			index[i] = ChoiceMatrix(matrixes);

			ClearScrean();

		}

		do {

			ClearScrean();
			cout << "Actions with information\n"
				 << "[1] - Information is stored in one of the matrix\n"
				 << "[2] - Information is output to the console\n[0] - Exit" << endl;

			if (choiceInfo >= 0 && choiceInfo <= 2)cout << "Enter your choice: ";
			else cout << "There is no such choice!\nEnter your choice again: ";

			cin >> choiceInfo;

		} while (choiceInfo < 0 || choiceInfo > 2);



		if (choiceInfo != 0) {

			do {

				ClearScrean();
				cout << "Arithmetic operations\n[1] - Addition(+)\n"
					<< "[2] - Subtraction(-)\n[3] - Multiplication(*)\n"
					<< "[4] - Division(/)\n[0] - Exit" << endl;

				if (choice >= 0 && choice <= 4)cout << "Enter your choice: ";
				else cout << "There is no such choice!\nEnter your choice again: ";

				cin >> choice;

			} while (choice < 0 || choice > 4);

			if (choiceInfo == 1) {

				if (choice == 1)matrixes[index[0]] += matrixes[index[1]];
				else if (choice == 2)matrixes[index[0]] -= matrixes[index[1]];
				else if (choice == 3)matrixes[index[0]] *= matrixes[index[1]];
				else if (choice == 4)matrixes[index[0]] /= matrixes[index[1]];

			}
			else if (choiceInfo == 2) {

				if (choice == 1) {

					cout << "Resault addition: " << matrixes[index[0]] + matrixes[index[1]] << endl;
				}
				else if (choice == 2) {

					cout << "Resault subtraction: " << matrixes[index[0]] - matrixes[index[1]] << endl;
				}
				else if (choice == 3) {

					cout << "Resault multiplication: " << matrixes[index[0]] * matrixes[index[1]] <<endl;
				}
				else if (choice == 4) {

					cout << "Resault division: " << matrixes[index[0]] / matrixes[index[1]] << endl;
				}

			}

		}
	}

}

template <typename T>
void MinimalValue(vector<Matrix<int>>& matrixes) {

	if (PrintMatrixes(matrixes) == true) {

		int index{ ChoiceMatrix(matrixes) };
		ClearScrean();

		T minT = matrixes[index].IsMinimal(matrixes[index]);
		cout << "Minimal value in " << index + 1 << "-th matrix: " << minT << endl;

	}

}

template <typename T>
void MaximalValue(vector<Matrix<int>>& matrixes) {

	if (PrintMatrixes(matrixes) == true) {

		int index{ ChoiceMatrix(matrixes) };
		ClearScrean();

		T maxT = matrixes[index].IsMaximal(matrixes[index]);
		cout << "Maximal value in " << index + 1 << "-th matrix: " << maxT << endl;

	}

}

int main() {

	srand(time(nullptr));

	vector<Matrix<int>> matrixes;
	int choice{ 0 };

	do {

		do {

			ClearScrean();
			cout << "[1] - Print matrixes\n[2] - Print info about matrix\n[3] - Add new matrix\n"
				 << "[4] - Delete matrix\n[5] - Change size array in matrix(Don't save information)\n"
				 << "[6] - Change size array in matrix(Save information)\n[7] - Change value in matrix\n"
				 << "[8] - Arithmetic operations with matrices\n"
				 << "[9] - Find minimal value\n[10] - Find maximal value\n[0] - Exit" << endl;

			if (choice >= 0 && choice <= 10)cout << "Enter your choice: ";
			else cout << "There is no such choice!\nEnter your choice again: ";

			cin >> choice;

		} while (choice < 0 || choice > 10);

		ClearScrean();

		switch (choice) {

		case 1:PrintMatrixes(matrixes); break;

		case 2:PrintInfoMatrix(matrixes); break;

		case 3:matrixes.push_back(AddMatrix<int>());; break;

		case 4:DeleteMatrix(matrixes); break;

		case 5:ResizeArrayDontSaveInfo(matrixes); break;

		case 6:ResizeArraySaveInfo(matrixes); break;

		case 7:ChangeValue(matrixes); break;

		case 8:ArithmeticOperations(matrixes); break;

		case 9:MinimalValue<int>(matrixes); break;

		case 10:MaximalValue<int>(matrixes); break;

		}

		if (choice != 0)Enter();

	} while (choice != 0);

	return 0;
}