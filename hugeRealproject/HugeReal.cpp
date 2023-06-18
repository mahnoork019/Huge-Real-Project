#include "HugeReal.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
HugeReal::HugeReal()
{
	this->size = 0;
	this->Hn = nullptr;
	this->isNeg = false;
	this->point_pos = 0;
}
HugeReal::HugeReal(int s)
{
	this->size = s;
	this->Hn = new int [s] {};
}
HugeReal::HugeReal(const HugeReal& H)
{
	assign(H);
}
void HugeReal::Load(ifstream& rdr)
{
	char sym = rdr.peek(), z = '0';
	if (sym == '-')
	{
		this->isNeg = true;
		rdr.ignore();
	}
	string N;
	getline(rdr, N);
	this->size = N.size();
	this->Hn = new int[N.size()];
	bool isFloat = false;
	for (int i = 0, j = 0;i < this->size; i++, j++)
	{
		if (N[j] == '.')
		{
			this->point_pos = this->size - i - 1;
			isFloat = true;
			j++;
		}
		this->Hn[this->size - i - 1] = N[j] - z;
	}
	if (isFloat)
	{
		this->size = N.size() - 1;
		int* NDs = new int[N.size() - 1] {};
		for (int i = 0;i < size;i++)
		{
			NDs[this->size - i - 1] = Hn[this->size - i];
		}
		delete[]Hn;
		Hn = NDs;
	}
}

HugeReal::HugeReal(ifstream& rdr)
{
	this->Load(rdr);
}
void HugeReal::insertAtEnd(int*& Vs, int& vSize, int T)
{
	int* HA = new int [vSize + 1] {};
	for (int i = 0; i < vSize;i++)
	{
		HA[i] = Vs[i];
	}
	HA[vSize] = T;
	delete[]Vs;
	Vs = HA;
	vSize++;
}
void HugeReal::insertAtFront(int*& Vs, int& vSize, int T)
{
	int* HA = new int [vSize + 1] {};
	for (int i = 0; i < vSize;i++)
	{
		HA[i + 1] = Vs[i];
	}
	HA[0] = T;
	delete[]Vs;
	Vs = HA;
	vSize++;
}
void HugeReal::assign(const HugeReal& H)
{
	this->size = H.size;
	this->Hn = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Hn[i] = H.Hn[i];
	}
	this->isNeg = H.isNeg;
	this->point_pos = H.point_pos;
}


const HugeReal& HugeReal:: operator= (const HugeReal& H)
{
	if (this == &H)
		return *this;
	delete[]this->Hn;
	this->assign(H);
	return *this;
}
ostream& operator<< (ostream&, const HugeReal& H)
{
	if (H.isNeg)
	{
		cout << "-";
	}
	else
		cout << "+";
	for (int i = H.size - 1; i >= 0; i--)
	{
		cout << H.Hn[i];
		if (i == H.point_pos)
			cout << ".";
	}
	return cout;
}
istream& operator>> (istream&, const HugeReal& H)
{
	for (int i = 0; i < H.size; i++)
	{
		cin >> H.Hn[i];
	}
	return cin;
}

int& HugeReal ::operator[](int i)
{
	if (i >= this->size)
	{
		int t = 0;
		return t;
	}
	return this->Hn[i];
}
int HugeReal :: operator[](int i)const
{
	if (i >= this->size)
	{
		return 0;
	}
	return this->Hn[i];
}


const HugeReal HugeReal::ADDQuantityWise(const HugeReal& H)const
{
	int Point_index = 0;
	int tBeforeD = this->point_pos;
	int tAfterD = this->size - (this->point_pos);
	int hBeforeD = H.point_pos;
	int hAfterD = H.size - (H.point_pos);
	int maxBefore = 0, maxAfter = 0;
	if (tBeforeD > hBeforeD)
	{
		maxBefore = tBeforeD;
		Point_index = this->point_pos;
	}
	else
	{
		maxBefore = hBeforeD;
		Point_index = H.point_pos;
	}
	if (tAfterD > hAfterD)
	{
		maxAfter = tAfterD;
	}
	else
		maxAfter = hAfterD;
	int total_max = maxBefore + maxAfter;
	HugeReal A;
	HugeReal B;
	int zeroes = max(this->size - tAfterD, H.size - hAfterD) - min(this->size - tAfterD, H.size - hAfterD);
	int a = 0, b = 0;
	HugeReal A2;
	HugeReal B2;
	if (this->size - tAfterD < H.size - hAfterD)
	{
		A.size = this->size + zeroes;
		A.Hn = new int [A.size] {};
		for (int i = 0, j = 0;i < A.size;i++)
		{
			if (i < zeroes)
			{
				A.Hn[i] = 0;
			}
			else
			{
				A.Hn[i] = this->Hn[j++];
			}
		}
		B.assign(H);
	}
	else
	{
		B.size = H.size + zeroes;
		B.Hn = new int [B.size] {};
		for (int i = 0, j = 0;i < B.size;i++)
		{
			if (i < zeroes)
			{
				B.Hn[i] = 0;
			}
			else
			{
				B.Hn[i] = H.Hn[j++];
			}
		}
		A.assign(*this);
	}
	if (this->size - tBeforeD > H.size - hBeforeD)
	{
		A2.size = this->size + zeroes + 1;
		A2.Hn = new int [A2.size] {};
		for (int i = 0, j = 0;i < A2.size;i++)
		{
			if (i == A2.size - 1)
			{
				A2.Hn[i] = 0;
			}
			else
			{
				A2.Hn[i] = A.Hn[j++];
			}
		}
		B2.assign(H);
	}
	else
	{
		B2.size = H.size + zeroes + 1;
		B2.Hn = new int [B2.size] {};
		for (int i = 0, j = 0;i < B2.size;i++)
		{
			if (i == B2.size - 1)
			{
				B2.Hn[i] = 0;
			}
			else
			{
				B2.Hn[i] = B.Hn[j++];
			}
		}
		A2.assign(*this);
	}
	int size = max(A2.size, B2.size);
	HugeReal R(size);
	int carry = 0;
	int ans = 0;
	int f = 0, s = 0;
	for (int i = 0; i < R.size; i++)
	{
		f = A2[i];
		s = B2[i];
		ans = (f + s + carry) % 10;
		carry = (f + s + carry) / 10;
		R[i] = ans;
	}
	R.point_pos = max(this->point_pos, H.point_pos);
	R.trim();
	return R;
}
const HugeReal HugeReal::SUBQuantityWise(const HugeReal& H)const
{
	int Point_index = 0;
	int tBeforeD = this->point_pos;
	int tAfterD = this->size - (this->point_pos);
	int hBeforeD = H.point_pos;
	int hAfterD = H.size - (H.point_pos);
	int maxBefore = 0, maxAfter = 0;
	if (tBeforeD > hBeforeD)
	{
		maxBefore = tBeforeD;
		Point_index = this->point_pos;
	}
	else
	{
		maxBefore = hBeforeD;
		Point_index = H.point_pos;
	}
	if (tAfterD > hAfterD)
	{
		maxAfter = tAfterD;
	}
	else
		maxAfter = hAfterD;
	int total_max = maxBefore + maxAfter;
	HugeReal A;
	HugeReal B;
	int zeroes = max(this->size - tAfterD, H.size - hAfterD) - min(this->size - tAfterD, H.size - hAfterD);
	int a = 0, b = 0;
	if (this->size - tAfterD < H.size - hAfterD)
	{
		A.size = this->size + zeroes;
		A.Hn = new int [A.size] {};
		for (int i = 0, j = 0;i < A.size;i++)
		{
			if (i < zeroes)
			{
				A.Hn[i] = 0;
			}
			else
			{
				A.Hn[i] = this->Hn[j++];
			}
		}
		B.assign(H);
	}
	else
	{
		B.size = H.size + zeroes;
		B.Hn = new int [B.size] {};
		for (int i = 0, j = 0;i < B.size;i++)
		{
			if (i < zeroes)
			{
				B.Hn[i] = 0;
			}
			else
			{
				B.Hn[i] = H.Hn[j++];
			}
		}
		A.assign(*this);
	}
	int size = max(A.size, B.size);
	HugeReal R(size);
	int carry = 0;
	int ans = 0;
	int f = 0, s = 0;
	for (int i = 0; i < R.size; i++)
	{
		f = A[i];
		s = B[i];
		int ans = (f - s - carry) % 10;
		if (ans < 0)
		{
			ans = ans + 10;
			carry = 1;
		}
		else
			carry = 0;
		R[i] = ans;
	}
	R.point_pos = max(this->point_pos, H.point_pos);
	R.trim();
	return R;
}
bool HugeReal::LessThanQuantityWise(const HugeReal& H) const
{

	if (this->point_pos == 0 && H.point_pos == 0)
	{
		if (this->size < H.size)
		{
			return true;
		}
		else if (this->size > H.size)
		{
			return false;
		}

		for (int i = size - 1;i >= 0;i--)
		{
			if (this->Hn[i] < H.Hn[i])
			{
				return true;
			}
			else if (this->Hn[i] > H.Hn[i])
			{
				return false;
			}
		}
		return false;
	}


	if (this->size-this->point_pos< H.size-H.point_pos)
	{
		return true;
	}
	else if (this->size-this->point_pos  > H.size-H.point_pos)
	{
		return false;
	}
	for(int i = this->size - 1;i > this->size-this->point_pos;i--)
	{
		if (this->Hn[i] < H.Hn[i])
		{
			return true;
		}
		else if (this->Hn[i] > H.Hn[i])
		{
			return false;
		}
	}
	for (int i = this->point_pos;i >= 0;i--)
	{
		if (this->Hn[i] < H.Hn[i])
		{
			return true;
		}
		else if (this->Hn[i] > H.Hn[i])
		{
			return false;
		}
	}
	return false;

	/*int Point_index = 0;
	int tBeforeD = this->point_pos;
	int tAfterD = this->size - (this->point_pos);
	int hBeforeD = H.point_pos;
	int hAfterD = H.size - (H.point_pos);
	int maxBefore = 0, maxAfter = 0;
	if (tBeforeD > hBeforeD)
	{
		maxBefore = tBeforeD;
		Point_index = this->point_pos;
	}
	else
	{
		maxBefore = hBeforeD;
		Point_index = H.point_pos;
	}
	if (tAfterD > hAfterD)
	{
		maxAfter = tAfterD;
	}
	else
		maxAfter = hAfterD;
	int total_max = maxBefore + maxAfter;
	HugeReal A;
	HugeReal B;
	int zeroes = max(this->size - tAfterD, H.size - hAfterD) - min(this->size - tAfterD, H.size - hAfterD);
	int a = 0, b = 0;
	if (tAfterD < hAfterD)
		return true;
	if (tAfterD > hAfterD)
		return false;
	if (this->size - tAfterD < H.size - hAfterD)
	{
		A.size = this->size + zeroes;
		A.Hn = new int [A.size] {};
		for (int i = 0, j = 0;i < A.size;i++)
		{
			if (i < zeroes)
			{
				A.Hn[i] = 0;
			}
			else
			{
				A.Hn[i] = this->Hn[j++];
			}
		}
		B.assign(H);
	}
	else
	{
		B.size = H.size + zeroes;
		B.Hn = new int [B.size] {};
		for (int i = 0, j = 0;i < B.size;i++)
		{
			if (i < zeroes)
			{
				B.Hn[i] = 0;
			}
			else
			{
				B.Hn[i] = H.Hn[j++];
			}
		}
		A.assign(*this);
	}
	int size = max(A.size, B.size);
	HugeReal R(size);
	int f = 0, s = 0;
	for (int i = R.size; i >= this->point_pos - 1; i--)
	{
		f = A.Hn[i];
		s = B.Hn[i];
		if (f < s)
		{
			return true;
		}
		if (f > s)
		{
			return false;
		}
	}
	return false;*/
}
bool HugeReal::GreaterThanQuantityWise(const HugeReal& H)const
{
	return H.LessThanQuantityWise(*this);
}
bool HugeReal::EqualQuantityWise(const HugeReal& H) const
{
	if (H.LessThanQuantityWise(*this) || H.GreaterThanQuantityWise(*this))
		return false;
	return true;
}



const  HugeReal HugeReal ::operator+ (const HugeReal& H)const
{
	if (this->isNeg != H.isNeg)
	{
		if (this->size == H.size)
		{
			int c = 0;
			for (int i = 0; i < this->size; i++)
			{
				if (this->Hn[i] != H.Hn[i])
				{
					break;
				}
				c++;
				if (c == this->size)
				{
					return Zero();
				}
			}
		}
	}
	if (this->isNeg == H.isNeg)
	{
		if (this->GreaterThanQuantityWise(H))
		{
			HugeReal R = this->ADDQuantityWise(H);
			R.isNeg = this->isNeg;
			return R;
		}
		else
		{
			HugeReal R = H.ADDQuantityWise(*this);
			R.isNeg = H.isNeg;
			return R;
		}
	}
	else
	{
		if (this->GreaterThanQuantityWise(H))
		{
			HugeReal R = this->SUBQuantityWise(H);
			R.isNeg = this->isNeg;
			return R;
		}
		else
		{
			HugeReal R = H.SUBQuantityWise(*this);
			R.isNeg = H.isNeg;
			return R;
		}
	}
}
const  HugeReal HugeReal ::operator- ()const
{
	HugeReal R = *this;
	R.isNeg = !R.isNeg;
	return R;
}
const HugeReal HugeReal ::operator- (const HugeReal& H)const
{
	return (*this) + (-H);
}
const HugeReal& HugeReal :: operator+= (const HugeReal& H)
{
	return *this = *this + H;
}
const HugeReal& HugeReal :: operator-= (const HugeReal& H)
{
	return *this = *this - H;
}



bool HugeReal:: operator >(const HugeReal& H)const
{
	if (this->isNeg == false && H.isNeg == true)
	{
		return true;
	}
	else if (this->isNeg == true && H.isNeg == false)
	{
		return false;
	}
	else if (this->isNeg == false && H.isNeg == false)
	{
		return this->GreaterThanQuantityWise(H);
	}
	else
	{
		return this->LessThanQuantityWise(H);
	}
}
bool HugeReal:: operator <(const HugeReal& H)const
{
	return H > (*this);
}
bool HugeReal:: operator ==(const HugeReal& H)const
{
	if (H > (*this))
		return false;
	if (H < (*this))
		return false;
	else
		return true;
}
bool HugeReal:: operator !=(const HugeReal& H)const
{
	return !((*this) == (H));
}
bool HugeReal:: operator <=(const HugeReal& H)const
{
	if ((*this) < H ||  (*this)==H)
		return true;
	return false;
}
bool HugeReal:: operator >=(const HugeReal& H)const
{
	if ((*this) < H)
		return false;
	else
		return true;
}


HugeReal HugeReal::operator ++()
{
	*this = *this + One();
	return *this;
}
HugeReal HugeReal::operator ++(int)
{
	HugeReal prev = *this;
	*this = prev + One();
	return *this;
}
HugeReal HugeReal::operator --()
{
	*this = *this - One();
	return *this;
}
HugeReal HugeReal::operator --(int)
{
	HugeReal prev = *this;
	*this = *this - One();
	return prev;
}


const HugeReal HugeReal::operator* (const HugeReal& H)const
{
	HugeReal A = *this;
	HugeReal B = H;
	B.point_pos = 0;
	A.point_pos = 0;
	HugeReal count;
	count= HugeReal::One();
	HugeReal Res;
	Res.point_pos = 0;
	count.point_pos = 0;
	//cout << "A " << A << endl;
	//cout << "B " << B << endl;
	while (B != HugeReal::Zero())
	{
		 count = HugeReal::One();
		 A = *this;
		 A.point_pos = 0;
		 count.point_pos = 0;
	//		cout << "count " <<count << endl;

//		 cout << "A " << A << endl;
	
		while (count + count <= B)
		{
			A += A;
			count += count;
//			A.point_pos = 0;
	//		cout << "A " << A << endl;
		//	cout << "count " <<count << endl;

		}
		Res += A;

		B -= count;
		//cout << "Res " << Res << endl;
		//cout << "B " << B << endl;

	}
	Res.trim();
	Res.point_pos = this->point_pos + H.point_pos;
	///cout << "Res " << Res << endl;
	return Res;
}
const HugeReal& HugeReal :: operator *= (const HugeReal& H)
{
	return *this = *this * H;
}


const HugeReal HugeReal::operator/ (const HugeReal& H)const
{
	HugeReal A = (*this);
	HugeReal B = (H);
	HugeReal R = Zero(), c;
	B.point_pos = 0;
	A.point_pos = 0;
	if (A.isNeg == true)
	{
		A.isNeg = false;
	}
	if (B.isNeg == true)
	{
		B.isNeg = false;
	}
	while (A >= H)
	{
		c = One();
		B = H;
		while (B + B <= A)
		{
			c += c;
			B += B;
		}
		R += c;
		A -= B;
	}
	if (A < H)
	{
		R = R * 10;
		A = A * 10;
	}
	return R;
}
const HugeReal HugeReal::operator% (const HugeReal& H)const
{
	HugeReal A = (*this);
	HugeReal B = (H);
	HugeReal R = Zero(), c;
	if (A.isNeg == true)
	{
		A.isNeg = false;
	}
	if (B.isNeg == true)
	{
		B.isNeg = false;
	}
	while (A >= H)
	{
		c = One();
		B = H;
		while (B + B <= A)
		{
			c += c;
			B += B;
		}
		R += c;
		A -= B;
	}
	return A;
}
const HugeReal& HugeReal :: operator %= (const HugeReal& H)
{
	return *this = *this % H;
}

HugeReal HugeReal::One()
{
	HugeReal R(1);
	R.Hn[0] = 1;
	R.point_pos = 0;
	return R;

}
HugeReal HugeReal::Zero()
{
	HugeReal R(1);
	R.Hn[0] = 0;
	R.point_pos = 0;
	return R;
}


void HugeReal::trim()
{
	int* HA;
	int newArrSize = 0, si = this->size - 1, count = 0;
	while (this->Hn[si] == 0)
	{
		si--;
		count++;
	}
	newArrSize = (this->size) - (count);
	HA = new int[newArrSize];
	for (int i = 0, j = 0; i < newArrSize;i++)
	{
		HA[j++] = this->Hn[i];
	}
	delete[]this->Hn;
	this->size = newArrSize;
	this->Hn = HA;
	HA = nullptr;
}


HugeReal::~HugeReal()
{
	delete[]Hn;
}
