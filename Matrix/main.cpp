#include "f.h"

int main() {
	srand(time(NULL));
	clock_t time;
	size_t w, h, rpart;
	char choice;
	while (true) {
		cout << "Width (amount of Xs): ";
		cin >> w;
		cout << "Height: ";
		cin >> h;
		cout << "Count of right parts: ";
		cin >> rpart;
		w += rpart;
		Matrix<double> m1(w, h, rpart);
		double *templine = new double[w];
		for (int i = 0; i < h; i++) {
			cout << "Line #" << i + 1 << ":\n";
			for (int j = 0; j < w; j++) {
				//templine[j] = rand() % 60;
				cin >> templine[j];
			}
			cout << "---\n";
			m1.addline(templine);
		}
		delete[] templine;
		Matrix<double> m2 = m1;
		m2 = (m1 + m2) * 2;
		m1.show();
		cout << "\n...\n";
		m2.show();
		cout << "Confirm? (Y/N)\n";
		cin >> choice;
		if (choice != 'Y' && choice != 'y') {
			continue;
		}
		cout << "\nAnswers:\n";
		time = clock();
		m1.startsolve();
		time = clock() - time;
		cout << time << "ms for " << w << "x" << h << '\n';
		time = clock();
		m2.startsolve();
		time = clock() - time;
		cout << time << "ms for " << w << "x" << h << '\n';
	}
	return 0;
}