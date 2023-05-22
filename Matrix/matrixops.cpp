#include "matrix.h"

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &sec) {
	if (width - right_part != sec.width - sec.right_part || lines != sec.lines) {
		return *this;
	}
	bool tmp = right_part >= sec.right_part;
	Matrix<T> res = tmp ? *this : sec;
	const Matrix<T> &anoth = tmp ? sec : *this;
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
	for (size_t i = 0; i < res.height; i++) {
		for (size_t j = 0; j < res.width; j++) {
			res.main[i][j] *= coef;
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &sec) {
	Matrix<T> *anoth; // this
	Matrix<T> thr(sec.width - sec.right_part, sec.width - sec.right_part, 0, 1); // special case E matrix
	anoth = this;
	if ((width - right_part) == 1 && height == 1) { // special case if 1x1 matrix
		thr = thr * main[0][0];
		anoth = &thr;
	}
	if (anoth->width-anoth->right_part != sec.lines) {
		return *this;
	}
	size_t cols = sec.width - sec.right_part;
	Matrix<T> res(cols, anoth->height);
	res.holds = anoth->holds * sec.holds;
	T *line = new T[cols];
	T sum;
	for (size_t i = 0; i < anoth->height; i++) {
		for (size_t j = 0; j < cols; j++) {
			sum = 0;
			for (size_t k = 0; k < sec.lines; k++) {
				sum += anoth->main[i][k] * sec.main[k][j];
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
	}
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(Matrix<T> &sec) {
	if (sec.width - sec.right_part != sec.lines) {
		return *this;
	}
	Matrix<T> resolv(2*sec.lines, sec.lines, sec.lines);
	Matrix<T> res(sec.lines, sec.lines, 0);
	T *line = new T[resolv.width];
	for (size_t i = 0; i < resolv.height; i++) {
		for (size_t j = 0; j < sec.lines; j++) {
			line[j] = sec.main[i][j];
		}
		for (size_t j = sec.lines; j < resolv.width; j++) {
			line[j] = j == (i + sec.lines) ? 1 : 0;
		}
		resolv.addline(line);
	}
	resolv.startsolve(1, 1);
	if (resolv.Determinator() != 0) {
		for (size_t i = 0; i < sec.lines; i++) {
			for (size_t j = 0; j < sec.lines; j++) {
				line[j] = resolv.main[i][j + sec.lines];
			}
			res.addline(line);
		}
		delete[] line;
		return *this * res;
	}
	else {
		delete[] line;
		return *this;
	}
}

template<typename T>
vector<T>& Matrix<T>::operator[](size_t index) {
	if (index > height) {
		return main[height-1];
	}
	return main[index];
}