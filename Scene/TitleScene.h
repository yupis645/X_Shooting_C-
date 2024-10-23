#ifndef TITLESCENE_H
#define TITLESCENE_H
#include <array>
#include "di.hpp"

class GameStatus;
class IInputManager;
struct StringText;

#include "Geometry.h"
#include "SceneBase.h"
#include "IInputManager.h"
#include "DIContainer.h"
#include "SpriteRenderer.h"

class TitleScene : public SceneBase {
public:
    TitleScene(std::shared_ptr<DIContainer> con);


    // ����������
    int Init() override;

    // �X�V����
    int Update()override;

    // �`�揈��
    int Draw() override;

    ~TitleScene() override;

private :
    std::shared_ptr<DIContainer> container_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;
    std::shared_ptr<SpriteRenderer>render_;

    std::shared_ptr<GameTexture> titlenameplate;       //�}�b�v�`�b�v�̉摜��ۊǂ��Ă����ϐ�
    std::array<StringText , 3> menu;


};


#endif // TITLESCENE_H
