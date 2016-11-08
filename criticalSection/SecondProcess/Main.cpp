#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#pragma comment(lib, "user32.lib")

using namespace std;

#define BUF_SIZE 2048
TCHAR szName[] = TEXT("MyFileMappingObject");

int _tmain()
{
	HANDLE hMapFile;
	LPCTSTR pBuf;

	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szName);

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not open file mapping object (%d).\n"), GetLastError());
		return 1;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}

	wcout << pBuf << endl;
		
	_getch();
	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

	return 0;
}
