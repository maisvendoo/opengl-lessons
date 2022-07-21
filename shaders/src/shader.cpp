#include    "shader.h"

#include    <fstream>
#include    <sstream>
#include    <iostream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // Читаем код шейдеров из файла
    std::string vShaderCode, fShaderCode;
    read_shader_source(vertexPath, vShaderCode);
    read_shader_source(fragmentPath, fShaderCode);

    // Компилируем шейдеры
    GLuint vertex = compile_shader(vShaderCode.c_str(), GL_VERTEX_SHADER);
    GLuint fragment = compile_shader(fShaderCode.c_str(), GL_FRAGMENT_SHADER);

    // Компонуем шейдерную программу
    GLint success;
    char infoLog[512];

    progID = glCreateProgram();
    glAttachShader(progID, vertex);
    glAttachShader(progID, fragment);
    glLinkProgram(progID);

    glGetProgramiv(progID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(progID, 512, nullptr, infoLog);
        std::cout << "ERROR: Link shader program failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Shader::read_shader_source(const char *path, std::string &code)
{
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(path);
        std::stringstream ss;

        ss << shaderFile.rdbuf();

        shaderFile.close();

        code = ss.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR: Shader file not read: " << e.what() << std::endl;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GLuint Shader::compile_shader(const char *code, GLenum shader_type)
{
    GLuint shader;
    GLint success;
    char infoLog[512];

    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR: Shader compilation failed: " << infoLog << std::endl;
    }

    return shader;
}
