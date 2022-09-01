#include <windows.h>
#include <winternl.h>

#include "PEB.h"

using f_NtQueryInformationProcess = NTSTATUS(__stdcall*)(
	_In_ HANDLE,
	_In_  unsigned int,
	_Out_ PVOID,
	_In_ ULONG,
	_Out_ PULONG
	);


bool CheckPEB() noexcept
{
	PROCESS_BASIC_INFORMATION ProcInfo = { 0 };
	ULONG length = 0;

	f_NtQueryInformationProcess NtQueryInformationProcess = (f_NtQueryInformationProcess)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess");

	if (NtQueryInformationProcess == NULL)
		return false;

	if (NT_SUCCESS(NtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &ProcInfo, sizeof(ProcInfo), &length)))
	{
		PPEB Peb = NULL;

		if (Peb = ProcInfo.PebBaseAddress; Peb == NULL)
			return false;

		if (!Peb->BeingDebugged)
			return false;
	}

	return true;
}