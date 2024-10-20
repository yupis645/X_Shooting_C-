#include "TOROID.h"


int TOROID::Init(){
	EnemyBase::Init();
}

int TOROID::Create(int number, int typenumber)
{

	type = typenumber;

	//number�̕S�̈ʂ̓G�l�~�[��Type��\��(100 = Type:1 , 200 = Type:2)
	if (number >= 100) {
		type = number / 100;								//�i���o�[��100�Ŋ�����Type�����o��
		number = number - (100 * type);						//100�̈ʂ���菜�����G�̃i���o�[�����o��
	}


	//_e->enemy[EmptyNum] = A_enemyDate[number];
	//��b�X�e�[�^�X���R�s�[ or �e�l�̃Z�b�g
	status = A_ENEMY_DATA_ARRAY[number];

	currentspeed = status.speed;

	//�o���ʒu�̐ݒ�
	//if (number == 0 || number == 4 || number == 6) {		//�Ώ�:�g�[���C�h,�W�A��,�e���W
		position.x = player_->GetPosition().x + 250 + (rand() % 200);		//player_���� 250 ���ꂽ�ʒu����X�� 0�`200 �̗��������Z����X���W���w�� 
	//}
	//else {													//����ȊO
	//	_e->enemy[EmptyNum].center_x = (float)(rand() % SRN_W + 1); 			//��ʂ̉��T�C�Y�Ɏ��܂�͈͂Ń����_����X���W���w��
	//}

	//���������Ŏ擾����X���W����ʂ̉��T�C�Y�𒴂��Ă�����
	if (position.x >= SRN_W) { position.x = player_->GetPosition().x - 350 + (rand() % 200); }

	/*�����̍s���p�^�[���̂���G�̃X�e�[�^�X�ύX*/
	////�W�\�[
	//if (_e->enemy[EmptyNum].number == 3) {
	//	if (_e->enemy[EmptyNum].type > 0 && _e->enemy[EmptyNum].type < 3) { _e->enemy[EmptyNum].points = 100; }	//Type�ɂ�链�_�̕ϓ�
	//}
	////�U�K�[�g
	//else if (_e->enemy[EmptyNum].number == 7) {
	//	if (_e->enemy[EmptyNum].type == 0) { _e->enemy[EmptyNum].points = 100; }
	//	if (_e->enemy[EmptyNum].type == 1) { _e->enemy[EmptyNum].points = 150;	_e->enemy[EmptyNum].speed = 4.0; }
	//	if (_e->enemy[EmptyNum].type == 2) { _e->enemy[EmptyNum].points = 200; }
	//	if (_e->enemy[EmptyNum].type == 3) { _e->enemy[EmptyNum].points = 300;	_e->enemy[EmptyNum].speed = 4.0; }
	//}

	/*�摜��������*/
	//LoadDivBmp(PngData.A_Enemy, 0, 0, _e->enemy[EmptyNum].pic_size, _e->enemy[EmptyNum].pic_size, A_ENEMY_PIC_LINE, 11, _e->enemy[EmptyNum].pic);

	/*���S���W����'�����蔻��'��'�摜'�̍���ƉE���̍��W*/
	//Hitbox_Sync(&_e->enemy[EmptyNum].hitbox, _e->enemy[EmptyNum].hitbox_size,				//RECT:�����蔻�� , int:�����蔻��̒��S���W���猩���T�C�Y
	//	&_e->enemy[EmptyNum].center_x, &_e->enemy[EmptyNum].center_y,						//float:���S���W(X) , ���S���W(Y)
	//	&_e->enemy[EmptyNum].pic_x, &_e->enemy[EmptyNum].pic_y, _e->enemy[EmptyNum].pic_size);	//int:�摜�����x���W , �摜�����y���W , int:�摜�̃T�C�Y
	hitbox.CenterPositionSync(position, status.hitbox_size);

	/*��ʂ̒��S�����ɍ��E�ǂ���Ɋ���Ă��邩�ɂ���čŏ��̐i�s�����������߂�*/
	direction = hitbox.left < CENTER_X ? -1 : 1;

	return 0;
}

int TOROID::ActionUpdate(int framecount)
{

	bool frame_out = false;					//��ʂ���������邩�𔻒������(�����̒���true�ɂȂ����ꍇ�A�����̍Ŋ��ŉ�ʂ���폜 & ���̏��������s��)

	ownframecount++;				//�G��̂ɂ��Ă���ʂ̃^�C�}�[��i�߂�(�s�������Ɏg��)

	//��e���肪true�̏ꍇ
	if (shootdown == true) {
		if (ownframecount % 2 == 0) {		//2�t���[���Ɉ�x����
			currentanim_number++;					//anim�ϐ������Z����(�����A�j���[�V�����̐i�s)
		}
		if ( currentanim_number> 11) {				//anim�ϐ��� 11�����傫���Ȃ�����
			InitClear();
		}
	}

	//�ȉ��͔�e���肪�o�Ă��Ȃ��ꍇ�ɏ����ɐi��

	UniqueUpdate(framecount);		//�G�̍s��(number�ɂ���ĈقȂ鋓��������)

	hitbox.CenterPositionSync(position, status.hitbox_size);
	////�����蔻��̓���
	//Hitbox_Sync(&_e->enemy[r].hitbox, _e->enemy[r].hitbox_size,				//RECT:�����蔻�� , int:�����蔻��̒��S���W���猩���T�C�Y
	//	&_e->enemy[r].center_x, &_e->enemy[r].center_y,						//float:���S���W(X) , ���S���W(Y)
	//	&_e->enemy[r].pic_x, &_e->enemy[r].pic_y, _e->enemy[r].pic_size);


	//���W����ʊO�ɏo���ꍇ�̍��W�̏�����
	if (ownframecount > 50) {				//�o�����Ă���50�t���[�������Ă��画��ɓ���(�o�����Ă��΂炭�͉�ʒ[�ɓ������Ă��Ă��������Ȃ�)
		if (hitbox.BoxCollision( winView) == false)		//�����蔻��ƃE�B���h�E�T�C�Y��RECT�Əd�Ȃ��Ă��Ȃ� = ��ʊO �Ȃ�
		{
			InitClear();
		}
	}
	return 0;
}


int TOROID::UniqueUpdate(int framecount)
{
	currentanim_number = AnimUpdate(framecount, 5);	//�A�j���[�V�����̐i�s

	/*�e�����O�̓���*/
	if (actionpattern == 0) ActionPattern01();
	if (actionpattern == 1) ActionPattern02(framecount);
	if (actionpattern == 2) ActionPattern03(framecount);

	return 0;
}

int TOROID::ActionPattern01()
{
	//�o�����Ƀv���C���[���������W�Ɍ������Đi��

		Enemy_Patterns(0);		//�s���p�^�[�� 0:���@�Ɍ�����

		/*Y���̋����֌W�Ȃ��v���C���[�̂̓����蔻���X�����d�Ȃ�����*/
		if (player_->GetHitbox().left <= position.x  &&
			player_->GetHitbox().right >= position.x &&
			player_->GetPosition().y > position.y) {		//���@��Y������v�����Ƃ�

			tiypeaction();

			actionpattern++;			//�����p�^�[���ֈڍs����

			direction = position.x > player_->GetPosition().x ? -1 : 1;	//�v���C���[�Ƃ̈ʒu�֌W�ɂ���Č������Đݒ肷��
		}
	return 0;
}

int TOROID::ActionPattern02(int framecount )
{	//��葬�x�ɗ�����܂Ō�������
	Enemy_Patterns(0);		//�s���p�^�[�� 0:���@�Ɍ�����

	currentspeed -= 0.1f;					//����
	if (currentspeed < 0.6)  actionpattern = 2; 		//���x��0.6����������瓦���p�^�[���Ɉڍs����

	return 0;
}

int TOROID::ActionPattern03(int framecount)
{
	//���Ε����Ɍ������ē�������
	Enemy_Patterns(5);		//�s���p�^�[�� 5:�����x�����Z�����������ɓ�����


	//currentanim_number = AnimUpdate(framecount, 5);	//�A�j���[�V�����̐i�s


	return 0;
}

int TOROID::tiypeaction()
{
	//type 0 : ���ɒǉ��A�N�V�����͂Ȃ�

	//type 1 : �v���C���[�Ɍ������Ēe�𔭎˂���
	if (type == 1) {
		bulletmanager_->CreateEnemyShot(position);	//bulletmanager�œG�̒e�����
	}


	return 0;
}
