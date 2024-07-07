#pragma once
#include <Windows.h>
#include <math.h>
#include "GameMacro.h"

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

class CMatrix;
class GameMath
{
public:
	static unsigned int FormatByteSize(DXGI_FORMAT _Fmt);

public:
	static const float PI;
	static const float PI_2;
	static const float DTOR;
	static const float RTOD;

public:
	GameMath();
	~GameMath();
};

class CVector
{
public:
	static UINT SX;
	static UINT SY;

	static const CVector ZERO;
	static const CVector ONE;
	static const CVector RED;
	static const CVector WHITE;
	static const CVector LEFT;
	static const CVector RIGHT;
	static const CVector UP;
	static const CVector DOWN;
	static const CVector FORWARD;
	static const CVector BACK;

public:
	static CVector VectorDegToDir2D(float _Rad)
	{
		CVector m_Pos;
		m_Pos.DegToDir2D(_Rad);
		return m_Pos;
	}

	unsigned int ColorToUint()
	{
		UINT Color;
		unsigned char* p = (unsigned char*)&Color;
		p[0] = (unsigned char)(r * 255);
		p[1] = (unsigned char)(g * 255);
		p[2] = (unsigned char)(b * 255);
		p[3] = (unsigned char)(a * 255);
		return Color;
	}

public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		float Arr[4];

		DirectX::XMFLOAT4 DXXMFLOAT4;
		DirectX::XMFLOAT3 DXXMFLOAT3;
		DirectX::XMVECTOR XMVEC;
	};

public:
	CVector() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {	}
	CVector(float _Value) : x(_Value), y(_Value), z(_Value), w(1.0f) {	}
	CVector(float _x, float _y) : x(_x), y(_y), z(0.0f), w(1.0f) {	}
	CVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f) {	}
	CVector(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {	}
	CVector(const DirectX::XMVECTOR& _Vec) : XMVEC(_Vec) {	}
	CVector(const CVector& _Vec) : XMVEC(_Vec.XMVEC) {	}

public:
	// 오일러->쿼터니언
	void EulerToQ()
	{
		(*this).operator*=(GameMath::DTOR);
		XMVEC = DirectX::XMQuaternionRotationRollPitchYawFromVector(XMVEC);
	}

public:
	int ix() { return (int)x; }
	int iy() { return (int)y; }
	unsigned int uix() { return (unsigned int)x; }
	unsigned int uiy() { return (unsigned int)y; }

	// 정규화가 중요하다. 정규화란 1을 기준으로 한 비율을 말한다. 
public:
	float Len2D()
	{
		float Len = (x * x) + (y * y);
		return sqrtf(Len);
	}

	float Len3D()
	{
		CVector Return = DirectX::XMVector3Length(XMVEC);
		return Return.XMVEC.m128_f32[0];
	}

	// 벡터의 1/2
	CVector HV() const
	{
		// this의 형태
		// CVEC4* const
		// 그런데 함수에 const가 붙으면
		// const HVEC4* const m_Pos;
		CVector Return = *this;
		Return *= 0.5f;
		return Return;
	}

	// 절대값
	CVector ABS() const
	{
		CVector Return = *this;
		Return = DirectX::XMVectorAbs(Return);
		return Return;
	}

	float Dot3D(const CVector& _Other)
	{
		// 내적은 기본적으로 벡터와 벡터의 곱셈을 통해서
		// 길이를 구해내는것이 기본이다.
		// 이때. 
		// 그 길이란 1차원 평면에 투영된 길이인데.
		// 일반적인 사용법으로는 크게 의미가 없고
		// 벡터의 내적은 그리고 교환법칙이 성립한다.
		// EX) AVECTOR * BVECTOR != BVECTOR * AVECTOR 
		// 이때 양쪽의 길이가 1이면 COS세타를 얻을수 있고.
		// COS세타는 역함수를 통해서 세타를 알아내서
		// 아직 정사형을 구하는 함수는 만들지 않은것인데

		//  1 나는 Nomral3d() 노말라이즈 되어있어야
		// 정사영이 성립한다./
		// |*this.Len()||_Other.Len()|cos세타
		// 정사영은 투영인데.

		CVector Return = DirectX::XMVector3Dot(XMVEC, _Other.XMVEC);

		return Return.XMVEC.m128_f32[0];
	}

	CVector Cross3D(const CVector& _Other)
	{
		CVector Return;
		Return.XMVEC = DirectX::XMVector3Cross(XMVEC, _Other.XMVEC);
		//HVEC4 Return;
		//Return.x = (y * _Other.z) - (z * _Other.y);
		//Return.y = (z * _Other.x) - (x * _Other.z);
		//Return.z = (x * _Other.y) - (y * _Other.x);
		return Return;
	}

	float VectorAngleDegZ(const CVector& _Other)
	{
		return VectorAngleRadZ(_Other) * GameMath::RTOD;
	}

	float VectorAngleRadZ(const CVector& _Other)
	{
		CVector Left = *this;
		CVector Right = _Other;
		Left.Normal3D();
		Right.Normal3D();

		float CosSeta = Left.Dot3D(Right);

		float Result = acosf(CosSeta);

		if (_Other.y >= y)
		{
			Result = GameMath::PI_2 - Result;
		}

		return Result;
	}


	void DegToDir2D(float _Rad)
	{
		RadToDir2D(_Rad * GameMath::DTOR);
	}

	// 3D는 어떻게 할까?
	void RadToDir2D(float _Rad)
	{
		// 어떤 X가 1, 
		// 
		// float fx = x * cosf(_Rad) - 0 * sinf(_Rad);
		// float fy = x * sinf(_Rad) + 0 * cosf(_Rad);

		x = cosf(_Rad);
		y = sinf(_Rad);
		return;
	}

	void DegToRot2DZ(float _Rad)
	{
		RadToRot2DZ(_Rad * GameMath::DTOR);
	}

	// 3D는 어떻게 할까?
	void RadToRot2DZ(float _Rad)
	{
		// DirectX::xmvector

		// 구면선형보간
		float fx = x * cosf(_Rad) - y * sinf(_Rad);
		float fy = x * sinf(_Rad) + y * cosf(_Rad);
		x = fx;
		y = fy;
		return;
	}

	void DegToRot2DX(float _Rad)
	{
		RadToRot2DX(_Rad * GameMath::DTOR);
	}

	// 3D는 어떻게 할까?
	void RadToRot2DX(float _Rad)
	{
		// DirectX::xmvector

		// 구면선형보간
		float fz = z * cosf(_Rad) - y * sinf(_Rad);
		float fy = z * sinf(_Rad) + y * cosf(_Rad);
		z = fz;
		y = fy;
		return;
	}

	void DegToRot2DY(float _Rad)
	{
		RadToRot2DY(_Rad * GameMath::DTOR);
	}

	// 3D는 어떻게 할까?
	void RadToRot2DY(float _Rad)
	{
		// DirectX::xmvector

		// 구면선형보간
		float fx = x * cosf(_Rad) - z * sinf(_Rad);
		float fz = x * sinf(_Rad) + z * cosf(_Rad);
		x = fx;
		z = fz;
		return;
	}

	void DegToRot2DXYZ(CVector _Rot)
	{
		RadToRot2DXYZ(_Rot * GameMath::DTOR);
	}

	void RadToRot2DXYZ(CVector _Rot)
	{
		// DirectX::xmvector

		// x축 회전
		//float xz = z * cosf(_Rad) - y * sinf(_Rad);
		//float xy = z * sinf(_Rad) + y * cosf(_Rad);

		//// yaxis
		//float yx = x * cosf(_Rad) - z * sinf(_Rad);
		//float yz = x * sinf(_Rad) + z * cosf(_Rad);

		//// zaxis
		//float zx = x * cosf(_Rad) - y * sinf(_Rad);
		//float zy = x * sinf(_Rad) + y * cosf(_Rad);


		// 1.0f, 0.0f, 0.0f, 1.0f
		// 0.5f, 0.0f, 0.0f, 1.0f



		//float rz = (z * cosf(_Rot.x) - y * sinf(_Rot.x)) * (x * sinf(_Rot.y) + z * cosf(_Rot.y));
		//float ry = (z * sinf(_Rot.x) + y * cosf(_Rot.x)) * (x * sinf(_Rot.z) + y * cosf(_Rot.z));
		//float rx = (x * cosf(_Rot.y) - z * sinf(_Rot.y)) * (x * cosf(_Rot.z) - y * sinf(_Rot.z));

		//z = rz;
		//y = ry;
		//x = rx;

		return;
	}

	void Copy2D(const CVector& _Pos)
	{
		x = _Pos.x;
		y = _Pos.y;
	}

	void Copy3D(const CVector& _Pos)
	{
		x = _Pos.x;
		y = _Pos.y;
		z = _Pos.z;
	}

	void Normal3D()
	{
		XMVEC = DirectX::XMVector3Normalize(XMVEC);
	}

	CVector Normal3DReturn()
	{
		return DirectX::XMVector3Normalize(XMVEC);
	}

public:
	// 형변환 연산자
	operator POINT()
	{
		POINT P;
		P.x = (int)x;
		P.y = (int)y;
		return P;
	}

	operator const DirectX::XMVECTOR& () const
	{
		return XMVEC;
	}

	operator const DirectX::XMFLOAT3& () const
	{
		return DXXMFLOAT3;
	}

	operator const DirectX::XMFLOAT4& () const
	{
		return DXXMFLOAT4;
	}

	CVector operator*(const CMatrix& _MAT);
	CVector TransCoord(const CMatrix& _MAT);
	CVector TransNormal(const CMatrix& _MAT);

public:
	CVector operator-()
	{
		CVector Return = { 0 };
		Return.x = x * -1;
		Return.y = y * -1;
		Return.z = z * -1;
		Return.w = w * -1;
		return Return;
	}

	CVector operator*(const float _Value) const
	{
		CVector Return = { 0 };
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	CVector operator-(const CVector& _Value) const
	{
		CVector Return = { 0 };
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	CVector operator+(const CVector& _Value) const
	{
		CVector Return = { 0 };
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	CVector& operator*=(const float _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		return *this;
	}

	CVector operator*(const CVector& _Value) const
	{
		CVector Return = { 0 };
		Return.x = x * _Value.x;
		Return.y = y * _Value.y;
		Return.z = z * _Value.z;
		return Return;
	}

	CVector& operator*=(const CVector& _Value)
	{
		x *= _Value.x;
		y *= _Value.y;
		z *= _Value.z;
		return *this;
	}

	CVector& operator+=(const CVector& _Value)
	{
		x += _Value.x;
		y += _Value.y;
		z += _Value.z;
		return *this;
	}

};

class CMatrix
{
public:
	static UINT SX;
	static UINT SY;

	union
	{
		float Arr2D[4][4];
		CVector ArrVec[4];
		float Arr1D[16];
		struct
		{
			float _00; float _01; float _02; float _03;
			float _10; float _11; float _12; float _13;
			float _20; float _21; float _22; float _23;
			float _30; float _31; float _32; float _33;
		};

		DirectX::XMMATRIX XMMAT;
	};

public:
	void IDEN()
	{
		XMMAT = DirectX::XMMatrixIdentity();

		// 단위행렬
		//memset(Arr1D, 0, sizeof(HMAT));

		//for (size_t i = 0; i < SX; i++)
		//{
		//	Arr2D[i][i] = 1.0f;
		//}
	}

	void Pos(const CVector& _Pos)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixTranslation(_Pos.x, _Pos.y, _Pos.z);

		// ArrVec[3].Copy3D(_Pos);
	}

	void Scale(const CVector& _Scale)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixScaling(_Scale.x, _Scale.y, _Scale.z);

		//for (size_t i = 0; i < SX - 1; i++)
		//{
		//	Arr2D[i][i] = _Scale.Arr[i];
		//}
	}

	void RotXDeg(const float _Value)
	{
		RotXRad(_Value * GameMath::DTOR);
	}

	void RotYDeg(const float _Value)
	{
		RotYRad(_Value * GameMath::DTOR);
	}

	void RotZDeg(const float _Value)
	{
		RotZRad(_Value * GameMath::DTOR);
	}

	void RotXRad(const float _Value)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixRotationX(_Value);

		//Arr2D[1][1] = cosf(_Value);
		//Arr2D[1][2] = sinf(_Value);
		//Arr2D[2][1] = -sinf(_Value);
		//Arr2D[2][2] = cosf(_Value);
	}

	void RotYRad(const float _Value)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixRotationY(_Value);

		//Arr2D[0][0] = cosf(_Value);
		//Arr2D[0][2] = -sinf(_Value);
		//Arr2D[2][0] = sinf(_Value);
		//Arr2D[2][2] = cosf(_Value);
	}

	void RotZRad(const float _Value)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixRotationZ(_Value);

		//Arr2D[0][0] = cosf(_Value);
		//Arr2D[0][1] = sinf(_Value);
		//Arr2D[1][0] = -sinf(_Value);
		//Arr2D[1][1] = cosf(_Value);
	}

	// LH RH
	// _EyePos내가 보고있는 위치
	void VIEWTOLH(const CVector& _EyePos, const CVector& _EyeDir, const CVector& _EyeUp)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp);

		//HVEC4 Dir = _EyeDir;
		//HVEC4 Up = _EyeUp;

		//ArrVec[2] = Dir;
		//ArrVec[1] = Up;
		//ArrVec[0] = ArrVec[1].Cross3D(ArrVec[2]);
		//// 회전행렬이 반전된 회전행렬 x 를 40 회전시키면
		//// 반전시키면 x를 -40
		//TransPos();

		//ArrVec[3] = 
		//HVEC4(
		//	ArrVec[0].Dot3D(_EyePos),
		//	-ArrVec[1].Dot3D(_EyePos),
		//	-ArrVec[2].Dot3D(_EyePos),
		//	1.0F
		//);

		// XMMAT = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp);

	}

	// _Fov 수직시야각
	// _Widht 너비 
	// _Height 높이
	void PERSLHDEG(float _Fov, float _Width, float _Height, float _Near, float _Far)
	{
		PERSLHRAD(_Fov * GameMath::DTOR, _Width, _Height, _Near, _Far);
	}

	void ORTHLH(CVector _Size, float _Near, float _Far)
	{
		ORTHLH(_Size.x, _Size.y, _Near, _Far);
	}

	void ORTHLH(float _Width, float _Height, float _Near, float _Far)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
	}

	void PERSLHRAD(float _Fov, float _Width, float _Height, float _Near, float _Far)
	{
		IDEN();

		XMMAT = DirectX::XMMatrixPerspectiveFovLH(_Fov, _Width / _Height, _Near, _Far);

		// a
		//float Ratio = _Width / _Height;
		//float HR = _Fov;
		//float XR = _Fov * Ratio;

		// [1 / Ratio * (tanf(A / 2))] [   ] [   ] [    ] 
		// [						 ] [   ] [   ] [    ] 
		// [						 ] [   ] [   ] [1.0f] 
		// [						 ] [   ] [   ] [    ] 


		// 100 1100

		//// 이건다 비율값인거 아시죠?
		//Arr2D[0][0] = 1 / (Ratio * (tanf(HR / 2)));
		//Arr2D[1][1] = 1 / (tanf(HR / 2));
		////            1100 / 1000
		//Arr2D[2][2] = _Far / (_Far - _Near);
		//// -110 / 1000
		//Arr2D[3][2] = (-_Near * _Far) / (_Far - _Near);

		//// 이건 점이랑 곱해졌을때 W위치에 Z값이 들어가게 만들려고 하는것.
		//Arr2D[2][3] = 1.0f; // 점이랑 곱해졌을대 
		//// 점의 W에 Z값이 들어가있게 만들려고 한것이다.

		//// w값에 1이 더해진다.
		//// 아래 이값에 넣어주지 않으면
		//// 91
		//Arr2D[3][3] = 0.0f; // 점이랑 곱해졌을대 
		// 값을 남겨놨다가
		// z를 w로 나누면서 
		// 0~1사이의 공간으로 보내버린다.
	}

	// BitBit
	// 화면 중앙을 0, 0
	void VIEWPORT(float _StartX, float _StartY, float _Width, float _Height, float _MinZ, float _MaxZ)
	{
		IDEN();

		// DirectX::XMMatrixAffineTransformation

		// XMMAT = DirectX::XMMatrixviewport(XMMAT);

		Arr2D[0][0] = _Width / 2;
		Arr2D[1][1] = -(_Height / 2); // y축 반전
		Arr2D[2][2] = _MaxZ - _MinZ; // 큰 의미는 없다.

		Arr2D[3][0] = _StartX + Arr2D[0][0];
		Arr2D[3][1] = _StartX + (_Height / 2);
		Arr2D[3][2] = _MinZ;
	}

	void TransPos()
	{
		XMMAT = DirectX::XMMatrixTranspose(XMMAT);

		// float Temp = 0.0f;
		//Temp = Arr2D[0][1];		
		//Arr2D[0][1] = Arr2D[1][0];		
		//Arr2D[1][0] = Temp;
		//Temp = Arr2D[0][2];		Arr2D[0][2] = Arr2D[2][0];		Arr2D[2][0] = Temp;
		//Temp = Arr2D[0][3];		Arr2D[0][3] = Arr2D[3][0];		Arr2D[3][0] = Temp;
		//Temp = Arr2D[1][2];		Arr2D[1][2] = Arr2D[2][1];		Arr2D[2][1] = Temp;
		//Temp = Arr2D[1][3];		Arr2D[1][3] = Arr2D[3][1];		Arr2D[3][1] = Temp;
		//Temp = Arr2D[2][3];		Arr2D[2][3] = Arr2D[3][2];		Arr2D[3][2] = Temp;
	}

public:
	CMatrix operator*(const CMatrix& _MAT);

public:
	CMatrix() {}
	CMatrix(const CMatrix& _Other) : XMMAT(_Other.XMMAT) {}
	~CMatrix() {}
};

struct CTransformData
{
	union
	{
		struct
		{
			CMatrix W;
			CMatrix V;
			CMatrix P;
			CMatrix WV;
			CMatrix VP;
			CMatrix WVP;
		};
		CMatrix Arr[6];
	};

public:
	void AllTP()
	{
		for (size_t i = 0; i < 6; i++)
		{
			Arr[i].TransPos();
		}
	}

public:
	CTransformData() {}
	CTransformData(const CTransformData& _Other) :
		W(_Other.W),
		V(_Other.V),
		P(_Other.P),
		WV(_Other.WV),
		VP(_Other.VP),
		WVP(_Other.WVP)
	{
	}
	~CTransformData() {}
};