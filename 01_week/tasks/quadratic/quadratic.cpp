#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>

void SolveQuadratic(int a, int b, int c) {
    using std::cout, std::setprecision;
    if(a == 0 && b == 0 && c == 0) {
      cout << "infinite solutions";
      return;
    }
    if(a == 0 && b == 0 && c != 0) {
      cout << "no solutions";
      return;
    }

    if(a != 0) { // two roots
		int discriminant = b * b - 4 * a * c;
		 
		cout << setprecision(6);
		if(discriminant > 0) {
		  double discriminantRoot = sqrt(discriminant);
		  double x1 = (-b - discriminantRoot) / (2.0*a);
		  double x2 = (-b + discriminantRoot) / (2.0*a);
		  cout << x1 << ' ' << x2;
		} else if(discriminant == 0){
		  double x1 = (-b) / (2.0*a);
		  cout << x1;
		} else {
		  cout << "no solutions";
		}
    } else { // only one root
      double x1 = static_cast<double>(-c) / b;
      cout << x1;
    }
}
