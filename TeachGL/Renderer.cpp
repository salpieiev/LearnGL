//
//  Renderer.cpp
//  TeachGL
//
//  Created by Sergey Alpeev on 29.12.12.
//  Copyright (c) 2012 Sergey Alpeev. All rights reserved.
//

#include "Renderer.h"
#include "Matrix.h"
#include <iostream>

using namespace std;



#define STRINGIFY(A)    #A
#include "Shaders/Shader.fsh"
#include "Shaders/Shader.vsh"



typedef struct
{
    float Position[3];
    float Color[4];
} Vertex;

const Vertex Vertices[] =
{
    {{1, -1, -7}, {1, 0, 0, 1}},
    {{1, 1, -7}, {0, 1, 0, 1}},
    {{-1, 1, -7}, {0, 0, 1, 1}},
    {{-1, -1, -7}, {0, 0, 0, 1}}
};

const GLubyte Indices[] =
{
    0, 1, 2,
    2, 3, 0
};

const Vertex LineVertices[] =
{
    {{-2, -3.55, -4}, {1, 1, 1, 1}},
    {{2, -3.55, -4}, {1, 1, 1, 1}},
    {{2, 3.55, -4}, {1, 1, 1, 1}},
    {{-2, 3.55, -4}, {1, 1, 1, 1}},
    
    {{-2, -3.55, -10}, {1, 1, 1, 1}},
    {{2, -3.55, -10}, {1, 1, 1, 1}},
    {{2, 3.55, -10}, {1, 1, 1, 1}},
    {{-2, 3.55, -10}, {1, 1, 1, 1}}
};

const GLubyte LineIndices[] =
{
    0, 1, 1, 2, 2, 3, 3, 0, 0, 4, 4, 5, 5, 6, 6, 7, 7, 4, 1, 5, 2, 6, 3, 7
};



Renderer::Renderer(int width, int height)
{
    m_program = BuildProgram(VertexShader, FragmentShader);
    glUseProgram(m_program);
    
    m_positionSlot = glGetAttribLocation(m_program, "Position");
    m_colorSlot = glGetAttribLocation(m_program, "SourceColor");
    m_projectionUniform = glGetUniformLocation(m_program, "Projection");
    
    glEnableVertexAttribArray(m_positionSlot);
    glEnableVertexAttribArray(m_colorSlot);
    
    float h = 4.0f * height / width;
    mat4 projection = mat4::Frustum(-2.0f, 2.0f, -h / 2.0f, h / 2.0f, 4.0f, 10.0f);
    glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, projection.Pointer());
}

Renderer::~Renderer()
{
    
}

void Renderer::Render() const
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glVertexAttribPointer(m_colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
    
    glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(Indices[0]), GL_UNSIGNED_BYTE, NULL);
    
    
    
    GLuint lineVertexBuffer;
    glGenBuffers(1, &lineVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertices), LineVertices, GL_STATIC_DRAW);
    
    GLuint lineIndexBuffer;
    glGenBuffers(1, &lineIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(LineIndices), LineIndices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glVertexAttribPointer(m_colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
    
    GLint drawCount = sizeof(LineIndices) / sizeof(LineIndices[0]);
    glDrawElements(GL_LINES, drawCount, GL_UNSIGNED_BYTE, 0);
}

void Renderer::TearDown()
{
    
}

GLuint Renderer::BuildShader(const char *source, GLenum shaderType)
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, NULL);
    glCompileShader(shaderHandle);
    
    GLint compileStatus;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);
    
    if (compileStatus == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(shaderHandle, sizeof(message), NULL, message);
        cout << message << endl;
        exit(1);
    }
    
    return shaderHandle;
}

GLuint Renderer::BuildProgram(const char *vertexShader, const char *fragmentShader)
{
    GLuint vShaderHandle = BuildShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fShaderHandle = BuildShader(fragmentShader, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vShaderHandle);
    glAttachShader(programHandle, fShaderHandle);
    glLinkProgram(programHandle);
    
    GLint linkStatus;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkStatus);
    
    if (linkStatus == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(programHandle, sizeof(message), NULL, message);
        cout << message << endl;
        exit(1);
    }
    
    return programHandle;
}