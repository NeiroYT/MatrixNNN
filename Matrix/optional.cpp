#include "optional.h"

void Frac::simpl() {
	size_t rec;
	size_t s1 = numer >= 0 ? numer : -numer;
	size_t s2 = denom;
	if (denom == 1 || denom == 0) {
		return;
	}
	do {
		rec = s1 % s2;
		s1 = s2;
		s2 = rec;
	} while (rec != 0);
	// s1 - gcd
	numer /= (int)s1;
	denom /= s1;
}

Frac Frac::operator*(const Frac &sec) {
	Frac res;
	res.numer = numer * sec.numer;
	res.denom = denom * sec.denom;
	res.simpl();
	return res;
}

Frac Frac::operator+(const Frac &sec) {
	Frac res;
	res.numer = numer * sec.denom + sec.numer * denom;
	res.denom = denom * sec.denom;
	res.simpl();
	return res;
}

Frac Frac::operator-(const Frac &sec) {
	Frac res;
	res.numer = numer * sec.denom - sec.numer * denom;
	res.denom = denom * sec.denom;
	res.simpl();
	return res;
}

Frac Frac::operator/(const Frac &sec) {
	int abnumer;
	Frac res;
	res.numer = numer * sec.denom;
	if (sec.numer < 0) {
		res.numer *= -1;
	}
	abnumer = sec.numer < 0 ? -sec.numer : sec.numer;
	res.denom = denom * abnumer;
	res.simpl();
	return res;
}

Frac& Frac::operator-=(const Frac &sec) {
	numer = numer * sec.denom - sec.numer * denom;
	denom *= sec.denom;
	simpl();
	return *this;
}

Frac& Frac::operator+=(const Frac &sec) {
	numer = numer * sec.denom + sec.numer * denom;
	denom *= sec.denom;
	simpl();
	return *this;
}

Frac &Frac::operator*=(const Frac &sec) {
	numer *= sec.numer;
	denom *= sec.denom;
	simpl();
	return *this;
}

Frac &Frac::operator/=(const Frac &sec) {
	if (numer == 0) {
		return *this;
	}
	int abnumer = sec.numer < 0 ? -sec.numer : sec.numer;
	numer *= sec.denom;
	if (sec.numer < 0) {
		numer *= -1;
	}
	denom *= abnumer;
	simpl();
	return *this;
}

ostream &operator<<(ostream &output, const Frac &m) {
	if (m.denom == 1) {
		output << m.numer;
	}
	else {
		output << m.numer << '/' << m.denom;
	}
	return output;
}

bool operator&&(const bool &a, const Frac &b) {
	return (a && (b.numer != 0));
}

Frac operator*(int &a, const Frac &b) {
	Frac res = b;
	res *= a;
	return res;
}