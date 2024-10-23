#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

class DIContainer;
class IGameManager;
class ResourceManager;
class SpriteRenderer;
class GameStatus;
class IInputManager;

class DebugInput;
class BoxCollider;
class Vector2;

#include <iostream>
#include "common.h"


class DebugManager{
public:
	DebugManager(std::shared_ptr<DIContainer> con);

	void DrawInputFrag();

	void DrawHitBox(const Boxcollider);

	void DrawCenterPos(const Vector2);

	~DebugManager() = default;

	std::shared_ptr<DIContainer> container;
	std::shared_ptr<IGameManager> gm;
	std::shared_ptr<GameStatus> gs;
	std::shared_ptr<ResourceManager> rm;
	std::shared_ptr<SpriteRenderer> sr;
	std::shared_ptr<IInputManager> im;

	std::shared_ptr<DebugInput> debug_im;
private:
	int writenum;

};

#endif //DEBUGMANAGER_H

