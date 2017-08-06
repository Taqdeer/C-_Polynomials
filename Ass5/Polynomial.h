//Taqdeer Grewal, 100252483
//Assignment 5: 2150
//Polynomials
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

//iostream has been included for overloaded << operator
#include <iostream>
class Term{
	public:
		//this class is using accessor and mutator functions to use private data
		Term();
		int getCoeff() const;
		int getX() const;
		int getY() const;
		void setCoeff(int cof);
		void setX(int x);
		void setY(int y);
	private:
		int coeff, deg_x, deg_y;
};

struct Compare{
	//this functor takes int parameters rather than Nodes because sometimes 
	//we need to compare with deg_x and sometimes deg_y
	bool operator()(int x, int y);
};

class Polynomial{
	public:
		Polynomial();
		//Big Three
		Polynomial(const Polynomial& rtSide);
		Polynomial& operator =(const Polynomial& rtSide);
		~Polynomial();
		//read n terms from standard input 
		void readPoly(int n);
		//create the polynomials with passed parameters
		//creates one Node->term at a time, so needs a for loop to create a polynomial with n terms
		void read( int cof, int x, int y);
		//calls mergeSort
		void sort();
		//deletes polynomial
		void reset();
		//differentiates with respect to x
		void differentiateX();
		//differentiate with respect to y
		void differentiateY();
		//adds 2 passed polynomials
		//note: it does not use the merge function used for sorting because it merges
		//the two polynomials by allocating memory to a new polynomial
		//The code is almost the same; the only difference is that it allocate snew memory
		friend const Polynomial operator +(const Polynomial& a, const Polynomial& b);
		//outputs polynomial
		friend std::ostream& operator <<(std::ostream& out, const Polynomial& p);
		//differentiate given polynomial and returns a new polynomial
		friend const Polynomial differX(const Polynomial& a);
	private:
		struct Node{
			Term *trm;
			Node *next;
		};
		Node *poly;
		static Node* createNode(int cof, int xDeg, int yDeg, Node *p);
		static Node* merge(Node *p, Node *q, Compare cmp);
		static Node* findMiddle(Node *p);
		static Node* mergeSort(Node *low, Compare cmp);
		static Node* copyPolynomial(Node *p, Node *q);
		static Node* deletePolynomial(Node *p);
		static Node* removeZero(Node *p);
};
#endif
