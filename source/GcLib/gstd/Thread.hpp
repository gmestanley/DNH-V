#ifndef __GSTD_THREAD__
#define __GSTD_THREAD__

#include "GstdConstant.hpp"

namespace gstd {

//================================================================
//Thread
class Thread {
public:
	enum Status {
		RUN,
		STOP,
		REQUEST_STOP,
	};

public:
	Thread();
	virtual ~Thread();
	virtual void Start();
	virtual void Stop();
	bool IsStop();
	DWORD Join(int mills = INFINITE);

	Status GetStatus() { return status_; }

protected:
	volatile HANDLE hThread_;
	unsigned int idThread_;
	volatile Status status_;
	virtual void _Run() = 0;

private:
	static unsigned int __stdcall _StaticRun(LPVOID data);
};

//================================================================
//CriticalSection
class CriticalSection {
public:
	CriticalSection();
	~CriticalSection();
	void Enter();
	void Leave();

private:
	CRITICAL_SECTION cs_;
	volatile DWORD idThread_;
	volatile int countLock_;
};

//================================================================
//Lock
class Lock {
public:
	Lock(CriticalSection& cs)
	{
		cs_ = &cs;
		cs_->Enter();
	}
	virtual ~Lock() { cs_->Leave(); }

protected:
	CriticalSection* cs_;
};

//================================================================
//ThreadSignal
class ThreadSignal {
public:
	ThreadSignal(bool bManualReset = false);
	virtual ~ThreadSignal();
	DWORD Wait(int mills = INFINITE);
	void SetSignal(bool bOn = true);

private:
	HANDLE hEvent_;
};

} // namespace gstd

#endif
