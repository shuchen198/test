#pragma once
#include "afxdialogex.h"
#include "ExamAnalyzer.h"

class CExamAnalyzerDlg : public CDialogEx
{
public:
    CExamAnalyzerDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_EXAMANALYZER_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    HICON m_hIcon;
    ExamAnalyzer m_analyzer;

    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedAddScore();
    afx_msg void OnBnClickedAnalyze();
    CListCtrl m_studentList;
    CComboBox m_studentCombo;
    CEdit m_scoreEdit;
    CEdit m_analysisEdit;
    void UpdateStudentList();
    void UpdateAnalysisResult();
};