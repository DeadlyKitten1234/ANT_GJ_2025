#pragma once
#include <Farmer.h>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "GameState.h"

class Hole {
public:
	Hole() { }
	~Hole() { }

	void init(SDL_Renderer* renderer, int screenW, int screenH) {
		bgrTexture = loadTexture(Config::holeBackgroundPath, renderer);
		floorTexture = loadTexture(Config::holeFloorPath, renderer);
		gripTexture = loadTexture(Config::gripPath, renderer);
		topTexture = loadTexture(Config::holeTop, renderer);
		catTexture = loadTexture(Config::catPath, renderer);
		farmer.init(renderer, screenW, screenH);
		Config::readLevel(grips, farmer.getXRef(), farmer.getYRef(), fieldW, fieldH, tileSize);
		lastGripY = farmer.getY();
		stX = farmer.getX();
		stY = farmer.getY();
		lastGrip = { -1, -1 };
	}
	void reset() {
		farmer.setX(stX);
		farmer.setY(stY);
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
				SDL_Rect rect
				    = {x * tileSize,
				       (y - farmer.getY()) * tileSize + Presenter::SCREEN_H / 2,
				       tileSize, tileSize};
				SDL_RenderCopy(renderer, floorTexture, NULL, &rect);
			}
		}
		SDL_Rect rect = {fieldW / 2 * tileSize,
		                 (fieldH - 1 - farmer.getY()) * tileSize + Presenter::SCREEN_H / 2,
		                 tileSize, tileSize};
		SDL_RenderCopy(renderer, catTexture, NULL, &rect);
		for (int2 gr : grips) {
			SDL_Rect newRect = { gr.x * tileSize, gr.y * tileSize, tileSize, tileSize };
			newRect.y += Presenter::SCREEN_H / 2 - farmer.getY() * tileSize;
			Presenter::drawObject(gripTexture, &newRect);
		}
		farmer.draw(renderer, tileSize);
	}
	void update(const InputManager& inputManager, GameState& gameState) {
		if (farmer.isHanging()) {
			lastGripY = farmer.getY();
		} else {
			if (farmer.getY() - lastGripY >= deathYDif) {
				gameState = GameState::Lose;
				return;
			}
		}
		for (int2 gr : grips) {
			SDL_Rect collisionRect = { gr.x * tileSize, gr.y * tileSize, tileSize, tileSize };
			collisionRect.y += Presenter::SCREEN_H / 2 - farmer.getY() * tileSize;
			collisionRect.x += collisionRect.w / 4;
			collisionRect.y += collisionRect.h / 4;
			collisionRect.w /= 2;
			collisionRect.h /= 2;
			if (gr == lastGrip) { 
				if (!rectCollision(farmer.getCollisionRect(tileSize), collisionRect)) {
					lastGrip = int2(-1, -1);
				} else {
					continue;
				}
			}

			if (rectCollision(farmer.getCollisionRect(tileSize), collisionRect)) {
				farmer.setHanging();
				farmer.setX(gr.x + 0.5);
				farmer.setY(gr.y + 0.5);
				lastGrip = gr;
				lastGripY = gr.y;
			}
		}
		farmer.update(inputManager);
		if (farmer.getY() > fieldH) {
			gameState = GameState::Win;
			return;
		}
	}

private:
	SDL_Texture* bgrTexture;
	SDL_Texture* gripTexture;
	SDL_Texture* floorTexture;
	SDL_Texture* topTexture;
	SDL_Texture* catTexture;
	Farmer farmer;
	int fieldW;
	int fieldH;
	int tileSize;
	int stX, stY;
	float deathYDif = 6;
	float lastGripY;
	int2 lastGrip;

	std::vector<int2> grips;
};