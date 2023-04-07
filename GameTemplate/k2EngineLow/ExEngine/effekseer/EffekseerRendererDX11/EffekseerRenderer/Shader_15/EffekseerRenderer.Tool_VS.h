#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tvs_4_0_level_9_3 /EVS /Fh Shader_15/EffekseerRenderer.Tool_VS.h
//    Shader_15/tool_renderer_VS.fx
//
//
// Buffer Definitions: 
//
// cbuffer $Globals
// {
//
//   float4x4 mCamera;                  // Offset:    0 Size:    64
//   float4x4 mProj;                    // Offset:   64 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// $Globals                          cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// POSITION                 0   xyz         0     NONE  float   xyz 
// NORMAL                   0   xyzw        1     NONE  float   xyzw
// TEXCOORD                 0   xy          2     NONE  float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float   xyzw
// COLOR                    0   xyzw        1     NONE  float   xyzw
// TEXCOORD                 0   xy          2     NONE  float   xy  
// TEXCOORD                 1   xyzw        3     NONE  float   xyzw
// TEXCOORD                 2   xyzw        4     NONE  float   xyzw
// TEXCOORD                 3   xyzw        5     NONE  float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c1         cb0             0         8  ( FLT, FLT, FLT, FLT)
//
//
// Runtime generated constant mappings:
//
// Target Reg                               Constant Description
// ---------- --------------------------------------------------
// c0                              Vertex Shader position offset
//
//
// Level9 shader bytecode:
//
    vs_2_x
    def c9, 0, 1, 0, 0
    dcl_texcoord v0
    dcl_texcoord1 v1
    dcl_texcoord2 v2
    mul r0, v0.y, c2
    mad r0, c1, v0.x, r0
    mad r0, c3, v0.z, r0
    add r0, r0, c4
    rcp r0.w, r0.w
    mad r1.xyz, r0, r0.w, c9.xyxw
    mul r2, r1.y, c6
    mad r2, c5, r1.x, r2
    mad r1, c7, r1.z, r2
    add r1, r1, c8
    rcp r2.x, r1.w
    mul oT3, r1, r2.x
    mad r1.xyz, r0, r0.w, c9.yxxw
    mul r0.xyz, r0.w, r0
    mul r2, r1.y, c6
    mad r2, c5, r1.x, r2
    mad r1, c7, r1.z, r2
    add r1, r1, c8
    rcp r0.w, r1.w
    mul oT4, r0.w, r1
    mul r1, r0.y, c6
    mad r1, c5, r0.x, r1
    mad r0, c7, r0.z, r1
    add r0, r0, c8
    rcp r1.x, r0.w
    mul oT2, r0, r1.x
    mad oPos.xy, r0.w, c0, r0
    mov oPos.zw, r0
    mov oT0, v1
    mov oT1.xy, v2

// approximately 30 instruction slots used
vs_4_0
dcl_constantbuffer cb0[8], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyzw
dcl_input v2.xy
dcl_output_siv o0.xyzw, position
dcl_output o1.xyzw
dcl_output o2.xy
dcl_output o3.xyzw
dcl_output o4.xyzw
dcl_output o5.xyzw
dcl_temps 3
mul r0.xyzw, v0.yyyy, cb0[1].xyzw
mad r0.xyzw, cb0[0].xyzw, v0.xxxx, r0.xyzw
mad r0.xyzw, cb0[2].xyzw, v0.zzzz, r0.xyzw
add r0.xyzw, r0.xyzw, cb0[3].xyzw
div r0.xyzw, r0.xyzw, r0.wwww
mul r1.xyzw, r0.yyyy, cb0[5].xyzw
mad r1.xyzw, cb0[4].xyzw, r0.xxxx, r1.xyzw
mad r1.xyzw, cb0[6].xyzw, r0.zzzz, r1.xyzw
mad r1.xyzw, cb0[7].xyzw, r0.wwww, r1.xyzw
mov o0.xyzw, r1.xyzw
div o3.xyzw, r1.xyzw, r1.wwww
mov o1.xyzw, v1.xyzw
mov o2.xy, v2.xyxx
add r1.xyzw, r0.xyzw, l(0.000000, 1.000000, 0.000000, 0.000000)
add r0.xyzw, r0.xyzw, l(1.000000, 0.000000, 0.000000, 0.000000)
mul r2.xyzw, r1.yyyy, cb0[5].xyzw
mad r2.xyzw, cb0[4].xyzw, r1.xxxx, r2.xyzw
mad r2.xyzw, cb0[6].xyzw, r1.zzzz, r2.xyzw
mad r1.xyzw, cb0[7].xyzw, r1.wwww, r2.xyzw
div o4.xyzw, r1.xyzw, r1.wwww
mul r1.xyzw, r0.yyyy, cb0[5].xyzw
mad r1.xyzw, cb0[4].xyzw, r0.xxxx, r1.xyzw
mad r1.xyzw, cb0[6].xyzw, r0.zzzz, r1.xyzw
mad r0.xyzw, cb0[7].xyzw, r0.wwww, r1.xyzw
div o5.xyzw, r0.xyzw, r0.wwww
ret 
// Approximately 26 instruction slots used
#endif

const BYTE g_VS[] =
{
     68,  88,  66,  67, 161,  98, 
    149, 242,  60, 102,  32, 142, 
    197, 221, 232, 115, 180, 111, 
     21, 233,   1,   0,   0,   0, 
     44,   9,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    168,   2,   0,   0, 152,   6, 
      0,   0,  20,   7,   0,   0, 
    252,   7,   0,   0, 112,   8, 
      0,   0,  65, 111, 110,  57, 
    104,   2,   0,   0, 104,   2, 
      0,   0,   0,   2, 254, 255, 
     52,   2,   0,   0,  52,   0, 
      0,   0,   1,   0,  36,   0, 
      0,   0,  48,   0,   0,   0, 
     48,   0,   0,   0,  36,   0, 
      1,   0,  48,   0,   0,   0, 
      0,   0,   8,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 254, 255, 
     81,   0,   0,   5,   9,   0, 
     15, 160,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      1, 128,   1,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      2, 128,   2,   0,  15, 144, 
      5,   0,   0,   3,   0,   0, 
     15, 128,   0,   0,  85, 144, 
      2,   0, 228, 160,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      1,   0, 228, 160,   0,   0, 
      0, 144,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   3,   0, 228, 160, 
      0,   0, 170, 144,   0,   0, 
    228, 128,   2,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   4,   0, 228, 160, 
      6,   0,   0,   2,   0,   0, 
      8, 128,   0,   0, 255, 128, 
      4,   0,   0,   4,   1,   0, 
      7, 128,   0,   0, 228, 128, 
      0,   0, 255, 128,   9,   0, 
    196, 160,   5,   0,   0,   3, 
      2,   0,  15, 128,   1,   0, 
     85, 128,   6,   0, 228, 160, 
      4,   0,   0,   4,   2,   0, 
     15, 128,   5,   0, 228, 160, 
      1,   0,   0, 128,   2,   0, 
    228, 128,   4,   0,   0,   4, 
      1,   0,  15, 128,   7,   0, 
    228, 160,   1,   0, 170, 128, 
      2,   0, 228, 128,   2,   0, 
      0,   3,   1,   0,  15, 128, 
      1,   0, 228, 128,   8,   0, 
    228, 160,   6,   0,   0,   2, 
      2,   0,   1, 128,   1,   0, 
    255, 128,   5,   0,   0,   3, 
      3,   0,  15, 224,   1,   0, 
    228, 128,   2,   0,   0, 128, 
      4,   0,   0,   4,   1,   0, 
      7, 128,   0,   0, 228, 128, 
      0,   0, 255, 128,   9,   0, 
    193, 160,   5,   0,   0,   3, 
      0,   0,   7, 128,   0,   0, 
    255, 128,   0,   0, 228, 128, 
      5,   0,   0,   3,   2,   0, 
     15, 128,   1,   0,  85, 128, 
      6,   0, 228, 160,   4,   0, 
      0,   4,   2,   0,  15, 128, 
      5,   0, 228, 160,   1,   0, 
      0, 128,   2,   0, 228, 128, 
      4,   0,   0,   4,   1,   0, 
     15, 128,   7,   0, 228, 160, 
      1,   0, 170, 128,   2,   0, 
    228, 128,   2,   0,   0,   3, 
      1,   0,  15, 128,   1,   0, 
    228, 128,   8,   0, 228, 160, 
      6,   0,   0,   2,   0,   0, 
      8, 128,   1,   0, 255, 128, 
      5,   0,   0,   3,   4,   0, 
     15, 224,   0,   0, 255, 128, 
      1,   0, 228, 128,   5,   0, 
      0,   3,   1,   0,  15, 128, 
      0,   0,  85, 128,   6,   0, 
    228, 160,   4,   0,   0,   4, 
      1,   0,  15, 128,   5,   0, 
    228, 160,   0,   0,   0, 128, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      7,   0, 228, 160,   0,   0, 
    170, 128,   1,   0, 228, 128, 
      2,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 128, 
      8,   0, 228, 160,   6,   0, 
      0,   2,   1,   0,   1, 128, 
      0,   0, 255, 128,   5,   0, 
      0,   3,   2,   0,  15, 224, 
      0,   0, 228, 128,   1,   0, 
      0, 128,   4,   0,   0,   4, 
      0,   0,   3, 192,   0,   0, 
    255, 128,   0,   0, 228, 160, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  12, 192, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  15, 224, 
      1,   0, 228, 144,   1,   0, 
      0,   2,   1,   0,   3, 224, 
      2,   0, 228, 144, 255, 255, 
      0,   0,  83,  72,  68,  82, 
    232,   3,   0,   0,  64,   0, 
      1,   0, 250,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  95,   0, 
      0,   3, 114,  16,  16,   0, 
      0,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      1,   0,   0,   0,  95,   0, 
      0,   3,  50,  16,  16,   0, 
      2,   0,   0,   0, 103,   0, 
      0,   4, 242,  32,  16,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
     50,  32,  16,   0,   2,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   3,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   4,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   5,   0, 
      0,   0, 104,   0,   0,   2, 
      3,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      0,   0,   0,   0,  86,  21, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,  16,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0, 166,  26, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   8, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  14,   0, 
      0,   7, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   6,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   7,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     14,   0,   0,   7, 242,  32, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      1,   0,   0,   0,  70,  30, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5,  50,  32, 
     16,   0,   2,   0,   0,   0, 
     70,  16,  16,   0,   2,   0, 
      0,   0,   0,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      2,   0,   0,   0,  86,   5, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   5,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      6,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      6,   0,   0,   0, 166,  10, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   7,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     14,   0,   0,   7, 242,  32, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   5,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      6,   0,   0,   0, 166,  10, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   7,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     14,   0,   0,   7, 242,  32, 
     16,   0,   5,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    116,   0,   0,   0,  26,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  11,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     82,  68,  69,  70, 224,   0, 
      0,   0,   1,   0,   0,   0, 
     72,   0,   0,   0,   1,   0, 
      0,   0,  28,   0,   0,   0, 
      0,   4, 254, 255,  16,   1, 
      0,   0, 174,   0,   0,   0, 
     60,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  36,  71, 108, 111, 
     98,  97, 108, 115,   0, 171, 
    171, 171,  60,   0,   0,   0, 
      2,   0,   0,   0,  96,   0, 
      0,   0, 128,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 144,   0,   0,   0, 
      0,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
    152,   0,   0,   0,   0,   0, 
      0,   0, 168,   0,   0,   0, 
     64,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
    152,   0,   0,   0,   0,   0, 
      0,   0, 109,  67,  97, 109, 
    101, 114,  97,   0,   3,   0, 
      3,   0,   4,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 109,  80, 114, 111, 
    106,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171,  73,  83, 
     71,  78, 108,   0,   0,   0, 
      3,   0,   0,   0,   8,   0, 
      0,   0,  80,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   7,   7, 
      0,   0,  89,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,  15, 
      0,   0,  96,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   3,   3, 
      0,   0,  80,  79,  83,  73, 
     84,  73,  79,  78,   0,  78, 
     79,  82,  77,  65,  76,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0, 171, 171, 171, 
     79,  83,  71,  78, 180,   0, 
      0,   0,   6,   0,   0,   0, 
      8,   0,   0,   0, 152,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0, 164,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     15,   0,   0,   0, 170,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      3,  12,   0,   0, 170,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
     15,   0,   0,   0, 170,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
     15,   0,   0,   0, 170,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   5,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  80,  79,  83,  73,  84, 
     73,  79,  78,   0,  67,  79, 
     76,  79,  82,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0, 171
};
