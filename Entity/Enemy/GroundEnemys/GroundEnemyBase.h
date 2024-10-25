#ifndef GROUNDENEMYBASE_H
#define GROUNDENEMYBASE_H

class IPlayer;

#include "EnemyBase.h"

class GroundEnemyBase : public EnemyBase {
public:
	virtual int Create(std::weak_ptr<IPlayer> pl, int number);


	virtual int Update(std::weak_ptr<IPlayer> pl);



protected:
	virtual int UniqueUpdate(std::weak_ptr<IPlayer> pl) = 0;

	virtual int AnimUpdate(int UpdateInterval);
	void CreateSetup();
};


class GroundEnemyDummy : public GroundEnemyBase
{
public:
	GroundEnemyDummy() {}
	~GroundEnemyDummy() = default;


	void Init() override {}
	int Create(std::weak_ptr<IPlayer> pl, int number) override { return 0; }


	int Update(std::weak_ptr<IPlayer> pl) override { return 0; }


private:
	int UniqueUpdate(std::weak_ptr<IPlayer> pl) override { return 0; }

};

#endif // GROUNDENEMYBASE_H