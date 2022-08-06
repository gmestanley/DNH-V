#ifndef __TOUHOUDANMAKUFU_VIEW_SCRIPTSELECT__
#define __TOUHOUDANMAKUFU_VIEW_SCRIPTSELECT__

#include "Common.hpp"
#include "Constant.hpp"

/**********************************************************
//ScriptSelectDialog
**********************************************************/
class ScriptSelectDialog : public ModalDialog {
protected:
	const static std::wstring KEY_ALL;
	const static std::wstring KEY_SINGLE;
	const static std::wstring KEY_PLURAL;
	const static std::wstring KEY_STAGE;
	const static std::wstring KEY_PACKAGE;
	const static std::wstring KEY_PLAYER;

	enum {
		LIST_TYPE,
		LIST_NAME,
		LIST_PATH,
		LIST_ARCHIVE,
		LIST_TEXT,
	};

public:
	virtual void Initialize();
	virtual void ShowModal(std::wstring path);

	ref_count_ptr<ScriptInformation> GetSelectedScript() { return infoSelected_; }

protected:
	virtual bool _IsValidScript(ref_count_ptr<ScriptInformation> info) { return NULL; }
	void _SearchScript(std::wstring dir);
	virtual void _Filter() {}
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	WListView listView_;
	WButton buttonOk_;
	WButton buttonCancel_;
	WComboBox combo_;

	std::vector<ref_count_ptr<ScriptInformation>> listInfo_;
	ref_count_ptr<ScriptInformation> infoSelected_;
};

/**********************************************************
//EnemySelectDialog
**********************************************************/
class EnemySelectDialog : public ScriptSelectDialog {
	enum {
		INDEX_ALL = 0,
		INDEX_SINGLE,
		INDEX_PLURAL,
		INDEX_STAGE,
		INDEX_PACKAGE,
	};

public:
	EnemySelectDialog();
	void Initialize();

private:
	virtual void _Filter();
	virtual bool _IsValidScript(ref_count_ptr<ScriptInformation> info);
};

/**********************************************************
//PlayerSelectDialog
**********************************************************/
class PlayerSelectDialog : public ScriptSelectDialog {
	enum {
		INDEX_PLAYER = 0,
	};

public:
	PlayerSelectDialog();
	void Initialize();

private:
	virtual void _Filter();
	virtual bool _IsValidScript(ref_count_ptr<ScriptInformation> info);
};

#endif
