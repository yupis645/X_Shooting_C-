#ifndef DEBUGPLAYER_H
#define DEBUGPLAYER_H


#include <iostream>
#include "conioex.h"
#include "IPlayer.h"

class DebugPlayer{
public :
	DebugPlayer(std::shared_ptr<IPlayer> pl):player_(pl) {}
	~DebugPlayer() = default;

	void DrawPos(bool is)
	{
		if (is) {
			int left = static_cast<int>(player_->GetHitbox().left);
			int top = static_cast<int>(player_->GetHitbox().top);
			int right = static_cast<int>(player_->GetHitbox().right);
			int bottom = static_cast<int>(player_->GetHitbox().bottom);

			int x = static_cast<int>(player_->GetPosition().x);
			int y = static_cast<int>(player_->GetPosition().y);



			DrawRect(left, top, right, bottom, DWRGB(255, 0, 0), true);								//ìñÇΩÇËîªíË
			DrawRect(x - 1, y - 1, x + 1, y + 1, DWRGB(255, 255, 255), true);	//íÜêSì_
			//DrawRect(_p.sight_hitbox.left, _p.sight_hitbox.top, _p.sight_hitbox.right, _p.sight_hitbox.bottom, DWRGB(0, 255, 255), false);	//ìñÇΩÇËîªíË

		}
	}

	void DrawHitbox() {

	}

	std::shared_ptr<IPlayer> player_;
};

#endif //DEBUGPLAYER_H
