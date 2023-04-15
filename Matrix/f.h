#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

void sgndprint(size_t first, size_t sgn);

template<typename T>
class Matrix {
public:
	Matrix(size_t w, size_t h, size_t right_part = 0, bool one = 0);
	Matrix(const Matrix &c);
	~Matrix() {
		delete[] isready;
		delete[] main;
		delete[] solved;
	}
	bool swap(size_t l1, size_t l2);
	void addline(T *arr);
	void show();
	void startsolve(bool jord = 1);
	bool checkzeroerror(size_t rpart);
	bool summarize(size_t from, size_t to, T coef);
	bool division(size_t to, T coef);
	Matrix<T> transposed();
	void killholds() {
		holds = 1;
	}
	T Determinator();
	//ops
	Matrix<T> operator+(const Matrix &sec);
	Matrix<T>& operator=(const Matrix<T> &sec);
	Matrix<T> operator*(const T& coef);
	Matrix<T> operator*(const Matrix<T> &sec);
private:
	void showfx(size_t rpart);
	int searchforxline(size_t num);
	bool full = 0;
	bool *solved;
	bool *isready;
	vector<T> *main;
	size_t width = 0; size_t height = 0;
	size_t right_part = 1;
	size_t lines = 0;
	bool autozero = 0;
	T holds = 1;
	bool issolved = 0;
};

#include "f.cpp"
#include "operators.cpp"