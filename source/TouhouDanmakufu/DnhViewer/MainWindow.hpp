#ifndef __TOUHOUDANMAKUFU_VIEW_MAINWINDOW__
#define __TOUHOUDANMAKUFU_VIEW_MAINWINDOW__

#include "../Common/StgSystem.hpp"
#include "Constant.hpp"
#include "DebugWindow.hpp"
#include "ScenePanel.hpp"

class StgControllerForViewer;
class GraphicsWindow;
/**********************************************************
//MainWindow
**********************************************************/
class MainWindow : public WindowBase, public gstd::Singleton<MainWindow> {
public:
	MainWindow();
	~MainWindow();
	bool Initialize();

	GraphicsWindow* GetGraphicsWindow() { return wndGraphics_.GetPointer(); }
	ScenePanel* GetScenePanel() { return panelScene_.GetPointer(); }
	DebugWindow* GetDebugWindow() { return wndDebug_.GetPointer(); }

	ref_count_ptr<StgControllerForViewer> GetStgController() { return controller_; }
	void SetStgController(ref_count_ptr<StgControllerForViewer> controller);

	void ClearData();
	bool Load(std::wstring path);
	bool Save(std::wstring path);

protected:
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	ref_count_ptr<WTabControll> wndTab_;
	ref_count_ptr<WStatusBar> wndStatus_;
	ref_count_ptr<GraphicsWindow> wndGraphics_;
	ref_count_ptr<ScenePanel> panelScene_;
	ref_count_ptr<DebugWindow> wndDebug_;

	ref_count_ptr<StgControllerForViewer> controller_;
};

/**********************************************************
//GraphicsWindow
**********************************************************/
class GraphicsWindow : public WindowBase {
public:
	enum {
		TYPE_WINDOW_PANEL,
		TYPE_WINDOW_OVERLAPPED,
	};

public:
	GraphicsWindow();
	~GraphicsWindow();
	bool Initialize();
	void SetWindowType(int type, HWND hParent);

protected:
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

/**********************************************************
//StgControllerForViewer
**********************************************************/
class StgControllerForViewer : public StgSystemController {
public:
	virtual void DoEnd();
	virtual void DoRetry();
	static ref_count_ptr<StgControllerForViewer> Create();
};

#endif
