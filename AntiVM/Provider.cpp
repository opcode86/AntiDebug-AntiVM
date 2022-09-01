#include "Provider.h"

std::vector<std::string> IllegalProviders = {
	"VirtualBox Shared Folders"
};

bool ProviderCheck(LPNETRESOURCEA lpnr) noexcept
{
	DWORD result, localResult, entries = -1, buffer = 16384;
	HANDLE resourceHandle;
	LPNETRESOURCEA lpnrLocal;


	result = WNetOpenEnumA(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, lpnr, &resourceHandle);

	if (result != NO_ERROR)
		return false;


	lpnrLocal = (LPNETRESOURCEA)GlobalAlloc(GPTR, buffer);

	if (lpnrLocal == NULL)
		return false;

	do {
		ZeroMemory(lpnrLocal, buffer);

		localResult = WNetEnumResourceA(resourceHandle, &entries, lpnrLocal, &buffer);

		if (localResult == NO_ERROR)
		{
			for (DWORD i = 0; i < entries; i++)
			{
				for (auto x : IllegalProviders)
				{
					if (x == lpnrLocal[i].lpProvider)
						return true;
				}

				if (RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER) && entries > 0)
				{
					ProviderCheck(&lpnrLocal[i]);
				}
			}
		}
		else if (localResult != ERROR_NO_MORE_ITEMS)
			break;

	} while (localResult != ERROR_NO_MORE_ITEMS);

	GlobalFree((HGLOBAL)lpnrLocal);
	WNetCloseEnum(resourceHandle);

	return false;
}