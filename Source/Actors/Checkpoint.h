//
// Created by roger on 18/06/2025.
//

#pragma once

#include "Actor.h"
#include "../Game.h"

class Checkpoint : public Actor
{
public:
    Checkpoint(class Game* game, float width, float height);

    void OnProcessInput(const Uint8* keyState, SDL_GameController &controller) override;
    void OnUpdate(float deltaTime) override;

    void ChangeResolution(float oldScale, float newScale) override;

private:
    float mWidth;
    float mHeight;

    bool mStoreOpened;

    class DrawPolygonComponent* mDrawPolygonComponent;
    class AABBComponent *mAABBComponent;
};

