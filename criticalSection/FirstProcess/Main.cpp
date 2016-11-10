#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include"CriticalSection.h"

using namespace std;

void printLastError()
{
	cout << "Cannot create process" << endl << GetLastError() << endl;
	_getch();
}

int _tmain(int argc, _TCHAR* argv[])
{
	CriticalSection criticalSection;

	if (argc == 1)
	{
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		TCHAR zb[] = TEXT("second process");

		if (!CreateProcess(TEXT("FirstProcess.exe"), zb, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			printLastError();
			return 0;
		}

		for (int i = 0; i < 100; i++)
		{
			criticalSection.writeInSharedMemory(i);
			Sleep(1000);
		}
		_getch();
	}
	else
	{
		for (int i = 0; i < 100; i++)
		{
			criticalSection.readFromSharedMemory();
			Sleep(450);
		}
		_getch();
	}
	return 0;
}

