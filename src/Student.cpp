#include "Student.h"
#include <numeric>

Student::Student(const std::string& name, int id) : name(name), id(id) {}

void Student::addExamScore(double score) {
    examScores.push_back(score);
}

double Student::getAverageScore() const {
    if (examScores.empty()) return 0.0;
    return std::accumulate(examScores.begin(), examScores.end(), 0.0) / examScores.size();
}