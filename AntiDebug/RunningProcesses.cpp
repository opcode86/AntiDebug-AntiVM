#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

#include "RunningProcesses.h"

std::vector<std::string> IllegalPrograms = {
	"ida",
	"x32dbg",
	"x64dbg",
	"ida64",
	"x86_64-SSE4-AVX2",
	"wireshark",
	"processhacker",
	"netstat",
	"netmon",
	"tcpview",
	"filemon",
	"regmon",
	"cain"
};

bool CheckRunningProcesses() noexcept
{
	HANDLE ProcSnap = NULL;

	if (ProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); ProcSnap == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 currProc32;

	currProc32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(ProcSnap, &currProc32))
		return false;

	while (Process32Next(ProcSnap, &currProc32))
		for (auto x : IllegalPrograms)
			if (strcmp((char*)currProc32.szExeFile, (x + ".exe").c_str()) == 0)
				return true;

	CloseHandle(ProcSnap);
	return false;
}