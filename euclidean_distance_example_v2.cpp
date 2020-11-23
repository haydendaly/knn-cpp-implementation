#include <iostream>
#include <math.h> // pow(base,exponent)

using namespace std;

double calculateDistance(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	double distance;

	distance = pow(x, 2) + pow(y, 2);
	distance = sqrt(distance);                  

	return distance;
}

int main()
{
	double x1, y1, x2, y2;
	double distance;
	cout << "Enter x1:" << endl;
	cin >> x1;
	cout << "Enter y1:" << endl;
	cin >> y1;
	cout << "Enter x2:" << endl;
	cin >> x2;
	cout << "Enter y2:" << endl;
	cin >> y2;

	distance = calculateDistance(x1, y1, x2, y2);
	cout << "Distance Between (" << x1 << " , " << y1 << ") and (" << x2 << " , " << y2 << ") = " << distance << endl;
}
