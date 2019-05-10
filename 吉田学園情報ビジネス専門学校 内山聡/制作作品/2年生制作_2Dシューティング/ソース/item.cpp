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
#include "Item.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

LPDIRECT3DTEXTURE9 CItem::m_pTexture[MAX_ITEM] = {};

//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CItem::CItem() :CScene2d(4)
{

}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CItem::~CItem()
{

}

HRESULT CItem::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\��03.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\pipo-hiteffect0019.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\bg01.png", &m_pTexture[2]);

	return S_OK;
}

void CItem::Unlood(void)
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
HRESULT CItem::Init(D3DXVECTOR3 posPlay)
{
	//CScene2d::SetLength(50.0f, 50.0f);
	m_nLife = 10;
	CScene2d::Init();
	CScene2d::SetPos(D3DXVECTOR3(posPlay));
	CScene2d::SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	SetObjType(CScene::OBJTYPE_ITEM);//�^�C�v�̎d����
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CItem::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CItem::Update(void)
{
	bool Decision = false;
	CInputKeyboard *pKeyboard = CManager::GetInput();
	m_posItem = GetPos();

	m_move.x -= sinf(D3DX_PI) * 0.4f;
	m_move.y -= cosf(D3DX_PI) * 0.4f;

	m_move.x += (0.0f - m_move.x)*0.1f;
	m_move.y += (0.0f - m_move.y)*0.1f;

	m_posItem += m_move;

	
	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
			CScene2d *scene2d;
			scene2d = (CScene2d*)CScene::GetScene(nCount, 4);

		if (scene2d != NULL)
		{
			CScene::OBJTYPE objType = scene2d->GetObjType();
			//�e��������I�u�W�F�N�g�^�C�v��Player�Ȃ�
			if (objType == OBJTYPE_PLAYER)
			{
				D3DXVECTOR3 player;
				CPlayer *pPlayer = (CPlayer*)scene2d;
				player = scene2d->GetPos();
				//�����蔻��
				if (player.x - pPlayer->GetSize().x < 10.0f + m_posItem.x && player.x + pPlayer->GetSize().x > 10.0f - m_posItem.x &&
					player.y - pPlayer->GetSize().y < 10.0f + m_posItem.y && player.y + pPlayer->GetSize().y > 10.0f - m_posItem.y)
				{
					Decision = true;
					CScore::AddScore(500);
					break;
				}
			}
		}
	}


	//�����蔻��
	if (SCREEN_WIDTH < m_posItem.x)
	{
		m_posItem.x = m_posItem.x - SCREEN_WIDTH;
	}
	else if (0 > m_posItem.x)
	{
		m_posItem.x = SCREEN_WIDTH + m_posItem.x;
	}

	if (m_posItem.y > 720.0f)
	{
		Decision = true;
	}
	CScene2d::SetPos(m_posItem);

	// Decision��true�Ȃ������
	if (Decision == true)
	{
		Uninit();
	}
}

void CItem::Draw(void)
{
	CScene2d::Draw();
}

void CItem::HitItem(int nDamage, D3DXVECTOR3 pos)
{
	float Angle;
	CManager *psound = NULL;
	Angle = atan2f(pos.x - m_posItem.x, pos.y - m_posItem.y);
	D3DXVECTOR3 SetPos(sinf(Angle)*MAX_X, cosf(Angle)*MAX_Y, 0.0);

	m_nLife -= nDamage;

	if (m_nLife <= 0)
	{
		//�����̃N���G�C�g
		CExplosion::Create(m_posItem);
		CScore::AddScore(3000);
		psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO3);
		Uninit();
	}
	else
	{
		//CExplosion::Create(m_posItem);
		m_move = SetPos;
		CScore::AddScore(100);
		psound->GetCSound()->PlaySound(CSound::SOUND_LABEL_SE_POTATO3);
	}
}

CItem *CItem::Create(D3DXVECTOR3 posC, ITEM_TYPE type)
{
	CItem *pEnemy;
	pEnemy = new  CItem;
	pEnemy->Init(posC);
	pEnemy->m_type = type;

	pEnemy->BindTexture(m_pTexture[type]);

	return pEnemy;
}