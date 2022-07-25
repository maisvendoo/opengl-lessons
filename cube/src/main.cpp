#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 800;

static glm::mat4 projection = glm::mat4(1.0f);

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void resize_callback(GLFWwindow *window, int width, int height)
{
    (void) window;

    if (height == 0)
        height = 1;

    projection = glm::perspective(
                glm::radians(45.0f),
                static_cast<float>(width) / static_cast<float>(height),
                0.1f,
                100.0f);

    glViewport(0, 0, width, height);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void create_texture(const std::string &image_path, GLuint &texture)
{
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(image_path.c_str(),
                                    &width, &height, &nrChannels, 0);

    if (data != nullptr)
    {
        GLint color_format = GL_RGB;
        if (nrChannels == 4)
            color_format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     color_format,
                     width,
                     height,
                     0,
                     color_format,
                     GL_UNSIGNED_BYTE,
                     data);

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
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
                                          "Textured cubes",
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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Создаем объект буфера вершин (Vertex Buffer OBject - VBO)
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Загружаем и обрабатываем шейдеры
    Shader ourShader("../sources/resources/shaders/cube.vert",
                     "../sources/resources/shaders/cube.frag");

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    projection = glm::perspective(
                glm::radians(45.0f),
                static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
                0.1f,
                100.0f);

    GLuint texture1, texture2;
    create_texture("../sources/resources/img/wall.jpg", texture1);
    create_texture("../sources/resources/img/awesomeface.png", texture2);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Главный цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        // Заполняем цветовой буфер заданным цветом
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        glBindVertexArray(VAO);

        for (unsigned int i = 0; i < 10; ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i + glfwGetTime() * 5.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Переключаем экранный буфер (двойная буферизация)
        glfwSwapBuffers(window);
        // Обработка событий
        glfwPollEvents();
    }    

    // Освобождаем ресурсы, занятые GLFW
    glfwTerminate();

    return 0;
}
