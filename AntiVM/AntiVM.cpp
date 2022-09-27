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

	// NOTE:
	// This CAN be an indicator of a virtual environment since
	// the person setting up the VM might not care to configure
	// touch input. Some users might have this off by choice though
	// so one should not rely very heavily on this detection method.
	if (GetSystemMetrics(SM_MAXIMUMTOUCHES) == 0)
		printf("[VM] Potential VM detected (Touches)!\n");

	// NOTE:
	// This is NOT very accurate but can indicate usage of VM.
	// I would argue it's worth checking but nothing to rely on ...
	// ... needs more testing :>)
	if (TimeCheck())
		printf("[VM] Potential VM detected (Time Check)!\n");

	if (PowerCheck())
		printf("[VM] Potential VM detected (Power Check)!\n");
}