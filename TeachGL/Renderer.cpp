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
#include <vector>

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

const GLushort Indices[] =
{
    0, 1, 2,
    2, 3, 0
};

const Vertex LineVertices[] =
{
    // Frustum
    {{-2, -3.55, -4}, {1, 1, 1, 1}},
    {{2, -3.55, -4}, {1, 1, 1, 1}},
    {{2, 3.55, -4}, {1, 1, 1, 1}},
    {{-2, 3.55, -4}, {1, 1, 1, 1}},
    {{-2, -3.55, -9.99}, {1, 1, 1, 1}},
    {{2, -3.55, -9.99}, {1, 1, 1, 1}},
    {{2, 3.55, -9.99}, {1, 1, 1, 1}},
    {{-2, 3.55, -9.99}, {1, 1, 1, 1}},
    
    {{0, 0, -4}, {1, 0, 0, 1}},
    {{2, 0, -4}, {1, 0, 0, 1}},
    {{0, 3, -9.99}, {0, 1, 0, 1}},
    {{2, 3, -9.99}, {0, 1, 0, 1}},
    {{-2, -3, -4}, {0, 0, 1, 1}},
    {{2, -3, -4}, {0, 0, 1, 1}}
};

const GLushort LineIndices[] =
{
    // Frustum
    0, 1, 1, 2, 2, 3, 3, 0, 0, 4, 4, 5, 5, 6, 6, 7, 7, 4, 1, 5, 2, 6, 3, 7,
    
    8, 9, 10, 11, 12, 13
};

const Vertex CubeVertices[]
{
    {{1, -3, -6}, {0, 0, 0, 1}},
    {{2, -3, -6}, {0, 0, 1, 1}},
    {{2, -3, -7}, {0, 1, 0, 1}},
    {{1, -3, -7}, {0, 1, 1, 1}},
    {{1, -2, -6}, {1, 0, 0, 1}},
    {{2, -2, -6}, {1, 0, 1, 1}},
    {{2, -2, -7}, {1, 1, 0, 1}},
    {{1, -2, -7}, {1, 1, 1, 1}},
    
    {{1, 3, -6}, {0.3, 0.3, 0.3, 1}},
    {{2, 3, -6}, {0.3, 0.3, 0.3, 1}},
    {{2, 3, -7}, {0.3, 0.3, 0.3, 1}},
    {{1, 3, -7}, {0.3, 0.3, 0.3, 1}},
    {{1, 2, -6}, {0.3, 0.3, 0.3, 1}},
    {{2, 2, -6}, {0.3, 0.3, 0.3, 1}},
    {{2, 2, -7}, {0.3, 0.3, 0.3, 1}},
    {{1, 2, -7}, {0.3, 0.3, 0.3, 1}}
};

const GLushort CubeIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    4, 6, 5,
    4, 7, 6,
    3, 6, 7,
    2, 6, 3,
    1, 6, 2,
    1, 5, 6,
    0, 3, 7,
    0, 7, 4,
    0, 5, 1,
    0, 4, 5,
    
    8, 10, 9,
    8, 11, 10,
    12, 13, 14,
    12, 14, 15,
    11, 15, 14,
    10, 11, 14,
    9, 10, 14,
    9, 14, 13,
    8, 15, 11,
    8, 12, 15,
    8, 9, 13,
    8, 13, 12
};



Renderer::Renderer()
{
    m_program = BuildProgram(VertexShader, FragmentShader);
    glUseProgram(m_program);
    
    m_positionSlot = glGetAttribLocation(m_program, "Position");
    m_colorSlot = glGetAttribLocation(m_program, "SourceColor");
    m_projectionUniform = glGetUniformLocation(m_program, "Projection");
    m_modelviewUniform = glGetUniformLocation(m_program, "Modelview");
    
    glEnableVertexAttribArray(m_positionSlot);
    glEnableVertexAttribArray(m_colorSlot);
    
    glEnable(GL_DEPTH_TEST);
    
    // Generate new vertices for cubes with lighting
    int cubeIndicesCount = sizeof(CubeIndices) / sizeof(CubeIndices[0]);
    
    vector<float> normalFloats(cubeIndicesCount * 7 * 2);
    
    for (int i = 2, j = 0; i < cubeIndicesCount; i += 3)
    {
        GLushort index0 = CubeIndices[i - 2];
        GLushort index1 = CubeIndices[i - 1];
        GLushort index2 = CubeIndices[i];
        
        Vertex vertex0 = CubeVertices[index0];
        Vertex vertex1 = CubeVertices[index1];
        Vertex vertex2 = CubeVertices[index2];
        
        vec3 vector0(vertex0.Position[0] - vertex1.Position[0],
                     vertex0.Position[1] - vertex1.Position[1],
                     vertex0.Position[2] - vertex1.Position[2]);
        vec3 vector1(vertex2.Position[0] - vertex1.Position[0],
                     vertex2.Position[1] - vertex1.Position[1],
                     vertex2.Position[2] - vertex1.Position[2]);
        vec3 normal = vector0.Cross(vector1);
        normal.Normalize();
        
        
        normalFloats[j++] = vertex0.Position[0];
        normalFloats[j++] = vertex0.Position[1];
        normalFloats[j++] = vertex0.Position[2];
        
        normalFloats[j++] = 1;
        normalFloats[j++] = 0;
        normalFloats[j++] = 0;
        normalFloats[j++] = 1;
        
        normalFloats[j++] = vertex0.Position[0] + normal.x;
        normalFloats[j++] = vertex0.Position[1] + normal.y;
        normalFloats[j++] = vertex0.Position[2] + normal.z;
        
        normalFloats[j++] = 1;
        normalFloats[j++] = 1;
        normalFloats[j++] = 0;
        normalFloats[j++] = 1;
        
        normalFloats[j++] = vertex1.Position[0];
        normalFloats[j++] = vertex1.Position[1];
        normalFloats[j++] = vertex1.Position[2];
        
        normalFloats[j++] = 1;
        normalFloats[j++] = 0;
        normalFloats[j++] = 0;
        normalFloats[j++] = 1;
        
        normalFloats[j++] = vertex1.Position[0] + normal.x;
        normalFloats[j++] = vertex1.Position[1] + normal.y;
        normalFloats[j++] = vertex1.Position[2] + normal.z;
        
        normalFloats[j++] = 1;
        normalFloats[j++] = 1;
        normalFloats[j++] = 0;
        normalFloats[j++] = 1;
        
        normalFloats[j++] = vertex2.Position[0];
        normalFloats[j++] = vertex2.Position[1];
        normalFloats[j++] = vertex2.Position[2];
        
        normalFloats[j++] = 1;
        normalFloats[j++] = 0;
        normalFloats[j++] = 0;
        normalFloats[j++] = 1;
        
        normalFloats[j++] = vertex2.Position[0] + normal.x;
        normalFloats[j++] = vertex2.Position[1] + normal.y;
        normalFloats[j++] = vertex2.Position[2] + normal.z;
        
        normalFloats[j++] = 1;
        normalFloats[j++] = 1;
        normalFloats[j++] = 0;
        normalFloats[j++] = 1;
    }
    
    glGenBuffers(1, &m_normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normalFloats.size() * sizeof(float), &normalFloats[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_lineVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_lineVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertices), LineVertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_lineIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lineIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(LineIndices), LineIndices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_cubeVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_cubeIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeIndices), CubeIndices, GL_STATIC_DRAW);
}

Renderer::~Renderer()
{
    
}

void Renderer::Render(int width, int height, double time) const
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, width, height);
    
    float h = 4.0f * height / width;
    mat4 projection = mat4::Frustum(-2.0f, 2.0f, -h / 2.0f, h / 2.0f, 4.0f, 10.0f);
    glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, projection.Pointer());
    
    mat4 modelview;
    modelview = modelview.RotateZ(8 * std::sin(time));
    glUniformMatrix4fv(m_modelviewUniform, 1, GL_FALSE, modelview.Pointer());
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    
    glVertexAttribPointer(m_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glVertexAttribPointer(m_colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
    
    glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(Indices[0]), GL_UNSIGNED_SHORT, NULL);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, m_lineVertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lineIndexBuffer);
    
    glVertexAttribPointer(m_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glVertexAttribPointer(m_colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
    
    GLint drawCount = sizeof(LineIndices) / sizeof(LineIndices[0]);
    glDrawElements(GL_LINES, drawCount, GL_UNSIGNED_SHORT, NULL);
    
    
    float degree = ((int)(time * 10000.0f)) % 36000 / 100.0f;
    
    mat4 translated1 = mat4::Translate(0, 0, -7);
    mat4 rotated1 = mat4::RotateY(degree);
    mat4 translated2 = mat4::Translate(0, 0, 7);
    
    modelview = translated2 * rotated1 * translated1 * modelview;
    glUniformMatrix4fv(m_modelviewUniform, 1, GL_FALSE, modelview.Pointer());
    
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndexBuffer);
    
    glVertexAttribPointer(m_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glVertexAttribPointer(m_colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
    
    drawCount = 3 * 12;
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_SHORT, NULL);
    
    
    mat4 translated3 = mat4::Translate(0, 0, -7);
    mat4 rotated2 = mat4::RotateY(-degree * 2);
    mat4 translated4 = mat4::Translate(0, 0, 7);
    
    modelview = translated4 * rotated2 * translated3 * modelview;
    glUniformMatrix4fv(m_modelviewUniform, 1, GL_FALSE, modelview.Pointer());
    
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_SHORT, (GLvoid *)(sizeof(GLushort) * drawCount));
    
    
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glVertexAttribPointer(m_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, NULL);
    glVertexAttribPointer(m_colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid *)(sizeof(float) * 3));
    glDrawArrays(GL_LINES, 0, sizeof(CubeIndices) / sizeof(CubeIndices[0]) * 2);
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