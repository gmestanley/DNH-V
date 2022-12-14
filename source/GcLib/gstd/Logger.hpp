#ifndef __GSTD_LOGGER__
#define __GSTD_LOGGER__

#include "File.hpp"
#include "GstdConstant.hpp"
#include "GstdUtility.hpp"
#include "Thread.hpp"

#include "Window.hpp"

namespace gstd {

/**********************************************************
//Logger
**********************************************************/
class Logger {
public:
	Logger();
	virtual ~Logger();
	virtual bool Initialize() { return true; }
	void AddLogger(ref_count_ptr<Logger> logger) { listLogger_.push_back(logger); }
	virtual void Write(std::wstring str);

	static void SetTop(Logger* logger) { top_ = logger; }
	static void WriteTop(std::wstring str)
	{
		if (top_ != NULL)
			top_->Write(str);
	} //トップのロガに出力します
	void ConcatenateLog(std::wstring text);

protected:
	static Logger* top_;
	gstd::CriticalSection lock_;
	std::list<ref_count_ptr<Logger>> listLogger_; //子のロガ
	virtual void _WriteChild(SYSTEMTIME& time, std::wstring str);
	virtual void _Write(SYSTEMTIME& time, std::wstring str) = 0;
};

/**********************************************************
//FileLogger
**********************************************************/
class FileLogger : public Logger {
public:
	FileLogger();
	~FileLogger();
	void Clear();
	bool Initialize(bool bEnable = true);
	bool Initialize(std::wstring path, bool bEnable = true);
	bool SetPath(std::wstring path);
	void SetMaxFileSize(int size) { sizeMax_ = size; }

protected:
	bool bEnable_;
	std::wstring path_;
	std::wstring path2_;
	int sizeMax_;
	virtual void _Write(SYSTEMTIME& systemTime, std::wstring str);
	void _CreateFile(File& file);
};

/**********************************************************
//WindowLogger
//ログウィンドウ
//ウィンドウは別スレッド動作です
**********************************************************/
class WindowLogger : public Logger, public WindowBase {
public:
	class WindowThread;
	class Panel;
	class LogPanel;
	class InfoPanel;
	class InfoCollectThread;
	friend WindowThread;
	friend LogPanel;
	friend InfoPanel;
	friend InfoCollectThread;
	enum {
		WM_ENDLOGGER = WM_APP + 1,
		WM_ADDPANEL,

		STATUS_MEMORY = 0,
		STATUS_CPU = 1,

		MENU_ID_OPEN = 1,
	};

public:
	WindowLogger();
	~WindowLogger();
	bool Initialize(bool bEnable = true);
	void SaveState();
	void LoadState();
	void SetInfo(int row, std::wstring textInfo, std::wstring textData);
	bool AddPanel(ref_count_ptr<Panel> panel, std::wstring name);

	void ShowLogWindow();
	static void InsertOpenCommandInSystemMenu(HWND hWnd);

protected:
	struct AddPanelEvent {
		std::wstring name;
		ref_count_ptr<Panel> panel;
	};
	bool bEnable_;
	ref_count_ptr<WindowThread> threadWindow_;
	ref_count_ptr<WTabControll> wndTab_;
	ref_count_ptr<WStatusBar> wndStatus_;
	ref_count_ptr<LogPanel> wndLogPanel_;
	ref_count_ptr<InfoPanel> wndInfoPanel_;
	ref_count_ptr<InfoCollectThread> threadInfoCollect_;
	gstd::CriticalSection lock_;
	std::list<AddPanelEvent> listEventAddPanel_;

	void _Run();
	void _CreateWindow();
	virtual void _Write(SYSTEMTIME& systemTime, std::wstring str);
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
class WindowLogger::WindowThread : public gstd::Thread, public gstd::InnerClass<WindowLogger> {
	friend WindowLogger;

protected:
	WindowThread(WindowLogger* logger);
	void _Run();
};
class WindowLogger::Panel : public WPanel {
	friend WindowLogger;

protected:
	virtual bool _AddedLogger(HWND hTab) = 0;

	virtual void _ReadRecord(RecordBuffer& record) {}
	virtual void _WriteRecord(RecordBuffer& record) {}
};

class WindowLogger::LogPanel : public WindowLogger::Panel {
public:
	LogPanel();
	~LogPanel();
	virtual void LocateParts();
	void AddText(std::wstring text);

protected:
	virtual bool _AddedLogger(HWND hTab);

private:
	WEditBox wndEdit_;
};

class WindowLogger::InfoPanel : public WindowLogger::Panel {
public:
	InfoPanel();
	~InfoPanel();
	virtual void LocateParts();
	void SetInfo(int row, std::wstring textInfo, std::wstring textData);

protected:
	virtual bool _AddedLogger(HWND hTab);

private:
	enum {
		ROW_INFO = 0,
		ROW_DATA,
	};
	WListView wndListView_;
};

class WindowLogger::InfoCollectThread : public Thread {
public:
	InfoCollectThread(ref_count_ptr<WStatusBar> wndStatus);
	~InfoCollectThread();

protected:
	//CPU情報構造体
	struct CpuInfo {
		char venderID[13];
		char name[49];
		std::string cpuName;
		double clock;
		int type;
		int family;
		int model;
		int stepping;
		bool bMMXEnabled;
		bool bAMD3DNowEnabled;
		bool bSIMDEnabled;
	};
	ref_count_ptr<WStatusBar> wndStatus_;
	CpuInfo infoCpu_;
	virtual void _Run();
	CpuInfo _GetCpuInformation();
	double _GetCpuPerformance();
};

} // namespace gstd;

#endif
