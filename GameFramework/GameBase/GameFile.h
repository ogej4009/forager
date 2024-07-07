#pragma once
#include <iostream>
#include <assert.h>
#include "GamePath.h"

class GameFile : public GamePath
{
private:
	std::wstring m_OpenMode;
	FILE* m_pFile;

public:
	template<typename T>
	void Write(const T& _Data)
	{
		if (false == IsOpen())
		{
			assert(false);
		}

		if (false == IsWrite())
		{
			assert(false);
		}

		fwrite(&_Data, sizeof(T), 1, m_pFile);
	}

	template<>
	void Write(const GameString& _Data)
	{
		if (false == IsOpen())
		{
			assert(false);
		}

		if (false == IsWrite())
		{
			assert(false);
		}

		int Size = (int)_Data.Size();
		fwrite(&Size, sizeof(int), 1, m_pFile);
		fwrite(_Data.StrPtr(), sizeof(wchar_t) * Size, 1, m_pFile);
	}

	void Read(void* _Buffer, size_t _BufferSize)
	{
		if (false == IsOpen())
		{
			assert(false);
		}

		if (false == IsRead())
		{
			assert(false);
		}

		fread_s(_Buffer, _BufferSize, _BufferSize, 1, m_pFile);
	}

	template<typename T>
	void Read(T& _Data)
	{
		if (false == IsOpen())
		{
			assert(false);
		}

		if (false == IsRead())
		{
			assert(false);
		}

		fread_s(&_Data, sizeof(T), sizeof(T), 1, m_pFile);
	}

	template<>
	void Read(GameString& _Data)
	{
		if (false == IsOpen())
		{
			assert(false);
		}

		if (false == IsRead())
		{
			assert(false);
		}

		int Size;
		fread_s(&Size, sizeof(int), sizeof(int), 1, m_pFile);

		// 받은 버퍼를 동적으로 만든다.
		wchar_t* Arr = new wchar_t[Size + 1] { 0, };
		fread_s(Arr, sizeof(wchar_t) * Size, sizeof(wchar_t) * Size, 1, m_pFile);
		_Data = Arr;

		if (nullptr != Arr)
		{
			delete[] Arr;
			Arr = nullptr;
		}
	}

public:
	bool IsOpen()
	{
		return nullptr != m_pFile;
	}

	bool IsWrite()
	{
		if (false == IsOpen())
		{
			return false;
		}

		if ((size_t)-1 == m_OpenMode.find_first_of(L'w'))
		{
			return false;
		}

		return true;
	}

	bool IsRead()
	{
		if (false == IsOpen())
		{
			return false;
		}

		if ((size_t)-1 == m_OpenMode.find_first_of(L'r'))
		{
			return false;
		}

		return true;
	}

	bool IsExist()
	{
		return GamePath::IsExist(m_Path);
	}

private:
	void Copy(const GameFile& _Other);

public:
	GameFile& operator=(const GameFile& _Other)
	{
		Close();
		Copy(_Other);
	}

public:
	void PathSetting(const GameString& _Path);
	bool Open(const wchar_t* _Path, const wchar_t* _Mode);
	bool Open();
	void Close();

public:
	GameFile();
	GameFile(const GameFile& _Other);
	GameFile(const wchar_t* _Path, const wchar_t* _Mode);
	~GameFile();
};


