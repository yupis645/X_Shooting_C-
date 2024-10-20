#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>

struct Vector2 {
    float x, y;

    // �����t���R���X�g���N�^
    Vector2(float x = 0.0f, float y = 0.0f);

    // �x�N�g���̒������v�Z
    float magnitude() const;

    // �x�N�g���𐳋K���i������1�ɂ���j
    Vector2 normalized() const;

    // �x�N�g���̉��Z
    Vector2 operator+(const Vector2& other) const;

    // �x�N�g���̌��Z
    Vector2 operator-(const Vector2& other) const;

    // �X�J���[�Ƃ̏�Z�i�|���Z�j
    Vector2 operator*(float scalar) const;

    // �X�J���[�Ƃ̏��Z�i����Z�j
    Vector2 operator/(float scalar) const;

    //
    void CenterPositionSync(Vector2 centerpos, int size);

    // 0�ŏ���������ÓI�Ȓ萔
    static const Vector2 zero;   
};

struct Boxcollider {
    float left;
    float top;
    float right;
    float bottom;

    Boxcollider() : left(0), top(0), right(0), bottom(0) {}
    Boxcollider(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
    Boxcollider(float i) : left(i), top(i), right(i), bottom(i) {}

    // ��`���m�̏Փ˔���
    bool BoxCollision(const Boxcollider& other) const;

    // �w�肳�ꂽ�_�����̋�`�̒��ɂ��邩�𔻒�
    bool PosCollision(Vector2 pos) const;

    // ���S���W���璸�_�̈ʒu���Z�b�g����
    void CenterPositionSync(Vector2 centerpos, int size);

  // 0�ŏ���������ÓI�Ȓ萔
    static const Boxcollider zero;
};


struct StringText {
    std::string str;  // ������ std::string �ŕ�������Ǘ�

    // �R���X�g���N�^�ŏ�����
    //StringText(const std::string& input = "") : str(input) {}
    StringText() {}

    // std::string �� char[] �ɕϊ����ĊO���ɓn���֐�
    const char* toCharArray() const;

    // �e�L�X�g�𓮓I�ɍX�V����֐�
    void updateText(const std::string& newText);

    // �e�L�X�g�ɒǋL����֐�
    void appendText(const std::string& additionalText);

    // �e�L�X�g�̓��e��\���i�f�o�b�O�p�j
    void printString() const;

    void WriteTextprintf() {

    }
};


#endif // GEOMETRY_H
