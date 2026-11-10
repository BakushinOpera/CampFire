#include "Projectile.h"


GamesEngineeringBase::Image Projectile::projImgs[2];

projectileType Projectile::projTypes[2] = {
	//damage, hitbox, img
	{ 15.f,{ -4, -1, 8, 3 } , &projImgs[0] },
	{ 8.f, { -4, -1, 8, 3 }  , &projImgs[1] }
};

void Projectile::Move(float dt) {
	if (timeleft <= 0) return;
	timeleft -= dt;
	//x += dirX * type->speed * dt;
	//y += dirY * type->speed * dt;
}

void Projectile::LoadAssets(){

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
	if (Box::Overlap(Box::OffsetBox(player.hurtbox, player.x, player.y), worldBox)) {
		player.TakeDmg(type->damage);
		active = false;
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