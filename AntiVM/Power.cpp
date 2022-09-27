#include <windows.h>
#include <winternl.h>
#include <iostream>

#include "Power.h"

using f_NtPowerInformation = NTSTATUS(__stdcall*)(
	_In_    POWER_INFORMATION_LEVEL InformationLevel,
	_In_	PVOID                   InputBuffer OPTIONAL,
	_In_    ULONG                   InputBufferLength,
	_Out_	PVOID                   OutputBuffer OPTIONAL,
	_In_	ULONG                   OutputBufferLength
	);

bool PowerCheck() noexcept
{
	
	f_NtPowerInformation NtPowerInformation = (f_NtPowerInformation)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtPowerInformation");
	if (NtPowerInformation == NULL)
		return false;
	
	SYSTEM_POWER_CAPABILITIES state = {};

	if(!NT_SUCCESS(NtPowerInformation(SystemPowerCapabilities, NULL, 0, &state, sizeof(SYSTEM_POWER_CAPABILITIES))))
		return false;

	// NOTE:
	// Hybrid Sleep State (FastSystemS4) is on by default ON desktop whilst OFF by default on laptops
	// ... however, my VM's seem to have it OFF by default. Can check and compare with if 
	// SystemBatteriesPresent is TRUE and LidPresent

	bool isLaptop = false;
	if (state.SystemBatteriesPresent || state.LidPresent)
		isLaptop = true;

	if ((isLaptop && state.FastSystemS4) || (!isLaptop && !state.FastSystemS4))
		return true;


	// NOTE:
	// *MAYBE* if all but SystemS1 and SystemS1 are true then probably real, if all false then VM. (Not counting 5)
	if (!state.SystemS1 && !state.SystemS2 && !!state.SystemS3 && !state.SystemS4 && state.SystemS5)
		return true;

	// NOTE:
	// If HiberState or HiberFilePresent is false might be VM.
	if (!state.Hiberboot || !state.HiberFilePresent)
		return true;

	// NOTE:
	// If RtcWake is 5 it seems to be legit system, if 0 maybe virtual environment...
	if (state.RtcWake == 0)
		return true;

	return false;
}