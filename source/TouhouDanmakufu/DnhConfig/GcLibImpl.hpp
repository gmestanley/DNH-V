#ifndef __TOUHOUDANMAKUFU_CONFIG_GCLIBIMPL__
#define __TOUHOUDANMAKUFU_CONFIG_GCLIBIMPL__

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

#endif
