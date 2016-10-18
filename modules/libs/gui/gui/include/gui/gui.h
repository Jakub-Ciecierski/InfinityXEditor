#ifndef PROJECT_GUI_H
#define PROJECT_GUI_H

#include <GLFW/glfw3.h>

namespace ifx {

class GUI {
public:

    GUI(GLFWwindow* window);
    virtual ~GUI();

    /**
     * Must be called before (at the beginning of) each Render()
     */
    void NewFrame();

    virtual void Render() = 0;
};
}

#endif //PROJECT_GUI_H
