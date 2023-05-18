#include "matrix.h"
#include "fracs.h"
#include <cstdlib>
#include <ctime>

typedef Frac INP;

Matrix<INP> mainchoice();

int main() {
	srand(time(NULL));
	clock_t time;
	ofstream file;
	char choice;
	file.open("log.txt");
	while (true) {
		Matrix<INP> m1 = mainchoice();
		Matrix<INP> m2(0, 0);
		//Matrix<INP> m2 = mainchoice();
		m2 = (INP)1 / m1;
		//m2 = m1 * m2;
		m1.show(file);
		file << "\n...\n";
		m2.show(file);
		cout << "Confirm? (Y/N)\n";
		cin >> choice;
		if (choice != 'Y' && choice != 'y') {
			continue;
		}
		file << "\nAnswers:\n";
		time = clock();
		m1.startsolve(1, 0, file);
		m1.getvec(1).show(file);
		time = clock() - time;
		file << time << "ms for " << m1.get_width() << "x" << m1.get_height() << '\n';
		time = clock();
		m2.startsolve(1, 0, file);
		m2.getvec(1).show(file);
		time = clock() - time;
		file << time << "ms for " << m2.get_width() << "x" << m2.get_height() << '\n';
		file.flush();
	}
	file.close();
	return 0;
}

Matrix<INP> mainchoice() {
	size_t w, h, rpart;
	int choice2;
	int choice3 = 0;
	cout << "Width (amount of Xs): ";
	cin >> w;
	cout << "Height: ";
	cin >> h;
	cout << "Count of right parts: ";
	cin >> rpart;
	cout << "Random? ";
	cin >> choice2;
	cout << "Q field? ";
	cin >> choice3;
	w += rpart;
	Matrix<INP> m1(w, h, rpart);
	INP *templine = new INP[w];
	int a;
	size_t b;
	for (size_t i = 0; i < h; i++) {
		cout << "Line #" << i + 1 << ":\n";
		for (size_t j = 0; j < w; j++) {
			if (choice2 == 1) {
				if (choice3) {
					templine[j] = (INP)Frac(rand() % 10, rand() % 9 + 1);
				}
				else {
					templine[j] = rand() % 10;
				}
			}
			else {
				cin >> a;
				if (choice3 && a != 0) {
					cin >> b;
					templine[j] = (INP)Frac(a, b);
				}
				else {
					templine[j] = a;
				}
			}
		}
		cout << "---\n";
		m1.addline(templine);
	}
	delete[] templine;
	return m1;
}