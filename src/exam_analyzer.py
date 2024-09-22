class Student:
    def __init__(self, name, student_id):
        self.name = name
        self.student_id = student_id
        self.exam_scores = []

    def add_exam_score(self, score):
        self.exam_scores.append(score)

    def get_average_score(self):
        if not self.exam_scores:
            return 0
        return sum(self.exam_scores) / len(self.exam_scores)

class ExamAnalyzer:
    def __init__(self):
        self.students = []

    def add_student(self, student):
        self.students.append(student)

    def get_overall_average(self):
        if not self.students:
            return 0
        return sum(student.get_average_score() for student in self.students) / len(self.students)

    def get_top_student(self):
        if not self.students:
            return None
        return max(self.students, key=lambda student: student.get_average_score())