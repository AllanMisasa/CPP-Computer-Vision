#include <format>
#include <iostream>

using namespace std;

int multiply(int x, int y) {
	return x * y;
}


int main() {
	int x = 42;
	int y = 7;

	if (x > y) {					// If... else
		cout << "x is above y" << endl;
	}
	else {
		cout << "x is below  y" << endl;
	}

	auto s = x < y ? "yes" : "no";  //Ternary condition
	cout << "answer is: " << s;		//Reason to use extra insertion operator (<<)
}