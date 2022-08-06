#ifndef __TOUHOUDANMAKUFU_VIEW_COMMON__
#define __TOUHOUDANMAKUFU_VIEW_COMMON__

#include "../Common/DnhCommon.hpp"
#include "GcLibImpl.hpp"

/**********************************************************
//SystemResidentTask
**********************************************************/
class SystemResidentTask : public TaskBase {
public:
	enum {
		TASK_PRI_RENDER_FPS = 9,
	};

public:
	SystemResidentTask();
	~SystemResidentTask();
	void RenderFps();

private:
	DxText textFps_;
};

#endif
