#include "AntiDebug/AntiDebug.h"
#include "AntiVM/AntiVM.h"

#pragma comment(lib, "mpr.lib")

int main()
{
	printf("\n\n\n");
	printf("	            @@@@@@@@@@@\n");
	printf("                @@@@@@@@@@@@@@@@@@@\n");
	printf("             @@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("          @@@@@@@@@@@@@@  @@@@@@@@@@@@@@\n");
	printf("          @@@@@@@@@@@        @@@@@@@@@\n");
	printf("          @@@@@@@\n");
	printf("          @@@@@@@\n");
	printf("          @@@@@@@\n");
	printf("          @@@@@@@\n");
	printf("          @@@@@@@\n");
	printf("          @@@@@@@@@@@        @@@@@@@@@\n");
	printf("          @@@@@@@@@@@@@@  @@@@@@@@@@@@@@\n");
	printf("             @@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("                @@@@@@@@@@@@@@@@@@@\n");
	printf("                    @@@@@@@@@@@\n\n\n\n\n");

	AntiDebug();
	AntiVM();

	Sleep(5000);

	return 0;
}