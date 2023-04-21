#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

void sgndprint(size_t first, size_t sgn, ostream& output = cout);

template<typename T>
class Matrix {
public:
	Matrix(size_t w, size_t h, size_t right_part = 0, bool one = 0);
	Matrix(const T& num);
	Matrix(const Matrix &c);
	~Matrix() {
		delete[] isready;
		delete[] main;
		delete[] solved;
	}
	bool swap(size_t l1, size_t l2);
	void addline(T *arr);
	void show(ostream& output = cout);
	void startsolve(bool jord = 1, bool quiet = 0, ostream& output = cout);
	bool checkzeroerror(size_t rpart);
	bool summarize(size_t from, size_t to, T coef);
	bool division(size_t to, T coef);
	Matrix<T> transposed();
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
	Matrix<T> operator+(const Matrix &sec);
	Matrix<T>& operator=(const Matrix<T> &sec);
	Matrix<T> operator*(const T& coef);
	Matrix<T> operator*(Matrix<T> &sec);
	Matrix<T> operator/(Matrix<T> &sec);
	vector<T>& operator[](size_t index);
private:
	void showfx(size_t rpart, ostream& output);
	int searchforxline(size_t num);
	bool full;
	bool *solved;
	bool *isready;
	vector<T> *main;
	size_t width;
	size_t height;
	size_t right_part;
	size_t lines;
	bool autozero;
	T holds;
	bool issolved;
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

#include "f.cpp"
#include "operators.cpp"