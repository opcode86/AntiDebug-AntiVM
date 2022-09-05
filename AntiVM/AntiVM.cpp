#include "AntiVM.h"
#include <iostream>

void AntiVM() noexcept
{
	LPNETRESOURCEA lpnr = NULL;

	printf("|-----------ANTI VM----------|\n\n");

	if (CheckDevices())
		printf("[VM] Caught by illegal Device Vendor IDs!\n");

	if (DriverCheck())
		printf("[VM] Caught by illegal drivers!\n");

	if (CheckScreenSize())
		printf("[VM] Caught by odd screen size!\n");

	if (ProviderCheck(lpnr))
		printf("[VM] Caught by illegal provider!\n");

	if (CheckDlls())
		printf("[VM] Caught by illegal DLL's!\n");
}