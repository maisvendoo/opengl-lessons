#include    <glad/glad.h>
#include    <GLFW/glfw3.h>

#include    <iostream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void resize_callback(GLFWwindow *window, int width, int height)
{
    (void) window;

    glViewport(0, 0, width, height);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280,
                                          720,
                                          "Hello, modern OpenGL!",
                                          nullptr,
                                          nullptr);

    if (window == nullptr)
    {
        std::cout << "Error: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, resize_callback);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
