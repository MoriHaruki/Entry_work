#pragma once

#include "Scene.h"

class CPlay : public CScene {
public:
	CPlay();
	virtual ~CPlay();
public:
	void Init()			override;	//������
	void Load()			override;	//�ǂݍ���
	void OnLoadEnd()	override;	//�ǂݍ��ݏI��
	void Step()			override;	//�ʏ�
	void Update()		override;	//�X�V
	void Draw()			override;	//�`��
	void Fin()			override;	//�㏈��

private:
	void InitBullet();		//�e		������
	void InitPlayer();		//�v���C���[������
	void InitEnemy();		//�G�l�~�[	������
	void InitBox();			//���I�u�W�F������
	void InitObstacles();	//��Q��	������
	void InitStage();		//�X�e�[�W	������
	void InitCamera();		//�J����	������
	void InitEffect();		//�G�t�F�N�g������
	void InitCollision();	//�����蔻�菉����
	void InitSky();			//�V��		������	

	void LoadBullet();		//�e		�ǂݍ���
	void LoadPlayer();		//�v���C���[�ǂݍ���
	void LoadBox();			//���I�u�W�F�ǂݍ���
	void LoadObstacles();	//��Q��	�ǂݍ���
	void LoadEffect();		//�G�t�F�N�g�ǂݍ���
	void LoadSound();		//�T�E���h	�ǂݍ���
	void LoadSky();			//�V��		�ǂݍ���
	void LoadField();		//�t�B�[���h�ǂݍ���
};