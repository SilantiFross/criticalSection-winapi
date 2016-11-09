#include "CriticalSection.h"

using namespace std;

CriticalSection::CriticalSection()
{
	_hMap  = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 100, TEXT("filemapping"));
	_mutex = CreateMutex(NULL, FALSE, TEXT("Mutex"));
}

void CriticalSection::writeInSharedMemory(int writeNumber)
{
	
	TCHAR szMsg[5];
	WaitForSingleObject(_mutex, INFINITE);
	wsprintf(szMsg, L"%d", writeNumber);
	projectionFileInSharedMemory();
	CopyMemory((PVOID)_pBuf, szMsg, (5 * sizeof(TCHAR)));
	wcout << L"First process write: " << writeNumber << endl;
	ReleaseMutex(_mutex);
}

void CriticalSection::readFromSharedMemory()
{
	WaitForSingleObject(_mutex, INFINITE);
	projectionFileInSharedMemory();
	wcout << L"Second process read: " << _pBuf << endl;
	ReleaseMutex(_mutex);
}

void CriticalSection::projectionFileInSharedMemory()
{
	_pBuf = (LPTSTR)MapViewOfFile(_hMap, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
}
