#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
// Specify C++11 standard within your source code
#pragma GCC diagnostic ignored "-Wc++11-extensions"

using namespace std;
// Define the Student struct
struct Student {
    string name;
    int studentID;
    int assignmentScore;
    int quizScore;
    int examScore;
};

// Function to check if a score is valid (between 0 and 100)
bool isValidScore(int score) {
    return score >= 0 && score <= 100;
}

// Function to calculate the overall grade based on weightage
double calculateOverallGrade(const Student& student) {
    double assignmentWeight = 0.3;
    double quizWeight = 0.3;
    double examWeight = 0.4;
    return (student.assignmentScore * assignmentWeight + student.quizScore * quizWeight + student.examScore * examWeight);
}

// Function to calculate the letter grade based on overall grade
char calculateLetterGrade(double overallGrade) {
    if (overallGrade >= 90) {
        return 'A';
    } else if (overallGrade >= 80) {
        return 'B';
    } else if (overallGrade >= 70) {
        return 'C';
    } else if (overallGrade >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

// Function to provide feedback based on the letter grade
    string getFeedback(char letterGrade) {
    if (letterGrade == 'A') {
        return "Congratulations! Excellent performance.";
    } else if (letterGrade == 'B') {
        return "Good job! Keep up the great work.";
    } else if (letterGrade == 'C') {
        return "You're doing fine, but there's room for improvement.";
    } else if (letterGrade == 'D') {
        return "Consider studying more to improve your grades.";
    } else {
        return "You need to work harder to pass this course.";
    }
}

// Function to save student data to a file
void saveStudentDataToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open the file for writing." << endl;
        return;
    }

    for (const Student& student : students) {
        file << student.name << "," << student.studentID << ","
             << student.assignmentScore << "," << student.quizScore << ","
             << student.examScore << "\n";
    }

    file.close();
}

// Function to load student data from a file
void loadStudentDataFromFile(vector<Student>& students, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open the file for reading." << endl;
        return;
    }

    Student student;
    while (file >> student.name >> student.studentID >> student.assignmentScore >> student.quizScore >> student.examScore) {
        students.push_back(student);
    }

    file.close();
}

// Function to display student information
void displayStudentInfo(const Student& student) {
    char letterGrade = calculateLetterGrade(calculateOverallGrade(student));
    string feedback = getFeedback(letterGrade);

    cout << "Student Information:" << endl;
    cout << "Name: " << student.name << endl;
    cout << "ID: " << student.studentID << endl;
    cout << "Assignment Score: " << student.assignmentScore << endl;
    cout << "Quiz Score: " << student.quizScore << endl;
    cout << "Exam Score: " << student.examScore << endl;
    cout << "Overall Grade: " << calculateOverallGrade(student) << endl;
    cout << "Letter Grade: " << letterGrade << endl;
    cout << "Feedback: " << feedback << endl;
    cout << "--------------------------" << endl;
}

// Function to process student data
void processStudentData(vector<Student>& students) {
    Student student;

    cout << "Enter student name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, student.name);

    cout << "Enter student ID: ";
    cin >> student.studentID;

    do {
        cout << "Enter assignment score (0-100): ";
        cin >> student.assignmentScore;
        if (!isValidScore(student.assignmentScore)) {
            cout << "Error: Assignment score must be between 0 and 100." << endl;
        }
    } while (!isValidScore(student.assignmentScore));

    do {
        cout << "Enter quiz score (0-100): ";
        cin >> student.quizScore;
        if (!isValidScore(student.quizScore)) {
            cout << "Error: Quiz score must be between 0 and 100." << endl;
        }
    } while (!isValidScore(student.quizScore));

    do {
        cout << "Enter exam score (0-100): ";
        cin >> student.examScore;
        if (!isValidScore(student.examScore)) {
            cout << "Error: Exam score must be between 0 and 100." << endl;
        }
    } while (!isValidScore(student.examScore));

    students.push_back(student);
}

int main() {
    vector<Student> students;
    char continueInput = 'y';

    while (continueInput == 'y' || continueInput == 'Y') {
        processStudentData(students);

        cout << "Do you want to enter data for another student (y/n)? ";
        cin >> continueInput;
    }

    // Save student data to a file (optional)
    saveStudentDataToFile(students, "student_data.txt");

    // Load student data from a file (optional)
    vector<Student> loadedStudents;
    loadStudentDataFromFile(loadedStudents, "student_data.txt");

    // Display results
    for (const Student& student : students) {
        displayStudentInfo(student);
    }

    return 0;
}
