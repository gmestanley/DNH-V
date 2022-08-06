#ifndef __GSTD_TASK__
#define __GSTD_TASK__

#include "GstdConstant.hpp"
#include "GstdUtility.hpp"
#include "Logger.hpp"

namespace gstd {

class TaskBase;
class TaskFunction;
class TaskManager;

enum {
	TASK_FREE_ID = 0xffffffff,
	TASK_GROUP_FREE_ID = 0xffffffff,
};
/**********************************************************
//TaskFunction
**********************************************************/
class TaskFunction : public IStringInfo {
	friend TaskManager;

protected:
	ref_count_ptr<TaskBase> task_; //タスクへのポインタ
	int id_; //id
	bool bEnable_;
	int delay_;

public:
	TaskFunction()
	{
		task_ = NULL;
		id_ = TASK_FREE_ID;
		bEnable_ = true;
		delay_ = 0;
	}
	virtual ~TaskFunction() {}
	virtual void Call() = 0;

	ref_count_ptr<TaskBase> GetTask() { return task_; }
	int GetID() { return id_; }
	bool IsEnable() { return bEnable_; }

	int GetDelay() { return delay_; }
	void SetDelay(int delay) { delay_ = delay; }
	bool IsDelay() { return delay_ > 0; }

	virtual std::wstring GetInfoAsString();
};

template <class T>
class TTaskFunction : public TaskFunction {
public:
	typedef void (T::*Function)();

public:
	TTaskFunction(ref_count_ptr<T> task, Function func)
	{
		task_ = task;
		pFunc = func;
	}
	virtual void Call()
	{
		if (task_ != NULL)
			((T*)task_.GetPointer()->*pFunc)();
	}

	static ref_count_ptr<TaskFunction> Create(ref_count_ptr<TaskBase> task, Function func)
	{
		ref_count_ptr<T> dTask = ref_count_ptr<T>::DownCast(task);
		return TTaskFunction<T>::Create(dTask, func);
	}
	static ref_count_ptr<TaskFunction> Create(ref_count_ptr<T> task, Function func)
	{
		return new TTaskFunction<T>(task, func);
	}

protected:
	Function pFunc; //メンバ関数ポインタ
};

/**********************************************************
//TaskBase
**********************************************************/
class TaskBase : public IStringInfo {
	friend TaskManager;

public:
	TaskBase();
	virtual ~TaskBase();
	int GetTaskID() { return idTask_; }
	_int64 GetTaskIndex() { return indexTask_; }

protected:
	_int64 indexTask_; //TaskManagerによってつけられる一意のインデックス
	int idTask_; //ID
	int idTaskGroup_; //グループID
};

/**********************************************************
//TaskManager
**********************************************************/
class TaskInfoPanel;
class TaskManager : public TaskBase {
	friend TaskInfoPanel;

public:
	typedef std::map<int, std::vector<std::list<ref_count_ptr<TaskFunction>>>> function_map;

public:
	TaskManager();
	virtual ~TaskManager();
	void Clear(); //全タスク削除
	void ClearTask();
	void AddTask(ref_count_ptr<TaskBase> task); //タスクを追加
	ref_count_ptr<TaskBase> GetTask(int idTask); //指定したIDのタスクを取得
	ref_count_ptr<TaskBase> GetTask(const std::type_info& info);
	void RemoveTask(TaskBase* task); //指定したタスクを削除
	void RemoveTask(int idTask); //タスク元IDで削除
	void RemoveTaskGroup(int idGroup); //タスクをグループで削除
	void RemoveTask(const std::type_info& info); //クラス型で削除
	void RemoveTaskWithoutTypeInfo(std::set<const std::type_info*> listInfo); //クラス型以外のタスクを削除
	std::list<ref_count_ptr<TaskBase>> GetTaskList() { return listTask_; }

	void InitializeFunctionDivision(int divFunc, int maxPri);
	void CallFunction(int divFunc); //タスク機能実行
	void AddFunction(int divFunc, ref_count_ptr<TaskFunction> func, int pri, int idFunc = TASK_FREE_ID); //タスク機能追加
	void RemoveFunction(TaskBase* task); //タスク機能削除
	void RemoveFunction(TaskBase* task, int divFunc, int idFunc); //タスク機能削除
	void RemoveFunction(const std::type_info& info); //タスク機能削除
	function_map GetFunctionMap() { return mapFunc_; }

	void SetFunctionEnable(bool bEnable); //全タスク機能の状態を切り替える
	void SetFunctionEnable(bool bEnable, int divFunc); //タスク機能の状態を切り替える
	void SetFunctionEnable(bool bEnable, int idTask, int divFunc); //タスク機能の状態を切り替える
	void SetFunctionEnable(bool bEnable, int idTask, int divFunc, int idFunc); //タスク機能の状態を切り替える
	void SetFunctionEnable(bool bEnable, TaskBase* task, int divFunc); //タスク機能の状態を切り替える
	void SetFunctionEnable(bool bEnable, TaskBase* task, int divFunc, int idFunc); //タスク機能の状態を切り替える
	void SetFunctionEnable(bool bEnable, const std::type_info& info, int divFunc); //タスク機能の状態を切り替える

	void SetInfoPanel(ref_count_ptr<TaskInfoPanel> panel) { panelInfo_ = panel; }
	gstd::CriticalSection& GetStaticLock() { return lockStatic_; }

protected:
	static gstd::CriticalSection lockStatic_;
	std::list<ref_count_ptr<TaskBase>> listTask_; //タスクの元クラス
	function_map mapFunc_; //タスク機能のリスト(divFunc, priority, func)
	_int64 indexTaskManager_; //一意のインデックス
	ref_count_ptr<TaskInfoPanel> panelInfo_;

	void _ArrangeTask(); //必要のなくなった領域削除
	void _CheckInvalidFunctionDivision(int divFunc);
};

/**********************************************************
//TaskInfoPanel
**********************************************************/
class TaskInfoPanel : public WindowLogger::Panel {
public:
	TaskInfoPanel();
	void SetUpdateInterval(int time) { timeUpdateInterval_ = time; }
	virtual void LocateParts();
	virtual void Update(TaskManager* taskManager);

protected:
	enum {
		ROW_FUNC_ADDRESS = 0,
		ROW_FUNC_CLASS,
		ROW_FUNC_ID,
		ROW_FUNC_DIVISION,
		ROW_FUNC_PRIORITY,
		ROW_FUNC_ENABLE,
		ROW_FUNC_INFO,
	};
	WSplitter wndSplitter_;
	WTreeView wndTreeView_;
	WListView wndListView_;
	int timeLastUpdate_;
	int timeUpdateInterval_;
	int addressLastFindManager_;

	virtual bool _AddedLogger(HWND hTab);
	void _UpdateTreeView(TaskManager* taskManager, ref_count_ptr<WTreeView::Item> item);
	void _UpdateListView(TaskManager* taskManager);
};

/**********************************************************
//WorkRenderTaskManager
//動作、描画機能を保持するTaskManager
**********************************************************/
class WorkRenderTaskManager : public TaskManager {
public:
	WorkRenderTaskManager();
	~WorkRenderTaskManager();
	virtual void InitializeFunctionDivision(int maxPriWork, int maxPriRender);

	//動作機能
	void CallWorkFunction();
	void AddWorkFunction(ref_count_ptr<TaskFunction> func, int pri, int idFunc = TASK_FREE_ID);
	void RemoveWorkFunction(TaskBase* task, int idFunc);
	void SetWorkFunctionEnable(bool bEnable);
	void SetWorkFunctionEnable(bool bEnable, int idTask);
	void SetWorkFunctionEnable(bool bEnable, int idTask, int idFunc);
	void SetWorkFunctionEnable(bool bEnable, TaskBase* task);
	void SetWorkFunctionEnable(bool bEnable, TaskBase* task, int idFunc);
	void SetWorkFunctionEnable(bool bEnable, const std::type_info& info);

	//描画機能
	void CallRenderFunction();
	void AddRenderFunction(ref_count_ptr<TaskFunction> func, int pri, int idFunc = TASK_FREE_ID);
	void RemoveRenderFunction(TaskBase* task, int idFunc);
	void SetRenderFunctionEnable(bool bEnable);
	void SetRenderFunctionEnable(bool bEnable, int idTask);
	void SetRenderFunctionEnable(bool bEnable, int idTask, int idFunc);
	void SetRenderFunctionEnable(bool bEnable, TaskBase* task);
	void SetRenderFunctionEnable(bool bEnable, TaskBase* task, int idFunc);
	void SetRenderFunctionEnable(bool bEnable, const std::type_info& info);

private:
	enum {
		DIV_FUNC_WORK, //動作
		DIV_FUNC_RENDER, //描画
	};
};

} // namespace gstd

#endif
