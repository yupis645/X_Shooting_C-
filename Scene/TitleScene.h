#ifndef TITLESCENE_H
#define TITLESCENE_H
#include <array>
#include "di.hpp"

class Scenestatus;
class GameStatus;
class IInputManager;
struct StringText;

#include "Geometry.h"
#include "SceneBase.h"
#include "IInputManager.h"
#include "DIContainer.h"

class TitleScene : public SceneBase {
public:
    TitleScene(std::shared_ptr<DIContainer> con, 
        std::shared_ptr<Scenestatus> ss, 
        std::shared_ptr<GameStatus> gs,
        std::shared_ptr<IInputManager> im,
        std::shared_ptr<ResourceManager> rm);
  
    // ����������
    int Init() override;

    // �X�V����
    int Update() override;

    // �`�揈��
    int Draw() override;

    ~TitleScene() override;

//private :
    std::shared_ptr<DIContainer> container_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<Scenestatus> scenestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;
    std::array<StringText , 3> menu;
};


#endif // TITLESCENE_H
