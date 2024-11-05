

#include "DebugManager.h"

#include "conioex.h"
#include "InputManager.h"
#include "DIContainer.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include "DebugInput.h"
#include "DebugTexture.h"

DebugManager::DebugManager(std::shared_ptr<DIContainer> con) :
	container(con)
{
	debug_im = std::make_shared<DebugInput>(container);
	debug_tex = std::make_shared<DebugTexture>(con->Create<ResourceManager>(),con->Create<SpriteRenderer>());
	writenum = 3;
}

void DebugManager::DrawInputFrag()
{
	debug_im->InputPritf();
}

void DebugManager::DebugDrawTexture(DebugTexture::DebugSelectDraw draw)
{
	debug_tex->DebugScreenDrawTexture(draw);
}

void DebugManager::DrawBoxcollider(const Boxcollider box)
{
	DrawRect(static_cast<int>(box.left), static_cast<int>(box.top), static_cast<int>(box.right), static_cast<int>(box.bottom), DWRGB(0, 255, 255), true);	//当たり判定

}
void DebugManager::DrawPsotion(const Vector2 pos)
{
	DrawRect(static_cast<int>(pos.x )- 1, static_cast<int>(pos.y )- 1, static_cast<int>(pos.x )+ 1, static_cast<int>(pos.y )+ 1, DWRGB(255, 255, 255), true);	//中心点


}

void DebugManager::DrawHitBox(const GameObject& obj, int r, int g, int b, bool frame)
{
	int left = static_cast<int>(obj.GetHitbox().left);
	int top = static_cast<int>(obj.GetHitbox().top);
	int right = static_cast<int>(obj.GetHitbox().right);
	int bottom = static_cast<int>(obj.GetHitbox().bottom);

	int x = static_cast<int>(obj.GetPosition().x);
	int y = static_cast<int>(obj.GetPosition().y);

	DrawRect(left, top, right, bottom, DWRGB(r, g, b), frame);								//当たり判定
	DrawRect(x - 1, y - 1, x + 1, y + 1, DWRGB(255, 255, 255), true);	//中心点

}
