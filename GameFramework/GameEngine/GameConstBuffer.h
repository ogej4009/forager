
#pragma once
#include "GameDeviceBuffer.h"
#include "GameShader.h"
#include <GameRTTI.h>
#include <vector>

class GameConstBuffer : public GameRes<GameConstBuffer>, public GameDeviceBuffer, public GameRTTI
{
private:
	bool m_bLink;
	GameShader::SHADER_TYPE m_SHADER;
	unsigned int m_uiReg; // 레지스터 번호
	void (GameConstBuffer::* m_UpdateFunc)();

public:
	unsigned int Slot()
	{
		return m_uiReg;
	}

public:
	bool Create(GameShader::SHADER_TYPE _SHADER, unsigned int _uiReg, unsigned int _Size);
	void SettingInit(GameShader::SHADER_TYPE _SHADER, unsigned int _uiReg);

	template<typename T>
	void SettingData(T& _Data)
	{
		SettingData((void*)&_Data, sizeof(T));
	}

	void SettingData(void* _Ptr, unsigned int _Size);

	void Setting();

private:
	void VSSetting();
	void HSSetting();
	void DSSetting();
	void GSSetting();
	void PSSetting();

public:
	GameConstBuffer();
	~GameConstBuffer();
};

