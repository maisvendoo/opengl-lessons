#ifndef     SHADER_H
#define     SHADER_H

#include    <glad/glad.h>
#include    <glm/glm.hpp>

#include    <string>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Shader
{
public:

    Shader(const char *vertexPath, const char *fragmentPath);

    GLuint getProgramID() const { return progID; }

    void use() { glUseProgram(progID); }

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(progID, name.c_str()), (GLint) value);
    }

    void setInt(const std::string &name,  GLint value) const
    {
        glUniform1i(glGetUniformLocation(progID, name.c_str()), value);
    }

    void setFloat(const std::string &name, GLfloat value) const
    {
        glUniform1f(glGetUniformLocation(progID, name.c_str()), value);
    }

    void setMat4(const std::string &name, const glm::mat4 &matrix)
    {
        GLuint location = glGetUniformLocation(progID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

private:

    GLuint progID;

    void read_shader_source(const char *path, std::string &code);

    GLuint compile_shader(const char *code, GLenum shader_type);
};

#endif // SHADER_H
