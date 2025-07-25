//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "DrawPolygonComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawPolygonComponent::DrawPolygonComponent(Actor* owner, std::vector<Vector2>& vertices, SDL_Color color, int drawOrder)
    :DrawComponent(owner)
    ,mDrawOrder(drawOrder)
    ,mVertices(vertices)
    ,mColor(color)
{
}

void DrawPolygonComponent::Draw(SDL_Renderer* renderer)
{
    if (!mIsVisible) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

    Vector2 pos = mOwner->GetPosition();
    Vector2 cameraPos = mOwner->GetGame()->GetCamera()->GetPosCamera();

    // Render vertices as lines
    for (int i = 0; i < mVertices.size() - 1; i++) {
        SDL_RenderDrawLine(renderer, pos.x + mVertices[i].x - cameraPos.x,
                           pos.y + mVertices[i].y - cameraPos.y,
                           pos.x + mVertices[i + 1].x - cameraPos.x,
                           pos.y + mVertices[i + 1].y - cameraPos.y);
    }
    SDL_RenderDrawLine(renderer, pos.x + mVertices[mVertices.size() - 1].x - cameraPos.x,
                       pos.y + mVertices[mVertices.size() - 1].y - cameraPos.y,
                       pos.x + mVertices[0].x - cameraPos.x,
                       pos.y + mVertices[0].y - cameraPos.y);
}
