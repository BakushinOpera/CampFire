#include "Projectile.h"
#include <iostream>


GamesEngineeringBase::Image Projectile::projImgs[Projectile::TYPE_COUNT];
int Projectile::killY = 1024;
float Projectile::speedScale = 1.0f;

projectileType Projectile::projTypes[Projectile::TYPE_COUNT] = {
	// umbrellaDmg, fireHeat, hitbox, img, speed
	{ 0.f, -10.f, {0,0,0,0}, &projImgs[Rain], 300.f },
	{ 25.f, -20.f, {0,0,0,0}, &projImgs[Hail], 220.f },
	{ 10.f, +15.f, {0,0,0,0}, &projImgs[Branch], 160.f },
};;

void Projectile::Move(float dt) {
	x += dirX * type->speed * speedScale * dt;
	y += dirY * type->speed * speedScale * dt;
	if (y - type->img->height / 2 > killY) 
	{
		active = false;
	}
}

void Projectile::LoadAssets(){
	const char* files[TYPE_COUNT] = { "assets/drop_rain.png", "assets/drop_hail.png", "assets/drop_branch.png" };
	for (int i = 0;i < TYPE_COUNT;i++) {
		if (!projImgs[i].load(files[i])) {
			std::cerr << "Failed to load projectile image: " << files[i] << '\n';
		}
		int w = projImgs[i].width;
		int h = projImgs[i].height;
		projTypes[i].hitbox = { -w / 2, -h / 2, w, h };
	}
}

void Projectile::Update(float dt){
	if (!active) return;
	Move(dt);

}

void Projectile::Draw(GamesEngineeringBase::Window& window, int camX, int camY) {
	int w = type->img->width, h = type->img->height;
	Graphics::DrawSubImg(window, *type->img, 0, 0, w, h, (int)x - w/2 - camX, (int)y - h/2 - camY);
}

bool Projectile::Collide(Characters& player) {
	Box worldBox = Box::OffsetBox(type->hitbox, x, y);
	if (Box::Overlap(GetBox(), player.GetWorldBox())) {
		player.TakeDmg(type->umbrellaDmg);   // rain is 0, with no damage
		Kill();                              // hide by the umbrella, disappeared
		return true;
	}
	return false;
}

// ProjectilePool

void ProjectilePool::DrawAll(GamesEngineeringBase::Window& window, int camX, int camY){
	for (int i = 0;i < pool_size;i++) {
		if (projectile[i].active) projectile[i].Draw(window, camX, camY);
	}
}
void ProjectilePool::CheckCollide(Characters& player) {
	for (int i = 0;i < pool_size;i++) {
		if (!projectile[i].active) continue;
		if (projectile[i].Collide(player)) continue;
	}
}