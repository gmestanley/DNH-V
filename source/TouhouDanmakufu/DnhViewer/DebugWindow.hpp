#ifndef __TOUHOUDANMAKUFU_VIEW_DEBUGWINDOW__
#define __TOUHOUDANMAKUFU_VIEW_DEBUGWINDOW__

#include "Common.hpp"
#include "Constant.hpp"

/**********************************************************
//DebugWindow
**********************************************************/
class DebugWindow : public WindowBase {
public:
	DebugWindow();
	void Initialize();
	void ShowModeless();

	bool IsPlayerInvincivility();
	void SetPlayerInvincivility(bool bInvincivility);

protected:
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	WButton checkPlayerInvincivility_;
};

/**********************************************************
//DebugTask
**********************************************************/
class DebugTask : public TaskBase {
public:
	enum {
		TASK_PRI_WORK = 0,
	};

public:
	DebugTask();
	~DebugTask();
	void Work();

private:
	bool bPlayerInvincivility_;
};

#endif
