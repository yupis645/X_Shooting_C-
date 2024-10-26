#ifndef AIRENEMYBASE_H
#define AIRENEMYBASE_H

#include "EnemyBase.h"

//=================================================================================================
//							空中敵の基底クラス
//=================================================================================================
class AirEnemyBase : public EnemyBase {
public:
	AirEnemyBase() {}


	virtual int Create(std::weak_ptr<IPlayer> pl, int number) ;
	virtual int Update(std::weak_ptr<IPlayer> pl);

	~AirEnemyBase() = default;

protected:

	virtual int UniqueUpdate(std::shared_ptr<IPlayer> pl) = 0;

	virtual int AnimUpdate(int UpdateInterval);
	void CreateSetup();
	void InitPostionPattern(float x_pos = -1.0f);
	void TergetRadian(const Vector2& pos);
};


//=================================================================================================
//						初期化用のダミー派生クラス
//=================================================================================================
class AirEnemyDummy : public AirEnemyBase{
public:
	AirEnemyDummy() {}

	void Init() override {}
	int Create(std::weak_ptr<IPlayer> pl, int number)  { return 0; }
	int Update(std::weak_ptr<IPlayer> pl) { return 0; }
	int UniqueUpdate(std::shared_ptr<IPlayer> pl)  { return 0; }

	~AirEnemyDummy() = default;
};

//=================================================================================================
//							トーロイド
//=================================================================================================
class TOROID : public AirEnemyBase{
public:
	TOROID(std::weak_ptr<IPlayer> player, int num);

	void Init() override;
	int Create(std::weak_ptr<IPlayer> pl, int number) override;
	int Update(std::weak_ptr<IPlayer> pl) override;
	int UniqueUpdate(std::shared_ptr<IPlayer> pl) override;

	~TOROID() = default;

private:
	int ActionPattern01(const Boxcollider& playerhitbox, const Vector2& playerpos);
	void ActionPattern02();
	void ActionPattern03();
};

//=================================================================================================
//							タルケン
//=================================================================================================
class TORKAN : public AirEnemyBase{
public:
	TORKAN(std::weak_ptr<IPlayer> player, int num);

	void Init() override;
	int Create(std::weak_ptr<IPlayer> pl, int number) override;
	int Update(std::weak_ptr<IPlayer> pl) override;
	int UniqueUpdate(std::shared_ptr<IPlayer> pl) override;

	~TORKAN() = default;

private:
	int ActionPattern01();
	void ActionPattern02(std::shared_ptr<IPlayer> pl);
	void ActionPattern03();


};


//=================================================================================================
//						ギドスパリオ
//=================================================================================================
class GIDDOSPARIO : public AirEnemyBase{
public:
	GIDDOSPARIO(std::weak_ptr<IPlayer> player, int num);

	void Init() override;
	int Create(std::weak_ptr<IPlayer> pl, int number) override;
	int Update(std::weak_ptr<IPlayer> pl) override;
	int UniqueUpdate(std::shared_ptr<IPlayer> pl) override;

	~GIDDOSPARIO() = default;


};

#endif // AIRENEMYBASE_H
