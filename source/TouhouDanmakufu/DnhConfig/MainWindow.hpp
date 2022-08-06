#ifndef __TOUHOUDANMAKUFU_CONFIG_MAINWINDOW__
#define __TOUHOUDANMAKUFU_CONFIG_MAINWINDOW__

#include "Common.hpp"
#include "Constant.hpp"

class DevicePanel;
class KeyPanel;
class OptionPanel;
/**********************************************************
//MainWindow
**********************************************************/
class MainWindow : public WindowBase, public gstd::Singleton<MainWindow> {
public:
	MainWindow();
	~MainWindow();
	bool Initialize();
	bool StartUp();

	void ClearData();
	bool Load();
	bool Save();

	void UpdateKeyAssign();

	void ReadConfiguration();
	void WriteConfiguration();

protected:
	void _RunExecutor();
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	ref_count_ptr<WTabControll> wndTab_;
	ref_count_ptr<DevicePanel> panelDevice_;
	ref_count_ptr<KeyPanel> panelKey_;
	ref_count_ptr<OptionPanel> panelOption_;
};

/**********************************************************
//DevicePanel
**********************************************************/
class DevicePanel : public WPanel {
public:
	DevicePanel();
	~DevicePanel();
	bool Initialize(HWND hParent);

	void ReadConfiguration();
	void WriteConfiguration();

protected:
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	WComboBox comboWindowSize_;
};

/**********************************************************
//KeyPanel
**********************************************************/
class KeyPanel : public WPanel {
	class KeyListView;

protected:
	enum {
		COL_ACTION,
		COL_KEY_ASSIGN,
		COL_PAD_ASSIGN,
	};

public:
	KeyPanel();
	~KeyPanel();
	bool Initialize(HWND hParent);
	bool StartUp();
	void UpdateKeyAssign();

	void ReadConfiguration();
	void WriteConfiguration();

protected:
	WComboBox comboPadIndex_;
	ref_count_ptr<KeyListView> viewKey_;
	KeyCodeList listKeyCode_;
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void _UpdateText(int row);
};

class KeyPanel::KeyListView : public WListView {
protected:
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

/**********************************************************
//OptionPanel
**********************************************************/
class OptionPanel : public WPanel {
protected:
	enum {
		ROW_LOG_WINDOW,
		ROW_LOG_FILE,
		ROW_MOUSE_UNVISIBLE,
	};

public:
	OptionPanel();
	~OptionPanel();
	bool Initialize(HWND hParent);

	void ReadConfiguration();
	void WriteConfiguration();

protected:
	ref_count_ptr<WListView> viewOption_;

	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
