#ifndef __TOUHOUDANMAKUFU_LIN_GCLIBIMPL__
#define __TOUHOUDANMAKUFU_LIN_GCLIBIMPL__

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
//ESimpleGraphics
**********************************************************/
class ESimpleGraphics : public Singleton<ESimpleGraphics>, public SimpleGraphicsPrimaryWindow {
	friend Singleton<ESimpleGraphics>;

private:
	ESimpleGraphics();

protected:
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	~ESimpleGraphics();
	virtual bool Initialize();
	void SetRenderStateFor2D(int blend);
};

#endif
