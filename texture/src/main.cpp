#include    <glad/glad.h>
#include    <GLFW/glfw3.h>
#include    <stb_image.h>

#include    <iostream>
#include    <cmath>

#include    "shader.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 800;

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
    // Инициализируем GLFW
    glfwInit();
    // Устанавливаем используемую версию OpenGL и профиль
    // (OpenGL 3.3 Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создаем экземпляр окна приложения
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          "Texture example",
                                          nullptr,
                                          nullptr);

    if (window == nullptr)
    {
        std::cout << "Error: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Создаем контекст отображения (контекст окна, связанный с OpenGL)
    glfwMakeContextCurrent(window);

    // Инициализируем GLAD - загрузчик указателей на требуемые нам
    // функции OpenGL
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Устанавливаем функкцию обратного вызова (callback)
    // регулизующую размер области отрисовки, при изменении
    // размеров окна
    glfwSetFramebufferSizeCallback(window, resize_callback);

    // Задаем массив вершин, каждой вершине присваиваем дополнительный
    // атрибут - цвет
    GLfloat vertices[] = {
       0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
       0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      -0.5,  -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f
    };

    GLuint indices[] = {
      0, 1, 2,
      2, 1, 3
    };

    // Создаем объект буфера вершин (Vertex Buffer OBject - VBO)
    GLuint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Загружаем и подготавливаем текстуру
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../sources/resources/img/wall.jpg",
                                    &width, &height, &nrChannels, 0);

    // Создаем один текстурный объект
    GLuint texture1;
    glGenTextures(1, &texture1);

    // Связываем текстурный объект с конкретным типамо текстуры - 2D-текстура
    glBindTexture(GL_TEXTURE_2D, texture1);

    // Указываем способ наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Указываем способ фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data != nullptr)
    {
        // Генерируем текстуру
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB,
                     width,
                     height,
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     data);

        // Генерируем mipmap-уровни
        glGenerateMipmap(GL_TEXTURE_2D);

        // Оcвобождаем изображение
        stbi_image_free(data);
    }

    // Создаем второй текстурный объект
    GLuint texture2;
    glGenTextures(1, &texture2);

    // Связываем текстурный объект с конкретным типамо текстуры - 2D-текстура
    glBindTexture(GL_TEXTURE_2D, texture2);

    // Указываем способ наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Указываем способ фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Переворачиваем PNG перед загрузкой
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../sources/resources/img/awesomeface.png",
                     &width, &height, &nrChannels, 0);

    if (data !=  nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width,
                     height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     data);

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    // Загружаем и обрабатываем шейдеры
    Shader ourShader("../sources/resources/shaders/face.vert",
                     "../sources/resources/shaders/face.frag");

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // Главный цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        // Заполняем цветовой буфер заданным цветом
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);        

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Переключаем экранный буфер (двойная буферизация)
        glfwSwapBuffers(window);
        // Обработка событий
        glfwPollEvents();
    }    

    // Освобождаем ресурсы, занятые GLFW
    glfwTerminate();

    return 0;
}
