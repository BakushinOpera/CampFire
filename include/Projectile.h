#pragma once
#include "GamesEngineeringBase.h" 
#include "Box.h" 
#include "Characters.h" 
#include "Graphics.h"
#include "FireSeedManager.h"


struct projectileType {
	float umbrellaDmg;
	float fireHeat;
	Box hitbox;
	GamesEngineeringBase::Image* img;
	float speed;
};

enum DropType { Rain = 0, Hail = 1, Branch = 2 };

class Projectile {
private:
	float x, y, dirX, dirY, timeleft;
public:
	bool active = false;

	static const int TYPE_COUNT = 3;
	static GamesEngineeringBase::Image projImgs[TYPE_COUNT];
	static projectileType projTypes[TYPE_COUNT];
	static int killY;
	static float speedScale;   // Falling speed multiplier, increases over time

	const projectileType* type = nullptr;

	// variables for free list in object pool
	Projectile* next;
	bool inFreeList = true;

	Projectile() :timeleft(0) {}

	void init(float x_, float y_, float dirX_, float dirY_,
		      const projectileType* t)
	{
		active = true;
		x = x_, y = y_, dirX = dirX_, dirY = dirY_, type = t;
	}

	Projectile* getNext() const { return next; }
	void setNext(Projectile* next_) { next = next_; }
	
	void Move(float dt);
	// load all assets once
	static void LoadAssets();
	void Update(float dt);
	void Draw(GamesEngineeringBase::Window& window, int camX, int camY);
	bool Collide(Characters& player);
	bool HitFire(FireSeedManager& fire);
	Box GetBox() const { return Box::OffsetBox(type->hitbox, x, y); }
	void Kill() { active = false; }
};
class ProjectilePool {
private:
	static const int pool_size = 128;
	Projectile projectile[pool_size];
	Projectile* firstAvailable_;
	int full_cnt = 0;
public:
	ProjectilePool() {
		firstAvailable_ = &projectile[0];

		for (int i = 0;i < pool_size - 1;i++) {
			projectile[i].setNext(&projectile[i + 1]);
		}
		projectile[pool_size - 1].setNext(NULL);
	}
	void ResetFreeList() {
		firstAvailable_ = &projectile[0];

		for (int i = 0;i < pool_size - 1;i++) {
			projectile[i].setNext(&projectile[i + 1]);
			projectile[i].inFreeList = true;
		}
		projectile[pool_size - 1].setNext(NULL);
		projectile[pool_size - 1].inFreeList = true;
	}
	void Clear() {// clear all while swtiching levels.
		for (int i = 0;i < pool_size;i++) {
			projectile[i].active = false;
		}
		ResetFreeList();
	}
	void create(float x, float y, float dirX, float dirY,
		        const projectileType* t) 
	{
		if (firstAvailable_ == NULL) {
			Release(&projectile[full_cnt % pool_size]);
			full_cnt++;
		}

		Projectile* newProj = firstAvailable_;
		firstAvailable_ = newProj->getNext();
		newProj->init(x, y, dirX, dirY, t);
		newProj->inFreeList = false;
	}
	void UpdateAll(float dt) {
		for (int i = 0;i < pool_size;i++) {
			if (!projectile[i].active && !projectile[i].inFreeList) Release(&projectile[i]);
			if (!projectile[i].active && projectile[i].inFreeList) continue;
			projectile[i].Update(dt);
		}
	}
	void DrawAll(GamesEngineeringBase::Window& window, int camX, int camY);
	void CheckCollide(Characters& player);
	void CheckFireHit(FireSeedManager& fire);
	void Release(Projectile* proj) {
		if (proj == NULL || proj->inFreeList) return;
		// put the available slot back to pool
		proj->active = false;
		proj->setNext(firstAvailable_);
		firstAvailable_ = proj;
		proj->inFreeList = true;
	}
	int getCapacity() { return pool_size; }
	Projectile* Get(int i) { return &projectile[i]; }
};