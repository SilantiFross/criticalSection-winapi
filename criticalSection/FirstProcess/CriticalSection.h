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
	HANDLE _mutex;
	HANDLE _hMap;
	int i;
	const int BUF_SIZE = 5;
};