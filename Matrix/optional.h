#pragma once
#include <iostream>
#include <fstream>

typedef unsigned long long int llu;

using namespace std;

class Frac {
public:
	Frac(int numer, size_t denom) {
		if (denom == 0) {
			//throw 1;
		}
		else {
			this->numer = numer;
			this->denom = denom;
			simpl();
		}
	}
	Frac() {}
	Frac(int _num) : numer(_num) {}
	operator bool() {
		return numer != 0;
	}
	Frac(const Frac &c) {
		numer = c.numer;
		denom = c.denom;
	}
	~Frac() {}
	int get_numer() {
		return numer;
	}
	size_t get_denom() {
		return denom;
	}
	void set_numer(int to) {
		numer = to;
	}
	void set_denom(size_t to) {
		if (to != 0) {
			denom = to;
		}
	}
	// ops
	friend ostream &operator<<(ostream &output, const Frac &m);
	friend bool operator&&(const bool &a, const Frac &b);
	Frac &operator=(const Frac &sec) {
		numer = sec.numer;
		denom = sec.denom;
		return *this;
	}
	Frac &operator=(const int &sec) {
		numer = sec;
		return *this;
	}
	Frac operator*(const Frac &sec);
	Frac operator/(const Frac &sec);
	Frac operator+(const Frac &sec);
	Frac operator-(const Frac &sec);
	Frac &operator+=(const Frac &sec);
	Frac &operator-=(const Frac &sec);
	Frac &operator*=(const Frac &sec);
	Frac &operator*=(const int a) {
		numer *= a;
		return *this;
	}
	Frac &operator/=(const Frac &sec);
	bool operator==(const Frac &sec) { return numer * sec.denom == sec.numer * denom; }
	bool operator!=(const Frac &sec) { return numer * sec.denom != sec.numer * denom; }
	bool operator<=(const Frac &sec) { return numer * sec.denom <= sec.numer * denom; }
	bool operator<(const Frac &sec) { return numer * sec.denom < sec.numer * denom; }
	bool operator>(const Frac &sec) { return numer * sec.denom > sec.numer * denom; }
	bool operator>=(const Frac &sec) { return numer * sec.denom >= sec.numer * denom; }
	bool operator&&(const Frac &sec) { return numer && sec.numer; }
	Frac operator-() { return Frac(-numer, denom); }
private:
	void simpl();
	int numer = 0;
	size_t denom = 1;
};