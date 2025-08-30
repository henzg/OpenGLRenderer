/* OpenGL Enditor
* Designed by Zachary Henry
 * Start of proj: Aug13,2025
 * Learning via learnopengl.com and the cherno
 * Made with nvim, g++, and other linux tools
 */
#include "Renderer.h"

int main()
{
    try 
    {
        const std::string myTitle = "zacstack.dev";
        Renderer program(myTitle, 1080, 720);
        program.Init();
        program.Run();
        program.Cleanup();
    } 
    catch (const std::runtime_error& e)
    {
        std::cerr << "Renderer init failed: " << e.what() << "\n";
        return -1;
    }

    return 0;
}
