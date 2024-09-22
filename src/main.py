import tkinter as tk
from tkinter import ttk, messagebox
from exam_analyzer import Student, ExamAnalyzer

class ExamAnalyzerApp:
    def __init__(self, master):
        self.master = master
        self.master.title("考试分析系统")
        self.analyzer = ExamAnalyzer()

        self.create_widgets()

    def create_widgets(self):
        # 学生列表
        self.tree = ttk.Treeview(self.master, columns=('Name', 'ID', 'Average'), show='headings')
        self.tree.heading('Name', text='姓名')
        self.tree.heading('ID', text='学号')
        self.tree.heading('Average', text='平均分')
        self.tree.grid(row=0, column=0, columnspan=3, padx=10, pady=10, sticky='nsew')

        # 添加学生区域
        ttk.Label(self.master, text="姓名:").grid(row=1, column=0, padx=5, pady=5, sticky='e')
        self.name_entry = ttk.Entry(self.master)
        self.name_entry.grid(row=1, column=1, padx=5, pady=5, sticky='w')

        ttk.Label(self.master, text="学号:").grid(row=2, column=0, padx=5, pady=5, sticky='e')
        self.id_entry = ttk.Entry(self.master)
        self.id_entry.grid(row=2, column=1, padx=5, pady=5, sticky='w')

        self.add_student_btn = ttk.Button(self.master, text="添加学生", command=self.add_student)
        self.add_student_btn.grid(row=3, column=0, columnspan=2, pady=10)

        # 添加成绩区域
        ttk.Label(self.master, text="成绩:").grid(row=4, column=0, padx=5, pady=5, sticky='e')
        self.score_entry = ttk.Entry(self.master)
        self.score_entry.grid(row=4, column=1, padx=5, pady=5, sticky='w')

        self.add_score_btn = ttk.Button(self.master, text="添加成绩", command=self.add_score)
        self.add_score_btn.grid(row=5, column=0, columnspan=2, pady=10)

        # 分析结果区域
        self.analysis_text = tk.Text(self.master, height=5, width=40)
        self.analysis_text.grid(row=6, column=0, columnspan=3, padx=10, pady=10, sticky='nsew')

        self.analyze_btn = ttk.Button(self.master, text="分析", command=self.analyze)
        self.analyze_btn.grid(row=7, column=0, columnspan=3, pady=10)

    def add_student(self):
        name = self.name_entry.get()
        student_id = self.id_entry.get()
        if name and student_id:
            student = Student(name, int(student_id))
            self.analyzer.add_student(student)
            self.update_student_list()
            self.name_entry.delete(0, tk.END)
            self.id_entry.delete(0, tk.END)
        else:
            messagebox.showerror("错误", "请输入姓名和学号")

    def add_score(self):
        selected_item = self.tree.selection()
        if selected_item:
            student_id = self.tree.item(selected_item)['values'][1]
            score = self.score_entry.get()
            if score:
                for student in self.analyzer.students:
                    if student.student_id == student_id:
                        student.add_exam_score(float(score))
                        break
                self.update_student_list()
                self.score_entry.delete(0, tk.END)
            else:
                messagebox.showerror("错误", "请输入成绩")
        else:
            messagebox.showerror("错误", "请选择一个学生")

    def analyze(self):
        overall_avg = self.analyzer.get_overall_average()
        top_student = self.analyzer.get_top_student()
        analysis = f"整体平均分: {overall_avg:.2f}\n"
        if top_student:
            analysis += f"最高分学生: {top_student.name} (学号: {top_student.student_id}, 平均分: {top_student.get_average_score():.2f})"
        self.analysis_text.delete('1.0', tk.END)
        self.analysis_text.insert(tk.END, analysis)

    def update_student_list(self):
        for item in self.tree.get_children():
            self.tree.delete(item)
        for student in self.analyzer.students:
            self.tree.insert('', 'end', values=(student.name, student.student_id, f"{student.get_average_score():.2f}"))

if __name__ == "__main__":
    root = tk.Tk()
    app = ExamAnalyzerApp(root)
    root.mainloop()