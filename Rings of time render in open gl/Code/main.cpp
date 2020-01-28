#include "MyDemo.hpp"
#include <tyga/Application.hpp>
#include <crtdbg.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
    // enable debug memory checks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    tyga::Application::run(std::make_shared<MyDemo>());

    // pause to display any console messages
    system("PAUSE");
    return 0;
}
