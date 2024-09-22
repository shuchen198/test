#pragma once
#include <string>
#include <vector>

class Student {
public:
    Student(const std::string& name, int id);
    void addExamScore(double score);
    double getAverageScore() const;
    // 其他必要的方法...

private:
    std::string name;
    int id;
    std::vector<double> examScores;
};