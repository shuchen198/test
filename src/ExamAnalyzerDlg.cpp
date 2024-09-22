#include "pch.h"
#include "framework.h"
#include "ExamAnalyzer.h"
#include "ExamAnalyzerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CExamAnalyzerDlg::CExamAnalyzerDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_EXAMANALYZER_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_STUDENTS, m_studentList);
    DDX_Control(pDX, IDC_COMBO_STUDENT, m_studentCombo);
    DDX_Control(pDX, IDC_EDIT_SCORE, m_scoreEdit);
    DDX_Control(pDX, IDC_EDIT_ANALYSIS, m_analysisEdit);
}

BEGIN_MESSAGE_MAP(CExamAnalyzerDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_ADD_SCORE, &CExamAnalyzerDlg::OnBnClickedAddScore)
    ON_BN_CLICKED(IDC_BUTTON_ANALYZE, &CExamAnalyzerDlg::OnBnClickedAnalyze)
END_MESSAGE_MAP()

BOOL CExamAnalyzerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    m_studentList.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 100);
    m_studentList.InsertColumn(1, _T("学号"), LVCFMT_LEFT, 100);
    m_studentList.InsertColumn(2, _T("平均分"), LVCFMT_LEFT, 100);

    // 添加一些示例学生
    m_analyzer.addStudent(Student("张三", 1001));
    m_analyzer.addStudent(Student("李四", 1002));
    m_analyzer.addStudent(Student("王五", 1003));

    UpdateStudentList();

    return TRUE;
}

void CExamAnalyzerDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CExamAnalyzerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CExamAnalyzerDlg::OnBnClickedAddScore()
{
    CString studentName, score;
    m_studentCombo.GetWindowText(studentName);
    m_scoreEdit.GetWindowText(score);

    if (!studentName.IsEmpty() && !score.IsEmpty())
    {
        double scoreValue = _ttof(score);
        for (auto& student : m_analyzer.getStudents())
        {
            if (student.getName() == studentName.GetString())
            {
                student.addExamScore(scoreValue);
                break;
            }
        }

        UpdateStudentList();
        m_scoreEdit.SetWindowText(_T(""));
    }
    else
    {
        AfxMessageBox(_T("请选择学生并输入成绩"));
    }
}

void CExamAnalyzerDlg::OnBnClickedAnalyze()
{
    UpdateAnalysisResult();
}

void CExamAnalyzerDlg::UpdateStudentList()
{
    m_studentList.DeleteAllItems();
    m_studentCombo.ResetContent();

    for (const auto& student : m_analyzer.getStudents())
    {
        CString name(student.getName().c_str());
        CString id;
        id.Format(_T("%d"), student.getId());
        CString avgScore;
        avgScore.Format(_T("%.2f"), student.getAverageScore());

        int nIndex = m_studentList.InsertItem(m_studentList.GetItemCount(), name);
        m_studentList.SetItemText(nIndex, 1, id);
        m_studentList.SetItemText(nIndex, 2, avgScore);

        m_studentCombo.AddString(name);
    }
}

void CExamAnalyzerDlg::UpdateAnalysisResult()
{
    CString analysis;
    analysis.Format(_T("整体平均分: %.2f\r\n"), m_analyzer.getOverallAverage());
    
    const Student& topStudent = m_analyzer.getTopStudent();
    CString topStudentInfo;
    topStudentInfo.Format(_T("最高分学生: %s (学号: %d, 平均分: %.2f)"),
        topStudent.getName().c_str(), topStudent.getId(), topStudent.getAverageScore());
    
    analysis += topStudentInfo;
    m_analysisEdit.SetWindowText(analysis);
}