#include <windows.h>
#include "InvalidHandle.h"

bool CloseInvalidHandle() noexcept
{
	HANDLE h = (HANDLE)0xDEADBEEF;

	__try {
		CloseHandle(h);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return true;
	}

	return false;
}