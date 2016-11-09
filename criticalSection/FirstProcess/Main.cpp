#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include"CriticalSection.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CriticalSection criticalSection;

	if (argc == 1)
	{
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		TCHAR zb[] = TEXT("second process");
		BOOL isProcessCreated;
		isProcessCreated = CreateProcess(TEXT("FirstProcess.exe"), zb, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		if (!isProcessCreated)
		{
			cout << "Cannot create process" << endl << GetLastError() << endl;
			_getch();
			return 0;
		}

		for (int i = 0; i < 100; i++)
		{
			criticalSection.writeInSharedMemory(i);
			Sleep(1000);
		}
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
	}
	else
	{
		for (int i = 0; i < 100; i++)
		{
			Sleep(900);
			criticalSection.readFromSharedMemory();
		}
		_getch();
	}
	return 0;
}

