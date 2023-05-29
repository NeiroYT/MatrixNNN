#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void sgndprint(size_t first, size_t sgn, ostream& output = cout);

template<typename T>
class Vector {
public:
	Vector(size_t n) {
		if (n != 0) {
			main = new T[n];
			coords = n;
		}
		else {
			main = nullptr;
			coords = 0;
		}
	}
	~Vector() {
		delete[] main;
	}
	Vector(const Vector<T> &c) {
		if (c.coords != 0) {
			main = new T[c.coords];
			for (size_t i = 0; i < c.coords; i++) {
				main[i] = c.main[i];
			}
			coords = c.coords;
		}
		else {
			main = nullptr;
			coords = 0;
		}
	}
	Vector(Vector<T> &&sec) {
		main = sec.main;
		coords = sec.coords;
		sec.main = nullptr;
		sec.coords = 0;
	}
	T &operator[](size_t i) {
		if (i < coords) {
			return main[i];
		}
	}
	void show(ostream& output = cout) {
		output << '(';
		for (size_t i = 0; i < coords-1; i++) {
			output << main[i] << ' ';
		}
		output << main[coords - 1] << ")\n";
		output.flush();
	}
private:
	T *main;
	size_t coords;
};

template<typename T>
class Matrix {
public:
	Matrix(size_t w, size_t h, size_t right_part = 0, bool one = 0); // w includes right_part
	Matrix(const T& num);
	Matrix(const Matrix<T> &c);
	Matrix(Matrix<T> &&sec);
	~Matrix() {
		delete[] isready;
		delete[] main;
		delete[] solved;
	}
	bool swap(size_t l1, size_t l2); // Swap lines, starts from 1
	void addline(T *arr); // Adds [width] array
	void show(ostream& output = cout);
	void startsolve(bool jord = 1, bool quiet = 0, ostream& output = cout);
	bool checkzeroerror(size_t rpart); // Is there (0 0 ... 0 |	1)?
	bool summarize(size_t from, size_t to, T coef); // Summarize lines, starts from 1
	bool division(size_t to, T coef); // Divide line by coef, line starts from 1
	Matrix<T> transposed();
	Vector<T> getvec(size_t num); // starts from 1
	void killholds() {
		holds = 1;
	}
	T Determinator();
	bool is_solved() {
		return issolved;
	}
	size_t get_width() {
		return width - right_part;
	}
	size_t get_height() {
		return lines;
	}
	size_t get_rightpart() {
		return right_part;
	}
	//ops
	Matrix<T> operator+(const Matrix<T> &sec);
	Matrix<T>& operator=(const Matrix<T> &sec);
	Matrix<T> operator*(const T& coef);
	Matrix<T> operator*(Matrix<T> &sec); // n^3
	Matrix<T> operator/(Matrix<T> &sec); // m1 * (m2)^-1 actually
	vector<T>& operator[](size_t index);
private:
	void showfx(size_t rpart, ostream& output);
	int searchforusableline(size_t num);
	size_t funcline(size_t w);
	bool full;
	bool *solved;
	bool *isready;
	bool issolved;
	bool autozero;
	vector<T> *main;
	size_t lines;
	size_t width;
	size_t height;
	size_t right_part;
	T holds;
};

template<typename T>
ostream& operator<<(ostream &output, Matrix<T> &m) {
	m.show(output);
	return output;
}

template<typename T>
inline Matrix<T> operator/(T frst, Matrix<T> sec) {
	return (Matrix<T>)frst / sec;
}

template<typename T>
size_t Matrix<T>::funcline(size_t w) {
	size_t maxline = height;
	for (size_t i = 0; i < height; i++) {
		if (isready[i] == 0) {
			maxline = i;
			break;
		}
	}
	for (size_t i = maxline; i < height; i++) {
		T el1 = main[i][w] > 0 ? main[i][w] : -main[i][w];
		T el2 = main[maxline][w] > 0 ? main[maxline][w] : -main[maxline][w];
		if (el1 > el2 && isready[i] == 0) {
			maxline = i;
		}
	}
	return maxline;
}

#include "matrix.cpp"
#include "matrixops.cpp"