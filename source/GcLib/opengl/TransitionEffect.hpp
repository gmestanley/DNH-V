#ifndef __DIRECTX_TRANSITIONEFFECT__
#define __DIRECTX_TRANSITIONEFFECT__

#include "RenderObject.hpp"

namespace directx {

/**********************************************************
//TransitionEffect
**********************************************************/
class TransitionEffect {
public:
	TransitionEffect();
	virtual ~TransitionEffect();
	virtual void Work() = 0;
	virtual void Render() = 0;
	virtual bool IsEnd() { return true; }

protected:
};

/**********************************************************
	//TransitionEffect_FadeOut
	**********************************************************/
class TransitionEffect_FadeOut : public TransitionEffect {
public:
	virtual void Work();
	virtual void Render();
	virtual bool IsEnd();
	void Initialize(int frame, gstd::ref_count_ptr<Texture> texture);

protected:
	double diffAlpha_;
	double alpha_;
	gstd::ref_count_ptr<Sprite2D> sprite_;
};

/**********************************************************
//TransitionEffectTask
**********************************************************/
class TransitionEffectTask : public gstd::TaskBase {

public:
	TransitionEffectTask();
	~TransitionEffectTask();

	void SetTransition(gstd::ref_count_ptr<TransitionEffect> effect);
	virtual void Work();
	virtual void Render();

protected:
	gstd::ref_count_ptr<TransitionEffect> effect_;
};

} // namespace directx

#endif
