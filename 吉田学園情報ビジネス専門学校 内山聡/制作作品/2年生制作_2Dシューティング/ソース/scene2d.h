//=============================================================================
//
// ���C������ [scene2d.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene.h"

//=====================================
//	�}�N����`
//=====================================
#define MAX_WIDTH		(300)		 //�傫��

//=====================================
//	CScene2d�N���X
//=====================================
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();

	//�|���S���̏���������
	HRESULT Init(void);
	//�|���S���̏I������
	void Uninit(void);
	//�|���S���̍X�V����
	void Update(void);
	//�|���S���̕`�揈��
	void Draw(void);

	//Scene2d�̃N���G�C�g
	//static CScene2d*Create(D3DXVECTOR3 posd);
	//���W���擾
	D3DXVECTOR3 GetPos(void);
	//�e�N�X�`���̓\��t��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	//�z�u����
	void SetPos(D3DXVECTOR3 pos);
	//�J���[�ύX
	void SetColor(D3DXCOLOR color);
	//�T�C�Y�̐ݒ�
	void SetSize(D3DXVECTOR3 sizeBg);
	//�����̔z�u
	void SetExplosion(int PatternAnimation);
	//�e�N�X�`���̔z�u
	void SetBgTexPos(D3DXVECTOR2 *pBgTexPos);
	//�|���S���̒���
	void SetLength(float fwidth, float fheight);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; };
private:
	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	//�p�x
	float m_fAngle;
	//����
	float m_fLength;

	// ��]
	D3DXVECTOR3				m_rotPolygon;
	// �|���S���̈ʒu
	D3DXVECTOR3				m_posPolygon;
	//�傫��
	D3DXVECTOR3				m_sizePolygon;
	//��
	float m_fwidth;
	//����
	float m_fheight;

	//�^�C�}�[
	int						m_nTime;
	float					m_nCnt;
};
#endif