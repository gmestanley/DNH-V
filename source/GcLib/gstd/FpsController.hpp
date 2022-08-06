#ifndef __GSTD_FPSCONTROLLER__
#define __GSTD_FPSCONTROLLER__

#include "GstdConstant.hpp"
#include "SmartPointer.hpp"

namespace gstd {

class FpsControlObject;
/**********************************************************
//FpsController
**********************************************************/
class FpsController {
public:
	enum {
		FPS_FAST_MODE = 1200,
	};

public:
	FpsController();
	virtual ~FpsController();
	virtual void SetFps(int fps) { fps_ = fps; }
	virtual int GetFps() { return fps_; }
	virtual void SetTimerEnable(bool b) { bUseTimer_ = b; }

	virtual void Wait() = 0;
	virtual bool IsSkip() { return false; }
	virtual void SetCriticalFrame() { bCriticalFrame_ = true; }
	virtual float GetCurrentFps() = 0;
	virtual float GetCurrentWorkFps() { return GetCurrentFps(); }
	virtual float GetCurrentRenderFps() { return GetCurrentFps(); }
	bool IsFastMode() { return bFastMode_; }
	void SetFastMode(bool b) { bFastMode_ = b; }

	void AddFpsControlObject(ref_count_weak_ptr<FpsControlObject> obj);
	void RemoveFpsControlObject(ref_count_weak_ptr<FpsControlObject> obj);
	int GetControlObjectFps();

protected:
	int fps_; //設定されているFPS
	bool bUseTimer_; //タイマー制御
	bool bCriticalFrame_;
	bool bFastMode_;

	std::list<ref_count_weak_ptr<FpsControlObject>> listFpsControlObject_;

	inline int _GetTime();
	inline void _Sleep(int msec);
};

/**********************************************************
//StaticFpsController
**********************************************************/
class StaticFpsController : public FpsController {
public:
	StaticFpsController();
	~StaticFpsController();

	virtual void Wait();
	virtual bool IsSkip();
	virtual void SetCriticalFrame()
	{
		bCriticalFrame_ = true;
		timeError_ = 0;
		countSkip_ = 0;
	}

	void SetSkipRate(int value);
	virtual float GetCurrentFps();
	virtual float GetCurrentWorkFps();
	virtual float GetCurrentRenderFps();

protected:
	float fpsCurrent_; //現在のFPS
	int timePrevious_; //前回Waitしたときの時間
	int timeError_; //持ち越し時間(誤差)
	int timeCurrentFpsUpdate_; //1秒を測定するための時間保持
	int rateSkip_; //描画スキップ数
	int countSkip_; //描画スキップカウント
	std::list<int> listFps_; //1秒ごとに現在fpsを計算するためにfpsを保持

private:
	enum {
		FAST_MODE_SKIP_RATE = 10,
	};
};

/**********************************************************
//AutoSkipFpsController
**********************************************************/
class AutoSkipFpsController : public FpsController {
public:
	AutoSkipFpsController();
	~AutoSkipFpsController();

	virtual void Wait();
	virtual bool IsSkip();
	virtual void SetCriticalFrame()
	{
		bCriticalFrame_ = true;
		timeError_ = 0;
		countSkip_ = 0;
	}

	virtual float GetCurrentFps() { return GetCurrentWorkFps(); }
	float GetCurrentWorkFps() { return fpsCurrentWork_; };
	float GetCurrentRenderFps() { return fpsCurrentRender_; };

protected:
	float fpsCurrentWork_; //実際のfps
	float fpsCurrentRender_; //実際のfps
	int timePrevious_; //前回Waitしたときの時間
	int timePreviousWork_;
	int timePreviousRender_;
	int timeError_; //持ち越し時間(誤差)
	int timeCurrentFpsUpdate_; //1秒を測定するための時間保持
	std::list<int> listFpsWork_;
	std::list<int> listFpsRender_;
	double countSkip_; //連続描画スキップ数
	int countSkipMax_; //最大連続描画スキップ数
};

/**********************************************************
//FpsControlObject
**********************************************************/
class FpsControlObject {
public:
	FpsControlObject() {}
	virtual ~FpsControlObject() {}
	virtual int GetFps() = 0;
};

} // namespace gstd

#endif
