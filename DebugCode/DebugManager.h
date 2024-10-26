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
class DebugPlayer;
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
	std::shared_ptr<IGameManager> gm;
	std::shared_ptr<GameStatus> gs;
	std::shared_ptr<ResourceManager> rm;
	std::shared_ptr<SpriteRenderer> sr;
	std::shared_ptr<IInputManager> im;

	std::shared_ptr<DebugInput> debug_im;
	std::shared_ptr<DebugTexture> debug_tex;
	std::shared_ptr<DebugPlayer> debug_player;
private:
	int writenum;

};

#endif //DEBUGMANAGER_H

