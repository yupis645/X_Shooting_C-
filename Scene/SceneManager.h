#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class SceneBase;
class DIContainer;

#include <iostream>

class SceneManager{
public :
	SceneManager(std::shared_ptr<DIContainer> con) : container_(con) {}

	int Init();
	int Update();
	int Draw();

	// �e���v���[�g�֐��ŃV�[���𐶐����Đ؂�ւ���
	template <typename SceneBase>
	void SwitchToScene() {
		currentscene_ = std::make_shared<SceneBase>(container_);
	}

	~SceneManager() {}

private:
	std::shared_ptr<SceneBase> currentscene_;
	std::shared_ptr<DIContainer> container_;

};

#endif //SCENEMANAGER_H