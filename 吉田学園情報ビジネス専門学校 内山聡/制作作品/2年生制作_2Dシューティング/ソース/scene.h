//=============================================================================
//
// ���C������ [scene.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"

//=====================================
//	Scene�N���X
//=====================================
class CScene
{
public:
	//�񋓌^
	typedef enum
	{
		OBJTYPE_NOEN = 0,
		OBJTYPE_BG,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_ITEM,
		OBJTYPE_EXPLOSION,
		OBJTYPE_MAX
	}OBJTYPE;

	//CScene();
	CScene(int nPriority);
	virtual ~CScene();
	
	//�|���S���̏���������
	virtual HRESULT Init(void) = 0;
	//�|���S���̏I������
	virtual void Uninit(void) = 0;
	//�|���S���̍X�V����
	virtual void Update(void) = 0;
	//�|���S���̕`�揈��
	virtual void Draw(void) = 0;

	//	�S�Ă��J��
	static void ReleaseAll(void);
	//	�ł̐i��
	static void UpdateAll(void);
	//	���̕`��̌���
	static void DrawAll(void);
	//	�I�u�W�F�N�g�̊J��
	void Release(void);

	//�I�u�W�F�N�g�̃^�C�v�̐ݒ�
	void SetObjType(OBJTYPE objType);
	//�I�u�W�F�N�g�̃^�C�v���擾
	OBJTYPE GetObjType(void);
	//�V�[���������Ă���
	static CScene *GetScene(int nIndex, int nPriority);
private:
	//�V�[���̃|�C���^
	//static CScene *m_apScene[MAX_MODEL];
	static CScene *m_apScene[MAX_PRIORITY_2][MAX_MODEL];
	int m_nPriority;
	//
	static int m_nNumAll;
	//
	OBJTYPE m_objType;
	//������ID
	int m_nID;
};
#endif
