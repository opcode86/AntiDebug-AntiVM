#include <iostream>
#include <windows.h>
#include <winternl.h>

#include "PEB.h"

typedef struct _S_PEB
{
    BYTE pad1[2];
    BOOLEAN BeingDebugged;
    BYTE pad2[17];
    PPEB_LDR_DATA Ldr;
	BYTE pad3[156];
    ULONG NtGlobalFlag;
} S_PEB, * PS_PEB;

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
        PS_PEB Peb = NULL;

        if (Peb = (PS_PEB)ProcInfo.PebBaseAddress; Peb == NULL)
            return false;

        //Peb->CloudFileFlags could potentially indicate VM if zero??
        //Peb->PlaceholderCompatibilityMode could indicate VM if empty?? 

		if (Peb->BeingDebugged)
			return true;

        if (Peb->NtGlobalFlag != 0) //0x70 when debugger is attached it seems
            return true;
	}

	return false;
}