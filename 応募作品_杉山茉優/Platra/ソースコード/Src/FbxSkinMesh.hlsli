// -----------------------------------------------------------------------
// 
// �e�����X�L�����b�V���̃V�F�[�_�[(�g�D�[�������_�����O)
// 
//                                                      FbxSkinMesh.hlsli
// -----------------------------------------------------------------------
#define MAX_BONE 255

// �O���[�o���ϐ�	
Texture2D g_Texture: register(t0);      // �e�N�X�`���[�� ���W�X�^�[t(n)
Texture2D g_NormalTexture : register(t1);     // �@���}�b�v
Texture2D g_SpecularTexture : register(t3);   // �X�y�L�����[�}�b�v
Texture2D g_ToonTexture : register(t4);       // M.S �g�D�[���e�N�X�`��

SamplerState g_samLinear : register(s0); // �T���v���[�̓��W�X�^�[s(n)
// �R���X�^���g�o�b�t�@
// ���[���h����ˉe�܂ł̕ϊ��s��E��(b0)
cbuffer global : register(b0)
{
	matrix g_mW;          // ���[���h�s��
	matrix g_mWV;         // M.S ���[���h�E�r���[�s��
	matrix g_mWVP;        // ���[���h����ˉe�܂ł̕ϊ��s��
	float4 g_LightDir;    // ���C�g�̕����x�N�g��
	float4 g_EyePos;      // ���_�ʒu
	float4 g_Diffuse;     // �f�B�t���[�Y�F	
	float4 g_DrawInfo;    // �e����(�g���Ă��Ȃ�)   // -- 2020.12.15
};

// �{�[���s��(b1)
cbuffer cbBones : register(b1)
{
	matrix BoneFramePose[MAX_BONE];		// �w��t���[���ł̃��b�V���ɉe����^����S�Ă̍��̃|�[�Y�s��
};

// �}�e���A���J���[�̃R���X�^���g�o�b�t�@
cbuffer global : register(b3)               // -- 2020.12.15
{
	float4 g_MatDiffuse = float4(0.5, 0.5, 0.5, 1);   // �f�B�t���[�Y�F	
	float4 g_MatSpecular = float4(0, 0, 0, 0);        // �X�y�L�����F
};

// �X�L�j���O��̒��_�E�@��������
struct Skin
{
	float4 Pos4;
	float3 Normal;
	float3 Tangent; // �ڐ�      // -- 2021.6.11
	float3 Binormal; // �]�@��   // -- 2021.6.11
};

// �o�[�e�b�N�X�V�F�[�_�[�̓��̓p�����[�^(���_�t�H�[�}�b�g�Ɠ���)
struct VS_IN
{
	float3 Pos     : POSITION;		// ���_���W
	float3 Normal  : NORMAL;		// �@��
	float2 Tex     : TEXCOORD;		// �e�N�Z��
	uint4  Bones   : BONE_INDEX;	// �{�[���̃C���f�b�N�X
	float4 Weights : BONE_WEIGHT;	// �E�F�C�g
	float3 Tangent : TANGENT; // �ڐ�
	float3 Binormal : BINORMAL; // �]�@��

};

// �o�[�e�b�N�X�V�F�[�_�[�̏o�͍\����
// (�s�N�Z���V�F�[�_�[�̓��͂ƂȂ�)
struct VS_OUTPUT
{
	float4 Pos    : SV_POSITION;
	float3 Normal : NORMAL;
	float2 Tex    : TEXCOORD;
	float4 lightTangentSpace : TEXCOORD1; // �ڋ�Ԃɕϊ����ꂽ���C�g�x�N�g��
	float4 PosWorld:TEXCOORD2;
	float4 ToonUV:TECCOORD3;              // M.S�g�D�[���y�C���g�̃e�N�X�`�����W
};

// �ڋ�ԍs��̋t�s����Z�o
float4x4 InverseTangentMatrix(float3 tangent, float3 binormal, float3 normal)
{
	tangent = normalize(mul(tangent, (float3x3)g_mW));     // �ڐ������[���h�ϊ�����      // -- 2021.6.11
	binormal = normalize(mul(binormal, (float3x3)g_mW));   // �]�@�������[���h�ϊ�����
	normal = normalize(mul(normal, (float3x3)g_mW));       // �@�������[���h�ϊ�����

	float4x4 mat = { float4(tangent, 0.0f),
		float4(binormal, 0.0f),
		float4(normal, 0.0f),
		{ 0.0f, 0.0f, 0.0f, 1.0f } };

	return transpose(mat); // �]�u�s��ɂ���
}


// ���_���X�L�j���O�i�{�[���ɂ��ό`�j����T�u�֐�          // -- 2021.6.11
// �i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j
Skin SkinVert(VS_IN In)
{
	Skin Out;
	Out.Pos4 = float4(0.0f, 0.0f, 0.0f, 0.0f);
	Out.Normal = float3(0.0f, 0.0f, 0.0f);
	Out.Tangent = float3(0.0f, 0.0f, 0.0f);
	Out.Binormal = float3(0.0f, 0.0f, 0.0f);

	float4 pos4 = float4(In.Pos, 1);
	float3 normal = In.Normal;
	float3 tangent = In.Tangent;
	float3 binormal = In.Binormal;


	// �{�[��0
	uint iBone = In.Bones.x;
	float fWeight = In.Weights.x;
	matrix m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// �{�[��1
	iBone = In.Bones.y;
	fWeight = In.Weights.y;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// �{�[��2
	iBone = In.Bones.z;
	fWeight = In.Weights.z;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);
	// �{�[��3
	iBone = In.Bones.w;
	fWeight = In.Weights.w;
	m = BoneFramePose[iBone];
	Out.Pos4 += fWeight * mul(pos4, m);
	Out.Normal += fWeight * mul(normal, (float3x3)m);
	Out.Tangent += fWeight * mul(tangent, (float3x3)m);
	Out.Binormal += fWeight * mul(binormal, (float3x3)m);

	return Out;
}
//
// �X�y�L�����̌v�Z
//
float4 CalcSpecular(float4 Color, float4 texSpecular, float4 PosWorld, float3 Normal, float NMbright)
{
	if (texSpecular.w == 1.0f) // �X�y�L�����}�b�v�����邩
	{
		// �n�[�t�x�N�g�����g�����X�y�L�����̌v�Z
		float3 ViewDir = normalize(g_EyePos.xyz - PosWorld.xyz);  // PosWorld����g_EyePos�֌����������x�N�g���i���K���j
		float3 HalfVec = normalize(g_LightDir.xyz + ViewDir);     // �n�[�t�x�N�g���i�����x�N�g���ƌ����x�N�N�g���̒��ԃx�N�g���j�i���K���j

		float Gloss = 4;   // ����x�W���B�w���l���傫���قǃX�y�L���������������Ȃ�B�����ł�4�Ƃ��Ă���B
		float Spec = 2.5f * pow(saturate(dot(HalfVec, Normal)), Gloss);   // �X�y�L�����̌v�Z�B��ŃX�y�L�����}�b�v�l���|���邽��2.5�{�ɂ��Ă���
		Color.rgb = saturate(Color.rgb + Spec * texSpecular.rgb * NMbright);   // �X�y�L�����ɃX�y�L�����}�b�v�l���|���ăJ���[�ɉ�����B

	}
	return Color;
}

//
// �o�[�e�b�N�X�V�F�[�_�[
//
VS_OUTPUT VS_TOON1(VS_IN In)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4x4 inverseTangentMat;

	Skin vSkinned = SkinVert(In);		// �X�L�j���O

	output.Pos = mul(vSkinned.Pos4, g_mWVP);   // ���_�����[���h�E�r���[�E�v���W�F�N�V�����ϊ�
	output.Normal = mul(vSkinned.Normal, (float3x3)g_mW);    // �@�������[���h�ϊ�����
	output.Normal = normalize(output.Normal);               // �@���𐳋K������
	// �ڋ�ԍs��̓]�u�s����Z�o
	inverseTangentMat = InverseTangentMatrix(normalize(In.Tangent), normalize(In.Binormal), normalize(In.Normal));   // -- 2021.6.11


	// ���C�g�x�N�g����ڋ�ԏ�ɕϊ�
	output.lightTangentSpace = mul(float4(g_LightDir.xyz, 1.0), inverseTangentMat);
	output.Tex = In.Tex;         // �e�N�X�`�����W�͂��̂܂܏o��

	// �g�D�[�������_�����O�̏���
	// �g�D�[���y�C���g(�A�e)�̃e�N�X�`�����WToonUV���쐬����B 
	// ���̕\�ʂ̖��邳0.01�`0.99���e�N�X�`����U���W�ɂ���B
	// (�{�[�_�[���C���̈ʒu(0��1)�������悤�ɂ���)
	output.ToonUV.x = min(0.99f, max(0.01f, dot(output.Normal, normalize(g_LightDir.xyz))));

	// M.S �g�D�[���C���N(�֊s��)�̃e�N�X�`�����W�����߂鏈��
	// M.S ���_�����[���h�E�r���[�ϊ�����
	float3 PosWV = normalize(mul(vSkinned.Pos4, g_mWV)).xyz;

	// M.S �@�������[���h�E�r���[�ϊ�����
	float3 NormalWV = normalize(mul(vSkinned.Normal, (float3x3)g_mWV)).xyz;

	// M.S ���ς����߂�B���ϒl��0.5���|���Ă���0.5�����Z����B���̒l���e�N�X�`����V���W�Ƃ���B
	output.ToonUV.y = dot(PosWV, NormalWV) * 0.5 + 0.5;


	return output;
}

//
// �s�N�Z���V�F�[�_�[
//
float4 PS_TOON1(VS_OUTPUT In) : SV_Target
{
	float4 Color;      // �ŏI�o�͒l
	uint width, height;
	g_Texture.GetDimensions(width, height);  // �f�B�t���[�Y�e�N�X�`���̃T�C�Y�𓾂�  // -- 2020.12.15
	// �e�N�X�`���J���[
	float4 texColor;
	if (width == 0)  // �f�B�t���[�Y�e�N�X�`�����Ȃ��Ƃ�  // -- 2020.12.15
	{
		texColor = g_MatDiffuse;      // -- 2020.12.15
	}
	else {
		texColor = g_Texture.Sample(g_samLinear, In.Tex);
	}
	// M.S �g�D�[���e�N�X�`���̐F�������߂�
	float4 texToon = g_ToonTexture.Sample(g_samLinear, In.ToonUV);
	// M.S�g�D�[�������_�����O
    // M.S �ʏ�̃e�N�X�`���F(texColor)�Ƀg�D�[���y�C���g(ToonUV�̃T���v��)���|�����킹��
	Color.rgb = texColor.rgb * 1.1f * texToon.rgb * g_Diffuse.rgb;    // M.S �������邭
	Color.a = texColor.a - (1 - g_Diffuse.a);
	return saturate(Color);
}