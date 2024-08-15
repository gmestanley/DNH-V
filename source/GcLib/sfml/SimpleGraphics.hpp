#ifndef __SFML_SIMPLEGRAPHICS__
#define __SFML_SIMPLEGRAPHICS__

#include "SfConstant.hpp"

namespace sfml {

class DxCamera;
class DxCamera2D;
class Texture;
/**********************************************************
//SimpleGraphicsConfig
**********************************************************/
class SimpleGraphicsConfig {
public:
	enum {
		COLOR_MODE_16BIT,
		COLOR_MODE_32BIT,
	};

public:
	SimpleGraphicsConfig();
	virtual ~SimpleGraphicsConfig();
	bool IsShowWindow() { return bShowWindow_; }
	void SetShowWindow(bool b) { bShowWindow_ = b; }
	int GetScreenWidth() { return widthScreen_; }
	void SetScreenWidth(int width) { widthScreen_ = width; }
	int GetScreenHeight() { return heightScreen_; }
	void SetScreenHeight(int height) { heightScreen_ = height; }
	bool IsWindowed() { return bWindowed_; }
	void SetWindowd(bool bWindowed) { bWindowed_ = bWindowed; }
	bool IsReferenceEnable() { return bUseRef_; }
	void SetReferenceEnable(bool bEnable) { bUseRef_ = bEnable; }
	int GetColorMode() { return colorMode_; }
	void SetColorMode(int mode) { colorMode_ = mode; }
	bool IsTripleBufferEnable() { return bUseTripleBuffer_; }
	void SetTripleBufferEnable(bool bEnable) { bUseTripleBuffer_ = bEnable; }
	bool IsWaitTimerEnable() { return bUseWaitTimer_; }
	void SetWaitTimerEnable(bool bEnable) { bUseWaitTimer_ = bEnable; }
	bool IsPseudoFullScreen() { return bPseudoFullScreen_; }
	void SetbPseudoFullScreen(bool b) { bPseudoFullScreen_ = b; }

protected:
	bool bShowWindow_;
	int widthScreen_;
	int heightScreen_;
	bool bWindowed_;
	bool bUseRef_;
	int colorMode_;
	bool bUseTripleBuffer_;
	bool bUseWaitTimer_;
	bool bPseudoFullScreen_;
};

class SimpleGraphicsListener {
public:
	virtual ~SimpleGraphicsListener() {}
	virtual void ReleaseSimpleGraphics() {}
	virtual void RestoreSimpleGraphics() {}
	virtual void StartChangeScreenMode() { ReleaseSimpleGraphics(); }
	virtual void EndChangeScreenMode() { RestoreSimpleGraphics(); }
};

class SimpleGraphics {
	static SimpleGraphics* thisBase_;

public:
	enum {
		SCREENMODE_FULLSCREEN,
		SCREENMODE_WINDOW,
	};
	enum {
		MODE_BLEND_NONE, //なし/None
		MODE_BLEND_ALPHA, //αで半透明合成/Translucent Composition with alpha
		MODE_BLEND_ADD_RGB, //RGBで加算合成/Addition with RGB
		MODE_BLEND_ADD_ARGB, //αで加算合成/Addition with alpha
		MODE_BLEND_MULTIPLY, //乗算合成/Multiplication Composition
		MODE_BLEND_SUBTRACT, //減算合成/Subtraction Composition
		MODE_BLEND_SHADOW, //影描画用/For drawing shadows
		MODE_BLEND_INV_DESTRGB, //描画先色反転合成/Color Inversion Before Drawing Composition

		MODE_TEXTURE_FILTER_NONE, //フィルタなし/No filter
		MODE_TEXTURE_FILTER_POINT, //補間なし/No interpolation
		MODE_TEXTURE_FILTER_LINEAR, //線形補間/Linear Interpolation
	};

public:
	SimpleGraphics();
	virtual ~SimpleGraphics();
	static SimpleGraphics* GetBase() { return thisBase_; }
	HWND GetAttachedWindowHandle() { return hAttachedWindow_; }

	virtual bool Initialize(HWND hWnd);
	virtual bool Initialize(HWND hWnd, SimpleGraphicsConfig& config);
	void AddSimpleGraphicsListener(SimpleGraphicsListener* listener);
	void RemoveSimpleGraphicsListener(SimpleGraphicsListener* listener);
	int GetScreenMode() { return modeScreen_; }
	D3DPRESENT_PARAMETERS GetFullScreenPresentParameter() { return d3dppFull_; }
	D3DPRESENT_PARAMETERS GetWindowPresentParameter() { return d3dppWin_; }

	IDirect3DDevice9* GetDevice() { return pDevice_; }
	SimpleGraphicsConfig& GetConfigData() { return config_; }

	void BeginScene(bool bClear = true); //描画開始/Drawing Start
	void EndScene(); //描画終了/Drawing Termination
	void ClearRenderTarget();
	void ClearRenderTarget(RECT rect);
	void SetRenderTarget(gstd::ref_count_ptr<Texture> texture);
	gstd::ref_count_ptr<Texture> GetRenderTarget() { return textureTarget_; }

	//レンダリングステートラッパ/Rendering State Wrapper
	void SetLightingEnable(bool bEnable); //ライティング/Lighting
	void SetSpecularEnable(bool bEnable); //スペキュラ/Specular
	void SetCullingMode(DWORD mode); //カリング/Culling
	void SetShadingMode(DWORD mode); //シェーディング/Shading
	void SetZBufferEnable(bool bEnable); //Zバッファ参照/Z-Buffer Browsing
	void SetZWriteEnalbe(bool bEnable); //Zバッファ書き込み/Z-Buffer Loading
	void SetAlphaTest(bool bEnable, DWORD ref = 0, D3DCMPFUNC func = D3DCMP_GREATER);
	void SetBlendMode(DWORD mode, int stage = 0);
	void SetFillMode(DWORD mode);
	void SetFogEnable(bool bEnable);
	bool IsFogEnable();
	void SetVertexFog(bool bEnable, Color color, float start, float end);
	void SetPixelFog(bool bEnable, Color color, float start, float end);
	void SetTextureFilter(DWORD mode, int stage = 0);
	DWORD GetTextureFilter(int stage = 0);

	void SetDirectionalLight(D3DVECTOR& dir);

	void SetViewPort(int x, int y, int width, int height);
	void ResetViewPort();

	int GetScreenWidth();
	int GetScreenHeight();
	double GetScreenWidthRatio();
	double GetScreenHeightRatio();
	POINT GetMousePosition();
	gstd::ref_count_ptr<DxCamera> GetCamera() { return camera_; }
	gstd::ref_count_ptr<DxCamera2D> GetCamera2D() { return camera2D_; }

	void SaveBackSurfaceToFile(std::wstring path);
	bool IsPixelShaderSupported(int major, int minor);

	int GetSFMLRenderMethod() { return renderMode_; };
	void SetSFMLRenderMethod(int type) { renderMode_ = type; };

protected:
	IDirect3D9* pDirect3D_;
	IDirect3DDevice9* pDevice_;
	D3DPRESENT_PARAMETERS d3dppFull_;
	D3DPRESENT_PARAMETERS d3dppWin_;
	IDirect3DSurface9* pBackSurf_;
	IDirect3DSurface9* pZBuffer_;

	SimpleGraphicsConfig config_;
	HWND hAttachedWindow_;
	DWORD wndStyleFull_;
	DWORD wndStyleWin_;
	int modeScreen_;
	int renderMode_;
	std::list<SimpleGraphicsListener*> listListener_;

	gstd::ref_count_ptr<DxCamera> camera_;
	gstd::ref_count_ptr<DxCamera2D> camera2D_;
	gstd::ref_count_ptr<Texture> textureTarget_;

	void _ReleaseDxResource();
	void _RestoreDxResource();
	void _Restore();
	void _InitializeDeviceState();
};

/**********************************************************
//SimpleGraphicsPrimaryWindow
**********************************************************/
class SimpleGraphicsPrimaryWindow : public SimpleGraphics, public gstd::WindowBase {
public:
	SimpleGraphicsPrimaryWindow();
	~SimpleGraphicsPrimaryWindow();
	virtual bool Initialize();
	virtual bool Initialize(SimpleGraphicsConfig& config);
	void ChangeScreenMode();

protected:
	gstd::WindowBase wndGraphics_;
	virtual LRESULT _WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //オーバーライド用プロシージャ
	void _PauseDrawing();
	void _RestartDrawing();
};

/**********************************************************
//DxCamera
**********************************************************/
class DxCamera {
public:
	DxCamera();
	virtual ~DxCamera();
	void Reset();
	sf::Vector3f GetCameraPosition();
	sf::Vector3f GetFocusPosition() { return pos_; }
	void SetFocus(float x, float y, float z)
	{
		pos_.x = x;
		pos_.y = y;
		pos_.z = z;
	}
	void SetFocusX(float x) { pos_.x = x; }
	void SetFocusY(float y) { pos_.y = y; }
	void SetFocusZ(float z) { pos_.z = z; }
	float GetRadius() { return radius_; }
	void SetRadius(float r) { radius_ = r; }
	float GetAzimuthAngle() { return angleAzimuth_; }
	void SetAzimuthAngle(float angle) { angleAzimuth_ = angle; }
	float GetElevationAngle() { return angleElevation_; }
	void SetElevationAngle(float angle) { angleElevation_ = angle; }

	float GetYaw() { return yaw_; }
	void SetYaw(float yaw) { yaw_ = yaw; }
	float GetPitch() { return pitch_; }
	void SetPitch(float pitch) { pitch_ = pitch; }
	float GetRoll() { return roll_; }
	void SetRoll(float roll) { roll_ = roll; }

	double GetNearClip() { return clipNear_; }
	double GetFarClip() { return clipFar_; }

	D3DXMATRIX GetMatrixLookAtLH();
	void UpdateDeviceWorldViewMatrix();
	void SetProjectionMatrix(float width, float height, float posNear, float posFar);
	void UpdateDeviceProjectionMatrix();

	sf::Vector2f TransformCoordinateTo2D(sf::Vector3f pos);

private:
	sf::Vector3f pos_; //焦点/Focus
	float radius_;
	float angleAzimuth_;
	float angleElevation_;
	D3DXMATRIX matProjection_;

	float yaw_;
	float pitch_;
	float roll_;

	double clipNear_;
	double clipFar_;
};

/**********************************************************
//DxCamera2D
**********************************************************/
class DxCamera2D {
public:
	DxCamera2D();
	virtual ~DxCamera2D();

	bool IsEnable() { return bEnable_; }
	void SetEnable(bool bEnable) { bEnable_ = bEnable; }

	sf::Vector2f GetFocusPosition() { return pos_; }
	float GetFocusX() { return pos_.x; }
	float GetFocusY() { return pos_.y; }
	void SetFocus(float x, float y)
	{
		pos_.x = x;
		pos_.y = y;
	}
	void SetFocus(sf::Vector2f pos) { pos_ = pos; }
	void SetFocusX(float x) { pos_.x = x; }
	void SetFocusY(float y) { pos_.y = y; }
	double GetRatio() { return max(ratioX_, ratioY_); }
	void SetRatio(double ratio)
	{
		ratioX_ = ratio;
		ratioY_ = ratio;
	}
	double GetRatioX() { return ratioX_; }
	void SetRatioX(double ratio) { ratioX_ = ratio; }
	double GetRatioY() { return ratioY_; }
	void SetRatioY(double ratio) { ratioY_ = ratio; }
	double GetAngleZ() { return angleZ_; }
	void SetAngleZ(double angle) { angleZ_ = angle; }

	RECT GetClip() { return rcClip_; }
	void SetClip(RECT rect) { rcClip_ = rect; }

	void SetResetFocus(gstd::ref_count_ptr<sf::Vector2f> pos) { posReset_ = pos; }
	void Reset();
	inline sf::Vector2f GetLeftTopPosition();
	inline static sf::Vector2f GetLeftTopPosition(sf::Vector2f focus, double ratio);
	inline static sf::Vector2f GetLeftTopPosition(sf::Vector2f focus, double ratioX, double ratioY);
	inline static sf::Vector2f GetLeftTopPosition(sf::Vector2f focus, double ratioX, double ratioY, RECT rcClip);

	D3DXMATRIX GetMatrix();

private:
	bool bEnable_;
	sf::Vector2f pos_; //焦点/Focus
	double ratioX_; //拡大率/Magnification Rate
	double ratioY_;
	double angleZ_;
	RECT rcClip_; //視野/Field of View

	gstd::ref_count_ptr<sf::Vector2f> posReset_;
};

} // namespace directx

#endif