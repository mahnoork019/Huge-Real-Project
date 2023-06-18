#pragma once
#include<iostream>
#include<fstream>
using namespace std;
class HugeReal
{
private:
	int* Hn;
	int size;
	bool isNeg;
	int point_pos;
	//////////
	
	int base_d;
	long long size_d;
	short* Ds;
	long long dpi;
	////////////////
	

	static void insertAtEnd(int*& Vs, int& vSize, int T);
	static void insertAtFront(int*& Vs, int& vSize, int T);


	static HugeReal One();
	static HugeReal Zero();

public:
	HugeReal();
	HugeReal(int hs);
	HugeReal(const HugeReal&);
	HugeReal(ifstream& rdr);
	void Load(ifstream& rdr);
	void assign(const HugeReal&);

	const HugeReal& operator= (const HugeReal&);
	friend ostream& operator<< (ostream&, const HugeReal&);
	friend istream& operator>> (istream&, const HugeReal&);

	const HugeReal ADDQuantityWise(const HugeReal& H)const;
	const HugeReal SUBQuantityWise(const HugeReal& H)const;
	bool LessThanQuantityWise(const HugeReal& H) const;
	bool GreaterThanQuantityWise(const HugeReal& H)const;
	bool EqualQuantityWise(const HugeReal& H) const;

	const HugeReal operator+ (const HugeReal& H)const;
	const HugeReal operator- ()const;
	const HugeReal operator- (const HugeReal& H)const;
	const HugeReal& operator+= (const HugeReal& H);
	const HugeReal& operator-= (const HugeReal& H);

	bool operator >(const HugeReal& H)const;
	bool operator <(const HugeReal& H)const;
	bool operator ==(const HugeReal& H)const;
	bool operator !=(const HugeReal& H)const;
	bool operator <=(const HugeReal& H)const;
	bool operator >=(const HugeReal& H)const;

	// increment and decrement
	HugeReal operator ++();
	HugeReal operator --();
	HugeReal operator ++(int);
	HugeReal operator --(int);


	const HugeReal operator* (const HugeReal& H)const;
	const HugeReal& operator*= (const HugeReal& H);
	const HugeReal operator/ (const HugeReal& H)const;
	const HugeReal operator % (const HugeReal& H)const;
	const HugeReal& operator%=(const HugeReal& H);
	

	int& operator[](int i);
	int operator[](int i)const;

	void trim();

	~HugeReal();
};



