//
//  Vector.h
//  TeachGL
//
//  Created by Sergey Alpeev on 30.12.12.
//  Copyright (c) 2012 Brisk Mobile Inc. All rights reserved.
//

#pragma once
#include <cmath>



const float Pi = 4 * std::atan(1.0f);
const float TwoPi = 2 * Pi;



template <typename T>
class Vector3
{
public:
    Vector3(T x, T y, T z);
    
    float Length() const;
    void Normalize();
    Vector3<T> Cross(const Vector3<T> &v) const;
    
    T x;
    T y;
    T z;
};

template <typename T>
class Vector4
{
public:
    
    T x;
    T y;
    T z;
    T w;
};



template <typename T>
float Vector3<T>::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

template <typename T>
void Vector3<T>::Normalize()
{
    float scale = 1.0f / Length();
    x *= scale;
    y *= scale;
    z *= scale;
}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z): x(x), y(y), z(z)
{
    
}

template <typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T> &v) const
{
    Vector3<T> cross = Vector3<T>(y * v.z - z * v.y,
                                  z * v.x - x * v.z,
                                  x * v.y - y * v.x);
    return cross;
}



typedef Vector3<float> vec3;
typedef Vector4<float> vec4;