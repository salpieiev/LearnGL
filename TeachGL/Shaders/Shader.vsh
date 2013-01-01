//
//  Shader.vsh
//  TeachGL
//
//  Created by Sergey Alpeev on 26.12.12.
//  Copyright (c) 2012 Sergey Alpeev. All rights reserved.
//

const char * VertexShader = STRINGIFY
(


 attribute vec4 Position;
 attribute vec4 SourceColor;
 
 varying vec4 DestinationColor;
 
 uniform mat4 Projection;
 
 
 void main(void)
 {
     DestinationColor = SourceColor;
     gl_Position = Projection * Position;
 }


);