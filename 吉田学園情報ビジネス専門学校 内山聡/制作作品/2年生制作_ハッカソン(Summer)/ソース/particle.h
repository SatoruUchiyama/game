//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : TAKUTO ISHIDA
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_EMITTER			(16)							// �G�~�b�^�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ���݂̊p�x
	D3DXCOLOR col;			// �G�~�b�^�̈ʒu
	float fLength;			// ���_�̋���
	float fCntRot;			// �p�x�̍X�V
	float fRotAngle;		// ��]����Ƃ��̊p�x
	float fAngle;			// �p�x
	float fRadius;			// �傫��
	int nLife;				// �\������
	int nType;				// �e�N�X�`���̎��
	float fGravity;			// �d��
	bool bUse;				// �g�p����Ă��邩
	float fBouncing;		// �o�E���h����l
	int nIdx;				// �G�~�b�^�̔ԍ����L��
	bool bDraw;				// ���Z�������ǂ���
	D3DXMATRIX mtxWorld;
}Particle;

typedef struct
{
	D3DXVECTOR3 pos;		// �G�~�b�^�̈ʒu
	int nWidth[2];			// ��(�ŏ��l�ƍő�l)
	int nHeight[2];			// ����(�ŏ��l�ƍő�l)
	int nDepth[2];			// ���s(�ŏ��l�ƍő�l)
	D3DXCOLOR col;			// �F
	D3DXCOLOR flameCol;		// ���t���[���̐F�̕ω�
	int nRadius[2];			// �傫��(�ŏ��l�ƍő�l)
	float fFlameRadius;		// ���t���[���̔��a�̊g�k
	int nLife;				// �G�~�b�^�̎���
	int nParLife[2];		// �\������(�ŏ��l�ƍő�l)
	int nType;				// �e�N�X�`���̎��
	float fSpread;			// �L����
	int nAppear;			// �o��Ԋu
	float fGravity;			// �d��
	int nLap;				// 1���ɏo����
	int nRot;				// ��]���邩�ǂ���(0:�Ȃ��@1:���v���@2:�����v��� 3:�����_��)
	float fRotSpeed;		// ��]���鑬�x
	bool bLoop;				// ���[�v�����邩 0:�Ȃ� 1:����
	bool bBouncing;			// �o�E���h�����邩 0:�Ȃ� 1:����
	bool bDraw;				// ���Z�������ǂ���
	bool bUse;				// �g�p����Ă��邩
}ParEmitter;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

void SetParticleEmitter(D3DXVECTOR3 pos, int nType);
void SetPosParticleEmitter(int nIdx, D3DXVECTOR3 pos);
void DestroyParticle(int nIdx);

void DeleteParticle(void);

#endif