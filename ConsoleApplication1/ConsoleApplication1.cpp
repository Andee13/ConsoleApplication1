#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

class objectOfCalculation {
protected:
	double calculatedParametr;
	virtual void calculate() = 0;
	virtual void inputDataFromFile(ifstream &in) = 0;
	virtual void outputDataToFile(ofstream &out) = 0;
};
class ResistanceForce:public objectOfCalculation {
	double fi;
	double d;
	double p;
	double Re;
	double u;
	double S;
	double V;
public:
	void inputDataFromFile(ifstream &in) {
		in >> p;
		in >> V;
		if (V < 8 || V > 20) {
			cout << "d is not in interval, correct it and start program" << endl;
			exit(0);
		}
		in >> d;
		if (d < 0.001 || d > 0.003) {
			cout << "d is not in interval, correct it and start program" << endl;
			exit(0);
		}
		in >> S;
		in >> u;
	}
	void outputDataToFile(ofstream &out) {
		if (fi != NULL) {
			out << "V = " << V << " S = " << S << " u = " << u << " Re = " << Re << " p = " << p << " d = " << d << " fi = " << fi << " calculatedobj = " << calculatedParametr << endl;
		}
		else{
			out << "object can't be calculated" << endl;
		}
	}
	void print() {
		if (fi != NULL) {
			cout << "Data Input:\np = " << p << " V = " << V << " S = " << S << " d = " << d << " u = " << u << endl;
			cout << "Data after calculation:\n Re = " << Re << " fi = " << fi << " calculatedParametr = " << calculatedParametr << endl;	
		}
		if (fi == NULL) {
			cout << "Object can't be calculated as fi = NULL" << endl;
		}
	}
	void calculate() {
		if (V < 8 || V > 20) {
			fi = NULL;
			cout << "V isn't in interval" << endl;
			return;
		}
		if (u != 0) {
			Re = (V * d * p) / u;
			if (Re <= 2) {
				fi = 24 / Re;
			}
			else if (Re > 2 && Re <= 520) {
				fi = 18.5 / (powl(Re, 0.6));
			}
			else if (Re > 520 && Re < powl(2, 10)) {
				fi = 0.44;
			}
			else {
				fi = NULL;
			}
		} else {
			cout << " u  = 0  Function with this data does not calculated" << endl;
		}
		if (fi != NULL) {
			calculatedParametr = fi * S * p * V * V / 2;
		} else {
			cout << "Function with this data does not calculated fi = NULL" << endl;
		}
	}
	void operator +=(int a) {
		V += a;
	}
	void operator = (ResistanceForce &v) {
		V = v.V;
		d = v.d;
		p = v.p;
		u = v.u;
		S = v.S;
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
		if (V < v.V && calculatedParametr < v.calculatedParametr) {
			return true;
		}
		return false;
	}
	bool operator >(ResistanceForce &v) {
		if (V > v.V && calculatedParametr > v.calculatedParametr) {
			return true;
		}
		return false;
	}
	bool operator <=(ResistanceForce &v) {
		if (V <= v.V && calculatedParametr <= v.calculatedParametr) {
			return true;
		}
		return false;
	}
	bool operator >=(ResistanceForce &v) {
		if ( V >= v.V && calculatedParametr >= v.calculatedParametr) {
			return true;
		}
		return false;
	}

	ResistanceForce() {}
	ResistanceForce(double square, double volume, double p, double r, double u) :S(square),V(volume),p(p), d(r), u(u){}
	ResistanceForce(const ResistanceForce &obj) {
		p = obj.p;
		V = obj.V;
		S = obj.S;
		u = obj.u;
		d = obj.d;
	}

};
int main()
{
	ResistanceForce object1;
	ofstream out("OutputData.txt");
	ifstream in("InputData.txt");
	if (!in) {
		cout << "file doesn't exist" << endl;
		system("pause");
		exit(0);
	}

	object1.inputDataFromFile(in); 
	object1.calculate();
	object1.print();
	object1.outputDataToFile(out);
	//constructors
	ResistanceForce obj1(), obj2(2, 4, 6, 3, 8), obj3(obj2);
	if (obj2 == obj3) {
		cout << "obj2 == obj3" << endl;
	} else {
		cout << "obj2 != obj3" << endl;
	}
	//Calculation of function
	ResistanceForce ar[10];
	ar[0].inputDataFromFile(in);
	ar[0].calculate();
	ar[0].print();
	ar[0].outputDataToFile(out);

	double v;
	cout << "Enter increment for V " << endl;
	cin >> v;
	for (int i = 1; i < 10; i++) {
		cout << "object "<< i << endl;
		ar[i] = ar[i-1];
		ar[i] += v;
		ar[i].calculate();
		ar[i].print();
		ar[i].outputDataToFile(out);
	}
	if (object1 == ar[0]) {
		cout << "obj1 = ar[0]" << endl;
	}
	if (object1 != ar[1]) {
		cout << "obj1 != ar[0]" << endl;
	}
	if (object1 <= ar[1]) {
		cout << "obj1 <=  ar[0]" << endl;
	}
	if (ar[1]  >= object1) {
		cout << "obj1 >=  ar[0]" << endl;
	}
	if (object1 < ar[1]) {
		cout << "object1 < ar[1]" << endl;
	}
	if (ar[1] > object1) {
		cout << "ar[1] > object1" << endl;
	}
	system("pause");
}

