#include "Drivers.h"

std::vector<std::string> IllegalDrivers = {
	"VBoxSF",
	"VBoxGuest",
	"VBoxMouse",
	"VBoxWddm"
};

bool DriverCheck() noexcept
{
	LPVOID drivers[1024];
	DWORD cb;

	if (EnumDeviceDrivers(drivers, sizeof(drivers), &cb) && cb < sizeof(drivers))
	{
		int count = cb / sizeof(drivers[0]);
		TCHAR buffer[1024];

		for (auto& i : drivers)
		{
			if (GetDeviceDriverBaseName(i, buffer, sizeof(buffer)))
				for (auto x : IllegalDrivers)
					if ((char*)buffer == x + ".sys")
						return true;
		}
	}

	return false;
}