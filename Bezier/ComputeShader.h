#ifndef CSHADER_H
#define CSHADER_H

#include <Windows.h>
#include <gl/GL.h>
  #include <QOpenGLFunctions_4_4_Core>

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class ComputeShader : public QOpenGLFunctions_4_4_Core
{
public:
    GLuint ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    ComputeShader(const char* computePath)
    {

        // 1. retrieve the vertex/fragment source code from filePath
        std::string computeCode;
        std::ifstream cShaderFile;
        // ensure ifstream objects can throw exceptions:
        cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            cShaderFile.open(computePath);
            std::stringstream cShaderStream;
            // read file's buffer contents into streams
            cShaderStream << cShaderFile.rdbuf();
            // close file handlers
            cShaderFile.close();
            // convert stream into string
            computeCode = cShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }

        const char* cShaderCode = computeCode.c_str();
        initializeOpenGLFunctions();
        // 2. compile shaders
        GLuint compute;
        // vertex shader
        compute = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(compute, 1, &cShaderCode, NULL);
        glCompileShader(compute);
        checkCompileErrors(compute, "COMPUTE");

        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, compute);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(compute);



    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value)
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value)
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value)
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value)
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y)
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value)
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat)
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat)
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void execute(int x, int y, int z) {
        glDispatchCompute(x, y, z);
    }

    void printWorkGroupsCapabilities() {
        int workgroup_count[3];
        int workgroup_size[3];
        int workgroup_invocations;

        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workgroup_count[0]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workgroup_count[1]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workgroup_count[2]);

        printf("Taille maximale des workgroups:\n\tx:%u\n\ty:%u\n\tz:%u\n",
            workgroup_size[0], workgroup_size[1], workgroup_size[2]);

        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workgroup_size[0]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workgroup_size[1]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workgroup_size[2]);

        printf("Nombre maximal d'invocation locale:\n\tx:%u\n\ty:%u\n\tz:%u\n",
            workgroup_size[0], workgroup_size[1], workgroup_size[2]);

        glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workgroup_invocations);
        printf("Nombre maximum d'invocation de workgroups:\n\t%u\n", workgroup_invocations);
    }
    

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif