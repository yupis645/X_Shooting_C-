#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

class IPlayer;


class Boxcollider;
class IBulletsManager;
class IEnemysManager;



class CollisionManager {
public:
	CollisionManager();
    ~CollisionManager() = default;

    bool CollisionUpdate(std::weak_ptr<IBulletsManager> bullets_, std::weak_ptr<IEnemysManager> enemys_, std::weak_ptr<IPlayer> player_);

private :
    template <typename T1,typename T2>
    bool ActiveCheck(T1 a,T2 b);
};
#endif ///COLLISIONMANAGER_H

template <typename T1, typename T2>
inline bool CollisionManager::ActiveCheck(T1 a, T2 b)
{
		if (T2->GetActive()) {
			if (T1->GetHitbox().BoxCollision(T2->GetHitbox()))
			{
				return true;
			}
		}

    return false;
}
