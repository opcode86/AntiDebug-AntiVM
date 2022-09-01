#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include "DLLCheck.h"

std::vector<std::string> IllegalDlls = {
	"SbieDll",
	"SxIn",
	"Sd2",
	"snxhk",
	"cmdvrt32",
	"VBoxDispD3D",
	"VBoxGL",
	"VBoxHook",
	"VBoxICD",
	"VBoxMRXNP",
	"VBoxNine",
	"VBoxSVGA",
	"VBoxTray"
};

bool CheckDlls() noexcept
{
	std::string path = "C:\\Windows\\System32\\";

	for (auto& x : std::filesystem::directory_iterator(path))
	{
		if (!x.exists() || x.is_directory())
			continue;

		for (auto& y : IllegalDlls)
		{
			if (y == x.path().string().substr(path.length()))
				return true;
		}
	}

	return false;
}