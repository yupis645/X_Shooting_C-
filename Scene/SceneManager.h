#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include "SceneBase.h"
#include "DIContainer.h"

class SceneManager{
public :
	SceneManager(std::shared_ptr<DIContainer> con) : container_(con) {}

	int Init();
	int Update();
	int Draw();

	// テンプレート関数でシーンを生成して切り替える
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