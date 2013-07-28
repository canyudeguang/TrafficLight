
// TrafficLightDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficLight.h"
#include "TrafficLightDlg.h"
#include "afxdialogex.h"
#include "CSettingsDlg.h"
#include <limits.h>

#include "Globals.h"
#include "Generic.h"
#include "Core/Line.h"
#include "Core/Cross.h"
#include "Emulator/Emulator.h"
#include "Controller/TrafficDrawer.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/FixedScheduler.h"
#include "Scheduler/ThroughputFirstScheduler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrafficLightDlg 对话框



CTrafficLightDlg::CTrafficLightDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrafficLightDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrafficLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CUR_SCHEDULER, m_combo_cur_scheduler);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_slider_simulate_speed_ratio);
	DDX_Control(pDX, IDC_SPIN_VEHICLES, m_spin_vehicle);
	DDX_Control(pDX, IDC_EDIT_VEHICLES, m_edit_vehicles);
	DDX_Control(pDX, IDC_SPIN_LOAD, m_spin_load);
	DDX_Control(pDX, IDC_EDIT_TRAFFIC_LOAD, m_edit_load);
	DDX_Control(pDX, IDC_SPIN_LOAD_MIN_GREEN_TIME, m_spin_min_green_time);
	DDX_Control(pDX, IDC_SPIN_LOAD_MAX_RED_TIME, m_spin_max_red_time);
	DDX_Control(pDX, IDC_EDIT_MIN_GREEN_TIME, m_edit_min_green_time);
	DDX_Control(pDX, IDC_EDIT_MAX_RED_TIME, m_edit_max_red_time);
}

BEGIN_MESSAGE_MAP(CTrafficLightDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_PIC, &CTrafficLightDlg::OnStnClickedPic)
	ON_BN_CLICKED(ID_RUN, &CTrafficLightDlg::OnBnClickedRun)
	ON_BN_CLICKED(ID_PAUSE, &CTrafficLightDlg::OnBnClickedPause)
	ON_BN_CLICKED(ID_STOP, &CTrafficLightDlg::OnBnClickedStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, &CTrafficLightDlg::OnBnClickedButtonSettings)
	ON_BN_CLICKED(IDC_RADIO1, &CTrafficLightDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTrafficLightDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CTrafficLightDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CTrafficLightDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CTrafficLightDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CTrafficLightDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CTrafficLightDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CTrafficLightDlg::OnBnClickedRadio8)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VEHICLES, &CTrafficLightDlg::OnDeltaposSpinVehicles)
	ON_CBN_SELCHANGE(IDC_COMBO_CUR_SCHEDULER, &CTrafficLightDlg::OnCbnSelchangeComboCurScheduler)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPEED, &CTrafficLightDlg::OnNMCustomdrawSliderSpeed)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LOAD, &CTrafficLightDlg::OnDeltaposSpinLoad)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LOAD_MIN_GREEN_TIME, &CTrafficLightDlg::OnDeltaposSpinLoadMinGreenTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LOAD_MAX_RED_TIME, &CTrafficLightDlg::OnDeltaposSpinLoadMaxRedTime)
END_MESSAGE_MAP()


// CTrafficLightDlg 消息处理程序

BOOL CTrafficLightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CWnd::SetWindowPos(NULL,0,0,800,640,SWP_NOZORDER|SWP_NOMOVE); 

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	initial_data();init_controls();
	initial_graphic();
	this->SetTimer(1,TIME_DELIM_SEC*1000,0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTrafficLightDlg::init_controls() {
	m_spin_vehicle.SetBuddy(&m_edit_vehicles);
	m_spin_vehicle.SetRange(0,200);

	m_spin_load.SetBuddy(&m_edit_load);
	m_spin_load.SetRange(0,10000);

	m_spin_min_green_time.SetBuddy(&m_edit_min_green_time);
	m_spin_min_green_time.SetRange(0,200);

	m_spin_max_red_time.SetBuddy(&m_edit_max_red_time);
	m_spin_max_red_time.SetRange(0,200);
	

	for_each(SCHEDULERS->begin(),SCHEDULERS->end(),[&](Scheduler*& s) {
		m_combo_cur_scheduler.AddString(s->name());
	});
	m_combo_cur_scheduler.SetCurSel(0);

	m_slider_simulate_speed_ratio.SetRange(1,7);
	m_slider_simulate_speed_ratio.SetPos(2);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);
	OnBnClickedRadio1();
	OnBnClickedRadio5();
	OnCbnSelchangeComboCurScheduler();
}

void CTrafficLightDlg::set_scheduler(CString& scheduler_string) {
	Scheduler* changed_scheduler = find_scheduler(scheduler_string);
	if (changed_scheduler != NULL)
	{
		GLOBAL_EMU->set_scheduler(changed_scheduler);
		SELECTED_SCHEDULER = changed_scheduler;
		SELECTED_SCHEDULER->first_time_calculate();
	}

}
BOOL CTrafficLightDlg::PreTranslateMessage(MSG* pMsg){
	if ( pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN ) {  
			CString temp_cstring;
			switch( GetFocus()->GetDlgCtrlID()){  
			case IDC_EDIT_VEHICLES: 
				if (SELECTED_LINE!=NULL && SELECTED_ROAD!=NULL)
				{
					GetDlgItem(IDC_EDIT_VEHICLES)->GetWindowTextW(temp_cstring);
					set_num_of_vehicles(temp_cstring);
					temp_cstring.Delete(0,temp_cstring.GetLength());
					temp_cstring.Format(_T("%d"),SELECTED_LINE->num_of_vehicles());
					GetDlgItem(IDC_EDIT_VEHICLES)->SetWindowTextW(temp_cstring);
				}
				break;
			case IDC_EDIT_TRAFFIC_LOAD:
				if (SELECTED_LINE != NULL)
				{
					GetDlgItem(IDC_EDIT_TRAFFIC_LOAD)->GetWindowTextW(temp_cstring);
					set_driver_gen_speed(temp_cstring);
					temp_cstring.Delete(0,temp_cstring.GetLength());
					temp_cstring.Format(_T("%.1f"),SELECTED_LINE->drivers_per_second()*3600.0f);
					GetDlgItem(IDC_EDIT_TRAFFIC_LOAD)->SetWindowTextW(temp_cstring);
				}
				break;
			case IDC_EDIT_MIN_GREEN_TIME:
				if (SELECTED_SCHEDULER != NULL)
				{
					GetDlgItem(IDC_EDIT_MIN_GREEN_TIME)->GetWindowTextW(temp_cstring);
					set_min_green_time(temp_cstring);
					temp_cstring.Delete(0,temp_cstring.GetLength());
					temp_cstring.Format(_T("%d"),SELECTED_SCHEDULER->min_green_time());
					GetDlgItem(IDC_EDIT_MIN_GREEN_TIME)->SetWindowTextW(temp_cstring);
				}
				break;
			case IDC_EDIT_MAX_RED_TIME:
				if (SELECTED_SCHEDULER != NULL)
				{
					GetDlgItem(IDC_EDIT_MAX_RED_TIME)->GetWindowTextW(temp_cstring);
					set_max_red_time(temp_cstring);
					temp_cstring.Delete(0,temp_cstring.GetLength());
					temp_cstring.Format(_T("%d"),SELECTED_SCHEDULER->max_red_time());
					GetDlgItem(IDC_EDIT_MAX_RED_TIME)->SetWindowTextW(temp_cstring);
				}
				break;
			default:

				break;

			}

			return TRUE;

	}

	return CDialog::PreTranslateMessage(pMsg);

}

void CTrafficLightDlg::set_min_green_time(CString& green_string) {
	if (SELECTED_SCHEDULER != NULL)
	{
		int min_green = _ttoi(green_string);
		SELECTED_SCHEDULER->set_min_green_time(min_green);
	}
}

void CTrafficLightDlg::set_max_red_time(CString& red_string) {
	if (SELECTED_SCHEDULER != NULL)
	{
		int max_red = _ttoi(red_string);
		SELECTED_SCHEDULER->set_max_red_time(max_red);
	}
}
void CTrafficLightDlg::set_num_of_vehicles( CString& vehicle_string )
{

	if (SELECTED_LINE != NULL)
	{
		int n_vehicles = _ttoi(vehicle_string);
		SELECTED_LINE->set_num_of_vehicles(n_vehicles);
	}
}

void CTrafficLightDlg::set_driver_gen_speed(CString& driver_string) {
	if (SELECTED_LINE != NULL)
	{
		int n_drivers =_ttoi(driver_string);
		SELECTED_LINE->set_drivers_per_second(float(n_drivers)/3600.0f);
	}
}

void CTrafficLightDlg::initial_data() {
	srand(time(NULL));
	setlocale(LC_CTYPE,"chs");

	//GLOBAL VARS
	GLOBAL_EMU = new Emulator();

	DEF_RED_LIGHT.lights()->clear();
	DEF_RED_LIGHT.add_light(SingleLight(ALL,RED,true));
	DEF_RED_LIGHT.add_light(SingleLight(ALL,YELLOW,false));
	DEF_RED_LIGHT.add_light(SingleLight(ALL,GREEN,false));
	DEF_RED_LIGHT.set_duration(5);

	DEF_YELLOW_LIGHT.lights()->clear();
	DEF_YELLOW_LIGHT.add_light(SingleLight(ALL,RED,false));
	DEF_YELLOW_LIGHT.add_light(SingleLight(ALL,YELLOW,true));
	DEF_YELLOW_LIGHT.add_light(SingleLight(ALL,GREEN,false));
	DEF_YELLOW_LIGHT.set_duration(3);

	DEF_GREEN_LIGHT.lights()->clear();
	DEF_GREEN_LIGHT.add_light(SingleLight(ALL,RED,false));
	DEF_GREEN_LIGHT.add_light(SingleLight(ALL,YELLOW,false));
	DEF_GREEN_LIGHT.add_light(SingleLight(ALL,GREEN,true));
	DEF_GREEN_LIGHT.set_duration(5);

	FixedScheduler* fixed_scheduler = new FixedScheduler();
	ThroughputFirstScheduler* thoughtput_scheduler = new ThroughputFirstScheduler();
	SCHEDULERS->push_back(fixed_scheduler);
	SCHEDULERS->push_back(thoughtput_scheduler);

	SELECTED_SCHEDULER = find_scheduler(fixed_scheduler->name());
	GLOBAL_EMU->initial();

	GLOBAL_EMU->set_scheduler(SELECTED_SCHEDULER);

	_get_wpgmptr(&EXE_PATH);
	directory_path(EXE_PATH,PATH_MAX,DIR_PATH);

}
void CTrafficLightDlg::initial_graphic() {
	pPIC = GetDlgItem(IDC_PIC);
	pPIC_DC = pPIC->GetWindowDC();
	pPIC->GetClientRect(&RECT_PIC);
	MEM_DC.CreateCompatibleDC(pPIC_DC);
	MEM_DC_BITMAP.CreateCompatibleBitmap(pPIC_DC,RECT_PIC.Width(),RECT_PIC.Height());
	auto pOldBit = MEM_DC.SelectObject(MEM_DC_BITMAP);
	MEM_DC.SetBkMode(TRANSPARENT);
}

afx_msg void CTrafficLightDlg::OnTimer(UINT_PTR n)
{

	MEM_DC.FillSolidRect(0,0,RECT_PIC.Width(),RECT_PIC.Height(),BACKGROUND_COLOR.rgb());
	draw_roads4(&MEM_DC);
	pPIC_DC->BitBlt(0,0,RECT_PIC.Width(),RECT_PIC.Height(),&MEM_DC,0,0,SRCCOPY);
}
void CTrafficLightDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTrafficLightDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		Invalidate(FALSE);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTrafficLightDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CTrafficLightDlg::OnClose() {
	delete GLOBAL_EMU;
	delete[] EXE_PATH;
	//delete[] DIR_PATH;
	return 0;
}


void CTrafficLightDlg::OnStnClickedPic()
{

}



void CTrafficLightDlg::selected_changed() {
	if (SELECTED_LINE != NULL)
	{
		CWnd* static_vehicle = GetDlgItem(IDC_EDIT_VEHICLES);
		CWnd* static_load = GetDlgItem(IDC_EDIT_TRAFFIC_LOAD);
		CString vehicle_string,load_string;
		vehicle_string.Format(_T("%d"),SELECTED_LINE->num_of_vehicles());
		int load_per_hour = SELECTED_LINE->drivers_per_second()*3600;
		load_string.Format(_T("%d"),load_per_hour);
		static_vehicle->SetWindowTextW(vehicle_string);
		static_load->SetWindowTextW(load_string);
	}

}


void CTrafficLightDlg::OnBnClickedRun()
{
	GLOBAL_EMU->start();
}


void CTrafficLightDlg::OnBnClickedPause()
{
	GLOBAL_EMU->pause();
}


void CTrafficLightDlg::OnBnClickedStop()
{
	GLOBAL_EMU->stop();
}




void CTrafficLightDlg::OnBnClickedButtonSettings()
{
	CSettingsDlg settings_dlg;
	settings_dlg.DoModal();
}

void CTrafficLightDlg::OnBnClickedRadio1()
{
	SELECTED_ROAD = GLOBAL_EMU->cross()->road_at(0);
	if (SELECTED_LINE != NULL)
	{
		SELECTED_LINE = SELECTED_ROAD->line_at(
			SELECTED_LINE->index());
	}
	selected_changed();
}



void CTrafficLightDlg::OnBnClickedRadio2()
{
	SELECTED_ROAD = GLOBAL_EMU->cross()->road_at(1);
	if (SELECTED_LINE != NULL)
	{
		SELECTED_LINE = SELECTED_ROAD->line_at(
			SELECTED_LINE->index());
	}
	selected_changed();
}


void CTrafficLightDlg::OnBnClickedRadio3()
{
	if (GLOBAL_EMU->cross()->num_of_roads()>2)
	{
		SELECTED_ROAD = GLOBAL_EMU->cross()->road_at(2);
		if (SELECTED_LINE != NULL)
		{
			SELECTED_LINE = SELECTED_ROAD->line_at(
				SELECTED_LINE->index());
		}
		selected_changed();
	}
}


void CTrafficLightDlg::OnBnClickedRadio4()
{
	if (GLOBAL_EMU->cross()->num_of_roads()>3)
	{
		SELECTED_ROAD = GLOBAL_EMU->cross()->road_at(3);
		if (SELECTED_LINE != NULL)
		{
			SELECTED_LINE = SELECTED_ROAD->line_at(
				SELECTED_LINE->index());
		}
		selected_changed();
	}
}


void CTrafficLightDlg::OnBnClickedRadio5()
{
	if (SELECTED_ROAD != NULL)
	{
		SELECTED_LINE = SELECTED_ROAD->line_at(0);
		selected_changed();
	}
}


void CTrafficLightDlg::OnBnClickedRadio6()
{
	if (SELECTED_ROAD != NULL)
	{
		if (SELECTED_ROAD->num_of_lines()>1)
		{
			SELECTED_LINE = SELECTED_ROAD->line_at(1);
			selected_changed();
		}
	}
	// TODO: Add your control notification handler code here
}


void CTrafficLightDlg::OnBnClickedRadio7()
{
	if (SELECTED_ROAD != NULL)
	{
		if (SELECTED_ROAD->num_of_lines()>2)
		{
			SELECTED_LINE = SELECTED_ROAD->line_at(2);
			selected_changed();
		}
	}
}


void CTrafficLightDlg::OnBnClickedRadio8()
{
	if (SELECTED_ROAD != NULL)
	{
		if (SELECTED_ROAD->num_of_lines()>3)
		{
			SELECTED_LINE = SELECTED_ROAD->line_at(3);
			selected_changed();
		}

	}
}








void CTrafficLightDlg::OnDeltaposSpinVehicles(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	//@TN
	*pResult = 0;

	CString vehicles_string;
	int cur_vehicles = 0;
	GetDlgItem(IDC_EDIT_VEHICLES)->GetWindowTextW(vehicles_string);
	cur_vehicles = _ttoi(vehicles_string);
	if (pNMUpDown->iDelta > 0) {
		++cur_vehicles;
	}
	else if (pNMUpDown->iDelta <0)
	{
		--cur_vehicles;
	}
	vehicles_string.Format(_T("%d"),cur_vehicles);
	GetDlgItem(IDC_EDIT_VEHICLES)->SetWindowTextW(vehicles_string);
	*pResult = 0;
}


void CTrafficLightDlg::OnCbnSelchangeComboCurScheduler()
{
	CString scheduler_string;
	CString time_string;
	m_combo_cur_scheduler.GetLBText(m_combo_cur_scheduler.GetCurSel(),scheduler_string);
	set_scheduler(scheduler_string);
	CWnd* min_green_edit = GetDlgItem(IDC_EDIT_MIN_GREEN_TIME);
	time_string.Format(_T("%d"),SELECTED_SCHEDULER->min_green_time());
	min_green_edit->SetWindowTextW(time_string);
	time_string.Delete(0,time_string.GetLength());
	CWnd* max_red_edit = GetDlgItem(IDC_EDIT_MAX_RED_TIME);
	time_string.Format(_T("%d"),SELECTED_SCHEDULER->max_red_time());
	max_red_edit->SetWindowTextW(time_string);
}


void CTrafficLightDlg::OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//@TN
	*pResult = 0;
	CString speed_string;
	CWnd* static_speed=GetDlgItem(IDC_STATIC_SPEED);
	float new_speed = m_slider_simulate_speed_ratio.GetPos()/2.0f;
	TIME_DELIM_DRIVER_DO = TIME_DELIM_SEC /new_speed;
	speed_string.Format(_T("%.1f"),new_speed);
	speed_string += _T("x");
	static_speed->SetWindowTextW(speed_string);
	*pResult = 0;
}



void CTrafficLightDlg::OnDeltaposSpinLoad(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	CString load_string;
	int cur_load = 0;
	m_edit_load.GetWindowTextW(load_string);
	cur_load = _ttoi(load_string);
	if (pNMUpDown->iDelta > 0) {
		++cur_load;
	}
	else if (pNMUpDown->iDelta <0)
	{
		--cur_load;
	}
	load_string.Format(_T("%d"),cur_load);
	m_edit_load.SetWindowTextW(load_string);
	*pResult = 0;
}


void CTrafficLightDlg::OnDeltaposSpinLoadMinGreenTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	CString min_green_string;
	int cur_min_green = 0;
	m_edit_min_green_time.GetWindowTextW(min_green_string);
	cur_min_green = _ttoi(min_green_string);
	if (pNMUpDown->iDelta > 0) {
		++cur_min_green;
	}
	else if (pNMUpDown->iDelta <0)
	{
		--cur_min_green;
	}
	min_green_string.Format(_T("%d"),cur_min_green);
	m_edit_min_green_time.SetWindowTextW(min_green_string);
	*pResult = 0;
}


void CTrafficLightDlg::OnDeltaposSpinLoadMaxRedTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
		*pResult = 0;
		CString max_red_time;
		int cur_max_red = 0;
		m_edit_max_red_time.GetWindowTextW(max_red_time);
		cur_max_red = _ttoi(max_red_time);
		if (pNMUpDown->iDelta > 0) {
			++cur_max_red;
		}
		else if (pNMUpDown->iDelta <0)
		{
			--cur_max_red;
		}
		max_red_time.Format(_T("%d"),cur_max_red);
		m_edit_max_red_time.SetWindowTextW(max_red_time);
	*pResult = 0;
}
