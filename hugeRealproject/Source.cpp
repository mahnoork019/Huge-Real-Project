#include<iostream>
#include<conio.h>
#include<fstream>
#include"HugeReal.h"
using namespace std;
int main()
{

	ifstream rdr("Real.txt");
	int hSize;
	HugeReal** hInt;
	rdr >> hSize;
	hInt = new HugeReal * [hSize] {};

	for (int i = 0; i < hSize; i++)
	{
		while (rdr.peek() == ' ' || rdr.peek() == '\n')
			rdr.ignore();
		hInt[i] = new HugeReal(rdr);
	}

	for (int i = 0; i < hSize; i++)
	{
		cout << *hInt[i] << endl;
	}
	
	cout << endl << endl << endl;
	cout << "Operators: " << endl << "+ for addition" << endl << "- for subtraction" << endl << "< for comparison" << endl <<
		"> for comparison" <<  endl << "= for comparison" << endl << "* for multiplication" << endl <<
		"/ for division" << endl;
	char opr, cont;
	int n1, n2;
	do
	{
		cout << "\n\n\nEnter the first number: ";
		cin >> n1;
		cout << "Enter the operator: ";
		cin >> opr;
		switch (opr)
		{
		case'+':
		{
			cout << "Enter the second number: ";
			cin >> n2;
			cout << endl << endl;
			cout << endl << "ans: " << (*hInt[n1]) + (*hInt[n2]) << endl;
			break;
		}
		case'-':
		{
			cout << "Enter the second number: ";
			cin >> n2;
			cout << endl << endl;
			cout << endl << "ans: " << (*hInt[n1]) - (*hInt[n2]) << endl;
			break;
		}
		case '<':
		{

			cout << "Enter the second number: ";
			cin >> n2;
			cout << endl << endl << endl;
			if ((*hInt[n1]) < (*hInt[n2]))
			{
				cout << (*hInt[n1]) << "is less than" << (*hInt[n2]);
			}
			else
			{
				cout << (*hInt[n2]) << "is less than" << (*hInt[n1]);
			}
			break;
		}
		case '>':
		{
			cout << "Enter the second number: ";
			cin >> n2;
			cout << endl << endl << endl;
			if ((*hInt[n1]) > (*hInt[n2]))
			{
				cout << (*hInt[n1]) << "is greater than" << (*hInt[n2]);
			}
			else
			{
				cout << (*hInt[n2]) << "is greater than" << (*hInt[n1]);
			}
			break;
		}
		case '=':
		{
			cout << "Enter the second number: ";
			cin >> n2;
			cout << endl << endl << endl;
			if ((*hInt[n1]) == (*hInt[n2]))
			{
				cout << (*hInt[n1]) << "is equal to" << (*hInt[n2]);
			}
			else
			{
				cout << (*hInt[n2]) << "is not equal to" << (*hInt[n1]);
			}
			break;
		}
		case'*':
		{
			cout << "Enter the second number: ";
			cin >> n2;
			cout << endl << endl;
			cout << endl << "ans: " << (*hInt[n1]) * (*hInt[n2]) << endl;
			break;
		}
		case' / ':
		{
			cout << "Enter the second number: ";
			cin >> n2;
			cout << endl << endl;
			cout << endl << "ans: " << (*hInt[n1]) / (*hInt[n2]) << endl;
			break;
		}
		default:
			cout << "Invalid Option !" << endl;
		}
		cout << "\n\nWant to continue(Y/N): ";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');
	return 0;
}
