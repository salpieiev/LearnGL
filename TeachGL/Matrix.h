//
//  Matrix.h
//  TeachGL
//
//  Created by Sergey Alpeev on 29.12.12.
//  Copyright (c) 2012 Brisk Mobile Inc. All rights reserved.
//

#pragma once
#include "Vector.h"



template <typename T>
class Matrix4
{
public:
    
    const T * Pointer() const;
    
    static inline Matrix4<T> Frustum(T left, T right, T bottom, T top, T near, T far);
    
    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;
};



template <typename T>
inline const T * Matrix4<T>::Pointer() const
{
    return &x.x;
}

template <typename T>
inline Matrix4<T> Matrix4<T>::Frustum(T left, T right, T bottom, T top, T near, T far)
{
    T a = 2 * near / (right - left);
    T b = 2 * near / (top - bottom);
    T c = (right + left) / (right - left);
    T d = (top + bottom) / (top - bottom);
    T e = -(far + near) / (far - near);
    T f = -2 * far * near / (far - near);
    
    Matrix4 m;
    m.x.x = a; m.x.y = 0; m.x.z = 0; m.x.w = 0;
    m.y.x = 0; m.y.y = b; m.y.z = 0; m.y.w = 0;
    m.z.x = c; m.z.y = d; m.z.z = e; m.z.w = -1;
    m.w.x = 0; m.w.y = 0; m.w.z = f; m.w.w = 1;
    return m;
}



typedef Matrix4<float> mat4;