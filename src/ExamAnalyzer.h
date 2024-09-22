#pragma once
#include <vector>
#include "Student.h"

class ExamAnalyzer {
public:
    void addStudent(const Student& student);
    double getOverallAverage() const;
    Student getTopStudent() const;
    const std::vector<Student>& getStudents() const { return students; }

private:
    std::vector<Student> students;
};