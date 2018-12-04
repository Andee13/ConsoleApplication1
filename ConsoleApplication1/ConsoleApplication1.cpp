#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

class objectOfCalculation {
protected:
	double calculatedParametr;
	virtual void inputDataFromFile(ifstream &in) = 0;
	virtual void outputDataToFile(ofstream &out) = 0;
};
class ResistanceForce:public objectOfCalculation {
	double fi;
	double V;
	double d;
	double p;
	double Re;
	double u;
public:
	void inputDataFromFile(ifstream &in) {
		in >> p;
		in >> V;
		in >> d;
		in >> u;
	}
	void outputDataToFile(ofstream &out) {
		out << "p = "<< p << " V = " << V << " d = " << d << " u = " << u << endl;
	}
	void print() {
		cout << "p = " << p << " V = " << V << " d = " << d << " u = " << u << endl;
	}
	void calculate() {
		calculatedParametr = d;
		if (u != 0) {
			double Re = (V * d * p) / u;
			if (Re <= 2) {
				fi = 24 / Re;
			}
			else if (Re > 2 && Re <= 520) {
				fi = 18.5 / (powl(Re, 0.6));
			}
			else if (Re > 520 && Re < 2 * 10) {
				fi = 0.44;
			}
			else {
				fi = NULL;
			}
		}
		else {
			cout << " u  = 0 " << endl;
		}

	}
	bool operator == (ResistanceForce &v){
		if (fi == v.fi && V == v.V && d == v.d && p == v.p && Re == v.Re && u == v.u) {
			return true;
		}
		return false;
	}
	bool operator != (ResistanceForce &v) {
		if (fi == v.fi && V == v.V && d == v.d && p == v.p && Re == v.Re && u == v.u) {
			return false;
		}
		return true;
	}
	bool operator <(ResistanceForce &v) {
		if (fi < v.fi && V < v.V && d < v.d && p < v.p && Re < v.Re && u < v.u) {
			return true;
		}
		return false;
	}
	bool operator <=(ResistanceForce &v) {
		if (fi <= v.fi && V <= v.V && d <= v.d && p <= v.p && Re <= v.Re && u <= v.u) {
			return true;
		}
		return false;
	}
	bool operator >(ResistanceForce &v) {
		if (fi > v.fi && V > v.V && d > v.d && p > v.p && Re > v.Re && u > v.u) {
			return true;
		}
		return false;
	}
	bool operator >=(ResistanceForce &v) {
		if (fi >= v.fi && V >= v.V && d >= v.d && p >= v.p && Re >= v.Re && u >= v.u) {
			return true;
		}
		return false;
	}

};
int main()
{
	ResistanceForce object1;
	ofstream out("D:\\Programming\\C++\\Курсовая 2 курс\\ConsoleApplication1\\OutputData.txt");
	ifstream in("D:\\Programming\\C++\\Курсовая 2 курс\\ConsoleApplication1\\InputData.txt");
	
	object1.inputDataFromFile(in);
	object1.print();
	system("pause");
}

