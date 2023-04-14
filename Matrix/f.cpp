#include "f.h"

template<typename T>
bool Matrix<T>::swap(size_t l1, size_t l2) {
	T buf;
	if (l1 >= lines || l2 >= lines) {
		return 1;
	}
	for (size_t j = 0; j < width; j++) {
		buf = main[l1][j];
		main[l1][j] = main[l2][j];
		main[l2][j] = buf;
	}
	holds *= -1;
	return 0;
}

template<typename T>
T Matrix<T>::Determinator() {
	if (width - right_part != height || !issolved) {
		return NAN;
	}
	for (size_t i = 0; i < width - right_part; i++) {
		if (searchforxline(i) == -1) {
			return 0;
		}
	}
	return holds;
}

template<typename T>
void Matrix<T>::addline(T *arr) {
	T null = 0;
	if (full) {
		return;
	}
	size_t newwidth = autozero ? width - 1 : width;
	for (size_t i = 0; i < newwidth; i++) {
		main[lines].push_back(arr[i]);
	}
	if (autozero) {
		main[lines].push_back(null);
	}
	lines++;
	if (lines == height) {
		full = 1;
	}
}

template<typename T>
void Matrix<T>::show() {
	size_t i;
	for (i = 0; i < lines; i++) {
		cout << "(";
		for (size_t j = 0; j < width; j++) {
			T elem = main[i][j];
			if (elem == 0) {
				cout << "0";
			}
			else {
				cout << elem;
			}
			if (j == width - right_part - 1) {
				cout << " |";
			}
			if (j < width - 1) {
				cout << " ";
			}
		}
		cout << ")\n";
	}
	while (i < height) {
		cout << "(...)\n";
		i++;
	}
}

template<typename T>
int Matrix<T>::searchforxline(size_t num) {
	size_t i;
	bool bad = 0;
	if (num > width - right_part) {
		return -1;
	}
	for (i = 0; i < height; i++) {
		if (main[i][num] != 0) {
			for (size_t j = 0; j < num; j++) {
				if (main[i][j] != 0) {
					bad = 1;
					break;
				}
			}
			if (!bad) {
				return i;
			}
		}
	}
	return -1;
}

template<typename T>
void Matrix<T>::startsolve() {
	bool *isready = new bool[height];
	bool errcheck;
	if (!full) {
		return;
	}
	for (size_t i = 0; i < height; i++) {
		isready[i] = 0;
	}
	for (size_t p = 0; p < width - right_part; p++) {
		for (size_t q = 0; q < height; q++) {
			T elem = main[q][p];
			if (!isready[q] && elem) {
				errcheck = division(q + 1, elem);
				holds *= elem;
				for (size_t t = 0; t < height; t++) {
					if (t != q) {
						T coef1 = -main[t][p];
						errcheck = errcheck || summarize(q + 1, t + 1, coef1);
					}
				}
				//show();
				isready[q] = 1;
				if (errcheck) {
					cout << "Bad error!\n";
					return;
				}
			}
		}
	}
	show();
	cout << '\n';
	for (size_t i = 0; i < right_part; i++) {
		solved[i] = !checkzeroerror(i + 1);
		showfx(i + 1);
	}
	int tline;
	for (size_t i = 0; i < width - right_part; i++) {
		tline = searchforxline(i);
		if (tline >= 0) {
			swap(tline, i);
		}
	}
	issolved = 1;
}

template<typename T>
bool Matrix<T>::checkzeroerror(size_t rpart) {
	bool good; // is line 0 0 0...
	if (rpart > right_part) {
		return 1;
	}
	for (size_t i = 0; i < height; i++) {
		good = 1;
		for (size_t j = 0; j < width - right_part; j++) {
			if (main[i][j] != 0) {
				good = 0;
				break;
			}
		}
		if (good && main[i][width - right_part + rpart - 1]) {
			return 1;
		}
	}
	return 0;
}

template<typename T>
bool Matrix<T>::division(size_t to, T coef) {
	to = to - 1;
	if (to >= lines) {
		return 1;
	}
	if (coef) {
		for (size_t i = 0; i < width; i++) {
			main[to][i] /= coef;
		}
	}
	else {
		return 1;
	}
	return 0;
}

template<typename T>
bool Matrix<T>::summarize(size_t from, size_t to, T coef) {
	from = from - 1;
	to = to - 1;
	if (from >= lines || to >= lines) {
		return 1;
	}
	for (size_t i = 0; i < width; i++) {
		main[to][i] += main[from][i] * coef;
	}
	return 0;
}

template<typename T>
void Matrix<T>::showfx(size_t rpart) {
	bool first;
	bool empty;
	size_t xl;
	cout << "--- #" << rpart << " ---\n";
	if (!solved[rpart - 1]) {
		cout << "Not solved.\n";
		return;
	}
	for (size_t i = 0; i < width - right_part; i++) {
		empty = 1;
		first = 1;
		xl = searchforxline(i);
		cout << "x" << i + 1 << " = ";
		if (xl != -1) {
			for (size_t j = i + 1; j < width; j++) {
				bool sgn;
				if (main[xl][j] == 0 || ((j >= width - right_part) && j != width - right_part + rpart - 1)) {
					continue;
				}
				if (empty) {
					empty = 0;
				}
				sgn = main[xl][j] > 0 ? 1 : 0;
				if (j == width - right_part + rpart - 1) { // our rpart
					sgndprint(first, sgn);
					cout << (2 * sgn - 1) * main[xl][j];
				}
				else {
					sgndprint(first, !sgn);
					cout << (2 * sgn - 1) * main[xl][j] << "x" << j + 1;
				}
				first = 0;
			}
		}
		else {
			cout << "const";
			empty = 0;
		}
		if (empty) {
			cout << '0';
		}
		cout << '\n';
	}
}

void sgndprint(size_t first, size_t sgn) {
	if (first && !sgn) {
		cout << "-";
	}
	else if (!first && sgn) {
		cout << " + ";
	}
	else if (!first && !sgn) {
		cout << " - ";
	}
}