#include "stdio.h"
#include "AvProcess.h"
#include "AvBridge.h"

AvProcess::AvProcess(AvBridge* parent) {
	bridge = parent;
}

bool AvProcess::init(const char* command) {
	if (!initHandles()) { return false; }
	if (!CreateChildProcess(command)) { return false; }
	return true;
}

bool AvProcess::initHandles() {
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0)) {
		die("StdoutRd CreatePipe failed."); return false;
	}
	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) {
		die("Stdout SetHandleInformation failed."); return false;
	}
	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0)) {
		die("Stdin CreatePipe failed"); return false;
	}
	if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0)) {
		die("Stdin SetHandleInformation failed."); return false;
	}
	return true;
}

bool AvProcess::CreateChildProcess(const char* command) {
	TCHAR szCmdline[1024];
	sprintf(szCmdline, "%s", command);
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;

	// Set up members of the PROCESS_INFORMATION structure. 
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	// Set up members of the STARTUPINFO structure. 
	// This structure specifies the STDIN and STDOUT handles for redirection.
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = g_hChildStd_OUT_Wr;
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	// Create the child process. 
	bSuccess = CreateProcess(NULL, szCmdline, NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo);

	if (!bSuccess) {
		die("CreateProcess failed."); return false;
	}

	// Close handles to the child process and its primary thread.
	// Some applications might keep these handles to monitor the status
	// of the child process, for example. 
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);
	return true;
}

void AvProcess::die(const char* error) {
	bridge->die(error);
}