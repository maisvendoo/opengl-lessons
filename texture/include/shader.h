#ifndef     SHADER_H
#define     SHADER_H

#include    <glad/glad.h>

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

private:

    GLuint progID;

    void read_shader_source(const char *path, std::string &code);

    GLuint compile_shader(const char *code, GLenum shader_type);
};

#endif // SHADER_H
