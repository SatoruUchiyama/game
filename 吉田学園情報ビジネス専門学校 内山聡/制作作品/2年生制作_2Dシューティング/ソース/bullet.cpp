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
#include "explosion.h"
#include "score.h"
#include "effect.h"
#include "enemy.h"
#include "game.h"
#include "item.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�:
//-----------------------------------------------------------------------------


LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//Texture�̓ǂݍ���
HRESULT CBullet::Lood(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "deta\\TEXTURE\\pipo-hiteffect004.png", &m_pTexture);

	return S_OK;
}
//Texture�̓ǂݍ���
void CBullet::Unlood(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CBullet::CBullet() : CScene2d(3)
{
	m_nLife = 0;
}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CBullet::~CBullet()
{

}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 moveBullet, TYPE_BULLET type)
{
	CScene2d::SetLength(20.0f, 20.0f);
	CScene2d::Init();
	CScene2d::SetPos(moveBullet);
	CScene2d::SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	SetObjType(CScene::OBJTYPE_BULLET);		//�^�C�v�̎d����

	m_nLife = MAX_BULLET_LIFE;
	m_BulletType = type;
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CBullet::Update(void)
{
	bool Decision = false;
	CScore *pscore = CGame::GetScore();
	CScene2d::Update();
	D3DXVECTOR3 posBullet;

	posBullet = CScene2d::GetPos();
	//for (int nCountPriority = 0; nCountPriority < MAX_PRIORITY_2; nCountPriority++)
	//{
		for (int nCount = 0; nCount < MAX_MODEL; nCount++)
		{
			CScene2d *scene2d;
			scene2d = (CScene2d*)CScene::GetScene(nCount,4);

			if (scene2d != NULL)
			{
				CScene::OBJTYPE objType = scene2d->GetObjType();
				//Player�̒e�Ȃ�
				if (m_BulletType == BULLET_TYPE_PLAYER)
				{
					//�e�̃X�s�[�h
					m_move.y = -8.0f;
					//�e��������I�u�W�F�N�g�^�C�v��Enemy�Ȃ�
					if (objType == OBJTYPE_ENEMY)
					{
						D3DXVECTOR3 enemy;
						enemy = scene2d->GetPos();

						//�����蔻��
						if (enemy.x - 20.0f < posBullet.x && enemy.x + 20.0f > posBullet.x &&
							enemy.y - 20.0f < posBullet.y && enemy.y + 20.0f > posBullet.y)
						{
							CEnemy*pEnemy = (CEnemy*)scene2d;
							pEnemy->HitEnemy(1);
							//�e�������邩
							Decision = true;

							break;
						}
					}
				}

				//Enemy�̒e�Ȃ�
				if (m_BulletType == BULLET_TYPE_ENEMY)
				{
					//�e�̃X�s�[�h
					m_move.y = 5.0f;

					//�e��������I�u�W�F�N�g�^�C�v��Player�Ȃ�
					if (objType == OBJTYPE_PLAYER)
					{

						D3DXVECTOR3 player;
						CPlayer *pPlayer = (CPlayer*)scene2d;

						player = scene2d->GetPos();
						//�����蔻��
						if (player.x - (pPlayer->GetSize().x - 10.0f) < posBullet.x && player.x + (pPlayer->GetSize().x - 10.0f) > posBullet.x &&
							player.y - (pPlayer->GetSize().y - 10.0f) < posBullet.y && player.y + (pPlayer->GetSize().y - 10.0f) > posBullet.y)
						{
							CPlayer*pPlayer = (CPlayer*)scene2d;
							pPlayer->HitPlayer(1);
							//�e�������邩
							Decision = true;

							break;
						}
					}
				}
				//�v���C���[�̒e���A�C�e���ɓ���������
				if (m_BulletType == BULLET_TYPE_PLAYER)
				{
					//�e�̃X�s�[�h
					m_move.y = -8.0f;
					//�e��������I�u�W�F�N�g�^�C�v��Enemy�Ȃ�
					if (objType == OBJTYPE_ITEM)
					{
						D3DXVECTOR3 item;
						item = scene2d->GetPos();

						//�����蔻��
						if (item.x - 20.0f < posBullet.x && item.x + 20.0f > posBullet.x &&
							item.y - 20.0f < posBullet.y && item.y + 20.0f > posBullet.y)
						{
							CItem*pItem = (CItem*)scene2d;
							pItem->HitItem(1, posBullet);
							//�e�������邩
							Decision = true;

							break;
						}
					}
				}
			}
		}
	//}

	posBullet.y += m_move.y;

	CScene2d::SetPos(posBullet);

	switch (m_BulletType)
	{
	case BULLET_TYPE_PLAYER:
		CEffect::Create(posBullet, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 15.0f, 10, D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
		break;
	case BULLET_TYPE_ENEMY:
		CEffect::Create(posBullet, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 15.0f, 10, D3DXCOLOR(255.0f, 0.0f, 0.0f, 255.0f));
		break;
	default:
		break;
	}

	//��ʂ� (���܂ōs������)�����邽�߂�true
	if (posBullet.y < 0)
	{
		Decision = true;
	}
	//��ʂ� (���܂ōs������)�����邽�߂�true
	if (posBullet.y > 720)
	{
		Decision = true;
	}

	// Decision��true�Ȃ������
	if (Decision == true)
	{
 		Uninit();
	}
}

void CBullet::Draw(void)
{

	

	CScene2d::Draw();

	
}

CBullet *CBullet::Create(D3DXVECTOR3 moveC, TYPE_BULLET type)
{
	CBullet *pBullet;
	pBullet = new  CBullet;
	pBullet->Init(moveC, type);

	pBullet->BindTexture(m_pTexture);

	return pBullet;
}
