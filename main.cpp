#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Student {
	string firstName;
	string lastName;
	double attendance;
	double labScores[8];
	double labAverage;
	double homeworkScores[4];
	double homeworkAverage;
	double quizScores[4];
	double quizAverage;
	double groupWork;
	double midtermAverage;
	double finalAverage;
	double courseAverage;
	string letterGrade;
};

string calculateLetterGrade(double weightedAverage) {
	// Score to letter grade conversion
	// A: [90, 100] B: [80, 89] C+: [75, 79] C: [70, 74] D: [60, 69] F: [0, 59]
	if(weightedAverage >= 90) {
		return "A";
	} else if(weightedAverage >= 80) {
		return "B";
	} else if(weightedAverage >= 75) {
		return "C+";
	} else if(weightedAverage >= 70) {
		return "C";
	} else if(weightedAverage >= 60) {
		return "D";
	} else {
		return "F";
	}
}

int findMinQuiz(double quizzes[], int size = 4) {
	// Finds the lowest quiz grade in the array, then return the index.
	double lowest = quizzes[0]; // Initialize with first quiz
	int lowestIndex = 0;

	for(int i = 1; i < size; i++) {  // Start from second element (i=1)
		if(quizzes[i] < lowest) {
			lowest = quizzes[i];
			lowestIndex = i;
		}
	}

	return lowestIndex;
}

double findAverageQuizScore(double quizzes[], int size = 4) {
	int minQuizIndex = findMinQuiz(quizzes); // Gets the lowest quiz grade.
	double sum = 0;

	for(int i = 0; i < size; i++) {
		sum += quizzes[i];
	}

	double sumWithoutLowest = sum - quizzes[minQuizIndex];

	return (sumWithoutLowest / 3.0); // Quiz average based on the 3 remaining quizzes.
}

double findAverageHomeworkScore(double homeworks[], int size = 4) {
	// 2 scores are out of 10 and 2 out of 20.
	// We need to make a copy because we don't want to modify the original scores
	double scaledHomeworks[4];
	for(int i = 0; i < size; i++) {
		scaledHomeworks[i] = homeworks[i];
	}

	// Scale the first two scores out of 10 to out of 20
	for(int i = 0; i < 2; i++) {
		scaledHomeworks[i] *= 2;
	}

	double sum = 0;
	for(int i = 0; i < size; i++) {
		sum += scaledHomeworks[i];
	}

	// Average out of 20, then convert to percentage (out of 100)
	return (sum / 4.0) * 5.0;
}

double findAverageLabScore(double labs[], int size = 8) {
	// Add all scores and divide by 8, then multiply by 10 to get out of 100
	double sum = 0;

	for(int i = 0; i < size; i++) {
		sum += labs[i];
	}

	return (sum / size) * 10.0; // Convert to score out of 100
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

	const int MAX_STUDENTS = 40; // Arbitrary limit
	Student students[MAX_STUDENTS];
	int count = 0;

	// Opening input file, with error handling
	ifstream inputFile("gradesIn.txt");
	if(!inputFile) {
		cerr << "Unable to open the file." << endl;
		return -1;
	}

	string line;

	// This will get rid of the header
	getline(inputFile, line);

	// Read the entire file until EOF
	while(inputFile >> students[count].firstName >> students[count].lastName) {
		inputFile >> students[count].attendance;

		for(int i = 0; i < 8; i++) {
			inputFile >> students[count].labScores[i];
		}

		for(int i = 0; i < 4; i++) {
			inputFile >> students[count].homeworkScores[i];
		}

		for(int i = 0; i < 4; i++) {
			inputFile >> students[count].quizScores[i];
		}

		inputFile >> students[count].groupWork;

		inputFile >> students[count].midtermAverage;
		inputFile >> students[count].finalAverage;

		students[count].quizAverage = findAverageQuizScore(students[count].quizScores);
		students[count].labAverage = findAverageLabScore(students[count].labScores);
		students[count].homeworkAverage = findAverageHomeworkScore(students[count].homeworkScores);

		// Calculate course average properly with the weights
		students[count].courseAverage = (students[count].attendance * 10) * 0.10 +  // Convert to percentage (out of 100)
										students[count].labAverage * 0.15 +
										students[count].homeworkAverage * 0.15 +
										students[count].quizAverage * 0.15 +
										(students[count].groupWork * 10) * 0.05 +   // Convert to percentage (out of 100)
										students[count].midtermAverage * 0.20 +
										students[count].finalAverage * 0.20;

		students[count].letterGrade = calculateLetterGrade(students[count].courseAverage);
		count++;
	}

	inputFile.close();

	ofstream outputFile1("gradesOut1.txt");
	ofstream outputFile2("gradesOut2.txt");

	// This ensures each the grades will have 2 decimal points max
	outputFile1 << fixed << setprecision(2);
	outputFile2 << fixed << setprecision(2);

	for(int i = 0; i < count; i++) {
		string fullName = students[i].firstName + " " + students[i].lastName;
		outputFile1 << fullName << endl
					<< students[i].attendance * 10 << endl
					<< students[i].groupWork * 10 << endl
					<< students[i].quizAverage << endl
					<< students[i].labAverage << endl
					<< students[i].homeworkAverage << endl
					<< students[i].finalAverage << endl
					<< students[i].courseAverage << endl << endl;

		outputFile2 << fullName << endl
					<< students[i].courseAverage << endl
					<< students[i].letterGrade << endl << endl;
	}

	outputFile1.close();
	outputFile2.close();

	return 0;
}
