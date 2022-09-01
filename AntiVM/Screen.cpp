#include "Screen.h"

std::vector<int> CommonHeights = {
	1080,
	768,
	900,
	864,
	768
};

std::vector<int> CommonWidths = {
	1920,
	1366,
	1440,
	1536,
	1024
};

bool CheckScreenSize() noexcept
{
	if (GetSystemMetrics(SM_CMONITORS) != 1)
		return false;

	bool found = false;

	int h = GetSystemMetrics(SM_CYVIRTUALSCREEN),
		w = GetSystemMetrics(SM_CXVIRTUALSCREEN);

	for (auto i : CommonHeights)
	{
		if (i == h)
		{
			for (auto j : CommonWidths)
			{
				if (j == w)
				{
					found = true;
					break;
				}
			}
			break;
		}
	}
	
	return !found;
}