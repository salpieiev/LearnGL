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
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    GLuint m_lineVertexBuffer;
    GLuint m_lineIndexBuffer;
    GLuint m_cubeVertexBuffer;
    GLuint m_cubeIndexBuffer;
    GLint m_positionSlot;
    GLint m_colorSlot;
    GLint m_projectionUniform;
    GLint m_modelviewUniform;
    
    GLuint m_normalBuffer;
};
