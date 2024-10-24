

#include "DebugManager.h"

#include "conioex.h"
#include "InputManager.h"
#include "DIContainer.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include "DebugInput.h"
#include "Geometry.h"

DebugManager::DebugManager(std::shared_ptr<DIContainer> con) :
	container(con),
	gm(con->Create<IGameManager>()),
	gs(con->Create<GameStatus>()),
	rm(con->Create<ResourceManager>()),
	sr(con->Create<SpriteRenderer>()),
	im(con->Create<IInputManager>())
{
	debug_im = std::make_shared<DebugInput>(im);
	writenum = 3;
}

void DebugManager::DrawInputFrag()
{
	debug_im->InputPritf();
}

void DebugManager::DrawHitBox(const Boxcollider box)
{
	DrawRect(static_cast<int>(box.left), static_cast<int>(box.top), static_cast<int>(box.right), static_cast<int>(box.bottom), DWRGB(0, 255, 255), true);	//“–‚½‚è”»’è

}
void DebugManager::DrawCenterPos(const Vector2 pos)
{
	DrawRect(static_cast<int>(pos.x )- 1, static_cast<int>(pos.y )- 1, static_cast<int>(pos.x )+ 1, static_cast<int>(pos.y )+ 1, DWRGB(255, 255, 255), true);	//’†S“_


}