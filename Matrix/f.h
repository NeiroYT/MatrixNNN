#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void sgndprint(size_t first, size_t sgn);

template<typename T>
class Matrix {
public:
	Matrix(size_t w, size_t h, size_t right_part = 0) {
		if (w == 0 || h == 0) {
			w = 1; h = 1;
		}
		width = w;
		height = h;
		if (right_part < width) {
			this->right_part = right_part;
		}
		else {
			right_part = 0;
		}
		if (right_part == 0) {
			width++;
			this->right_part = 1;
			autozero = 1;
		}
		solved = new bool[this->right_part];
		main = new vector<T>[h];
		isready = new bool[height];
	}
	~Matrix() {
		delete[] isready;
		delete[] main;
		delete[] solved;
	}
	bool swap(size_t l1, size_t l2);
	void addline(T *arr);
	void show();
	void startsolve();
	bool checkzeroerror(size_t rpart);
	bool summarize(size_t from, size_t to, T coef);
	bool division(size_t to, T coef);
	T Determinator();
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