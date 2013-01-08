//
//  Renderer.h
//  TeachGL
//
//  Created by Sergey Alpeev on 29.12.12.
//  Copyright (c) 2012 Sergey Alpeev. All rights reserved.
//

#pragma once
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>



struct SimpleAttributes
{
    GLint Position;
    GLint SourceColor;
};

struct SimpleUniforms
{
    GLint Projection;
    GLint Modelview;
};

struct LightAttributes
{
    GLint Position;
    GLint Normal;
    GLint DiffuseMaterial;
};

struct LightUniforms
{
    GLint Projection;
    GLint Modelview;
    GLint NormalMatrix;
    GLint LightPosition;
    GLint AmbientMaterial;
    GLint SpecularMaterial;
    GLint Shininess;
};



class Renderer
{
public:
    Renderer();
    ~Renderer();
    
    void Render(int width, int height, double time) const;
    void TearDown();
    
private:
    GLuint BuildShader(const char *source, GLenum shaderType);
    GLuint BuildProgram(const char *vertexShader, const char *fragmentShader);
    
    GLuint m_program;
    GLuint m_lightProgram;
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    GLuint m_lineVertexBuffer;
    GLuint m_lineIndexBuffer;
    GLuint m_cubeVertexBuffer;
    GLuint m_cubeIndexBuffer;
    GLuint m_normalBuffer;
    GLuint m_cubeLightVertexBuffer;
    
    SimpleAttributes m_simpleAttributes;
    SimpleUniforms m_simpleUniforms;
    LightAttributes m_lightAttributes;
    LightUniforms m_lightUniforms;
};
