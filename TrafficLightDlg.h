
// TrafficLightDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTrafficLightDlg 对话框
class CTrafficLightDlg : 
	public CDialogEx
	//virtual public CView
{
// 构造
public:
	CTrafficLightDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TRAFFICLIGHT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR n);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int OnClose();
	int OnEraseBkgnd();
	
public:
	afx_msg void OnStnClickedPic();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	//void OnTimer(HWND hWnd,UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime );
	afx_msg void OnBnClickedButtonSettings();
	void initial_graphic();
	void initial_data();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	void selected_changed();
	afx_msg void OnEnChangeEditVehicles();
	BOOL PreTranslateMessage(MSG* pMsg);
	void init_controls();
	
	afx_msg void OnDeltaposSpinVehicles(NMHDR *pNMHDR, LRESULT *pResult);
	void set_num_of_vehicles(CString& vehicle_string);
	void set_driver_gen_speed(CString& driver_string);
	void set_min_green_time(CString& green_string);
	void set_max_red_time(CString& red_string);
	void set_scheduler(CString& scheduler_string);
	CComboBox m_combo_cur_scheduler;
	afx_msg void OnCbnSelchangeComboCurScheduler();
	CSliderCtrl m_slider_simulate_speed_ratio;
	afx_msg void OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	CSpinButtonCtrl m_spin_vehicle;
	CEdit m_edit_vehicles;
	CSpinButtonCtrl m_spin_load;
	CEdit m_edit_load;
	afx_msg void OnDeltaposSpinLoad(NMHDR *pNMHDR, LRESULT *pResult);
	CSpinButtonCtrl m_spin_min_green_time;
	CSpinButtonCtrl m_spin_max_red_time;
	CEdit m_edit_min_green_time;
	CEdit m_edit_max_red_time;
	afx_msg void OnDeltaposSpinLoadMinGreenTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinLoadMaxRedTime(NMHDR *pNMHDR, LRESULT *pResult);
};


