#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 800;

static glm::mat4 projection = glm::mat4(1.0f);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastTime = 0.0f;

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
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    (void) window;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY;

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    else
        firstMouse = true;
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
                                          "Shader lighting",
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

    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Задаем массив вершин, каждой вершине присваиваем дополнительный
    // атрибут - компоненты нормалей
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // Создаем объект буфера вершин (Vertex Buffer OBject - VBO)
    GLuint VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof (GLfloat)));
    glEnableVertexAttribArray(1);

    GLuint lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);


    // Загружаем и обрабатываем шейдеры
    Shader cubeShader("../sources/resources/shaders/material.vert",
                     "../sources/resources/shaders/material.frag");

    Shader lightShader("../sources/resources/shaders/light_cube.vert",
                       "../sources/resources/shaders/light_cube.frag");

    projection = glm::perspective(
                glm::radians(45.0f),
                static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
                0.1f,
                100.0f);

    cubeShader.use();
    cubeShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    cubeShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    glm::vec3 lightPos(0.0f, 0.0f, 2.0f);

    // Главный цикл приложения
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);

        // Заполняем цветовой буфер заданным цветом
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Берем видовую матрицу из класса камеры
        glm::mat4 view = camera.GetViewMatrix();

        lightShader.use();

        // Задаем для источника видовую матрицу и матрицу проекции
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);

        // Позиционируем источник, через матрицу модели
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        float z = -0.5 * (float) (sin(0.1 * glfwGetTime()));
        glm::mat4 rot_mat = glm::rotate(model, glm::radians(20.0f * (float) glfwGetTime()), glm::vec3(0.0f, 1.0f, z));
        model = glm::translate(rot_mat, lightPos);
        model = glm::scale(model, glm::vec3(0.1f));
        lightShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        cubeShader.use();

        cubeShader.setMat4("view", view);
        cubeShader.setMat4("projection", projection);

        cubeShader.setVec3("viewPos", camera.Position);

        glBindVertexArray(cubeVAO);

        model = glm::mat4(1.0f);

        glm::vec3 lp = glm::vec3(rot_mat * glm::vec4(lightPos, 1.0f));
        cubeShader.setMat4("model", model);
        cubeShader.setVec3("light.position", lp);

        cubeShader.setVec3("material.ambient", glm::vec3(0.2125f, 0.1275f, 0.054f));
        cubeShader.setVec3("material.diffuse", glm::vec3(0.714f, 0.4284f, 0.18144f));
        cubeShader.setVec3("material.specular", glm::vec3(0.393548f, 0.271906f, 0.166721f));
        cubeShader.setFloat("material.shininess", 32.0f);

        cubeShader.setVec3("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        cubeShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        cubeShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);        

        // Переключаем экранный буфер (двойная буферизация)
        glfwSwapBuffers(window);
        // Обработка событий
        glfwPollEvents();
    }    

    // Освобождаем ресурсы, занятые GLFW
    glfwTerminate();

    return 0;
}
