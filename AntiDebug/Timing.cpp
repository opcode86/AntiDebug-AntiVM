#include <Windows.h>
#include <winternl.h>

#include "Timing.h"

using f_NtDelayExecution = NTSTATUS(__stdcall*) (
	IN BOOLEAN				Alertable,
	IN PLARGE_INTEGER       DelayInterval
	);


bool CheckTime() noexcept
{
	f_NtDelayExecution NtDelayExecution = (f_NtDelayExecution)(GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtDelayExecution"));
	if (NtDelayExecution == NULL)
		return false;

	DWORD before = GetTickCount64();
	LARGE_INTEGER time;
	time.QuadPart = -100000000;

	NtDelayExecution(false, &time);

	DWORD after = GetTickCount64();

	if (after - before < 10)
		return true;

	return false;
}