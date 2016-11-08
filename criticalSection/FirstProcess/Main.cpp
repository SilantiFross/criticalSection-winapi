#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 2048
TCHAR szName[] = TEXT("MyFileMappingObject");
TCHAR szMsg[] = TEXT("Test message");

int _tmain()
{
	HANDLE hMapFile;
	HANDLE hTextFile;
	TCHAR fileName[20] = TEXT(".\\file.cr");
	LPCTSTR pBuf;

	hTextFile = CreateFile(fileName, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hMapFile = CreateFileMapping(hTextFile, NULL, PAGE_READWRITE, 0, BUF_SIZE, szName);

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
		return 1;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}

	CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	_getch();

	UnmapViewOfFile(pBuf);

	CloseHandle(hTextFile);
	CloseHandle(hMapFile);

	return 0;
}