#pragma once
#include <Windows.h>
#include <iostream>

class CriticalSection
{
public:
	CriticalSection();
	void writeInSharedMemory(int);
	void readFromSharedMemory();
private:
	void projectionFileInSharedMemory();
	HANDLE _mutex;
	HANDLE _hMap;
	LPCTSTR _pBuf;
	const int BUF_SIZE = 5;
};