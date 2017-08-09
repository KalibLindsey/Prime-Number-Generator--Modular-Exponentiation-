// Name : Kalib Lindsey
// Date : March 10, 2016
// Course : CS 315 - Algorithms

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

vector <int> GenNum(int n)
{
	vector <int> numVec;
	srand(rand());
	if (n == 1)
	{
		numVec.push_back(1);
	}
	else if (n == 2)
	{
		numVec.push_back(1);
		numVec.push_back(1);
	}
	else
	{
		numVec.push_back(1);
		for (int i = 1; i < n - 1; i++)
		{
			numVec.push_back((rand())%2);
		}
		numVec.push_back(1);
	}

	return numVec;
}

void printNumber(vector<int> numVec)
// Input  : One vector of numbers in reverse order (LSD --> MSD)
// Output : Prints the number in normal order (MSD -- > LSD)
{
	for (int i = numVec.size() - 1; i >= 0; i--)
		cout << numVec[i];
}

void printVector(vector<int> numVec)
// Input  :	One vector of numbers in reverse order (LSD --> MSD)
// Output : Prints the vector (with brackets,commas) in reverse order (LSD --> MSD)
{
	cout << "[";
	for (int i = 0; i < numVec.size(); i++)
	{
		cout << numVec[i];
		if (i != numVec.size() - 1)
		{
			cout << ",";
		}
	}
	cout << "]";
}

vector <int> Addition(vector<int> xVec, vector<int> yVec)
// Input  : Two vectors containing numbers in reverse order (LSD --> MSD)
// Output : One vector containing the sum in reverse order (LSD --> MSD)
{
	if (xVec.size() != yVec.size())
	{
		if (xVec.size() > yVec.size())
		{
			while (xVec.size() != yVec.size())
			{
				yVec.push_back(0);
			}
		}
		else
		{
			while (xVec.size() != yVec.size())
			{
				xVec.push_back(0);
			}
		}
	}
	int n = xVec.size();

	int carry = 0;
	int inSum, posSum;
	vector <int> sum;
	for (int i = 0; i < n; i++)
	{
		inSum = carry + xVec[i] + yVec[i];

		if (inSum >= 2)
		{
			posSum = inSum - 2;
			sum.push_back(posSum);
			carry = 1;
		}
		else
		{
			sum.push_back(inSum);
			carry = 0;
		}
	}
	if (carry == 1)
	{
		sum.push_back(1);
	}

	return sum;
}

vector <int> Multiplication(vector<int> xVec, vector<int> yVec)
// Input  : Two vectors containing numbers in reverse order (LSD --> MSD)
// Output : One vector containing the product in reverse order (LSD --> MSD)
{
	vector <int> pVec;

	for (int i = 0; i < yVec.size(); i++)
	{
		if (i != 0)
			xVec.insert(xVec.begin(), 0);
		if (yVec[i] == 1)
			pVec = Addition(xVec, pVec);
	}
	return pVec;
}

bool compare(vector<int> xVec, vector<int> yVec)
// Input  :	Two vectors containing numbers in reverse order (LSD --> MSD)
// Output : Bool which will be true if the first number is greater than or 
//			equal to the second.  False if the second number is greater than
//			the first
{
	bool comFlag = true;

	int xLength = xVec.size();
	int yLength = yVec.size();

	if (yLength > xLength)
	{
		comFlag = false;
	}

	else if (xLength == yLength)
	{
		for (int i = xLength - 1; i >= 0; i--)
		{
			if (xVec[i] > yVec[i])
			{
				break;
			}
			else if (xVec[i] < yVec[i])
			{
				comFlag = false;
				break;
			}
		}
	}

	return comFlag;
}

vector <int> Subtraction(vector<int> xVec, vector<int> yVec)
// Input  : Two vectors containing numbers in reverse order (LSD --> MSD)
// Output : One vector containing the difference in reverse order (LSD --> MSD)
{
	if (xVec.size() != yVec.size())
	{
		if (xVec.size() > yVec.size())
		{
			while (xVec.size() != yVec.size())
				yVec.push_back(0);
		}
		else
		{
			while (xVec.size() != yVec.size())
				xVec.push_back(0);
		}
	}
	int n = xVec.size();

	int carry = 0;
	vector <int> dVec;

	for (int i = 0; i < n; i++)
	{
		if ((carry + xVec[i] + yVec[i]) % 2 == 1)
			dVec.push_back(1);
		else
			dVec.push_back(0);

		if (carry + yVec[i] + dVec[i] >= 2)
			carry = 1;
		else
			carry = 0;
	}

	for (int i = dVec.size() - 1; i >= 0; i--)
	{
		if (dVec[i] == 1)
			break;
		else if (dVec[i] == 0)
			dVec.pop_back();
	}

	return dVec;
}

vector <vector <int>> Division(vector<int> xVec, vector<int> yVec)
// Input  : Two vectors containing numbers in reverse order (LSD --> MSD)
// Output : One vector containing the two vectors, the first of which is
//			the vector of the quotient (LSD --> MSD), the second of which
//			is the vector of the remainder (LSD --> MSD)
{
	vector <vector<int>> dVec;
	vector <int> qVec, rVec;

	qVec.push_back(0);
	rVec.push_back(0);

	vector <int> oneVec, twoVec;

	twoVec.push_back(0);
	twoVec.push_back(1);

	oneVec.push_back(1);

	for (int i = xVec.size() - 1; i >= 0; i--)
	{
		qVec = Multiplication(twoVec, qVec);
		rVec = Multiplication(twoVec, rVec);

		if (xVec[i] == 1)
			rVec = Addition(rVec, oneVec);
		bool comFlag = compare(rVec, yVec);
		if (comFlag)
		{
			rVec = Subtraction(rVec, yVec);
			qVec = Addition(qVec, oneVec);
		}
		/*cout << "i = " << i << "	q = ";
		printVector(qVec);
		cout << "	r = ";
		printVector(rVec);
		cout << endl;*/
	}

	dVec.push_back(qVec);
	dVec.push_back(rVec);

	return dVec;
}

vector<int> modExp(vector<int> xVec, vector<int> yVec, vector<int> nVec)
// Input  : Three vectors containing numbers in reverse order (LSD --> MSD)
// Output : One vector containing the result of the modular exponential
//			expression with digits in reverse order (LSD --> MSD)
{
	vector<int> zVec, rVec;  // declare the result vector, as well as the remainder vector ( which ended up not being used )
	vector<vector<int>> dVec;   // vector needed to receive from the division function, to pull the remainder
	zVec.push_back(1);       // the vector must be initialized at 1

							 /*cout << "x = ";
							 printNumber(xVec);
							 cout << "\t";
							 printVector(xVec);

							 cout << "y = ";
							 printNumber(yVec);
							 cout << "\t";
							 printVector(yVec);

							 cout << "n = ";
							 printNumber(nVec);
							 cout << "\t";
							 printVector(nVec);*/

	for (int i = yVec.size() - 1; i >= 0; i--)
	{
		zVec = Multiplication(zVec, zVec);	// First the number must be squared
		dVec = Division(zVec, nVec);			// Then the modulus N must be considered, so DIVIDE by N, and...
		zVec = dVec[1];						// .... extract the remainder
		if (yVec[i] == 1)
		{
			zVec = Multiplication(zVec, xVec);
			dVec = Division(zVec, nVec);
			zVec = dVec[1];
		}
		/*cout << "i = " << i << "\t";
		printNumber(zVec);
		cout << "\t";
		printVector(zVec);
		cout << endl;*/

	}
	return zVec;							// Finally, we return back the result vector

}

vector<int> modAdd(vector<int> xVec, vector<int> yVec, vector<int> nVec)
{
	vector<int> sumVec,difVec;
	sumVec = Addition(xVec, yVec);
	bool comFlag;
	comFlag = compare(sumVec, nVec);
	if (comFlag == true)
	{
		difVec = Subtraction(sumVec, nVec);
		return difVec;
	}
	else
	{
		return sumVec;
	}
}

bool checkPrime(vector<int>nVec)
{
	vector<int> oneVec, xVec, yVec, zVec;
	bool primeFlag = false;
	oneVec.push_back(1);

	xVec.push_back(1);
	xVec.push_back(1);

	yVec = Subtraction(nVec, oneVec);

	zVec = modExp(xVec, yVec, nVec);

	if (zVec.size() == 1 && zVec[0] == 1)
	{
		primeFlag = true;
	}
	return primeFlag;
}

bool bruteForce(vector<int>nVec)
{
	vector<int> iVec, oneVec, twoVec;
	bool primeFlag = true;
	iVec.push_back(1);
	oneVec.push_back(1);

	twoVec.push_back(0);
	twoVec.push_back(1);
	
	while (!compare(Multiplication(iVec, iVec), nVec) && primeFlag == true)
	{
		vector<vector<int>> dVec;
		vector<int> rVec;
		dVec = Division(nVec, iVec);
		/*printNumber(nVec);
		cout << " divided by ";
		printNumber(iVec);
		cout << endl;*/
		rVec = dVec[1];
		if (rVec.size() == 1 && rVec[0] == 0)
		{
			primeFlag == false;
			break;
		}
		iVec = Addition(iVec, twoVec);
	}
	return primeFlag;
}

vector<int> findOne(int n)
{
	int i = 1;

	bool primeFlag = false;
	bool bruteFlag = false;
	vector<int> primeVec;

	while (primeFlag == false)
	{
		vector<int> numVec;
		numVec = GenNum(n);
		primeFlag = checkPrime(numVec);
		if (primeFlag == true)
		{
			bruteFlag = bruteForce(numVec);
			printNumber(numVec);
			if (bruteFlag == true)
			{
				cout << "\tPrime!" << endl;
				primeVec = numVec;
			}
			else
				cout << "\tNot Prime!" << endl;
		}
		cout << i << endl;
		i++;
	}
	return primeVec;
}

vector<int> findOneMEonly(int n)
{
	int i = 1;

	bool primeFlag = false;
	vector<int> primeVec;

	while (primeFlag == false)
	{
		vector<int> numVec;
		numVec = GenNum(n);
		cout << i << ": ";
		printNumber(numVec);

		primeFlag = checkPrime(numVec);

		if (primeFlag == true)
		{
			cout << "\tPrime!" << endl;
			primeVec = numVec;
		}
		else
		{
			cout << "\tNot Prime!" << endl;
		}
		i++;
	}
	return primeVec;
}

int main()
{
	cout << "What length n do you want your numbers to be? ";
	int n;
	cin >> n;

	int func;
	cout << "Which function would you like to perform?" << endl;
	cout << "1. Generate 100 " << n << "-bit numbers, primality checked by mod exp" << endl;
	cout << "2. Generate 100 " << n << "-bit numbers, primality checked by mod exp & brute force" << endl;
	cout << "3. Generate a single prime " << n << "-bit number (brute force)" << endl;
	cout << "4. Generate a single prime " << n << "-bit number (mod exp only)" << endl;
	cin >> func;

	srand(time(NULL));

	if (func == 1)
	{
		vector <vector <int>> NumVec;
		int i = 1;
		while (NumVec.size() < 100)
		{
			vector <int> RandNum;
			RandNum = GenNum(n);
			bool primeFlag = checkPrime(RandNum);
			if (primeFlag == true)
			{

				NumVec.push_back(RandNum);
				cout << i << ": ";
				printNumber(RandNum);
				cout << endl;
				i++;
			}
		}
	}
	else if (func == 2)
	{
		vector <vector <int>> NumVec;
		int i = 1;
		while (NumVec.size() < 100)
		{
			int BFcount = 0;
			vector <int> RandNum;
			RandNum = GenNum(n);
			bool primeFlag = checkPrime(RandNum);
			if (primeFlag == true)
			{
				NumVec.push_back(RandNum);
				cout << i << ": ";
				printNumber(RandNum);
				bool bruteFlag = bruteForce(RandNum);
				if (bruteFlag == true)
				{
					BFcount++;
					cout << "\tBrute force check: Prime!";
				}
				else
				{
					cout << "\tBrute force check: Not Prime!";
				}
				cout << endl;
				i++;
			}
		}
	}
	else if (func == 3)
	{
		vector<int> NumVec;
		NumVec = findOne(n);
	}
	else if (func == 4)
	{
		vector<int> NumVec;
		NumVec = findOneMEonly(n);
	}

	system("pause");

	return 0;
}