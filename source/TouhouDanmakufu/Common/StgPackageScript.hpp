#ifndef __TOUHOUDANMAKUFU_DNHSTG_PACKAGESCRIPT__
#define __TOUHOUDANMAKUFU_DNHSTG_PACKAGESCRIPT__

#include "StgCommon.hpp"
#include "StgControlScript.hpp"
#include "StgStageController.hpp"

/**********************************************************
//StgPackageScriptManager
**********************************************************/
class StgPackageScript;
class StgPackageScriptManager : public StgControlScriptManager {
public:
	StgPackageScriptManager(StgSystemController* controller);
	virtual ~StgPackageScriptManager();
	virtual void Work();
	virtual void Render();
	virtual ref_count_ptr<ManagedScript> Create(int type);

	ref_count_ptr<DxScriptObjectManager> GetObjectManager() { return objectManager_; }

protected:
	StgSystemController* systemController_;
	ref_count_ptr<DxScriptObjectManager> objectManager_;
};

/**********************************************************
//StgPackageScript
**********************************************************/
class StgPackageScript : public StgControlScript {
public:
	enum {
		TYPE_PACKAGE_MAIN,

		STAGE_STATE_FINISHED,
	};

public:
	StgPackageScript(StgPackageController* packageController);

	//パッケージ共通関数：パッケージ操作
	static gstd::value Func_ClosePackage(gstd::script_machine* machine, int argc, gstd::value const* argv);

	//パッケージ共通関数：ステージ操作
	static gstd::value Func_InitializeStageScene(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_FinalizeStageScene(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_StartStageScene(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_SetStageIndex(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_SetStageMainScript(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_SetStagePlayerScript(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_SetStageReplayFile(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_GetStageSceneState(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_GetStageSceneResult(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_PauseStageScene(gstd::script_machine* machine, int argc, gstd::value const* argv);
	static gstd::value Func_TerminateStageScene(gstd::script_machine* machine, int argc, gstd::value const* argv);

private:
	void _CheckNextStageExists();
	StgPackageController* packageController_;
};

#endif
