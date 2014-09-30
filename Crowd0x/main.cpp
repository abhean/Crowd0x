#include "DrawService.h"
#include "PedManager.h"
#include <SDL.h>
#include <iostream>

int main(int /*argc*/, char ** /*argv*/)
{
	DrawService::Init();

	PedManager::Init();

	//Our event structure
	bool quit = false;
	while (!quit)
	{
		// Events / Input
		DrawService::ProcessEvents();

		// Update
		PedManager::Update(1.0f / 30.0f);

		// Draw
		DrawService::RenderClear();

		PedManager::Draw();

		DrawService::RenderPresent();
	}

	PedManager::Done();

	DrawService::Done();

	return 0;
}