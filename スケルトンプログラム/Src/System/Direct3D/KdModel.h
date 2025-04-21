#pragma once

//==========================================================
// ���b�V���p ���_���
//==========================================================
struct MeshVertex
{
	Math::Vector3	Pos;		// ���W
	Math::Vector2	UV;			// UV
	Math::Vector3	Normal;		// �@��
};

//==========================================================
// ���b�V���p �ʏ��
//==========================================================
struct MeshFace
{
	UINT Idx[3];				// �O�p�`���\�����钸�_��Index
};

//==========================================================
// ���b�V���p �T�u�Z�b�g���
//==========================================================
struct MeshSubset
{
//	std::shared_ptr<Material>	MaterialData;		// �}�e���A���f�[�^�ւ̎Q��
	UINT		MaterialNo = 0;		// �}�e���A��No

	UINT		FaceStart = 0;		// ��Index�@���̃}�e���A���Ŏg�p����Ă���ŏ��̖ʂ�Index
	UINT		FaceCount = 0;		// �ʐ��@FaceStart����A�����̖ʂ��g�p����Ă��邩��
};

//==========================================================
//
// ���b�V���N���X
//
//==========================================================
class KdMesh
{
public:

	//=================================================
	// �擾�E�ݒ�
	//=================================================

	// �T�u�Z�b�g���z����擾
	const std::vector<MeshSubset>&		GetSubsets() const { return m_subsets; }

	// ���_�`���擾
//	const VertexDecl&					GetVertexDecl() const { return m_vertexDecl; }

	// ���_�̍��W�z����擾
	const std::vector<Math::Vector3>&	GetVertexPositions() const { return m_positions; }
	// �ʂ̔z����擾
	const std::vector<MeshFace>&		GetFaces() const { return m_faces; }

	// �����s���E�{�b�N�X�擾
	const DirectX::BoundingBox&			GetBoundingBox() const { return m_aabb; }
	// ���E���擾
	const DirectX::BoundingSphere&		GetBoundingSphere() const { return m_bs; }

	// ���b�V���f�[�^���f�o�C�X�փZ�b�g����
	void SetToDevice() const;


	//=================================================
	// �쐬�E���
	//=================================================

	// ���b�V���쐬
	// �Evertices		�c ���_�z��
	// �Efaces			�c �ʃC���f�b�N�X���z��
	// �Esubsets		�c �T�u�Z�b�g���z��
	// �߂�l			�c �����Ftrue
	bool Create(const std::vector<MeshVertex>& vertices, const std::vector<MeshFace>& faces, const std::vector<MeshSubset>& subsets);

	// ���
	void Release()
	{
		m_vb.Release();
		m_ib.Release();
		m_subsets.clear();
		m_positions.clear();
		m_faces.clear();
	}

	~KdMesh()
	{
		Release();
	}

	//=================================================
	// ����
	//=================================================

	// �w��T�u�Z�b�g��`��
	void DrawSubset(int subsetNo) const;

	// 
	KdMesh() {}

private:

	// ���_�o�b�t�@
	KdBuffer						m_vb;
	// �C���f�b�N�X�o�b�t�@
	KdBuffer						m_ib;
	// ���_�`��
//	VertexDecl					m_vertexDecl;

	// �T�u�Z�b�g���
	std::vector<MeshSubset>		m_subsets;

	// ���E�f�[�^
	DirectX::BoundingBox		m_aabb;	// �����s���E�{�b�N�X
	DirectX::BoundingSphere		m_bs;	// ���E��

	// ���W�݂̂̔z��(����)
	std::vector<Math::Vector3>	m_positions;
	// �ʏ��݂̂̔z��(����)
	std::vector<MeshFace>		m_faces;

private:
	// �R�s�[�֎~�p
	KdMesh(const KdMesh& src) = delete;
	void operator=(const KdMesh& src) = delete;
};

//==========================================================
// �}�e���A��(glTF�x�[�X��PBR�}�e���A��)
//==========================================================
struct KdMaterial
{
	//---------------------------------------
	// �ގ��f�[�^
	//---------------------------------------

	// ���O
	std::string					Name;

	// ��{�F
	std::shared_ptr<KdTexture>	BaseColorTex;				// ��{�F�e�N�X�`��
	Math::Vector4				BaseColor = { 1,1,1,1 };	// ��{�F�̃X�P�[�����O�W��(RGBA)

	// �������A�e��
	std::shared_ptr<KdTexture>	MetallicRoughnessTex;		// B:������ G:�e��
	float						Metallic = 0.0f;			// �������̃X�P�[�����O�W��
	float						Roughness = 1.0f;			// �e���̃X�P�[�����O�W��

	// ���Ȕ���
	std::shared_ptr<KdTexture>	EmissiveTex;				// ���Ȕ����e�N�X�`��
	Math::Vector3				Emissive = { 0,0,0 };		// ���Ȕ����̃X�P�[�����O�W��(RGB)

	// �@���}�b�v
	std::shared_ptr<KdTexture>	NormalTex;

	KdMaterial()
	{
		BaseColorTex			= D3D.GetWhiteTex();
		MetallicRoughnessTex	= D3D.GetWhiteTex();
		EmissiveTex				= D3D.GetWhiteTex();
	}
};

//==========================================================
//
// �m�[�h�z���}�e���A���z���g�ݍ��킹�A�P�̃��f���f�[�^�Ƃ����N���X
//
//==========================================================
class KdModel
{
public:

	//==========================================================
	// �擾
	//==========================================================

	// ���b�V���擾
	const std::shared_ptr<KdMesh>&	GetMesh() const { return m_mesh; }
	// �}�e���A���z��擾
	const std::vector<KdMaterial>&	GetMaterials() const { return m_materials; }

	//==========================================================
	// �쐬�E���
	//==========================================================

	// glTF�`����3D���f�������[�h����
	// �Efilename		�c �t�@�C����
	// �߂�l			�c �����Ftrue
	bool Load(const std::string& filename);

	// ���
	void Release()
	{
//		m_allNodes.clear();
//		m_onlyRootNodes.clear();
		m_mesh = nullptr;
		m_materials.clear();
	}

	~KdModel() {
		Release();
	}

	// 
	KdModel() {}

private:

	// ���b�V��
	std::shared_ptr<KdMesh>		m_mesh;

	// �}�e���A���z��
	std::vector<KdMaterial>		m_materials;

private:
	// �R�s�[�֎~�p
	KdModel(const KdModel& src) = delete;
	void operator=(const KdModel& src) = delete;
};

