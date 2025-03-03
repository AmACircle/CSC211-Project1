#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string calculateLetterGrade(double weightedAverage) {
	
	// Score to letter grade conversion
	// A: [90, 100] B: [80, 89] C+: [75, 79] C: [70, 74] D: [60, 64] F: [0, 59]
	// If... else if... Remember to use && to check between range and >= and <= to include upper and lower bounds.

	if (weightedAverage >= 90) {
		return "A";
	}
	else if (weightedAverage >= 80) {
		return "B";
	}
	else if (weightedAverage >= 75) {
		return "C+";
	}
	else if (weightedAverage >= 70) {
		return "C";
	}
	else if (weightedAverage >= 60) {
		return "D";
	}
	else {
		return "F";
	}
}

double findMinQuiz(double quiz1, double quiz2, double quiz3, double quiz4) {
	// Multiple ways to do this, easiest would be using if statements.

	double minQuiz = quiz1;
	
	if (quiz2 < minQuiz) minQuiz = quiz2;
	if (quiz3 < minQuiz) minQuiz = quiz3;
	if (quiz4 < minQuiz) minQuiz = quiz4;
	
	return minQuiz;
}

double findAverageQuizScore(double quiz1, double quiz2, double quiz3, double quiz4) {
	// This will call findMinQuiz() to get the lowest quiz grade to remove
	// Add the rest of the scores and divide by 3 to get the answer.
	double minQuiz = findMinQuiz(quiz1, quiz2, quiz3, quiz4); // Gets the lowest quiz grade.
	double totalSum = quiz1 + quiz2 + quiz3 + quiz4; // Adds up all 4 quiz grades.
	double sumWithoutLowest = totalSum - minQuiz; // Subtracts the lowest from total.

	return sumWithoutLowest / 3.0; // Quiz average based on the 3 remaining quizzes.
}

double findAverageHomeworkScore(double homework1, double homework2, double homework3, double homework4) {
	// 2 scores are out of 10 and 2 out of 20.
	// You would need to scale up two of the scores (multiply by 2) before calculating.
	// The average would still be out of 20 however, to get the score out of 100 we'd multiply by 5.
}

double findAverageLabScore(double lab1, double lab2, double lab3, double lab4, double lab5, double lab6, double lab7, double lab8) {
	// Add all scores and divide by 8.
	
	return (lab1 + lab2 + lab3 + lab4 + lab5 + lab6 + lab7 + lab8) / 8.0;
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
		cerr << "Unable to open gradesIn.txt." << endl;
		return -1;
	}

	//creating 2 outputfiles
	ofstream outFile1("gradesOut1.txt");
	if (!outFile) {

		cout << "Unable to open gradesOut1.txt." << endl;
		return -1;
	}
	
	ofstream outFile2("gradesOut2.txt");
	if (!outFile2) {

		cout << "Unable to open gradesOut2.txt." << endl;
		return -1;
	}

	string line;

	// This will get rid of the header
	getline(inputFile, line);

	while(getline(inputFile, line)) {
		cout << line << endl;
	}

	inputFile.close();
	outFile1.close();
	outFile2.close();

	return 0;
}
