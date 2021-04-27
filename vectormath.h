/*
 * Copyright (c) 2021 Brad Grantham, grantham@plunk.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef __VECTORMATH_H__
#define __VECTORMATH_H__

#include <math.h>
// #include <values.h>
#include <float.h>

/*
Style to do:
    vec{234}{i,f} should be specialized from std::array?
    size_t, not int, in arrays?
    run through clang-format to fix single-line, no-brace code
*/

template <class V>
float vec_dot(const V& v0, const V& v1)
{
    float total = 0;
    for(int i = 0; i < V::dimension(); i++) total += v0[i] * v1[i];
    return total;
}

template <class V>
float vec_length(const V& v)
{
    float sum = 0;
    for(int i = 0; i < V::dimension(); i++) sum += v[i] * v[i];
    return sqrtf(sum);
}

template <class V>
float vec_length_sq(const V& v)
{
    float sum = 0;
    for(int i = 0; i < V::dimension(); i++) sum += v[i] * v[i];
    return sum;
}

template <class V>
V vec_normalize(const V& v)
{
    float l = vec_length(v);
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v[i] / l;
    return tmp;
}

template <class V>
V vec_blend(const V& v0, float w0, const V& v1, float w1)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v0[i] * w0 + v1[i] * w1;
    return tmp;
}

template <class V>
V vec_scale(const V& v0, float w0)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v0[i] * w0;
    return tmp;
}

/* normalized i, n */
/* doesn't normalize r */
/* r = u - 2 * n * dot(n, u) */
template <class V>
V vec_reflect(const V& i, const V& n)
{
    V tmp;
    tmp = vec_blend(i, 1.0f, n, -2.0f * vec_dot(i, n));
    return tmp;
}

template <class V>
bool vec_refract(float eta, const V& i, const V& n, V& result)
{
    float dot = vec_dot(n, i); 

    float k = 1.0f - eta * eta * (1.0f - dot * dot);

    if(k < 0.0f) {
        result = V(0, 0, 0);
        return true;
    }

    result = eta * i - (eta * dot + sqrtf(k)) * n;
    return false;
}

#if 0
template <class V>
bool operator==(const V& v0, const V& v1)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++)
        if(v0[i] != v1[i])
            return false;
    return true;
}
#endif
    
template <class V>
V operator+(const V& v0, const V& v1)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v0[i] + v1[i];
    return tmp;
}

template <class V>
V operator-(const V& v0, const V& v1)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v0[i] - v1[i];
    return tmp;
}

template <class V>
V operator-(const V& v)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = -v[i];
    return tmp;
}

template <class V>
V operator*(float w, const V& v) 
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v[i] * w;
    return tmp;
}

template <class V>
V operator/(float w, const V& v)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v[i] / w;
    return tmp;
}

template <class V>
V operator*(const V& v, float w)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v[i] * w;
    return tmp;
}

template <class V>
V operator/(const V& v, float w)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v[i] / w;
    return tmp;
}

template <class V>
V operator*(const V& v0, const V& v1)
{
    V tmp;
    for(int i = 0; i < V::dimension(); i++) tmp[i] = v0[i] * v1[i];
    return tmp;
}

struct vec2f
{
    float m_v[2];
    float &x, &y;
    static constexpr int dimension() { return 2; }
    typedef float comp_type;

    vec2f(void) :
        x(m_v[0]),
        y(m_v[1])
    { }

    vec2f(float x, float y) :
        x(m_v[0]),
        y(m_v[1])
    { set(x, y); }

    void set(float x, float y)
        { m_v[0] = x; m_v[1] = y; }

    vec2f(float v) :
        x(m_v[0]),
        y(m_v[1])
    {
	for(int i = 0; i < 2; i++) m_v[i] = v;
    }

    vec2f(const float *v) :
        x(m_v[0]),
        y(m_v[1])
    {
	for(int i = 0; i < 2; i++) m_v[i] = v[i];
    }

    vec2f(const vec2f &v) :
        x(m_v[0]),
        y(m_v[1])
    {
	for(int i = 0; i < 2; i++) m_v[i] = v[i];
    }

    vec2f &operator=(const float *v) {
	for(int i = 0; i < 2; i++) m_v[i] = v[i];
	return *this;
    }

    vec2f &operator=(const vec2f& v) {
	for(int i = 0; i < 2; i++) m_v[i] = v[i];
	return *this;
    }

    vec2f(float *v) :
        x(m_v[0]),
        y(m_v[1])
        { set(v); }

    operator const float*() const { return m_v; }
    operator float*() { return m_v; }

    float& operator[] (int i)
        { return m_v[i]; }

    const float& operator[] (int i) const
        { return m_v[i]; }

    void clear() { 
	for(int i = 0; i < 2; i++) m_v[i] = 0;
    }

