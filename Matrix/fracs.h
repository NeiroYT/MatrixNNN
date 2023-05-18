#pragma once
#include <iostream>
#include <fstream>

typedef unsigned long long int llu;
typedef long long int ll;

using namespace std;

class Frac {
public:
	Frac(ll numer, llu denom) {
		if (denom == 0) {
			cout << "Overflow\n"; // debug
		}
		this->numer = numer;
		this->denom = denom;
		simpl();
	}
	Frac() {
		numer = 0;
		denom = 1;
	}
	Frac(int _num) : numer(_num) {
		denom = 1;
	}
	Frac(const Frac &c) {
		numer = c.numer;
		denom = c.denom;
	}
	explicit operator double() {
		return (double)numer / denom;
	}
	~Frac() {}
	ll get_numer() {
		return numer;
	}
	llu get_denom() {
		return denom;
	}
	void set_numer(ll to) {
		numer = to;
	}
	void set_denom(llu to) {
		if (to != 0) {
			denom = to;
		}
	}
	// ops
	friend ostream &operator<<(ostream &output, const Frac &m);
	Frac &operator=(const Frac &sec) {
		numer = sec.numer;
		denom = sec.denom;
		return *this;
	}
	Frac operator*(const Frac &sec);
	Frac operator/(const Frac &sec);
	Frac operator+(const Frac &sec);
	Frac operator-(const Frac &sec);
	Frac &operator+=(const Frac &sec);
	Frac &operator-=(const Frac &sec);
	Frac &operator*=(const Frac &sec);
	Frac &operator/=(const Frac &sec);
	bool operator==(const Frac &sec) { return numer * (ll)sec.denom == sec.numer * (ll)denom; }
	bool operator!=(const Frac &sec) { return numer * (ll)sec.denom != sec.numer * (ll)denom; }
	bool operator<=(const Frac &sec) { return numer * (ll)sec.denom <= sec.numer * (ll)denom; }
	bool operator<(const Frac &sec) { return numer * (ll)sec.denom < sec.numer * (ll)denom; }
	bool operator>(const Frac &sec) { return numer * (ll)sec.denom > sec.numer * (ll)denom; }
	bool operator>=(const Frac &sec) { return numer * (ll)sec.denom >= sec.numer * (ll)denom; }
	Frac operator-() { return Frac(-numer, denom); }
private:
	void simpl();
	ll numer;
	llu denom;
};

/*
what should be in a class:

ostream& operator<<(class obj)

= ,*, /, +=, *=, /=, !=, ==, >

*/
