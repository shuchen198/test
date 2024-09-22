#include "ExamAnalyzer.h"
#include <algorithm>

void ExamAnalyzer::addStudent(const Student& student) {
    students.push_back(student);
}

double ExamAnalyzer::getOverallAverage() const {
    if (students.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& student : students) {
        sum += student.getAverageScore();
    }
    return sum / students.size();
}

Student ExamAnalyzer::getTopStudent() const {
    if (students.empty()) throw std::runtime_error("No students available");
    return *std::max_element(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getAverageScore() < b.getAverageScore();
        });
}