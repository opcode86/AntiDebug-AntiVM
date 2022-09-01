#include <iostream>
#include <Windows.h>

#include "AntiDebug.h"

void AntiDebug() noexcept
{
	printf("|---------ANTI DEBUG---------|\n\n");

	if (IsDebuggerPresent())
		printf("[DBG] Caught by IsDebuggerPresent!\n");

	if (CheckPEB())
		printf("[DBG] Caught by PEB check!\n");

	if (CheckRunningProcesses())
		printf("[DBG] Caught by illgal processes running!\n");

	if (CloseInvalidHandle())
		printf("[DBG] Caught by closing invalid handle!\n");

	if (CheckTime())
		printf("[DBG] Caught by invalid timings!\n");
}