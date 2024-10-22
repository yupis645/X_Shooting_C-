
#include "Player.h"

using namespace PlayerConfig;
using namespace ScreenConfig;

//===============================================================
//					�R���X�g���N�^
//===============================================================
Player::Player(std::shared_ptr<ResourceManager> rm) : anim(0),  pat(0) ,shootdown(false)          
{
	//texture = rm->GetTextureManager()->GetTexture(TextureType::Player);     //�}�b�v�`�b�v�̃��[�h
	Create();
	// �K�v�ȏ���������������΂����ɋL�q
}



//===============================================================
//				 �f�X�g���N�^
//===============================================================
Player::~Player() {
	// �K�v�Ȃ烊�\�[�X����Ȃǂ��s��
}

//===============================================================
//					�v���C���[�̏�񏉊���
// 
// ���W�Ȃǂ̏�������������
//===============================================================
int Player::Init() {
	GameObject::InitClear();
	sight.Init();
	anim = 0;
	pat = 0;
	shootdown = false;
	ownframecount = 0;
	return 0;
}

//===============================================================
//					�v���C���[�̍쐬
// 
// ���ɍ����PLAYER�ɕK�v�ȃf�[�^���Z�b�g���ĕԂ�
// �E���S���W����摜�Ɠ����蔻��̍�����W�����߂�
// �E�Ə���̍��E���v���C���[�̍��E�Ƒ�����
// �E���@�A�V���b�g&�{���A�Ə���̉摜���擾����
//===============================================================
int Player::Create() {

	Init();


	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);

	/*�Ə��̓����蔻��̍X�V*/
	sight.Init();

	


	///*�v���C���[�摜�ǂݍ���*/
	//LoadDivBmp(PngData.Player, 0, 0, PLAYER_PIC_SIZE, PLAYER_PIC_SIZE, 6, 2,pic);		//���@ or �Ə��̉摜���[�h
	//LoadDivBmp(PngData.Shot, 0, 0, BULLET_SIZE, BULLET_SIZE, 3, 1, bullet);			//�U�b�p�[ or �u���X�^�[�̉摜���[�h	

	return 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																	/*���͂��ꂽ������������*/

//===============================================================
//					���͏��̏���
// 
// �E�ړ��L�[�ɂ��ړ�
// �E�V���b�g�L�[�ɂ��ˌ�
// �E�{���L�[�ɂ��Βn�U��
//===============================================================
int Player::Move(Vector2 move) {

	// ���ړ�: ���[�ɓ��B���Ă��Ȃ��Ȃ�ړ�������
	if (move.x < 0 && hitbox.left <= 0) {
		move.x = 0;  
	}
	// �E�ړ�: �E�[�ɓ��B���Ă��Ȃ��Ȃ�ړ�������
	if (move.x > 0 && hitbox.right >= SRN_W) {
		move.x = 0;  
	}

	// ��ړ�: ��[�ɓ��B���Ă��Ȃ��Ȃ�ړ�������
	if (move.y < 0 && hitbox.top <= 0) {
		move.y = 0; 
	}
	// ���ړ�: ���[�ɓ��B���Ă��Ȃ��Ȃ�ړ�������
	if (move.y > 0 && hitbox.bottom >= SRN_H) {
		move.y = 0;  
	}

	// �ړ��ʂ𔽉f
	position.x += move.x * SPEED;
	position.y += move.y * SPEED;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																	/*�X�V����*/

//===============================================================
//					�v���C���[�̍X�V
// 
// �E���W�ړ��ɍ��킹���摜�ⓖ���蔻��̈ړ�
// �E�A�j���[�V�����ԍ��̊Ǘ�
// �E�V���b�g�̍X�V(���W�ړ� & �q�b�g����)
// �E�{���̍X�V(���W�ړ� & �q�b�g����)
// �E�G�ƓG�e�ɑ΂����e����
// 
//  ��TestMode true & DebugEnable true�̏ꍇ�͔�e�����𖳌���
//===============================================================
int Player::Update( int framecount, Vector2 moveinput) {

	//�Ǝ���framecount��i�߂�
	ownframecount++;

	//�v���C���[�ƏƏ����boxcollider�̈ړ�
	Sync_PositionAndHitbox();

	////*���@�̃A�j���[�V�����ԍ��̐i�s*/
	int s = AnimationUpdate();
	if (s == 2) return 2;

	//���͂ɑ΂��鎩�@�̈ړ�
	Move(moveinput) ;

	

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																	/*�v���C���[�֘A�̃X�v���C�g��\��������*/
//===============================================================
//			�v���C���[�A�Ə���A�V���b�g�A�{���̕`��
// 
// anim�ԍ��ɂ����Ă��ꂼ��`�ʂ���B
// �E�Ə���͓����蔻�肪�n��G�Əd�Ȃ��Ă���ꍇ��anim�ԍ����ω�����(�ʏ�͐ŏd�Ȃ��Ă���ƐԂɂȂ�)
// �E��e����܂ł̓v���C���[�ƏƏ���̃X�v���C�g�B
//	   ��e��͔����A�j���[�V������`�悷��
// �E�V���b�g�̕`��
// �E�{���̕`��
//===============================================================
int Player::Draw() {


	//Vector2 pic = LeftTopPos(position, PLAYER_PIC_SIZE);
	///* �v���C���[ or �Ə��̕`�� */
	//if (!shootdown) {
	//	// ImageManager ����v���C���[�摜���擾���ĕ`��
	//	DrawBmp(pic.x, pic.y, ImageManager::player[anim]);               // ���@�̕`��
	//	//DrawBmp(pic_x, pic_y - BOM_ST, ImageManager::player[sight_anim]); // �Ə��̕`�ʁi�{���̎˒������������j
	//	sight.Draw();
	//}

	///* �v���C���[�����j���ꂽ�ꍇ */
	//else if (shootdown && anim < 6) {  // �����A�j���[�V�����̕`��ianim <= 6�͔����A�j���[�V������6�t���[���j
	//	DrawBmp(pic.x, pic.y, ImageManager::PlayerBomber[anim]);  // ���@�̕`��
	//	

		return 0;
	//}
}


int Player::Sync_PositionAndHitbox()
{
	/////*�v���C���[�̓����蔻����X�V����*/
	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);

	/////*�Ə��̓����蔻��̍X�V*/
	sight.hitboxsync(position);

	return 0;
}
int Player::AnimationUpdate(){

	////*���@�̃A�j���[�V�����ԍ��̐i�s*/

		//��e���Ă��Ȃ��ꍇ
	if (shootdown == false) {
		if (ownframecount % 12 == 0) {
			anim++;		//�A�j���[�V�����ԍ���i�߂�
			Clamp(anim, 2, 4);		//�v���C���[��anim�ԍ������[�v������
			ownframecount = 0;
		}
	}
	else {
		if (ownframecount % 20 == 0)	return 2;
	}

	return 0;
}
//
//int Player::AirEnemyCollision()
//{
//	return 0;
//}
//
//int Player::EnemyBulletCollision(std::shared_ptr<
// > EB)
//{
//	for (int i = 0; i < EB->EnemyshotSize(); i++)
//	{
//		shootdown = hitbox.BoxCollision(EB->GetEnemyShotArray(i).GetHitbox());
//	}
//
//	return 0;
//}
//
////===============================================================
////				�V���b�g�̕`��
//// 
//// �t���O�������Ă���V���b�g��`�ʂ���B�����ڏ�͓�e�����邪����͈����
//// �E���̒e�̕`��
//// �E�E�̒e�̕`��
////===============================================================
//void Shot_Draw(P_SHOT_ST _s[], Bmp _bmpR, Bmp _bmpL) {
//	for (int r = 0; r < MAX_SHOT; r++) {
//		if (_s[r].F == true) {
//			DrawBmp(_s[r].hitbox.left - BULLET_SIZE, _s[r].hitbox.top, &_bmpL);		//�V���b�g(��)�̕`��
//			DrawBmp(_s[r].hitbox.right, _s[r].hitbox.top, &_bmpR);		//�V���b�g(�E)�̕`��
//		}
//	}
//}
////===============================================================
////				�{���̕`��
//// 
//// �t���O�������Ă���Ԃ̂݃{����`�ʂ���B�U��������o���Ă���Ԃ͂Ȃɂ��\�����Ȃ�
//// �E�{���̕`��
////===============================================================
//void Bom_Draw(P_BOM_ST* _b, Bmp _bmp) {
//	if (_b->F == true) {
//		DrawBmp(_b->center_x - BULLET_SIZE, _b->center_y - BULLET_SIZE, &_bmp);		//�{���̕`��
//	}
//}