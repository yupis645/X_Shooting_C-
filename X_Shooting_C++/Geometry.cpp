#include "Geometry.h"

//�ǂ��ł�0�������ł���悤�ɒ�`���Ă���
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Boxcollider Boxcollider::zero = Boxcollider(0.0f, 0.0f, 0.0f, 0.0f);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    /*Vector2(���W��float�^ x, y�ŊǗ�����N���X)*/

// �����t���R���X�g���N�^
 Vector2::Vector2(float x, float y) : x(x), y(y) {}

//================================================================
// �x�N�g���̒������v�Z
//================================================================
 float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

//================================================================
// �x�N�g���𐳋K���i������1�ɂ���j
//================================================================
 Vector2 Vector2::normalized() const {
    float mag = magnitude();
    if (mag == 0) {
        return Vector2(0, 0);  // �x�N�g���̒�����0�̏ꍇ�A(0,0)��Ԃ�
    }
    return Vector2(x / mag, y / mag);  // ���K�������x�N�g����Ԃ�
}

//================================================================
// �x�N�g���̉��Z
//================================================================
 Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

//================================================================
// �x�N�g���̌��Z
//================================================================
 Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

//================================================================
// �X�J���[�Ƃ̏�Z�i�|���Z�j
//================================================================
 Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

//================================================================
// �X�J���[�Ƃ̏��Z�i����Z�j
//================================================================
 Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}

//================================================================
// 
//================================================================
 void Vector2::CenterPositionSync(Vector2 centerpos, int size)
{
    float pic_size_half = ((float)size / 2 - 1);				//RECT�̔����̒���()

    /*�X�v���C�g�̍�����W�ݒ�*/
    x = (centerpos.x) - pic_size_half;	//���S���W - �摜�T�C�Y�̔��a - 1(�␳)
    y = (centerpos.y) - pic_size_half;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                     /*Boxcollider(�l�p�`�̒��_��float�^ left , right ,top , bottom�ŊǗ�����)*/

//================================================================
// ��`���m�̏Փ˔���
//================================================================

 bool Boxcollider::BoxCollision(const Boxcollider& other) const {
    return !(right < other.left || left > other.right || bottom < other.top || top > other.bottom);
}

//================================================================
// �w�肳�ꂽ�_�����̋�`�̒��ɂ��邩�𔻒�
//================================================================
 bool Boxcollider::PosCollision(Vector2 pos) const {
    return (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom);
}

//================================================================
// ���S���W���璸�_�̈ʒu���Z�b�g����
//================================================================
 void Boxcollider::CenterPositionSync(Vector2 centerpos, int size)
{
    float hitbox_size_half = ((float)size / 2);		//�X�e�[�^�X�̓����蔻��̔����̒���()

    /*�����蔻��̓���*/
    left = (centerpos.x) - hitbox_size_half;
    top = (centerpos.y) - hitbox_size_half;
    right = (centerpos.x) + hitbox_size_half;
    bottom = (centerpos.y) + hitbox_size_half;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                     /*StringText(�������ێ����A�ꍇ�ɂ���Ă� C�X�^�C����char[]�ɕϊ�����)*/


//================================================================
// std::string �� char[] �ɕϊ����ĊO���ɓn���֐�
//================================================================
 const char* StringText::toCharArray() const {
    return str.c_str();  // std::string �� C�X�^�C��������ւ̃|�C���^��Ԃ�
}

//================================================================
// �e�L�X�g�𓮓I�ɍX�V����֐�
//================================================================
 void StringText::updateText(const std::string& newText) {
    str = newText;  // �V����������ōX�V
}

//================================================================
// �e�L�X�g�ɒǋL����֐�
//================================================================
 void StringText::appendText(const std::string& additionalText) {
    str += additionalText;  // �������ǋL
}

//================================================================
// �e�L�X�g�̓��e��\���i�f�o�b�O�p�j
//================================================================
 void StringText::printString() const {
    std::cout << "std::string: " << str << std::endl;
}
