#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string calculateLetterGrade(double weightedAverage) {
	// Score to letter grade conversion
	// A: [90, 100] B: [80, 89] C+: [75, 79] C: [70, 74] D: [60, 64] F: [0, 59]
}

double findMinQuiz(double quiz1, double quiz2, double quiz3, double quiz4) {

}

double findAverageQuizScore(double quiz1, double quiz2, double quiz3, double quiz4) {
	// This will call findMinQuiz() to get the lowest quiz grade to remove
}

double findAverageHomeworkScore(double homework1, double homework2, double homework3, double homework4) {

}

double findAverageLabScore(double lab1, double lab2, double lab3, double lab4, double lab5, double lab6, double lab7, double lab8) {

}

int main() {
	/**
		Grading Reference
		Attendance & Class Performance: 10% (0.5 point reduced for a lateness > 15 minutes)
		In-class labs: 15%
		Homework: 15%
		4 Quizzes: 15%
		Group work: 5% (Contribution, Participation, etc.)
		Midterm: 20%
		Final Exam: 20%
	**/

	// Opening input file, with error handling
	ifstream inputFile("gradesIn.txt");
	if(!inputFile) {
		cerr << "Unable to open the file." << endl;
		return -1;
	}

	string line;

	// This will get rid of the header
	getline(inputFile, line);

	while(getline(inputFile, line)) {
		cout << line << endl;
	}

	inputFile.close();

	return 0;
}
