#include "UIFont.h"
#include <vector>
#include <SDL_image.h>

UIFont::UIFont(SDL_Renderer* renderer)
    :mRenderer(renderer)
{

}

UIFont::~UIFont()
{

}

bool UIFont::Load(const std::string& fileName)
{
	// We support these font sizes
	std::vector<int> fontSizes = {8,  9,  10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32,
								  34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64, 68, 72};

    // --------------
    // TODO - PARTE 1-1
    // --------------

    // TODO 1.: Percorra a lista de tamanhos de fonte e carregue cada fonte usando TTF_OpenFont.
    //  Se alguma fonte falhar ao carregar, registre um erro e retorne false. Caso contrário,
    //  armazene a fonte carregada no mapa mFontData com o tamanho como chave.
    //  --------------
	for (int size: fontSizes) {
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (!font) {
			SDL_Log("Erro ao carregar fonte tamanho %d: %s", size, TTF_GetError());
			return false;
		}
		mFontData[size] = font;
	}
	return true;
}

void UIFont::Unload()
{
    // --------------
    // TODO - PARTE 1-1
    // --------------

    // TODO 2.: Percorra o mapa mFontData e feche cada fonte usando TTF_CloseFont.
    //  Em seguida, limpe o mapa mFontData.
	for (auto& pair : mFontData) {
		if (pair.second) {
			TTF_CloseFont(pair.second);
		}
	}
	mFontData.clear();
}

SDL_Texture* UIFont::RenderText(const std::string& text, const Vector3& color /*= Color::White*/,
                                int pointSize /*= 24*/, unsigned wrapLength /*= 900*/)
{
    if(!mRenderer)
    {
        SDL_Log("Renderer is null. Can't Render Text!");
        return nullptr;
    }

	// Convert to SDL_Color
	SDL_Color sdlColor;

	// Swap red and blue so we get RGBA instead of BGRA
	sdlColor.b = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.r = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

    // --------------
    // TODO - PARTE 1-1
    // --------------

    // TODO 3.1: Verifique se o tamanho do ponto (pointSize) é suportado, ou seja, se está presente no mapa mFontData.
    //  Se o tamanho do ponto for suportado, use TTF_RenderUTF8_Blended_Wrapped para renderizar o texto em uma superfície
    //  SDL_Surface. Se a superfície for criada com sucesso, continue para o próximo passo. Caso contrário, registre um
    //  erro e retorne nullptr.
	auto it = mFontData.find(pointSize);
	if (it == mFontData.end())
	{
		if (mFontData.empty())
		{
			SDL_Log("Nenhuma fonte disponível em mFontData!");
			return nullptr;
		}

		// Encontre o tamanho mais próximo
		int closestSize = -1;
		int smallestDiff = std::numeric_limits<int>::max();

		for (const auto& pair : mFontData)
		{
			int size = pair.first;
			int diff = std::abs(size - pointSize);
			if (diff < smallestDiff)
			{
				smallestDiff = diff;
				closestSize = size;
			}
		}

		// SDL_Log("Tamanho de fonte %d não suportado! Usando tamanho mais próximo: %d", pointSize, closestSize);
		it = mFontData.find(closestSize);
	}

	TTF_Font* font = it->second;

	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), sdlColor, wrapLength);
	if (!surface)
	{
		SDL_Log("Falha ao renderizar texto: %s", TTF_GetError());
		return nullptr;
	}

    //  TODO 3.2: Crie uma textura SDL_Texture a partir da superfície retornada por TTF_RenderUTF8_Blended_Wrapped.
    //   Se a criação da textura falhar, registre um erro e retorne nullptr. Caso contrário, retorne a textura criada.
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface); // Libera a superfície independentemente do sucesso

	if (!texture)
	{
		SDL_Log("Falha ao criar textura a partir do texto: %s", SDL_GetError());
		return nullptr;
	}

	return texture;
}
