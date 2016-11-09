#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#pragma comment(lib, "user32.lib")

using namespace std;

#define BUF_SIZE 2048
TCHAR szName[] = TEXT("MyFileMappingObject");

void printLastError()
{
	_tprintf(TEXT("Received error %d"), GetLastError());
	_getch();
}

int _tmain()
{
	HANDLE hMapFile;
	LPCTSTR pBuf;

	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szName);

	if (hMapFile == NULL)
	{
		printLastError();
		return 1;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);

	if (pBuf == NULL)
	{
		printLastError();
		CloseHandle(hMapFile);
		return 1;
	}

	wcout << pBuf << endl;
		
	_getch();
	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

	return 0;
}
