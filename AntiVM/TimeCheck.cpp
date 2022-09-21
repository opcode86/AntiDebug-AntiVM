#include <windows.h>
#include <winternl.h>
#include <iostream>

#include "TimeCheck.h"

using f_NtQuerySystemInformation = NTSTATUS(__stdcall*)(
	_In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Out_ PVOID	SystemInformation,
	_In_ ULONG SystemInformationLength,
	_Out_ PULONG ReturnLength OPTIONAL
	);

bool TimeCheck() noexcept
{
    bool detected = false;
    BYTE* outputBuffer = NULL;
    ULONG length = 0;

	f_NtQuerySystemInformation NtQuerySystemInformation = (f_NtQuerySystemInformation)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQuerySystemInformation");

    if (NtQuerySystemInformation == NULL)
        return detected;

    if (NtQuerySystemInformation(SystemProcessorPerformanceInformation, outputBuffer, length, &length) == ((NTSTATUS)0xC0000004))
    {
        //std::cout << outputBuffer->NumberOfThreads << "\n";
        outputBuffer = (BYTE*)LocalAlloc(LMEM_FIXED, length);
    }
    
    if (NtQuerySystemInformation(SystemProcessorPerformanceInformation, outputBuffer, length, &length))
    {
        printf("Failed!\n");
        return detected;
    }

    if (outputBuffer != NULL)
    {
        auto info = (SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION*)outputBuffer;

        __int64 threshold = 10; //Needs more testing, this should be changed
        if (info->KernelTime.QuadPart / info->UserTime.QuadPart > threshold)
            detected = true;
    }

    LocalFree(outputBuffer);

    return detected;
}