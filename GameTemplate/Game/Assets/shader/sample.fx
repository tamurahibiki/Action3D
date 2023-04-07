///////////////////////////////////////////
// 構造体
///////////////////////////////////////////
// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos      : POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
};

// ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos      : SV_POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
};


///////////////////////////////////////////
// 定数バッファー
///////////////////////////////////////////
// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

// ディレクションライト用のデータを受け取るための定数バッファーを用意する
cbuffer DirectionLightCb : register(b1)
{
    float3 dirDirection;
    float3 dirColor;

    float3 ptPosition;
    float3 ptColor;
    float ptRander;
    
    float3 eyePos;          //視点の位置
    float3 ambientLight;
};

float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor,float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor,float3 worldPos, float3 normal);

///////////////////////////////////////////
// シェーダーリソース
///////////////////////////////////////////
// モデルテクスチャ
Texture2D<float4> g_texture : register(t0);

///////////////////////////////////////////
// サンプラーステート
///////////////////////////////////////////
sampler g_sampler : register(s0);

/// <summary>
/// モデル用の頂点シェーダーのエントリーポイント
/// </summary>
SPSIn VSMain(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;

    psIn.pos = mul(mWorld, vsIn.pos);   // モデルの頂点をワールド座標系に変換
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);    // ワールド座標系からカメラ座標系に変換
    psIn.pos = mul(mProj, psIn.pos);    // カメラ座標系からスクリーン座標系に変換

    // 頂点法線をピクセルシェーダーに渡す
    psIn.normal = mul(mWorld, vsIn.normal); // 法線を回転させる
    psIn.uv = vsIn.uv;

    return psIn;
}

/// <summary>
/// モデル用のピクセルシェーダーのエントリーポイント
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    float3 diffDirection = CalcLambertDiffuse(dirDirection,dirColor,psIn.normal);

    float3 specDirection = CalcPhongSpecular(dirDirection,dirColor, psIn.worldPos, psIn.normal);

    float3 ligDir = psIn.worldPos - ptPosition;
    ligDir = normalize(ligDir);

    float3 diffPoint = CalcLambertDiffuse(
        ligDir,
        ptColor,
        psIn.normal
    );

    float3 specPoint = CalcPhongSpecular(
        ligDir,
        ptColor,
        psIn.worldPos,
        psIn.normal
    );

    float distance = lenght(psIn.worldPos - ptPosition);

    float affect = 1.0f - 1.0f / ptRange * distance;
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    affect = pow(affect, 3.0f);

    diffPoint *= affect;
    specPoint *= affect;

    float3 diffuseLig = diffPoint + diffDirection;
    float3 specularLig = specPoint + specDirection;

    float3 lig = diffuseLig + specularLig + ambientLight;
    float4 finalColor = g_texture.Sample(g_sampler, psIn.uv);

    finalColor.xyz *= lig;

    return finalColor;
}

float3 CalcLamberDiffuse(float3 lightDirection, float3 lightColor.float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    t = max(0.0f, t);

    return lightColor * t;
}
float3 CarPhongSpecular(float3 lightDirection,float3 lightColor,float3 worldPos,float3 normal)
{
    float3 refVec = reflect(lightDirection, normal);

    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);

    float t = dot(refVec, toEye);
    
    t = max(0.0f,t);

    t = pow(t, 5.0f);

    return lightColor * t;
}
