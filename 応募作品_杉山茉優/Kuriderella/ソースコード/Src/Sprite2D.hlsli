// -----------------------------------------------------------------------
// 
// �Q�c�X�v���C�g�̃V�F�[�_�[
// 
//                                                              2020.1.24
//                                                          Sprite2D.hlsli
// -----------------------------------------------------------------------

//�O���[�o��
Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

//�O���[�o��
cbuffer global_0:register(b0)
{
	matrix g_W;              //���[���h�ϊ��s��̂�
	float  g_ViewPortWidth;  //�r���[�|�[�g�i�X�N���[���j���T�C�Y
	float  g_ViewPortHeight; //�r���[�|�[�g�i�X�N���[���j�c�T�C�Y
	float2 g_UVOffset;       //�e�N�X�`�����W�@�I�t�Z�b�g
	float4 g_Diffuse;        // �f�B�t���[�Y�J���[                        // 2020.1.24
	float4 g_MatInfo;        // �}�e���A���֘A���@x:�e�N�X�`���L�薳��  // 2017.10.8
};

//�\����
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

//
// �o�[�e�b�N�X�V�F�[�_�[
//
PS_INPUT VS(float4 Pos : POSITION, float2 UV : TEXCOORD)
{
	PS_INPUT Out;

	Out.Pos = mul(Pos, g_W);

	Out.Pos.x = (Out.Pos.x / g_ViewPortWidth) * 2 - 1;
	Out.Pos.y = 1 - (Out.Pos.y / g_ViewPortHeight) * 2;

	Out.UV = UV + g_UVOffset;

	return Out;
}
//
// �s�N�Z���V�F�[�_�[
//
float4 PS(PS_INPUT In) : SV_Target
{
	float4 Color;
	if (g_MatInfo.x == 1)
	{   // �e�N�X�`���L��̂Ƃ�
		float4 texColor = g_Texture.Sample(g_Sampler, In.UV);
		Color.rgb = texColor.rgb * g_Diffuse.rgb;
		Color.a   = texColor.a - (1 - g_Diffuse.a);     // -- 2020.1.15
	}
	else { // �e�N�X�`���Ȃ��̂Ƃ�
		Color = g_Diffuse;
	}
	return saturate( Color );
}
