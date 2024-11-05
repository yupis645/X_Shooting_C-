#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

class DIContainer;
class IGameManager;
class ResourceManager;
class SpriteRenderer;
class GameStatus;
class IInputManager;

class DebugInput;
class DebugTexture;
class BoxCollider;
class Vector2;

#include <iostream>
#include "common.h"
#include "DebugTexture.h"


class DebugManager{
public:
	DebugManager(std::shared_ptr<DIContainer> con);

	void DrawInputFrag();

	void DebugDrawTexture(DebugTexture::DebugSelectDraw draw);

	void DrawBoxcollider(const Boxcollider);

	void DrawPsotion(const Vector2);


	void DrawHitBox(const GameObject& obj,int r,int g,int b,bool frame);

	~DebugManager() = default;

	std::shared_ptr<DIContainer> container;

	std::shared_ptr<DebugInput> debug_im;
	std::shared_ptr<DebugTexture> debug_tex;
private:
	int writenum;

};

#endif //DEBUGMANAGER_H

