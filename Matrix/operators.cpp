#include "f.h"

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &sec) {
	if (width - right_part != sec.width - sec.right_part || lines != sec.lines) {
		return *this;
	}
	Matrix<T> res = right_part >= sec.right_part ? *this : sec;
	const Matrix<T> &anoth = right_part >= sec.right_part ? sec : *this;
	for (size_t i = 0; i < res.right_part; i++) {
		res.solved[i] = 0;
	}
	for (size_t i = 0; i < res.height; i++) {
		res.isready[i] = 0;
		for (size_t j = 0; j < anoth.width; j++) {
			res.main[i][j] += anoth.main[i][j];
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& coef) {
	Matrix<T> res(0, 0);
	res = *this;
	for (int i = 0; i < res.height; i++) {
		for (int j = 0; j < res.width; j++) {
			res.main[i][j] *= coef;
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &sec) {
	if (width-right_part != sec.lines) {
		return *this;
	}
	size_t cols = sec.width - sec.right_part;
	Matrix<T> res(height, cols);
	res.holds = holds * sec.holds;
	T *line = new T[cols];
	T sum;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < cols; j++) {
			sum = 0;
			for (size_t k = 0; k < sec.lines; k++) {
				sum += main[i][k] * sec.main[k][j];
			}
			line[j] = sum;
		}
		res.addline(line);
	}
	delete[] line;
	return res;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &sec) {
	if (solved != nullptr) {
		delete[] solved;
	}
	if (main != nullptr) {
		delete[] main;
	}
	if (isready != nullptr) {
		delete[] isready;
	}
	width = sec.width;
	height = sec.lines;
	right_part = sec.right_part;
	autozero = sec.autozero;
	holds = sec.holds;
	full = 0;
	lines = 0;
	issolved = sec.issolved;
	solved = new bool[right_part];
	main = new vector<T>[height];
	isready = new bool[height];
	for (size_t i = 0; i < right_part; i++) {
		solved[i] = sec.solved[i];
	}
	for (size_t i = 0; i < height; i++) {
		addline(&sec.main[i][0]);
		isready[i] = sec.isready[i];
	}
	return *this;
}