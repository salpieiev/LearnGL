//
//  Vector.h
//  TeachGL
//
//  Created by Sergey Alpeev on 30.12.12.
//  Copyright (c) 2012 Brisk Mobile Inc. All rights reserved.
//

#pragma once



template <typename T>
class Vector4
{
public:
    
    
    T x;
    T y;
    T z;
    T w;
};



typedef Vector4<float> vec4;