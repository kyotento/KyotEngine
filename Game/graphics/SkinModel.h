#pragma once

#include "Skeleton.h"

/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};

const int directionLightNum = 1;		//�f�B���N�V�������C�g�̐��B(�����ς���Ƃ��̓V�F�[�_�[�����ύX���Ă�����K�v������)�B


struct DirectionLight {
	CVector4 direction[directionLightNum];	//�f�B���N�V�������C�g�̌����B
	CVector4 color[directionLightNum];		//�f�B���N�V�������C�g�̐F�B
	CVector3 eyePos;
	float specPos;
};


/// <summary>
/// �f�B���N�V�������C�g�f�ށB
/// </summary>
/// <remarks>
/// direction = ���C�g�̕����B
/// color = ���C�g�̐F�B
/// </remarks>
struct LightConstantBuffer
{
	DirectionLight		directionLight;		//�f�B���N�V�������C�g�B
	CVector3			eyePos;				//�J�����̎��_�B
	float				specPow;			//�X�y�L�������C�g�̍i��B
	CVector3			environmentpow;		//�����̋����B
};

/*!
*@brief	�X�L�����f���N���X�B
*/
class SkinModel
{
public:
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath, /*EnFbxUpAxis enFbxUpAxis,*/ const char* entryPS, const char* entryVS/*, bool ShadowReciever*/);

	/// <summary>
	/// ���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V�B
	/// </summary>
	/// <param name="position">���f���̍��W</param>
	/// <param name="rotation">���f���̉�]</param>
	/// <param name="scale">���f���̊g�嗦</param>
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);

	/// <summary>
	/// �{�[���������B
	/// </summary>
	/// <param name="boneName">�{�[���̖��O</param>
	/// <returns>���������{�[���Belse������Ȃ������ꍇ��null��Ԃ�</returns>
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	���f����`��B
	*@param[in]	viewMatrix		�J�����s��B
	*  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	*/
	/// <summary>
	/// ���f����`��B
	/// </summary>
	/// <param name="renderMode">�����_�����O���[�h</param>
	/// <param name="viewMatrix">�J�����s��(���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��)</param>
	/// <param name="projMatrix">�v���W�F�N�V�����s��(�J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��)</param>
	void Draw(EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix );

	/// <summary>
	/// �X�P���g���̎擾�B
	/// </summary>
	/// <returns>�X�P���g��</returns>
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}

	/// <summary>
	/// ���b�V���̌����B
	/// </summary>
	/// <param name="onFindMesh">���b�V���������������̃R�[���o�b�N�֐�</param>
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}

	/// <summary>
	/// �f�B���N�V�������C�g�̏������B
	/// </summary>
	void InitDirectionLight();

	/// <summary>
	/// �V���h�E�}�b�v
	/// </summary>
	/// <param name="srv"></param>
	void SetShadowMap(ID3D11ShaderResourceView* srv) {
		m_shadowMapSRV = srv;
	}

	/// <summary>
	/// �}�e���A���ɑ΂��ăN�G�����s���B
	/// </summary>
	/// <param name="func">���₢���킹�֐�</param>
	void QueryMaterials(std::function<void(SkinModel*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<SkinModel*>(material));
		});
	}

	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};

	/// <summary>
	/// �V���h�E�t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag">�V���h�E���V�[�o�[�t���O</param>
	void SetShadowReciever(bool flag) {
		m_isShadowReciever = flag;
	}

private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);

private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;			//���[���h�s��B	
		CMatrix mView;			//�r���[�s��B
		CMatrix mProj;			//�v���W�F�N�V�����s��B
		CMatrix mLightView;		//todo ���C�g�r���[�s��B
		CMatrix mLightProj;		//todo ���C�g�v���W�F�N�V�����s��B
		int isShadowReciever;
	};

	bool m_isShadowReciever = true;			//�V���h�E���V�[�o�[�t���O�B

	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	ID3D11Buffer*		m_lightConstantBuffer = nullptr;//���C�g�p�̒萔�o�b�t�@�B
	DirectionLight		m_directionLight;				//�f�B���N�V�������C�g�B
	ID3D11ShaderResourceView* m_shadowMapSRV = nullptr;

//	const int directionLightNum = 1;		//�f�B���N�V�������C�g�̐��B

	const char* m_vsmain;
	const char* m_psmain;

};

