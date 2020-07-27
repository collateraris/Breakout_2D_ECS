#include <iostream>

#include <gameEngine.h>

int main()
{
    auto engine = new breakout::GameEngine();

	engine->Init();
	engine->Start();

	delete engine;
    
    std::cout << "Kinda main" << std::endl;
    return 0;
}