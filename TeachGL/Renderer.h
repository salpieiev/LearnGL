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
    Renderer(int width, int height);
    ~Renderer();
    
    void Render() const;
    void TearDown();
    
private:
    GLuint BuildShader(const char *source, GLenum shaderType);
    GLuint BuildProgram(const char *vertexShader, const char *fragmentShader);
    
    GLuint m_program;
    GLint m_positionSlot;
    GLint m_colorSlot;
    
    GLint m_linePosition;
    GLint m_lineColor;
};
