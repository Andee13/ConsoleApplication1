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
	double d;
	double p;
	double Re;
	double u;
	double S;
public:
	double V;
	void inputDataFromFile(ifstream &in) {
		in >> p;
		in >> V;
		in >> S;
		in >> d;
		in >> u;
	}
	void outputDataToFile(ofstream &out) {
		out <<"V = "<< V <<" S = " << S << " u = "<< u <<" Re = " << Re <<" p = "<< p << " d = "<< d << " fi = "<< fi << " calculatedobj = "<< calculatedParametr<< endl;
	}
	void print() {
		cout << "Data from file:\np = " << p << " V = " << V << " S = " << S << " d = " << d << " u = " << u << endl;
		cout << "Data after calculation:\n Re = " << Re << " fi = " << fi << " calculatedParametr = " << calculatedParametr << endl;
	}
	void calculate() {
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
		}
		else {
			cout << "Function with this data does not calculated fi = NULL" << endl;
		}
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
		S = obj.u;
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
	ResistanceForce obj1(), obj2(2,4,6,3,8);
	//Calculation of function
	ResistanceForce ar[13];
	ar[0].inputDataFromFile(in);
	ar[0].calculate();
	ar[0].print();
	ar[0].outputDataToFile(out);
	for (int i = 1; i < 13; i++) {
		cout << "object "<< i << endl;
		ar[i] = ar[i-1];
		ar[i].V += 1;
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

