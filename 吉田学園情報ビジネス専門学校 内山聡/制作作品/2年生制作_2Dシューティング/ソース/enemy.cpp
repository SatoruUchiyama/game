//==========================================================================-==
//
// Player���� [player.cpp]
// Author : satoru uchiyama
//
//==========================================================================-==
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "item.h"
#include "sound.h"
#include "fade.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY] = {};
int CEnemy::nCountEnemyEnd = 0;
//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CEnemy::CEnemy():CScene2d(4)
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CEnemy::~CEnemy()
{

}

HRESULT CEnemy::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�G3.png", &m_pTexture[0]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�G2.png", &m_pTexture[1]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�G1.png", &m_pTexture[2]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�G1.png", &m_pTexture[3]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\�ŋ��g���I.png", &m_pTexture[4]);
	return S_OK;
}

void CEnemy::Unlood(void)
{
	for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------4
HRESULT CEnemy::Init(D3DXVECTOR3 posPlay,int nLife, D3DXVECTOR3 size)
{
	//CScene2d::SetLength(50.0f, 50.0f);
	m_nLife = nLife;
	CScene2d::Init();
	CScene2d::SetPos(D3DXVECTOR3(posPlay));
	CScene2d::SetSize(size);
	nCountEnemyEnd = 0;
	SetObjType(CScene::OBJTYPE_ENEMY);//�^�C�v�̎d����
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CEnemy::Update(void)
{
	bool Decision = false;
	CInputKeyboard *pKeyboard = CManager::GetInput();
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		m_posEnemy[nCount] = GetPos();
	}

	switch (m_EnemyType)
	{
	case ENEMY_TARGET_01:
		//	�G�̈ړ�����
		m_move[m_EnemyType].x -= sinf(D3DX_PI) * 0.5f;
		m_move[m_EnemyType].y -= cosf(D3DX_PI) * 0.5f;

		//	�G���e�����J�E���g
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 60)
		{
			//	�G�̒e�̃N���G�C�g	(�G�̈ʒu����)	(�^�C�v��enemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//�ړ�����
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];

		break;
	case ENEMY_TARGET_02:
		//	�G�̈ړ�����
		m_move[m_EnemyType].x -= sinf(D3DX_PI*0.5f) * MAX_SPEED_ENEMY;
		m_move[m_EnemyType].y -= cosf(D3DX_PI*0.5f) * MAX_SPEED_ENEMY;

		//	�G���e�����J�E���g
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 60)
		{
			//	�G�̒e�̃N���G�C�g	(�G�̈ʒu����)	(�^�C�v��enemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//�ړ�����
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];
		if (0  > m_posEnemy[m_EnemyType].x)
		{
			//m_posEnemy.x = m_posEnemy.x - SCREEN_WIDTH;
			Decision = true;
		}
		break;
	case ENEMY_TARGET_03:
		//	�G�̈ړ���
		m_move[m_EnemyType].x += sinf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;
		m_move[m_EnemyType].y += cosf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;

		//	�G���e�����J�E���g
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 120)
		{
			//	�G�̒e�̃N���G�C�g	(�G�̈ʒu����)	(�^�C�v��enemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//�ړ�����
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];
		//�����蔻��
		if (SCREEN_WIDTH  < m_posEnemy[m_EnemyType].x)
		{
			//m_posEnemy.x = m_posEnemy.x - SCREEN_WIDTH;
			Decision = true;
		}
	case ENEMY_TARGET_04:
		break;
	case ENEMY_TARGET_05:
		//	�G�̈ړ���
		m_move[m_EnemyType].x += sinf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;
		m_move[m_EnemyType].y += cosf(D3DX_PI*0.5) * MAX_SPEED_ENEMY;

		//	�G���e�����J�E���g
		m_nCountBullet_Enemy++;
		if (m_nCountBullet_Enemy == 20)
		{
			//	�G�̒e�̃N���G�C�g	(�G�̈ʒu����)	(�^�C�v��enemy)
			CBullet::Create(D3DXVECTOR3(m_posEnemy[m_EnemyType]), CBullet::BULLET_TYPE_ENEMY);
			m_nCountBullet_Enemy = 0;
		}
		m_move[m_EnemyType].x += (0.0f - m_move[m_EnemyType].x)*MAX_INERTIAL_ENEMY;
		m_move[m_EnemyType].y += (0.0f - m_move[m_EnemyType].y)*MAX_INERTIAL_ENEMY;
		//�ړ�����
		m_posEnemy[m_EnemyType] += m_move[m_EnemyType];
		//�����蔻��
		if (SCREEN_WIDTH < m_posEnemy[m_EnemyType].x)
		{
			m_posEnemy[m_EnemyType].x = m_posEnemy[m_EnemyType].x - SCREEN_WIDTH;
		}
		/*else if (0 > m_posEnemy[m_EnemyType].x)
		{
			m_posEnemy[m_EnemyType].x = SCREEN_WIDTH + m_posEnemy[m_EnemyType].x;
		}*/
		break;
	default:
		break;
	}

	////�����蔻��
	//if (SCREEN_WIDTH < m_posEnemy[2].x)
	//{
	//	//m_posEnemy.x = m_posEnemy.x - SCREEN_WIDTH;
	//	Decision = true;
	//}
	//else if (0 > m_posEnemy[1].x)
	//{
	//	//m_posEnemy.x = SCREEN_WIDTH + m_posEnemy.x;
	//	Decision = true;
	//}
	if (m_posEnemy[m_EnemyType].y > 720.0f)
	{
		Decision = true;
	}

	CScene2d::SetPos(m_posEnemy[m_EnemyType]);
	// Decision��true�Ȃ������
	if (Decision == true)
	{
		Uninit();
	}
}

void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

void CEnemy::HitEnemy(int nDamage)
{
	m_nLife -= nDamage;
	CManager *psound = NULL;
	CFade *pFade = CManager::GetFade();
	if (m_nLife ==0)
	{
		if (m_EnemyType == 0)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	�����̃N���G�C�g	(�G�̈ʒu��)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	�X�R�A�̉��Z
			CScore::AddScore(50);
			//	�I��
			Uninit();
		}
		else if (m_EnemyType == 1)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	�����̃N���G�C�g	(�G�̈ʒu��)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	�X�R�A�̉��Z
			CScore::AddScore(50);
			//	�I��
			Uninit();
		}
		else if (m_EnemyType == 2)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	�����̃N���G�C�g	(�G�̈ʒu��)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	�A�C�e���̃N���G�C�g	(�G�̈ʒu��)
			CItem::Create(m_posEnemy[m_EnemyType], CItem::ITEM_RECOVERY_01);
			//	�X�R�A�̉��Z
			CScore::AddScore(50);
			//	�I��
			Uninit();
		}
		else if (m_EnemyType == 3)
		{
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	�����̃N���G�C�g	(�G�̈ʒu��)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//	�I��
			Uninit();
		}
		else if (m_EnemyType == 4)
		{
			nCountEnemyEnd++;
			psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO1);
			//	�����̃N���G�C�g	(�G�̈ʒu��)
			CExplosion::Create(m_posEnemy[m_EnemyType]);
			//
			CScore::AddScore(5000);
			if (nCountEnemyEnd == END_ENEMY)
			{
				pFade->Set(CManager::MODE_RESULT);
			}
			//	�I��
			Uninit();
		}
	}
	else if(m_nLife <=100)
	{
		//	�����̃N���G�C�g	(�G�̈ʒu��)
		CExplosion::Create(m_posEnemy[m_EnemyType]);
	}
}

CEnemy *CEnemy::Create(D3DXVECTOR3 posC, ENEMY_TYPE type,int nLife, D3DXVECTOR3 size)
{
	CEnemy *pEnemy;
	pEnemy = new  CEnemy;
	pEnemy->Init(posC,nLife, size);
	pEnemy->m_EnemyType = type;
	pEnemy->BindTexture(m_pTexture[type]);


	return pEnemy;
}