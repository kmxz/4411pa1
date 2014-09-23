#ifndef AVPROCESS_H
#define AVPROCESS_H

#include <windows.h> 

class AvProcess {
	friend class AvBridge;
private:
	AvProcess(AvBridge* parent);
	HANDLE g_hChildStd_IN_Rd = NULL;
	HANDLE g_hChildStd_IN_Wr = NULL;
	HANDLE g_hChildStd_OUT_Rd = NULL;
	HANDLE g_hChildStd_OUT_Wr = NULL;
	bool CreateChildProcess(const char* command);
	bool init(const char* command);
	bool initHandles();
	void die(const char* error);
	AvBridge* bridge;
};

#endif