#ifndef __TOUHOUDANMAKUFU_VIEW_SCENEPANEL__
#define __TOUHOUDANMAKUFU_VIEW_SCENEPANEL__

#include "Common.hpp"
#include "Constant.hpp"
#include "ScriptSelect.hpp"

/**********************************************************
//ScenePanel
**********************************************************/
class ScenePanel : public WPanel {
public:
	virtual void LocateParts();
	bool Initialize(HWND hParent);

	bool StartStg();
	bool EndStg();
	void SetStgState(bool bStart);

	bool IsFixedArea() { return bFixedArea_; }
	void SetFixedArea(bool bFixed) { bFixedArea_ = bFixed; }

	void ClearData();
	virtual void Read(RecordBuffer& record);
	virtual void Write(RecordBuffer& record);

private:
	LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class ScriptPathPanel;

	bool bFixedArea_;
	ref_count_ptr<ScriptPathPanel> panelPathEnemy_;
	ref_count_ptr<ScriptPathPanel> panelPathPlayer_;

	WButton buttonStart_;
	WButton buttonPause_;
};

class ScenePanel::ScriptPathPanel : public WPanel {
public:
	enum {
		TYPE_ENEMY,
		TYPE_PLAYER,
	};

public:
	virtual ~ScriptPathPanel();
	bool Initialize(int type, HWND hParent);
	void SetWindowEnable(bool bEnable);
	std::wstring GetPath() { return editPath_.GetText(); }
	void SetPath(std::wstring path);

	ref_count_ptr<ScriptInformation> GetSelectedScriptInformation() { return infoSelected_; }

protected:
	LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	ref_count_ptr<ScriptInformation> _CreateScriptInformation(std::wstring path);

	WLabel labelPath_;
	WEditBox editPath_;
	WButton buttonPath_;
	ref_count_ptr<ScriptSelectDialog> dialogSelect_;
	ref_count_ptr<ScriptInformation> infoSelected_;
};

#endif
