#ifndef TOROID_H
#define TOROID_H

class Boxcollider;
class Vector2;
#include "AirEnemyBase.h"

class TOROID : public AirEnemyBase 
{
public:
	TOROID() {}
	~TOROID(){}


	void Init() override;
	int Create(std::shared_ptr<IPlayer> pl,int number, int typenumber = 0) override;


	int Update(std::shared_ptr<IPlayer> pl) override;
	int UniqueUpdate(std::shared_ptr<IPlayer> pl) override;


private:

	int ActionPattern01(const Boxcollider& playerhitbox,const Vector2& playerpos);
	void ActionPattern02();
	void ActionPattern03();
};


#endif // TOROID_H