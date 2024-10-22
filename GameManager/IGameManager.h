
#ifndef IGAMEMANAGER_H
#define IGAMEMANAGER_H

//----------------------------------------------------------------------------------------------------
//                         �Q�[���S�̂��Ǘ�����N���X(�C���^�[�t�F�[�X)
// 
// �Q�[���S�̂��Ǘ�����N���X�̃C���^�[�t�F�[�X�B
// ��{�I�ȃ��C�t�T�C�N�����`���Ă���
//----------------------------------------------------------------------------------------------------

class IGameManager {
public:
    IGameManager() {};
    ~IGameManager() = default;

    virtual int Init() = 0;     //������

    virtual int Input() = 0;    //����
    virtual int GameLoop() = 0;   //�X�V

    virtual int End() = 0;      //�I������

};

#endif // IGAMEMANAGER_H
