#pragma once
#include <GameRes.h>
#include <vector>

class GameShader;
class GameVtxShader;
class GamePixShader;
class GameRender;
class GameBlend;
class GameRasterizer;
class GameDepthstencil;

class GameMaterial : public GameRes<GameMaterial>
{
private:
	bool m_IsClone;

	S_Ptr<GameVtxShader>		m_VTXShader;
	S_Ptr<GamePixShader>		m_PIXShader;
	S_Ptr<GameBlend>			m_BLEND;
	S_Ptr<GameRasterizer>		m_RASTERIZER;
	S_Ptr<GameDepthstencil>		m_DEPTHSTENCIL;
	std::vector<GameShader*>	m_SHADER;

	static GameShader* LastShader[5];
	static GameBlend* LastBLEND;
	static GameRasterizer* LastRASTERIZER;
	static GameDepthstencil* LastDEPTHSTENCIL;

public:
	bool IsClone()
	{
		return m_IsClone;
	}

public:
	GameShader* Shader(size_t _Index)
	{
		return m_SHADER[_Index];
	}

	GameVtxShader* VTXShader()
	{
		return m_VTXShader;
	}

	GamePixShader* PIXShader()
	{
		return m_PIXShader;
	}


public:
	void VTXShader(const GameString& _Name);
	void PIXShader(const GameString& _Name);
	void BLEND(const GameString& _Name);
	void RASTERIZER(const GameString& _Name);
	void DEPTHSTENCIL(const GameString& _Name);


public:
	static S_Ptr<GameMaterial> Create(const GameString& _Name)
	{
		GameMaterial* NewRes = CreateRes(_Name);
		NewRes->Create();
		return NewRes;
	}

public:
	S_Ptr<GameMaterial> Clone();

public:
	bool Create();
	void Setting();

public:
	GameMaterial();
	GameMaterial(const GameMaterial& _Other);
	~GameMaterial();
};

