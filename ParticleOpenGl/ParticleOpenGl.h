#include "Application.h"


int main(int argc, char** argv) 
{
    auto app = std::make_unique<Application>("Title");
    app->loop();
    return 0;
}

