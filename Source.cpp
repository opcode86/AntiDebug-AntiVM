#include "AntiDebug/AntiDebug.h"
#include "AntiVM/AntiVM.h"

#pragma comment(lib, "mpr.lib")

int main()
{
	AntiDebug();
	AntiVM();
	getchar();

	return 0;
}