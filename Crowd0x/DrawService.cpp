#include "DrawService.h"
#include "Transform.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <ctime>

namespace DrawService
{

namespace // private variables
{

SDL_Window* s_pWindow = nullptr;
SDL_Renderer* s_pRenderer = nullptr;
TTF_Font* s_pDebugFont = nullptr;

std::clock_t start;
unsigned s_frameCount = 0;
float s_elapsedTime = 0.0f;

Point2s16 ViewportCoordsToScreen(const Point2f& ptPosition)
{
	assert(s_pWindow);

	int w, h;
	SDL_GetWindowSize(s_pWindow, &w, &h);

	Point2s16 ptScreenPos { static_cast<s16>(floor(ptPosition[0] * w)), static_cast<s16>(floor(ptPosition[1] * h)) };

	return ptScreenPos;
}

} // private variables

namespace // internal functions
{

void OnFatalError(const char* _pszError)
{
	std::cout << _pszError << " Error: " << SDL_GetError() << std::endl;
	Done();
}

void DestroyRenderer()
{
	if (s_pRenderer)
	{
		SDL_DestroyRenderer(s_pRenderer);
		s_pRenderer = nullptr;
	}
}

void DestroyWindow()
{
	if (s_pWindow)
	{
		SDL_DestroyWindow(s_pWindow);
		s_pWindow = nullptr;
	}
}

} // internal functions


int Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		OnFatalError("SDL_Init");
		return 1;
	}

	int iFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int iInitted = IMG_Init(iFlags);
	if ((iInitted & iFlags) != iFlags)
	{
		OnFatalError("IMG_Init");
		return 1;
	}

	if (TTF_Init() == -1)
	{
		OnFatalError("TTF_Init");
		return 1;
	}

	s_pWindow = SDL_CreateWindow("Hello World!", 100, 100, 640, 640, SDL_WINDOW_SHOWN);
	if (s_pWindow == nullptr)
	{
		OnFatalError("SDL_CreateWindow");
		return 1;
	}

	s_pRenderer = SDL_CreateRenderer(s_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (s_pRenderer == nullptr)
	{
		OnFatalError("SDL_CreateRenderer");
		return 1;
	}

	s_pDebugFont = TTF_OpenFont("../data/FreeSans.ttf", 16); //this opens a font style and sets a size
	if (s_pDebugFont == nullptr)
	{
		OnFatalError("TTF_OpenFont");
		return 1;
	}

	start = std::clock();

	return 0;
}

void Done()
{
	DestroyRenderer(),
	DestroyWindow();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void ProcessEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
		}
		if (e.type == SDL_KEYDOWN)
		{
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
		}
	}

}

void RenderClear()
{
	SDL_SetRenderDrawColor(s_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(s_pRenderer);
}

void RenderPresent()
{
	double diff = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	++s_frameCount;

	char szFPSMessage[128];
	sprintf_s(szFPSMessage, "FPS: %5.2f", s_frameCount / diff);
	SDL_Color White = { 255, 255, 255 }; 
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(s_pDebugFont, szFPSMessage, White); 
	SDL_Texture* Message = SDL_CreateTextureFromSurface(s_pRenderer, surfaceMessage); 
	SDL_Rect Message_rect;
	Message_rect.x = 0;
	Message_rect.y = 0;
	TTF_SizeText(s_pDebugFont, szFPSMessage, &Message_rect.w, &Message_rect.h);

	SDL_RenderCopy(s_pRenderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);


	SDL_RenderPresent(s_pRenderer);
}

void DrawTriangle(const STransform& transform, float height, float base, u32 color)
{
	const float fHalfBase = base * 0.5f;
	const float fHalfHeight = height * 0.5f;

	Point2s16 ptScreenCoords0 = ViewportCoordsToScreen(transform.Position + cml::rotate_vector_2D(Vec2f(-fHalfBase, -fHalfHeight), transform.Rotation));
	Point2s16 ptScreenCoords1 = ViewportCoordsToScreen(transform.Position + cml::rotate_vector_2D(Vec2f(fHalfBase, -fHalfHeight), transform.Rotation));
	Point2s16 ptScreenCoords2 = ViewportCoordsToScreen(transform.Position + cml::rotate_vector_2D(Vec2f(0.0f, fHalfHeight), transform.Rotation));

	SDL_SetRenderDrawColor(s_pRenderer, color >> 24 & 0xFF, color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF);
	SDL_RenderDrawLine(s_pRenderer, ptScreenCoords0[0], ptScreenCoords0[1], ptScreenCoords1[0], ptScreenCoords1[1]);
	SDL_RenderDrawLine(s_pRenderer, ptScreenCoords1[0], ptScreenCoords1[1], ptScreenCoords2[0], ptScreenCoords2[1]);
	SDL_RenderDrawLine(s_pRenderer, ptScreenCoords2[0], ptScreenCoords2[1], ptScreenCoords0[0], ptScreenCoords0[1]);
}

void DrawCircle(const Point2f& position, float radius, u32 color)
{
	const u32 numSegments = 32;

	SDL_SetRenderDrawColor(s_pRenderer, color >> 24 & 0xFF, color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF);

	Point2s16 segment0 = ViewportCoordsToScreen(position + Vec2f(0.0f, radius));
	for (u32 uSegmentIdx = 1; uSegmentIdx <= numSegments; ++uSegmentIdx)
	{
		const float fAngle = 3.14159f * 2.0f * static_cast<float>(uSegmentIdx) / numSegments;
		Point2s16 segment1 = ViewportCoordsToScreen(position + cml::rotate_vector_2D(Vec2f(0.0f, radius), fAngle));
		SDL_RenderDrawLine(s_pRenderer, segment0[0], segment0[1], segment1[0], segment1[1]);
		segment0 = segment1;
	}
}

void TestInit()
{
	std::string imagePath = "../data/hello.bmp";

	SDL_RenderClear(s_pRenderer);

	//SDL_Texture* pTexture = IMG_LoadTexture(s_pRenderer, imagePath.c_str());
	//if (pTexture)
	//{
	//	SDL_RenderCopy(s_pRenderer, pTexture, NULL, NULL);
	//}
	//else
	//{
	//	OnFatalError("IMG_LoadTexture");
	//}

	SDL_RenderPresent(s_pRenderer);
	SDL_Delay(5000);
}

}
