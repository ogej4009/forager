#pragma once
#include <vector>
#include "GameDevice.h"

class GameRenderData;
class GameConstBuffer;
class GameShader
{
public:
	friend GameRenderData;

public:
	class CMemberData
	{
	public:
		GameString DataTypeName;
		size_t TypeSize;
	};

	class CStructData
	{
	public:
		GameString Name;
		size_t DataSize;
		std::vector<CMemberData> MemberData;
	};

public:
	enum SHADER_TYPE
	{
		ST_VS,
		ST_HS,
		// ST_TS,
		ST_DS,
		ST_GS,
		ST_PS,
		ST_MAX,
	};

protected:
	ID3DBlob* m_Blob;
	ID3DBlob* m_ErrBlob;
	unsigned int m_VH; // 쉐이더 버전용 5
	unsigned int m_VL;
	SHADER_TYPE m_Type;

public:
	SHADER_TYPE ShType()
	{
		return m_Type;
	}

public:
	void CShaderDataParsing(GameString& _Path);

public:
	void VerSetting(unsigned int _VH, unsigned int _VL)
	{
		m_VH = _VH;
		m_VL = _VL;
	}

public:
	virtual void Setting() = 0;

private:
	std::map<GameString, S_Ptr<GameConstBuffer>> m_CB;
	std::map<GameString, unsigned int> m_SMP;
	std::map<GameString, unsigned int> m_TEX;

public:
	template<typename T>
	void CB(const GameString& _Name, unsigned int _uiReg)
	{
		CB(_Name, _uiReg, sizeof(T), &typeid(T));
	}

	void CB(const GameString& _Name, unsigned int _uiReg, unsigned int _Size, const type_info* _Type);
	void TEX(const GameString& _Name, unsigned int _uiReg);
	void SMP(const GameString& _Name, unsigned int _uiReg);

protected:
	GameShader(SHADER_TYPE _Type);
	virtual ~GameShader();
};
