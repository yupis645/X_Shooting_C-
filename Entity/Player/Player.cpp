
#include "Player.h"

#include "InputManager.h"
#include "GameTexture.h"
#include "types.h"

using namespace PlayerConfig;
using namespace ScreenConfig;

//===============================================================
//					�R���X�g���N�^
//===============================================================
//===============================================================
//					�R���X�g���N�^
//===============================================================
Player::Player(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> render, std::shared_ptr<IInputManager> input)
	: anim(0), pat(0), shootdown(false), ownframecount(0), render_(render),input_(input),
	texture(rm->GetTexture(TextureType::Player)) // �K�v�Ȃ珉����
{
	// Targetsight�̃C���X�^���X�𓮓I�ɍ쐬
	targetsight = std::make_unique<Targetsight>(*this, rm);
}




//===============================================================
//					�v���C���[�̏�񏉊���
// 
// ���W�Ȃǂ̏�������������
//===============================================================
int Player::Init() {
	position = Vector2(CENTER_X, CENTER_Y);
	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);
	targetsight->Init();
	anim = 0;
	pat = 0;
	shootdown = false;
	ownframecount = 0;
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

	targetsight->Update();

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


	/* �v���C���[ or �Ə��̕`�� */
	if (!shootdown) {
		render_->DrawFromCenterPos(texture,anim, position, PLAYER_PIC_SIZE);
		targetsight->Draw();

		
	}

	/* �v���C���[�����j���ꂽ�ꍇ */
	else if (shootdown && anim < 6) {  // �����A�j���[�V�����̕`��ianim <= 6�͔����A�j���[�V������6�t���[���j
		render_->DrawBomberFromCenterPos(SpriteRenderer::BomberType::bomber,anim, position);
		//DrawBmp(pic.x, pic.y, ImageManager::PlayerBomber[anim]);  // ���@�̕`��
		//render_->DrawFromCenterPos(texture, anim, position.x, position.y, PLAYER_PIC_SIZE);


		return 0;
	}

	return 0;
}


int Player::Sync_PositionAndHitbox()
{
	/////*�v���C���[�̓����蔻����X�V����*/
	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);

	/////*�Ə��̓����蔻��̍X�V*/
	targetsight->hitboxsync(position);

	return 0;
}
int Player::AnimationUpdate(){

	////*���@�̃A�j���[�V�����ԍ��̐i�s*/

		//��e���Ă��Ȃ��ꍇ
	if (shootdown == false) {
		if (ownframecount % 12 == 0) {
			anim++;		//�A�j���[�V�����ԍ���i�߂�
			//Clamp(anim, 2, 4);		//�v���C���[��anim�ԍ������[�v������
			if(anim >= TextureConfigs::PLAYER.indexcount) anim = 0;
			ownframecount = 0;
		}
	}

	else {
		if (ownframecount % 12 == 0) {
			anim++;		//�A�j���[�V�����ԍ���i�߂�
			//Clamp(anim, 2, 4);		//�v���C���[��anim�ԍ������[�v������
			if (anim >= 5) anim = 0;
		}
		if (ownframecount % 20 == 0)	return 2;
	}

	return 0;
}