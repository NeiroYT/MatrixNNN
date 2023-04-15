#include "f.h"

int main() {
	srand(time(NULL));
	clock_t time;
	size_t w, h, rpart;
	char choice;
	ofstream file;
	file.open("log.txt");
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
				templine[j] = rand() % 10;
				//cin >> templine[j];
			}
			cout << "---\n";
			m1.addline(templine);
		}
		delete[] templine;
		Matrix<double> m2(w, h, rpart, 1);
		m2 = ((Matrix<double>)1 / m1);
		m1.show(file);s
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
		time = clock() - time;
		file << time << "ms for " << w << "x" << h << '\n';
		time = clock();
		m2.startsolve(1, 0, file);
		time = clock() - time;
		file << time << "ms for " << w << "x" << h << '\n';
		file.flush();
	}
	file.close();
	return 0;
}