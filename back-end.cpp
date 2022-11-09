#include <Windows.h>
#include <iostream>
#include "RAM.h"

void DisplayVolumePaths(
    __in PWCHAR VolumeName
)
{
    DWORD  CharCount = MAX_PATH + 1;
    PWCHAR Names = NULL;
    PWCHAR NameIdx = NULL;
    BOOL   Success = FALSE;

    for (;;)
    {
        //
        //  Allocate a buffer to hold the paths.
        Names = (PWCHAR) new BYTE[CharCount * sizeof(WCHAR)];

        if (!Names)
        {
            //
            //  If memory can't be allocated, return.
            return;
        }

        //
        //  Obtain all of the paths
        //  for this volume.
        Success = GetVolumePathNamesForVolumeNameW(
            VolumeName, Names, CharCount, &CharCount
        );

        if (Success)
        {
            break;
        }

        if (GetLastError() != ERROR_MORE_DATA)
        {
            break;
        }

        //
        //  Try again with the
        //  new suggested size.
        delete[] Names;
        Names = NULL;
    }

    if (Success)
    {
        //
        //  Display the various paths.
        for (NameIdx = Names;
            NameIdx[0] != L'\0';
            NameIdx += wcslen(NameIdx) + 1)
        {
            std::cout << (L"  %s", NameIdx) << std::endl;
        }
        std::cout << (L"\n") << std::endl;
    }

    if (Names != NULL)
    {
        delete[] Names;
        Names = NULL;
    }

    return;
}


int main()
{
	HANDLE handle = INVALID_HANDLE_VALUE;
	WCHAR VolumeName[MAX_PATH] = L"";
	
	handle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

	if (handle == INVALID_HANDLE_VALUE) {
		std::cout << "Error: " << GetLastError() << std::endl;
	}
	else {
        DisplayVolumePaths(VolumeName);
	}







	RAM ram = RAM();

	for (int x = 0; x < 20; x++) {
		std::cout << "####################################################" << std::endl;
		std::cout << "\n";
		std::cout << "Load: " << ram.load() << "% || Size: " << ram.size() << "Kb || used memory: " << ram.freeSize() << "Kb" << std::endl;
		std::cout << "\n";
		Sleep(2000);
	}
	ram.~RAM();
}