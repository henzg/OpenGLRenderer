#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
private:
    uint32_t m_ShaderID;
public:

    Shader(const char* vertexPath, const char* fragmentPath) : m_ShaderID(0)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        
        try 
        {   
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read files buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream to string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure e) 
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex shaders
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // print erros if any at compile time
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
        }

        // fragment shaders
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
        }

        //shader program
        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertex);
        glAttachShader(m_ShaderID, fragment);
        glLinkProgram(m_ShaderID);
        // print linking errors
        glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl; 
        }

        // delete shader
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    ~Shader(){glDeleteProgram(m_ShaderID);}

    void Bind()
    {
        glUseProgram(m_ShaderID);
    }

    void Unbind()
    {
        glUseProgram(0);
    }

    bool IsValid() const { return m_ShaderID != 0; }

    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (int)value);
    }
    
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
    }
    
    void setFloat(const std::string& name, float value) const 
    {
        glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
    }

    void setMat4(const std::string& name, const glm::mat4& value) const    {
        glUniformMatrix4fv(
            glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    inline uint32_t getShaderId() { return m_ShaderID; }
};

#endif
