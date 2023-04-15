#include "f.h"

// Matrix basic functions (not operators)

template<typename T>
Matrix<T>::Matrix(size_t w, size_t h, size_t right_part, bool one) {
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
	main = new vector<T>[height];
	isready = new bool[height];
	if (one) {
		T *line = new T[width];
		for (size_t j = 0; j < width; j++) {
			line[j] = 0;
		}
		for (size_t i = 0; i < height; i++) {
			if (i > 0) {
				line[i - 1] = 0;
			}
			if (i < width - right_part) {
				line[i] = 1;
			}
			addline(line);
		}
		delete[] line;
	}
}

template<typename T>
Matrix<T>::Matrix(T num) {
	Matrix<T> tocopy(1, 1, 0, 1);
	*this = tocopy * num;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &c) {
	width = c.width;
	height = c.lines;
	right_part = c.right_part;
	autozero = c.autozero;
	//holds = c.holds;
	issolved = c.issolved;
	solved = new bool[right_part];
	main = new vector<T>[height];
	isready = new bool[height];
	for (size_t i = 0; i < right_part; i++) {
		solved[i] = c.solved[i];
	}
	for (size_t i = 0; i < height; i++) {
		addline(&c.main[i][0]);
		isready[i] = c.isready[i];
	}
}

template<typename T>
bool Matrix<T>::swap(size_t l1, size_t l2) {
	T buf;
	if (l1 == l2) {
		return 0;
	}
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
		return 0;
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
	if (full) {
		return;
	}
	size_t newwidth = autozero ? width - 1 : width;
	for (size_t i = 0; i < newwidth; i++) {
		main[lines].push_back(arr[i]);
	}
	if (autozero) {
		main[lines].push_back(0);
	}
	lines++;
	if (lines == height) {
		full = 1;
	}
}

template<typename T>
void Matrix<T>::show(ostream& output) {
	size_t i;
	for (i = 0; i < lines; i++) {
		output << "(";
		for (size_t j = 0; j < width; j++) {
			T elem = main[i][j];
			if (elem == 0) {
				output << "0";
			}
			else {
				output << elem;
			}
			if (j == width - right_part - 1) {
				output << " |";
			}
			if (j < width - 1) {
				output << " ";
			}
		}
		output << ")\n";
	}
	while (i < height) {
		output << "(...)\n";
		i++;
	}
	output.flush();
}

template<typename T>
int Matrix<T>::searchforxline(size_t num) {
	size_t i;
	bool bad;
	if (num > width - right_part) {
		return -1;
	}
	for (i = 0; i < height; i++) {
		bad = 0;
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
void Matrix<T>::startsolve(bool jord, bool quiet, ostream& output) {
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
				for (size_t t = q*(!jord); t < height; t++) {
					if (t != q) {
						T coef1 = -main[t][p];
						errcheck = errcheck || summarize(q + 1, t + 1, coef1);
					}
				}
				//show(output); // debug
				isready[q] = 1;
				if (errcheck) {
					output << "Bad error!\n";
					return;
				}
			}
		}
	}
	int tline;
	for (size_t i = 0; i < width - right_part; i++) {
		tline = searchforxline(i);
		if (tline >= 0) {
			swap(tline, i);
		}
	}
	if (!quiet) {
		show(output);
	}
	issolved = 1;
	for (size_t i = 0; i < right_part; i++) {
		solved[i] = !checkzeroerror(i + 1);
		if (solved[i] == 0) {
			issolved = 0;
		}
		if (!quiet) {
			showfx(i + 1, output);
		}
	}
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
void Matrix<T>::showfx(size_t rpart, ostream& output) {
	//return;
	bool first;
	bool empty;
	size_t xl;
	output << "--- #" << rpart << " ---\n";
	if (!solved[rpart - 1]) {
		output << "Not solved.\n";
		return;
	}
	for (size_t i = 0; i < width - right_part; i++) {
		empty = 1;
		first = 1;
		xl = searchforxline(i);
		output << "x" << i + 1 << " = ";
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
					sgndprint(first, sgn, output);
					output << (2 * sgn - 1) * main[xl][j];
				}
				else {
					sgndprint(first, !sgn, output);
					output << (2 * sgn - 1) * main[xl][j] << "x" << j + 1;
				}
				first = 0;
			}
		}
		else {
			output << "const";
			empty = 0;
		}
		if (empty) {
			output << '0';
		}
		output << '\n';
	}
	output << "Determinator: " << Determinator() << '\n';
	output.flush();
}

void sgndprint(size_t first, size_t sgn, ostream& output) {
	if (first && !sgn) {
		output << "-";
	}
	else if (!first && sgn) {
		output << " + ";
	}
	else if (!first && !sgn) {
		output << " - ";
	}
}

template<typename T>
Matrix<T> Matrix<T>::transposed() {
	Matrix<T> res(lines, width-right_part);
	T *line = new T[res.width];
	for (size_t i = 0; i < res.height; i++) {
		for (size_t j = 0; j < res.width-1; j++) {
			line[j] = main[j][i];
		}
		res.addline(line);
	}
	delete[] line;
	return res;
}