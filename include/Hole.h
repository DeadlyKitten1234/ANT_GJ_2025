#pragma once
#include "Farmer.h"
#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "HealthBar.h"
#include "GameState.h"
#include "Grip.h"

class Hole {
public:
	Hole() { }
	~Hole() {
		SDL_DestroyTexture(bgrTexture);
		SDL_DestroyTexture(floorTexture);
		SDL_DestroyTexture(gripTexture);
		SDL_DestroyTexture(topTexture);
		SDL_DestroyTexture(catTexture);
		SDL_DestroyTexture(slipperyTexture);
		SDL_DestroyTexture(checkpointTexture);
	}

	void init(SDL_Renderer* renderer, int screenW, int screenH) {
		bgrTexture = loadTexture(Config::holeBackgroundPath, renderer);
		floorTexture = loadTexture(Config::holeFloorPath, renderer);
		gripTexture = loadTexture(Config::gripPath, renderer);
		topTexture = loadTexture(Config::holeTop, renderer);
		catTexture = loadTexture(Config::catPath, renderer);
		slipperyTexture = loadTexture(Config::slipperyGripPath, renderer);
		checkpointTexture = loadTexture(Config::checkpointGripPath, renderer);
		farmer.init(renderer, screenW, screenH);
		health.init(renderer);
		Config::readLevel(grips, farmer.getXRef(), farmer.getYRef(), fieldW, fieldH, tileSize);
		lastGripY = farmer.getY();
		stX = farmer.getX();
		stY = farmer.getY();
		lastGrip = { -1, -1 };
		ticksHanging = 0;
		isOnSlippery = false;
		lastCheckpoint = { -1, -1 };
	}
	void reset(bool fromStart) {
		if (fromStart) {
			lastCheckpoint = { -1, -1 };
			farmer.setX(stX);
			farmer.setY(stY);
			health.setLives(HealthBar::HEARTS_COUNT);
		} else {
			farmer.setX(lastCheckpoint.x);
			farmer.setY(lastCheckpoint.y);
		}
		lastGrip = { -1, -1 };
		lastGripY = farmer.getY();
		ticksHanging = 0;
		isOnSlippery = false;
	}

	bool isFarmerDead() {
		return farmer.getY() - lastGripY >= deathYDif;
	}

	void draw(SDL_Renderer* renderer) {
		SDL_Rect topRect = { 0, -farmer.getY() * tileSize - Presenter::SCREEN_H / 2, Presenter::SCREEN_W, Presenter::SCREEN_H };
		Presenter::drawObject(topTexture, &topRect);
		for (int x = 0; x < fieldW + 1; x++) {
			for (int y = 0; y < fieldH; y++) {
				SDL_Rect rect = {
				    x * tileSize,
				    (y - farmer.getY()) * tileSize + Presenter::SCREEN_H / 2,
					tileSize,
					tileSize
				};
				SDL_RenderCopy(renderer, bgrTexture, NULL, &rect);
			}
		}
		for (int x = 0; x < fieldW + 1; x++) {
			for (int y = fieldH; y < fieldH + 20; y++) {
				SDL_Rect rect = {x * tileSize,
				       (y - farmer.getY()) * tileSize + Presenter::SCREEN_H / 2,
				       tileSize, tileSize};
				SDL_RenderCopy(renderer, floorTexture, NULL, &rect);
			}
		}
		SDL_Rect rect = {fieldW / 2 * tileSize,
		                 (fieldH - 1 - farmer.getY()) * tileSize + Presenter::SCREEN_H / 2,
		                 tileSize, tileSize};
		SDL_RenderCopy(renderer, catTexture, NULL, &rect);
		for (Grip gr : grips) {
			SDL_Rect newRect = { gr.pos.x * tileSize, gr.pos.y * tileSize, tileSize, tileSize };
			newRect.y += Presenter::SCREEN_H / 2 - farmer.getY() * tileSize;
			Presenter::drawObject((gr.isCheckpoint ? checkpointTexture : (gr.isSlippery ? slipperyTexture : gripTexture)), &newRect);
		}
		farmer.draw(renderer, isFarmerDead(), tileSize);
		health.render(renderer);
	}
	void update(const InputManager& inputManager, GameState& gameState) {
		if (farmer.isHanging()) {
			lastGripY = farmer.getY();
			ticksHanging++;
		} else {
			ticksHanging = 0;
		}
		if (isOnSlippery && ticksHanging > 35) {
			farmer.setHanging(false);
		}
		if (!isFarmerDead()) {
			for (Grip gr : grips) {
				SDL_Rect collisionRect
				    = {gr.pos.x * tileSize, gr.pos.y * tileSize, tileSize, tileSize};
				collisionRect.y
				    += Presenter::SCREEN_H / 2 - farmer.getY() * tileSize;
				collisionRect.x += collisionRect.w / 4;
				collisionRect.y += collisionRect.h / 4;
				collisionRect.w /= 2;
				collisionRect.h /= 2;
				if (gr.pos == lastGrip) {
					if (!rectCollision(farmer.getCollisionRect(tileSize), collisionRect)) {
						lastGrip = int2(-1, -1);
					} else {
						continue;
					}
				}

				if (rectCollision(farmer.getCollisionRect(tileSize), collisionRect)) {
					farmer.setHanging(true);
					farmer.setX(gr.pos.x + 0.5);
					farmer.setY(gr.pos.y + 0.5);
					lastGrip = gr.pos;
					lastGripY = gr.pos.y;
					isOnSlippery = gr.isSlippery;
					if (gr.isCheckpoint) {
						lastCheckpoint = gr.pos;
					}
				}
			}
		}
		farmer.update(inputManager, isFarmerDead());
		if (farmer.getY() + 2.5 > fieldH) {
			if (!isFarmerDead()) {
				gameState = GameState::Win;
			} else {
				if (health.getLives() == 1) {
					gameState = GameState::Lose;
				} else {
					health.decreaseLives();
					reset(false);
				}
			}
			return;
		}
	}

private:
	SDL_Texture* bgrTexture;
	SDL_Texture* gripTexture;
	SDL_Texture* slipperyTexture;
	SDL_Texture* checkpointTexture;
	SDL_Texture* floorTexture;
	SDL_Texture* topTexture;
	SDL_Texture* catTexture;
	Farmer farmer;
	int fieldW;
	int fieldH;
	int tileSize;
	int ticksHanging;
	bool isOnSlippery;
	int stX, stY;
	float deathYDif = 6;
	float lastGripY;
	int2 lastGrip;
	int2 lastCheckpoint;
	HealthBar health;

	std::vector<Grip> grips;
};