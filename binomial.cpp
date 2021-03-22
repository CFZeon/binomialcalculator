#include <iostream>
#include <unordered_map>
#include <cmath>

using namespace std;

void instructions() {
	cout << "Key in your input\n ";
	cout << "0: change n and p values\n ";
	cout << "1: probability fixed x\n 2: probability of range of 0 to x\n 3: probability of range of x to y\n 4: expected value\n 5: quit\n";
}

// Binomial Coefficient function code from https://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/
double nCr(int n, int k) {
	double res = 1;

	// Since C(n, k) = C(n, n-k) 
	if (k > n - k)
		k = n - k;

	// Calculate value of 
	// [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1] 
	for (int i = 0; i < k; ++i) {
		res *= (n - i);
		res /= (i + 1);
	}

	return res;
}

unordered_map<int, double> populateBinomialTable(unordered_map<int, double> binomialTable, int n, float p) {
	for (int i = 0; i <= n; i++) {
		binomialTable[i] = nCr(n, i) * (pow(p, i)) * (pow(1 - p, n - i));
	}
	return binomialTable;
}

int main(void) {
	int input;
	int n;
	float p;
	int x, y;
	float sum = 0;
	unordered_map<int, double> binomialTable;

	cout << "Input your n and p\n";
	cout << "n = ";
	cin >> n;
	cout << "p = ";
	cin >> p;
	binomialTable = populateBinomialTable(binomialTable, n, p);
	instructions();
	cout << "input is: ";
	cin >> input;
	while (input != 5) {
		if (input == 1) {
			cout << "X value is: ";
			cin >> x;
			cout << "P[X=" << x << "] = " << binomialTable[x] << endl;
		}
		else if (input == 0) {
			cout << "new n value is: ";
			cin >> n;
			cout << "new p value is: ";
			cin >> p;
			populateBinomialTable(binomialTable, n, p);
			cout << "Variables changed successfully!" << endl;
		}
		else if (input == 2) {
			cout << "X value is: ";
			cin >> x;
			for (int i = 0; i <= x; i++) {
				sum += binomialTable[i];
			}
			cout << "P[X<=" << x << "] = " << sum << endl;
		}
		else if (input == 3) {
			cout << "X value is: ";
			cin >> x;
			cout << "Y value is: ";
			cin >> y;
			for (int i = x; i <= y; i++) {
				sum += binomialTable[i];
			}
			cout << "P[" << x << " <= X <= " << y << "] = " << sum << endl;
		}
		else if (input == 4) {
			cout << "expected value is: " << n * p << endl;
		}
		else {
			cout << "invalid input";
		}
		cout << endl;
		sum = 0;
		instructions();
		cout << "input is: ";
		cin >> input;
	}
	return 0;
}
