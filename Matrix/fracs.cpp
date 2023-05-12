#include "fracs.h"

const bool precise = 1;

void Frac::simpl() {
	llu rec;
	llu s1 = numer >= 0 ? numer : -numer;
	llu s2 = denom;
	if (denom == 1 || denom == 0) {
		return;
	}
	do {
		rec = s1 % s2;
		s1 = s2;
		s2 = rec;
	} while (rec != 0);
	// s1 - gcd
	numer /= (ll)s1;
	denom /= s1;
	// if not to be precise
	if (!precise && ((abs(numer) > 10000000LL) || (denom > 10000000LL))) {
		long double tmp = (long double)numer / denom;
		tmp *= 100000;
		numer = (ll)(tmp + 0.5);
		denom = (llu)100000;
		cout << "Value loss\n";
	}
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
	ll abnumer;
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
	ll abnumer = sec.numer < 0 ? -sec.numer : sec.numer;
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