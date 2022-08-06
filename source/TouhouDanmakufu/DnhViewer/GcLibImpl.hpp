#ifndef __TOUHOUDANMAKUFU_EXE_GCLIBIMPL__
#define __TOUHOUDANMAKUFU_EXE_GCLIBIMPL__

#include "../Common/DnhGcLibImpl.hpp"
#include "Constant.hpp"

/**********************************************************
//EApplication
**********************************************************/
class EApplication : public Singleton<EApplication>, public Application {
	friend Singleton<EApplication>;

private:
	EApplication();

protected:
	bool _Initialize();
	bool _Loop();
	bool _Finalize();

public:
	~EApplication();
};

/**********************************************************
//EDirectGraphics
**********************************************************/
class EDirectGraphics : public Singleton<EDirectGraphics>, public DirectGraphics {
	friend Singleton<EDirectGraphics>;

private:
	EDirectGraphics();

public:
	~EDirectGraphics();
	virtual bool Initialize();
	void SetRenderStateFor2D(int blend);
};

#endif
