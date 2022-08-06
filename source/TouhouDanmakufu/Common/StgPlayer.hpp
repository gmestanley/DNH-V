#ifndef __TOUHOUDANMAKUFU_DNHSTG_PLAYER__
#define __TOUHOUDANMAKUFU_DNHSTG_PLAYER__

#include "StgCommon.hpp"
#include "StgIntersection.hpp"
#include "StgStageScript.hpp"

class StgPlayerObject;
class StgPlayerInformation;
class StgPlayerSpellManageObject;
class StgPlayerSpellObject;
/**********************************************************
//StgPlayerObject
**********************************************************/
class StgPlayerInformation {
	friend StgPlayerObject;

public:
	StgPlayerInformation() {}
	virtual ~StgPlayerInformation() {}

	double GetLife() { return life_; }
	void SetLife(double life) { life_ = life; }
	double GetSpell() { return countBomb_; }
	void SetSpell(double spell) { countBomb_ = spell; }
	double GetPower() { return power_; }
	void SetPower(double power) { power_ = power; }

	int GetRebirthFrame() { return frameRebirth_; }
	void SetRebirthFrame(int frame) { frameRebirth_ = frame; }

private:
	double life_;
	double countBomb_;
	double power_;
	int frameRebirth_; //くらいボム有効フレーム
};

class StgPlayerObject : public DxScriptSpriteObject2D, public StgMoveObject, public StgIntersectionObject {
public:
	enum {
		STATE_NORMAL,
		STATE_HIT,
		STATE_DOWN,
		STATE_END,

		REBIRTH_DEFAULT = -99999,
	};

public:
	StgPlayerObject(StgStageController* stageController);
	virtual ~StgPlayerObject();
	void Clear() { ClearIntersectionRelativeTarget(); }
	void SetScript(StgStagePlayerScript* script) { script_ = script; }

	virtual void Work();
	void Move();
	virtual void Intersect(ref_count_ptr<StgIntersectionTarget>::unsync ownTarget, ref_count_ptr<StgIntersectionTarget>::unsync otherTarget);
	void CallSpell();

	virtual void SetX(double x)
	{
		posX_ = x;
		DxScriptRenderObject::SetX(x);
	}
	virtual void SetY(double y)
	{
		posY_ = y;
		DxScriptRenderObject::SetY(y);
	}

	ref_count_ptr<StgPlayerInformation> GetPlayerInformation() { return infoPlayer_; }
	void SetPlayerInforamtion(ref_count_ptr<StgPlayerInformation> info) { infoPlayer_ = info; }
	ref_count_ptr<StgPlayerSpellManageObject>::unsync GetSpellManageObject() { return objSpell_; }

	StgStagePlayerScript* GetPlayerScript() { return script_; }
	ref_count_ptr<StgPlayerObject>::unsync GetOwnObject();
	double GetX() { return posX_; }
	double GetY() { return posY_; }
	double GetFastSpeed() { return speedFast_; }
	void SetFastSpeed(double speed) { speedFast_ = speed; }
	double GetSlowSpeed() { return speedSlow_; }
	void SetSlowSpeed(double speed) { speedSlow_ = speed; }

	RECT GetClip() { return rcClip_; }
	void SetClip(RECT rect) { rcClip_ = rect; }

	int GetState() { return state_; }
	int GetDownStateFrame() { return frameStateDown_; }
	void SetDownStateFrame(int frame) { frameStateDown_ = frame; }
	int GetRebirthFrame() { return infoPlayer_->GetRebirthFrame(); }
	void SetRebirthFrameMax(int frame) { frameRebirthMax_ = frame; }
	void SetRebirthFrame(int frame) { infoPlayer_->SetRebirthFrame(frame); }
	void SetRebirthLossFrame(int frame) { frameRebirthDiff_ = frame; }
	double GetItemIntersectionRadius() { return itemCircle_; }
	void SetItemIntersectionRadius(double r) { itemCircle_ = r; }
	double GetLife() { return infoPlayer_->GetLife(); }
	void SetLife(double life) { infoPlayer_->SetLife(life); }
	double GetSpell() { return infoPlayer_->GetSpell(); }
	void SetSpell(double spell) { infoPlayer_->SetSpell(spell); }
	double GetPower() { return infoPlayer_->GetPower(); }
	void SetPower(double power) { infoPlayer_->SetPower(power); }
	int GetInvincibilityFrame() { return frameInvincibility_; }
	void SetInvincibilityFrame(int frame) { frameInvincibility_ = frame; }
	int GetAutoItemCollectY() { return yAutoItemCollect_; }
	void SetAutoItemCollectY(int y) { yAutoItemCollect_ = y; }

	void SetRebirthPosition(double x, double y) { rebirthX_ = x; rebirthY_ = y; }

	bool IsPermitShot();
	void SetForbidShot(bool bForbid) { bForbidShot_ = bForbid; }
	bool IsPermitSpell();
	void SetForbidSpell(bool bForbid) { bForbidSpell_ = bForbid; }
	bool IsWaitLastSpell();

	void SetEnableStateEnd(bool bEnable) { enableStateEnd_ = bEnable; }
	void SetEnableShootdownEvent(bool bEnable) { enableShootdownEvent_ = bEnable; }

protected:
	void _InitializeRebirth();
	void _Move();
	void _AddIntersection();
	bool _IsValidSpell();

	StgStageController* stageController_;
	StgStagePlayerScript* script_;
	ref_count_ptr<StgPlayerInformation> infoPlayer_;
	ref_count_ptr<StgPlayerSpellManageObject>::unsync objSpell_;

	double speedFast_;
	double speedSlow_;
	RECT rcClip_;

	int state_;
	int frameState_; //各ステートで使用されるフレーム
	int frameRebirthMax_; //くらいボム有効フレーム初期値
	int frameRebirthDiff_; //くらいボム減少量
	int frameStateDown_;

	std::vector<ref_count_weak_ptr<StgIntersectionObject>::unsync> listGrazedShot_;
	int hitObjectID_;

	double itemCircle_;
	int frameInvincibility_;
	bool bForbidShot_;
	bool bForbidSpell_;
	int yAutoItemCollect_;

	bool enableStateEnd_;
	bool enableShootdownEvent_;

	double rebirthX_;
	double rebirthY_;
};

class StgIntersectionTarget_Player : public StgIntersectionTarget_Circle {
public:
	StgIntersectionTarget_Player(bool bGraze)
	{
		typeTarget_ = TYPE_PLAYER;
		bGraze_ = bGraze;
	}
	bool IsGraze() { return bGraze_; }

private:
	bool bGraze_;
};

/**********************************************************
//StgPlayerSpellManageObject
**********************************************************/
class StgPlayerSpellManageObject : public DxScriptObjectBase {
public:
	StgPlayerSpellManageObject() { bVisible_ = false; }
	virtual void Render() {}
	virtual void SetRenderState() {}
};

/**********************************************************
//StgPlayerSpellObject
**********************************************************/
class StgPlayerSpellObject : public DxScriptPrimitiveObject2D, public StgIntersectionObject {
public:
	enum {
		TO_TYPE_IMMEDIATE,
		TO_TYPE_FADE,
		TO_TYPE_ITEM,
	};
	StgPlayerSpellObject(StgStageController* stageController);
	virtual void Work();
	virtual void Intersect(ref_count_ptr<StgIntersectionTarget>::unsync ownTarget, ref_count_ptr<StgIntersectionTarget>::unsync otherTarget);

	double GetDamage() { return damage_; }
	void SetDamage(double damage) { damage_ = damage; }
	bool IsEraseShot() { return bEraseShot_; }
	int ShotDeleteTo() { return bEraseShotTypeTo_; }
	void SetEraseShot(bool b) { bEraseShot_ = b; }
	void SetEraseShotTypeTo(int bEraseType) { bEraseShotTypeTo_ = bEraseType; }
	double GetLife() { return life_; }
	void SetLife(double life) { life_ = life; }

protected:
	StgStageController* stageController_;
	double damage_;
	bool bEraseShot_;
	int bEraseShotTypeTo_; //Bullet deletion type
	double life_; //貫通力
};

#endif
