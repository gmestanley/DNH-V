#ifndef __SFML_UTILITY__
#define __SFML_UTILITY__

#include "SfConstant.hpp"

namespace sfml {

	typedef struct ColorValue {
		float r;
		float g;
		float b;
		float a;
	};
	typedef struct Vector4f {
		float x;
		float y;
		float z;
		float w;
	};
	typedef unsigned long Color;
/**********************************************************
//ColorAccess
**********************************************************/
class ColorAccess {
public:
	enum {
		BIT_ALPHA = 24,
		BIT_RED = 16,
		BIT_GREEN = 8,
		BIT_BLUE = 0,
	};
	static int GetColorA(Color& color);
	static Color& SetColorA(Color& color, int alpha);
	static int GetColorR(Color color);
	static Color& SetColorR(Color& color, int red);
	static int GetColorG(Color& color);
	static Color& SetColorG(Color& color, int green);
	static int GetColorB(Color& color);
	static Color& SetColorB(Color& color, int blue);

	static ColorValue SetColor(ColorValue value, Color color);
	static D3DMATERIAL9 SetColor(D3DMATERIAL9 mat, Color color);
	static Color& ApplyAlpha(Color& color, double alpha);

	static Color& SetColorHSV(Color& color, int hue, int saturation, int value);
};

/**********************************************************
//衝突判定用図形
**********************************************************/
class DxCircle {
public:
	DxCircle()
	{
		x_ = 0;
		y_ = 0;
		r_ = 0;
	}
	DxCircle(double x, double y, double r)
	{
		x_ = x;
		y_ = y;
		r_ = r;
	}
	virtual ~DxCircle() {}
	double GetX() { return x_; }
	void SetX(float x) { x_ = x; }
	double GetY() { return y_; }
	void SetY(float y) { y_ = y; }
	double GetR() { return r_; }
	void SetR(float r) { r_ = r; }

private:
	double x_;
	double y_;
	double r_;
};

class DxWidthLine {
	//幅のある線分/A certain width line segment
public:
	DxWidthLine()
	{
		posX1_ = 0;
		posY1_ = 0;
		posX2_ = 0;
		posY2_ = 0;
		width_ = 0;
	}
	DxWidthLine(double x1, double y1, double x2, double y2, double width)
	{
		posX1_ = x1;
		posY1_ = y1;
		posX2_ = x2;
		posY2_ = y2;
		width_ = width;
	}
	virtual ~DxWidthLine() {}
	double GetX1() { return posX1_; }
	double GetY1() { return posY1_; }
	double GetX2() { return posX2_; }
	double GetY2() { return posY2_; }
	double GetWidth() { return width_; }

private:
	double posX1_;
	double posY1_;
	double posX2_;
	double posY2_;
	double width_;
};

class DxLine3D {
public:
	DxLine3D(){};
	DxLine3D(const sf::Vector3f& p1, const sf::Vector3f& p2)
	{
		vertex_[0] = p1;
		vertex_[1] = p2;
	}

	sf::Vector3f& GetPosition(int index) { return vertex_[index]; }
	sf::Vector3f& GetPosition1() { return vertex_[0]; }
	sf::Vector3f& GetPosition2() { return vertex_[1]; }

private:
	sf::Vector3f vertex_[2];
};

class DxTriangle {
public:
	DxTriangle() {}
	DxTriangle(const sf::Vector3f& p1, const sf::Vector3f& p2, const sf::Vector3f& p3)
	{
		vertex_[0] = p1;
		vertex_[1] = p2;
		vertex_[2] = p3;
		_Compute();
	}

	sf::Vector3f& GetPosition(int index) { return vertex_[index]; }
	sf::Vector3f& GetPosition1() { return vertex_[0]; }
	sf::Vector3f& GetPosition2() { return vertex_[1]; }
	sf::Vector3f& GetPosition3() { return vertex_[2]; }

private:
	sf::Vector3f vertex_[3];
	sf::Vector3f normal_;

	void _Compute()
	{
		sf::Vector3f lv[3];
		lv[0] = vertex_[1] - vertex_[0];
		lv[0] = *D3DXVec3Normalize(&sf::Vector3f(), &lv[0]);

		lv[1] = vertex_[2] - vertex_[1];
		lv[1] = *D3DXVec3Normalize(&sf::Vector3f(), &lv[1]);

		lv[2] = vertex_[0] - vertex_[2];
		lv[2] = *D3DXVec3Normalize(&sf::Vector3f(), &lv[2]);

		sf::Vector3f cross = *D3DXVec3Cross(&sf::Vector3f(), &lv[0], &lv[1]);
		normal_ = *D3DXVec3Normalize(&sf::Vector3f(), &cross);
	}
};

/**********************************************************
//DxMath
**********************************************************/
class DxMath {
public:
	static sf::Vector2f Normalize(const sf::Vector2f& v)
	{
		return *D3DXVec2Normalize(&sf::Vector2f(), &v);
	}
	static sf::Vector3f Normalize(const sf::Vector3f& v)
	{
		return *D3DXVec3Normalize(&sf::Vector3f(), &v);
	}
	static float DotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		return D3DXVec2Dot(&v1, &v2);
	}
	static float DotProduct(const sf::Vector3f& v1, const sf::Vector3f& v2)
	{
		return D3DXVec3Dot(&v1, &v2);
	}
	static float CrossProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		return D3DXVec2CCW(&v1, &v2);
	}
	static sf::Vector3f CrossProduct(const sf::Vector3f& v1, const sf::Vector3f& v2)
	{
		return *D3DXVec3Cross(&sf::Vector3f(), &v1, &v2);
	}

	//ベクトルと行列の積
	static Vector4f VectMatMulti(Vector4f v, D3DMATRIX& mat);

	//衝突判定：点－多角形
	static bool IsIntersected(sf::Vector2f& pos, std::vector<sf::Vector2f>& list);

	//衝突判定：円-円
	static bool IsIntersected(DxCircle& circle1, DxCircle& circle2);

	//衝突判定：円-直線
	static bool IsIntersected(DxCircle& circle, DxWidthLine& line);

	//衝突判定：直線-直線
	static bool IsIntersected(DxWidthLine& line1, DxWidthLine& line2);

	//衝突判定：直線：三角
	static bool IsIntersected(DxLine3D& line, std::vector<DxTriangle>& triangles, std::vector<sf::Vector3f>& out);
};

struct RECT_D {
	double left;
	double top;
	double right;
	double bottom;
};

inline RECT_D GetRectD(RECT& rect)
{
	RECT_D res = { (double)rect.left, (double)rect.top, (double)rect.right, (double)rect.bottom };
	return res;
}

inline void SetRectD(RECT_D* rect, double left, double top, double right, double bottom)
{
	rect->left = left;
	rect->top = top;
	rect->right = right;
	rect->bottom = bottom;
}

} // namespace directx

#endif
