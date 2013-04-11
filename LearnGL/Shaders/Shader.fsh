//
//  Shader.fsh
//  LearnGL
//
//  Created by Sergey Alpeev on 26.12.12.
//  Copyright (c) 2012 Sergey Alpeev. All rights reserved.
//

const char *FragmentShader = STRINGIFY
(

varying lowp vec4 DestinationColor;

void main(void)
{
    gl_FragColor = DestinationColor;
}

);