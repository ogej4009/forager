struct VTX2D_IN
{
    float4 POS : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

struct VTX2D_OUT
{
    float4 POS : SV_Position;
    float2 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

cbuffer CB_TRANSDATA : register(b0)
{
    matrix W;
    matrix V;
    matrix P;
    matrix WV;
    matrix VP;
    matrix WVP;
}

cbuffer CB_CUT : register(b1)
{
    float4 CutData;
}

VTX2D_OUT VS_SPRITE2D(VTX2D_IN _In)
{
    VTX2D_OUT Out = (VTX2D_OUT) 0.0f;
    Out.POS = mul(_In.POS, WVP);
    Out.COLOR = _In.COLOR;
    Out.UV.x = CutData.x + (_In.UV.x * CutData.z);
    Out.UV.y = CutData.y + (_In.UV.y * CutData.w);
    return Out;
}

cbuffer CB_COLOR : register(b0)
{
    float4 CbColor;
}

Texture2D TEX2D : register(t0);
SamplerState LSMP : register(s0);
SamplerState PSMP : register(s1);

float4 PS_SPRITE2D(VTX2D_OUT _In) : SV_Target
{
    float4 TexColor = TEX2D.Sample(PSMP, _In.UV);
    
    if (0 >= TexColor.a)
    {
        clip(-1);
    }
    
    _In.COLOR = TexColor * CbColor;
    return _In.COLOR;
}