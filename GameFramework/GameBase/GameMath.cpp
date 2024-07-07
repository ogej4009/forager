#include "GameMath.h"
#include "GameTime.h"

UINT CVector::SX = 4;
UINT CVector::SY = 1;

const CVector CVector::ZERO = { 0.0f, 0.0f , 0.0f, 0.0f };
const CVector CVector::ONE =	{ 1.0f, 1.0f , 1.0f, 1.0f };
const CVector CVector::RED =	{ 1.0f, 0.0f , 0.0f, 1.0f };
const CVector CVector::WHITE = { 1.0f, 1.0f , 1.0f, 1.0f };
const CVector CVector::LEFT =	{ -1.0f, 0.0f , 0.0f, 0.0f };
const CVector CVector::RIGHT = { 1.0f, 0.0f , 0.0f, 0.0f };
const CVector CVector::UP =	{ 0.0f, 1.0f , 0.0f, 0.0f };
const CVector CVector::DOWN = { 0.0f, -1.0f , 0.0f, 0.0f };
const CVector CVector::FORWARD = { 0.0f, 0.0f , 1.0f, 0.0f };
const CVector CVector::BACK = { 0.0f, 0.0f , -1.0f, 0.0f };

UINT CMatrix::SX = 4;
UINT CMatrix::SY = 4;

const float GameMath::PI = 3.14159265359f;
const float GameMath::PI_2 = GameMath::PI * 2.0F;
const float GameMath::DTOR = GameMath::PI / 180.0f;
const float GameMath::RTOD = 180.0f / GameMath::PI;

GameMath::GameMath() {}
GameMath::~GameMath() {}

unsigned int GameMath::FormatByteSize(DXGI_FORMAT _Fmt)
{
	switch (_Fmt)
	{
	case DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT:
		return 16;
	case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT:
		return 4;
	default:
		CodeEmbeddedErrorDetection;
		break;
	}
	CodeEmbeddedErrorDetection;
	return 0;
}



// 벡터    행렬
// 4   1   4  4     4   4
// AX, AY  BX BY == AX, BY
CVector CVector::operator*(const CMatrix& _MAT)
{
	CVector Return = *this;

	Return.Arr[0] = (Arr[0] * _MAT.Arr2D[0][0]) + (Arr[1] * _MAT.Arr2D[1][0]) + (Arr[2] * _MAT.Arr2D[2][0]) + (Arr[3] * _MAT.Arr2D[3][0]);
	Return.Arr[1] = (Arr[0] * _MAT.Arr2D[0][1]) + (Arr[1] * _MAT.Arr2D[1][1]) + (Arr[2] * _MAT.Arr2D[2][1]) + (Arr[3] * _MAT.Arr2D[3][1]);
	Return.Arr[2] = (Arr[0] * _MAT.Arr2D[0][2]) + (Arr[1] * _MAT.Arr2D[1][2]) + (Arr[2] * _MAT.Arr2D[2][2]) + (Arr[3] * _MAT.Arr2D[3][2]);
	Return.Arr[3] = (Arr[0] * _MAT.Arr2D[0][3]) + (Arr[1] * _MAT.Arr2D[1][3]) + (Arr[2] * _MAT.Arr2D[2][3]) + (Arr[3] * _MAT.Arr2D[3][3]);

	return Return;

	// for문으로 바꿔와라.
}

CVector CVector::TransCoord(const CMatrix& _MAT)
{
	CVector Return = *this;
	Return.w = 1.0f;
	Return = Return * _MAT;
	return Return;
}

CVector CVector::TransNormal(const CMatrix& _MAT)
{
	CVector Return = *this;
	Return.w = 0.0f;
	Return = Return * _MAT;
	return Return;
}

CMatrix CMatrix::operator*(const CMatrix& _MAT)
{
	CMatrix ReturnMat = *this;
	ReturnMat.IDEN();

	ReturnMat.XMMAT = DirectX::XMMatrixMultiply(XMMAT, _MAT.XMMAT);

	/*
		ReturnMat.Arr2D[0][0] = (Arr2D[0][0] * _MAT.Arr2D[0][0]) + (Arr2D[0][1] * _MAT.Arr2D[1][0]) + (Arr2D[0][2] * _MAT.Arr2D[2][0]) + (Arr2D[0][3] * _MAT.Arr2D[3][0]);
		ReturnMat.Arr2D[0][1] = (Arr2D[0][0] * _MAT.Arr2D[0][1]) + (Arr2D[0][1] * _MAT.Arr2D[1][1]) + (Arr2D[0][2] * _MAT.Arr2D[2][1]) + (Arr2D[0][3] * _MAT.Arr2D[3][1]);
		ReturnMat.Arr2D[0][2] = (Arr2D[0][0] * _MAT.Arr2D[0][2]) + (Arr2D[0][1] * _MAT.Arr2D[1][2]) + (Arr2D[0][2] * _MAT.Arr2D[2][2]) + (Arr2D[0][3] * _MAT.Arr2D[3][2]);
		ReturnMat.Arr2D[0][3] = (Arr2D[0][0] * _MAT.Arr2D[0][3]) + (Arr2D[0][1] * _MAT.Arr2D[1][3]) + (Arr2D[0][2] * _MAT.Arr2D[2][3]) + (Arr2D[0][3] * _MAT.Arr2D[3][3]);

		ReturnMat.Arr2D[1][0] = (Arr2D[1][0] * _MAT.Arr2D[0][0]) + (Arr2D[1][1] * _MAT.Arr2D[1][0]) + (Arr2D[1][2] * _MAT.Arr2D[2][0]) + (Arr2D[1][3] * _MAT.Arr2D[3][0]);
		ReturnMat.Arr2D[1][1] = (Arr2D[1][0] * _MAT.Arr2D[0][1]) + (Arr2D[1][1] * _MAT.Arr2D[1][1]) + (Arr2D[1][2] * _MAT.Arr2D[2][1]) + (Arr2D[1][3] * _MAT.Arr2D[3][1]);
		ReturnMat.Arr2D[1][2] = (Arr2D[1][0] * _MAT.Arr2D[0][2]) + (Arr2D[1][1] * _MAT.Arr2D[1][2]) + (Arr2D[1][2] * _MAT.Arr2D[2][2]) + (Arr2D[1][3] * _MAT.Arr2D[3][2]);
		ReturnMat.Arr2D[1][3] = (Arr2D[1][0] * _MAT.Arr2D[0][3]) + (Arr2D[1][1] * _MAT.Arr2D[1][3]) + (Arr2D[1][2] * _MAT.Arr2D[2][3]) + (Arr2D[1][3] * _MAT.Arr2D[3][3]);

		ReturnMat.Arr2D[2][0] = (Arr2D[2][0] * _MAT.Arr2D[0][0]) + (Arr2D[2][1] * _MAT.Arr2D[1][0]) + (Arr2D[2][2] * _MAT.Arr2D[2][0]) + (Arr2D[2][3] * _MAT.Arr2D[3][0]);
		ReturnMat.Arr2D[2][1] = (Arr2D[2][0] * _MAT.Arr2D[0][1]) + (Arr2D[2][1] * _MAT.Arr2D[1][1]) + (Arr2D[2][2] * _MAT.Arr2D[2][1]) + (Arr2D[2][3] * _MAT.Arr2D[3][1]);
		ReturnMat.Arr2D[2][2] = (Arr2D[2][0] * _MAT.Arr2D[0][2]) + (Arr2D[2][1] * _MAT.Arr2D[1][2]) + (Arr2D[2][2] * _MAT.Arr2D[2][2]) + (Arr2D[2][3] * _MAT.Arr2D[3][2]);
		ReturnMat.Arr2D[2][3] = (Arr2D[2][0] * _MAT.Arr2D[0][3]) + (Arr2D[2][1] * _MAT.Arr2D[1][3]) + (Arr2D[2][2] * _MAT.Arr2D[2][3]) + (Arr2D[2][3] * _MAT.Arr2D[3][3]);

		ReturnMat.Arr2D[3][0] = (Arr2D[3][0] * _MAT.Arr2D[0][0]) + (Arr2D[3][1] * _MAT.Arr2D[1][0]) + (Arr2D[3][2] * _MAT.Arr2D[2][0]) + (Arr2D[3][3] * _MAT.Arr2D[3][0]);
		ReturnMat.Arr2D[3][1] = (Arr2D[3][0] * _MAT.Arr2D[0][1]) + (Arr2D[3][1] * _MAT.Arr2D[1][1]) + (Arr2D[3][2] * _MAT.Arr2D[2][1]) + (Arr2D[3][3] * _MAT.Arr2D[3][1]);
		ReturnMat.Arr2D[3][2] = (Arr2D[3][0] * _MAT.Arr2D[0][2]) + (Arr2D[3][1] * _MAT.Arr2D[1][2]) + (Arr2D[3][2] * _MAT.Arr2D[2][2]) + (Arr2D[3][3] * _MAT.Arr2D[3][2]);
		ReturnMat.Arr2D[3][3] = (Arr2D[3][0] * _MAT.Arr2D[0][3]) + (Arr2D[3][1] * _MAT.Arr2D[1][3]) + (Arr2D[3][2] * _MAT.Arr2D[2][3]) + (Arr2D[3][3] * _MAT.Arr2D[3][3]);
	*/

	return ReturnMat;
}