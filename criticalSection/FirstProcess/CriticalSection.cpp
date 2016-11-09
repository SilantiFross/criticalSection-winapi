#include "CriticalSection.h"

using namespace std;

CriticalSection::CriticalSection()
{
	i = 1;
	_hMap  = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 100, TEXT("filemapping"));
	HANDLE mutex = CreateMutex(NULL, FALSE, TEXT("Mutex"));
}

void CriticalSection::writeInSharedMemory()
{
	LPCTSTR pBuf;
	TCHAR szMsg[5];
	WaitForSingleObject(_mutex, INFINITE);
	wsprintf(szMsg, L"%d", i);
	pBuf = (LPTSTR)MapViewOfFile(_hMap, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
	CopyMemory((PVOID)pBuf, szMsg, (5 * sizeof(TCHAR)));
	wcout << L"First process write: " << i << endl;
	i++;
	ReleaseMutex(_mutex);
}

void CriticalSection::readFromSharedMemory()
{
	LPCTSTR pBuf;
	WaitForSingleObject(_mutex, INFINITE);
	pBuf = (LPTSTR)MapViewOfFile(_hMap, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
	wcout << L"Second process read: " << pBuf << endl;
	ReleaseMutex(_mutex);
	}