//Taqdeer Grewal, 100252483
//Assignment 5: 2150
//Polynomials
#include "Polynomial.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
	cout<<"POLYNOMIALS";
	cout<<"\n\n*****************************************";
	cout<<"\nTesting the examples given in assignment";
	Polynomial ex1,ex2,a,b,c;
	ex1.read(5,2,3);ex1.read(2,8,5);ex1.read(-3,5,1);ex1.read(7,5,2);
	cout<<"\nex1: "<<ex1;
	ex2.read(103,1,1);ex2.read(3,2,1);ex2.read(1,1,4);ex2.read(1,5,100);
	cout<<"\nex2: "<<ex2;
	a.read(5,2,3);a.read(2,8,5);a.read(1,1,0);a.read(7,0,0);
	cout<<"\na: "<<a;
	b.read(-2,8,5),b.read(7,8,1),b.read(3,2,1);
	cout<<"\nb: "<<b;
	c=a+b;
	cout<<"\nAfter addition c=a+b: ";
	cout<<"\nc: "<<c;
	a.differentiateX();
	cout<<"\nAfter differentiating a w.r.t x: ";
	cout<<"\a: "<<a;
	b.differentiateY();
	cout<<"\nAfter differentiating a w.r.t y: ";
	cout<<"\a: "<<b;

	cout<<"\n\n*****************************************";
	cout<<"\nTesting input from file";
	Polynomial p;
	ifstream infile;
	ofstream outfile;
	int n,cof,x,y;
	//the filaname has been hardcoded because it was mentioned in the assignment
	//so, one does not have to input it repeatedly. Just call- readFile
	infile.open("polys.txt");
	outfile.open("polysOutput.txt");
	outfile<<"Please note that I know how to create a new polynomial upon differentiating";
	outfile<<"\nIt has been tested under 'My tests'";
	outfile<<"\nThe following tests will actually manipulate the original polynomial upon differentiation";
	while(!infile.eof()){
		infile>>n;
		for (int j=0 ; j<n; j++){
			infile>>cof>>x>>y;
			p.read(cof,x,y);
		}
		p.sort();
		outfile<<"\n\np: "<<p;
		outfile<<"\np+p: "<<p+p;
		p.differentiateX();
		outfile<<"\ndifferentiate w.r.t X: "<<p;
		p.differentiateY();
		outfile<<"\ndifferentiate w.r.t Y: "<<p;
		p.reset();
	}
	infile.close();
	outfile.close();
	cout<<"\nPlease find polysOutput.txt in your folder";
	cout<<"\n\n*****************************************";
	cout<<"\nMy Tests";
	Polynomial my1,my2;
	cout<<"\nEmpty my1: "<<my1;
	my1.read(0,0,0);my1.read(1,1,1);
	cout<<"\nmy1: "<<my1;
	my2=my1+my1;
	cout<<"\nmy2=my1+my1: "<<my2;
	my1.reset();
	cout<<"\nreset my1: "<<my1;
	cout<<"\nBut my2: "<<my2<<" remains same : )";
	cout<<"\nTesting differentiate X which returns a new polynomial rather than changing the existing one";
	Polynomial differXa,differXb;
	differXa.read(3,2,1);differXa.read(4,5,6);
	cout<<"\ndifferXa before differentiation: "<<differXa;
	cout<<"\ndifferXb before differentiation: "<<differXb; 
	differXb=differX(differXa);
	cout<<"\ndifferXa after differentiation: "<<differXa;
	cout<<"\ndifferXb after differentiation: "<<differXb; 
	
	cout<<"\n\n*****************************************";
	cout<<"\nTesting BIG THREE\n";
	Polynomial bigThree;
	bigThree.read(1,2,3);
	bigThree.read(4,5,6);
	cout<<"bigThree: "<<bigThree;
	cout<<"\nTesting Copy Constructor: ";
	Polynomial bigThreeCopy(bigThree);
	cout<<bigThreeCopy;
	cout<<"\nTesting = Operator: ";
	Polynomial bigThreeAss;
	bigThreeAss=bigThree;
	bigThree.reset();
	cout<<bigThreeAss;
	
	cout<<"\n\n*****************************************";
	cout<<"\nUser Test";
	Polynomial userTest,u; int num;
	cout<<"\nDo you want to test your values?: ";
	cout<<"\nEnter number of terms in a polynomial: ";
	cin>>num;
	userTest.readPoly(num);
	cout<<"\nYour polynomial: "<<userTest;
	userTest.differentiateX();
	cout<<"\nAfter differentiating w.r.t x: "<<userTest;
	userTest.differentiateY();
	cout<<"\nAfter differentiating w.r.t y: "<<userTest;
	u.read(3,2,0);
	cout<<"\nAdd +3x^2y^0 to your polynomial";
	cout<<"\nAfter adding: "<<userTest;
	
	return 0;
}
