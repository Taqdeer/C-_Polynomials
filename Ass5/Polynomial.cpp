//Taqdeer Grewal, 100252483
//Assignment 5: 2150
//Polynomials
#include "Polynomial.h"
#include <iostream>
#include <fstream>

//Term implementation
Term::Term(){ coeff=deg_x=deg_y=0; }
int Term::getCoeff() const { return coeff; }
int Term::getX() const { return deg_x; }
int Term::getY() const { return deg_y; }
void Term::setCoeff(int cof) { coeff=cof; return; }
void Term::setX(int x){ deg_x=x; return; }
void Term::setY(int y){ deg_y=y; return; }

//struct compare
bool Compare::operator()(int x, int y){
	if(x<y) return true;
	else return false;
}

//Polynomial
Polynomial::Polynomial(){
	poly=nullptr;
}
void Polynomial::readPoly(int n){
	int cof, x, y;
	for (int i=0; i<n; i++){
		std::cin>>cof>>x>>y;
		read(cof,x,y);
	}
	return;
}
void Polynomial::read(int cof, int x, int y){
	poly=createNode(cof,x,y,poly);
	//stores a sorted polynomial; 
	//i was a bit confused why to make sort public when we will never use it in test program?
	sort();
	poly=removeZero(poly);
	return;
}
Polynomial::Node* Polynomial::createNode(int cof, int xDeg, int yDeg, Node *p){
	Node *newNode=new Node;
	Term *newTerm= new Term;
	newTerm->setCoeff(cof);
	newTerm->setX(xDeg);
	newTerm->setY(yDeg);
	newNode->trm= newTerm;
	//creates a node at the front of the passed list p's head
	newNode->next=p;
	return newNode;
}
std::ostream& operator <<(std::ostream& out, const Polynomial& p){
	Polynomial::Node *ply=p.poly;
	while(ply!=nullptr){
		out<<" + "<<ply->trm->getCoeff()<<"x^"<<ply->trm->getX()<<"y^"<<ply->trm->getY(); 
		ply=ply->next;
	}
	return out;
}
const Polynomial differX(const Polynomial& a){
	Polynomial result;
	Polynomial::Node *p=a.poly, *resultPoly=nullptr;
	while (p!=nullptr){
		//does not manipulate a's data but creates a new Polynomial
		resultPoly=Polynomial::createNode(p->trm->getCoeff()*p->trm->getX(),p->trm->getX()-1,p->trm->getY(),resultPoly);
		p=p->next;
	}
	result.poly=resultPoly;
	result.sort();
	return result;
}
void Polynomial::differentiateX(){
	Node *p=poly;
	while(p!=nullptr){
		//"sets" or manipulates the data of the object
		p->trm->setCoeff(p->trm->getCoeff()*p->trm->getX());
		p->trm->setY(p->trm->getX()-1);
		p=p->next;
	}
	poly=removeZero(poly);
	return;
}
void Polynomial::differentiateY(){
	Node *p=poly;
	while(p!=nullptr){
		p->trm->setCoeff(p->trm->getCoeff()*p->trm->getY());
		p->trm->setY(p->trm->getY()-1);
		p=p->next;
	}
	poly=removeZero(poly);
	return;
}
const Polynomial operator+(const Polynomial& a, const Polynomial& b){
	Polynomial result;
	Polynomial::Node *apoly=a.poly, *bpoly=b.poly;
	Polynomial::Node *p=nullptr;
	while(apoly!=nullptr && bpoly!=nullptr){
		//check with x first
		if (apoly->trm->getX() > bpoly->trm->getX()){
			//creates a new node instead os exchanging the pointers
			p=Polynomial::createNode(apoly->trm->getCoeff(),apoly->trm->getX(),apoly->trm->getY(),p);
			apoly=apoly->next;
		}
		else if(apoly->trm->getX() < bpoly->trm->getX()){
			p=Polynomial::createNode(bpoly->trm->getCoeff(),bpoly->trm->getX(),bpoly->trm->getY(),p);
			bpoly=bpoly->next;
		}
		//degree x is equal at this point so check y
		else{
			if (apoly->trm->getY() < bpoly->trm->getY()){
				p=Polynomial::createNode(bpoly->trm->getCoeff(),bpoly->trm->getX(),bpoly->trm->getY(),p);
				bpoly=bpoly->next;
			}
			else if(apoly->trm->getY() > bpoly->trm->getY()){
				p=Polynomial::createNode(apoly->trm->getCoeff(),apoly->trm->getX(),apoly->trm->getY(),p);
				apoly=apoly->next;
			}
			//degree y is not equal
			//so add the coeff
			else{
				p=Polynomial::createNode(apoly->trm->getCoeff()+bpoly->trm->getCoeff(),apoly->trm->getX(),apoly->trm->getY(),p);
				apoly=apoly->next;
				bpoly=bpoly->next;
			}
		}
	}
	//if one of the polynomial has finished, then just "hard copy" the other one
	if(apoly==nullptr && bpoly!=nullptr){
		p=Polynomial::copyPolynomial(bpoly,p);
	}
	else if(apoly!=nullptr && bpoly==nullptr){
		p=Polynomial::copyPolynomial(apoly,p);
	}
	//removes all the zeroes
	p=Polynomial::removeZero(p);
	result.poly=p;
	result.sort();
	return result;
}
//this function can also be used at other places- e.g. in reading the polynomial
Polynomial::Node* Polynomial::removeZero(Node *p){
	Node *ans=p;
	if(p==nullptr) return p;
	//if the very first term is zero then just smply delete it
	if(p->trm->getCoeff()==0){
		Node *discard=p;
		p=p->next;
		ans=ans->next;
		delete discard;
	}
	
	//delete zeroes in the rest of the list
	while(p!=nullptr){
		Node *q=p; p=p->next;
		if	(p!=nullptr && p->trm->getCoeff()==0){
			Node *discard=p;
			p=p->next;
			q->next=p;
			delete discard;
		}
	}
	return ans;
}
//makes a hard copy by creating a new list
Polynomial::Node* Polynomial::copyPolynomial(Node *p, Node *q){
	while(p!=nullptr){
		q=createNode(p->trm->getCoeff(),p->trm->getX(),p->trm->getY(),q);
		p=p->next;
	}
	return q;
}
void Polynomial::sort(){
	Compare cmp;
	poly=mergeSort(poly,cmp);
	return;
}
Polynomial::Node* Polynomial::mergeSort(Node *low, Compare cmp){
	if(low==nullptr || low->next==nullptr){
		return low;
	}
	Node *middle=findMiddle(low);
	//if there are only two terms left, i.e. middle next Node is nullptr then just merge them
	if(middle->next==nullptr){
		low->next=nullptr;
		return merge(low,middle,cmp);
	}
	//otherwise treat the middle's next node as high and sort it separately
	Node *high = middle->next;
	middle->next=nullptr;
	low=mergeSort(low,cmp);
	high=mergeSort(high,cmp);
	return merge(low, high, cmp);
}
Polynomial::Node* Polynomial::findMiddle(Node *p){
	//the faster moves two times with every single move of slower
	//so finda the middle in just one pass
	Node *faster, *slower;
	if(p==nullptr) return nullptr;
	else faster=slower=p;
	while(faster!=nullptr){
		if(faster->next==nullptr){
			return slower;
		}
		else{
			faster=faster->next->next;
			slower=slower->next;
		}
	}
	return slower;
}
//a part of the following function has been taken from a lecture by Dr. Gladys Mongan
//Year: Fall 2015
//Location: Langara college, CPSC 1160 Class
Polynomial::Node* Polynomial::merge(Node *p, Node *q, Compare cmp){
	if (p==nullptr){
		return q;
	}
	if (q==nullptr){
		return p;
	}
	//sort based on degree x
	if (cmp(q->trm->getX() , p->trm->getX())){
		p->next=merge(p->next,q,cmp);
		return p;
	}
	else if (cmp(p->trm->getX(), q->trm->getX())){
		q->next=merge(p,q->next,cmp);
		return q;
	}
	else {
		//if x is equal then sort based on degree y
		if(cmp(q->trm->getY() , p->trm->getY())){
			p->next=merge(p->next,q,cmp);
			return p;
		}
		else if(cmp(p->trm->getY(), q->trm->getY())){
			q->next=merge(p,q->next,cmp);
			return q;
		}
		//if the terms with same degree are being entered
		else return nullptr;
	}
	//to avoid the warning of "control reaches end of non void function"
	return nullptr;
}
Polynomial::Node* Polynomial::deletePolynomial(Node *p){
	while(p!=nullptr){
		Node *discard= p;
		p=p->next;
		delete discard->trm;
		delete discard;
	}
	p=nullptr;
	return p;
}
void Polynomial::reset(){
	poly=deletePolynomial(poly);
}
/////////////////////////////////////////////
//BIG THREE
Polynomial::Polynomial(const Polynomial& rtSide){
	if(rtSide.poly==nullptr) poly=nullptr;
	else poly=copyPolynomial(rtSide.poly,nullptr);
	sort();
}
Polynomial& Polynomial::operator=(const Polynomial& rtSide){
	if(poly!=nullptr) poly=deletePolynomial(poly);
	poly=copyPolynomial(rtSide.poly,poly);
	sort();
	return *this;
}
Polynomial::~Polynomial(){
	poly=deletePolynomial(poly);
}
