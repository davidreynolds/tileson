
#include "SfmlDemoManager.h"

int main()
{
    SfmlDemoManager demo;
    demo.initialize({400 * 3, 240 * 3}, {600, 360});
    //if(demo.parseMap())
    if(demo.parseMap() && demo.parseProject())
    {
        demo.run();
    }
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}