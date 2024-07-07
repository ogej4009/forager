struct VTX2D_IN
{
    float4 POS : POSITION;
};

struct VTX2D_OUT
{
    float4 POS : SV_Position;
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

VTX2D_OUT VS_DEBUG2D(VTX2D_IN _In)
{
    VTX2D_OUT Out = (VTX2D_OUT) 0.0f;
    Out.POS = mul(_In.POS, WVP);
    return Out;
}

cbuffer CB_DEBUG_COLOR : register(b0)
{
    float4 CbColor;
}

float4 PS_DEBUG2D(VTX2D_OUT _In) : SV_Target
{
    return CbColor;
}