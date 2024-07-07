#pragma once
#include "GameMacro.h"
#include "GameTFunc.h"

class GameRef
{
public:
	template<typename T>
	friend class S_Ptr;

private:
	bool m_bDebug;
	int m_RefCount;

public:
	void DebugOn()
	{
		m_bDebug = true;
	}

	void DebugOff()
	{
		m_bDebug = false;
	}

	void DebugCheck()
	{
		if (false == m_bDebug)
		{
			return;
		}
	}

private:
	void PlusRef();
	void MinusRef();

public:
	GameRef();
	virtual ~GameRef();
};

template<typename T>
// typedef GameRef T;
class S_Ptr
{
private:
	T* m_Ptr;

public:
	template<typename ConvertPtr>
	S_Ptr<ConvertPtr> DynamicConvert()
	{
		ConvertPtr* Ptr = dynamic_cast<ConvertPtr*>(m_Ptr);
		return Ptr;
	}

	template<typename T>
	operator T* ()
	{
		return m_Ptr;
	}

	template<typename T>
	operator S_Ptr<T>()
	{
		return dynamic_cast<T*>(m_Ptr);
	}

	T* operator->()
	{
		return m_Ptr;
	}

	bool Equal(const T* _Other) const
	{
		return _Other != m_Ptr;
	}

	bool operator!=(const nullptr_t& _Other) const
	{
		return _Other != m_Ptr;
	}

	bool operator==(const nullptr_t& _Other) const
	{
		return _Other == m_Ptr;
	}

	S_Ptr& operator=(const S_Ptr& _Other)
	{
		if (nullptr == m_Ptr)
		{
			m_Ptr = _Other.m_Ptr;
			m_Ptr->PlusRef();
			return *this;
		}

		if (m_Ptr == _Other.m_Ptr)
		{
			return *this;
		}

		m_Ptr->MinusRef();
		m_Ptr = _Other.m_Ptr;
		m_Ptr->PlusRef();

		return *this;
	}

public:
	S_Ptr() : m_Ptr(nullptr)
	{
	}

	S_Ptr(const S_Ptr& _PTR) : m_Ptr(_PTR.m_Ptr)
	{
		if (nullptr == m_Ptr)
		{
			return;
		}

		this->m_Ptr->PlusRef();
	}

	S_Ptr(T* _PTR) : m_Ptr(_PTR)
	{
		if (nullptr == m_Ptr)
		{
			return;
		}

		m_Ptr->PlusRef();
	}

	~S_Ptr()
	{
		if (nullptr == m_Ptr)
		{
			return;
		}

		m_Ptr->MinusRef();
	}
};

template<typename T>
bool operator!=(const nullptr_t& _Left, const S_Ptr<T>& _Right)
{
	return _Right.operator!=(_Left);
}

template<typename T>
bool operator==(const nullptr_t& _Left, const S_Ptr<T>& _Right)
{
	return _Right.operator==(_Left);
}