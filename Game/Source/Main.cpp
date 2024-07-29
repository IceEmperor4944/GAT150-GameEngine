#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[]) {
	g_engine.Initilize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		// clear screen
		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();

		PS.Draw(RENDERER);

		RENDERER.EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}