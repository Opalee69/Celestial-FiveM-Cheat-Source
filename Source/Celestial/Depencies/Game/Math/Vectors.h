#pragma once
#include <Includes.h>

class Vector1 final
{
public:

    float x;

    Vector1(const float x) : x(x) {}

};

class Vector2 final
{
public:

    float x, y;

    Vector2(const float x, const float y) : x(x), y(y) {}
    constexpr Vector2() : x(0.0f), y(0.0f) { };
};

class Vector2int final
{
public:

    int x, y;

    Vector2int(const int x, const int y) : x(x), y(y) {}
    constexpr Vector2int() : x(0.0f), y(0.0f) { };
};

class Vector3 final
{
public:

    float x, y, z;

    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
    Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
    bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
    Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
    Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
    Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
    Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
    float Length() const { return sqrt(x * x + y * y + z * z); }
    Vector3 Normalize() const { return *this * (1 / Length()); }
    Vector3 Multiple(const Vector3 caca) const { return Vector3(x * caca.x, y * caca.y, z * caca.z); }

    float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
    void Invert() { *this *= -1; }
    static Vector3 FromM128(__m128 in) { return Vector3(in.m128_f32[0], in.m128_f32[1], in.m128_f32[2]); }
};

class Vector4 final
{
public:
    float x, y, z, w;
    Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}

};

typedef struct PVector3
{
    float x;
    DWORD _paddingx;
    float y;
    DWORD _paddingy;
    float z;
    DWORD _paddingz;

    PVector3(float x, float y, float z) :
        x(x), y(y), z(z),
        _paddingx(0), _paddingy(0), _paddingz(0)
    {
    }
    PVector3() noexcept : PVector3(0.f, 0.f, 0.f) {}
}PVector3;

inline PVector3 ToPVector3(Vector3 pVec) {
    return PVector3(pVec.x, pVec.y, pVec.z);
}
inline Vector3 ToVector3(Vector3 pVec) {
    return Vector3(pVec.x, pVec.y, pVec.z);
}

inline Vector3 GetCoordsInfrontOfaddr(Vector3 addrPos, Vector3 addrRot, float distance) {
    return addrPos + addrRot * distance;
}