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



struct LightAttributes
{
    GLint Position;
    GLint Normal;
    GLint Diffuse;
};

struct LightUniforms
{
    GLint Modelview;
    GLint Projection;
    GLint NormalMatrix;
    GLint LightPosition;
    GLint Ambient;
    GLint Specular;
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
    GLuint m_visualNormalBuffer;
    GLint m_positionSlot;
    GLint m_colorSlot;
    GLint m_normalSlot;
    GLint m_projectionUniform;
    GLint m_modelviewUniform;
    
    LightAttributes m_lightAttributes;
    LightUniforms m_lightUniforms;
};
