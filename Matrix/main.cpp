#include "f.h"
#include "optional.h"

typedef Frac INP;

int main() {
	srand(time(NULL));
	clock_t time;
	size_t w, h, rpart;
	char choice;
	int choice2;
	ofstream file;
	file.open("log.txt");
	while (true) {
		cout << "Width (amount of Xs): ";
		cin >> w;
		cout << "Height: ";
		cin >> h;
		cout << "Count of right parts: ";
		cin >> rpart;
		cout << "Random? ";
		cin >> choice2;
		w += rpart;
		Matrix<INP> m1(w, h, rpart);
		INP *templine = new INP[w];
		int a;
		for (size_t i = 0; i < h; i++) {
			cout << "Line #" << i + 1 << ":\n";
			for (size_t j = 0; j < w; j++) {
				if (choice2 == 1) {
					templine[j] = rand() % 10;
				}
				else {
					cin >> a;
					templine[j] = a;
				}
			}
			cout << "---\n";
			m1.addline(templine);
		}
		delete[] templine;
		Matrix<INP> m2(w, h, rpart, 1);
		//m2 = (INP)1 / m1;
		m2 = m1 + Matrix<INP>(w, h, rpart, 1);
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