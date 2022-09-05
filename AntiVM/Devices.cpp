#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <vector>

#include "Devices.h"

std::vector<std::wstring> IllegalVendors = {
	L"VID_80EE", //VirtualBox
	L"PNP0F03"  //Unitek UPS Systems Alpha 1200Sx
};

bool CheckDevices() noexcept
{
	UINT devices = 0;
	PRAWINPUTDEVICELIST deviceList = NULL;

	while (true)
	{
		if (GetRawInputDeviceList(NULL, &devices, sizeof(RAWINPUTDEVICELIST)) != 0)
			break;

		if (devices == 0)
			break;

		deviceList = (RAWINPUTDEVICELIST*)malloc(sizeof(RAWINPUTDEVICELIST) * devices);

		if (deviceList == NULL)
			break;

		devices = GetRawInputDeviceList(deviceList, &devices, sizeof(RAWINPUTDEVICELIST));
		if (devices == (UINT)-1)
		{
			free(deviceList);
			continue;
		}
		break;
	}

	if (deviceList == NULL)
		goto END;

	for(int i = 0; i < devices; i ++)
	{
		UINT numChars = 0u;
		GetRawInputDeviceInfoW(deviceList[i].hDevice, RIDI_DEVICENAME, nullptr, &numChars);
		
		std::wstring test(numChars, 0);
		GetRawInputDeviceInfoW(deviceList[i].hDevice, RIDI_DEVICENAME, test.data(), &numChars);
		
		for (auto x : IllegalVendors)
		{
			if (test.find(x) != std::wstring::npos)
			{
				free(deviceList);
				return true;
			}
		}
	}

	END:
	free(deviceList);
	return false;
}