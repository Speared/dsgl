/*

Copyright 2010 Etay Meiri

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
Some functions added by David Speare
*/
#include <stdlib.h>
#include <assert.h>
#include <random>
#include "math_3d.h"

Vector3f Vector3f::Cross(const Vector3f& v) const
{
	const float _x = y * v.z - z * v.y;
	const float _y = z * v.x - x * v.z;
	const float _z = x * v.y - y * v.x;

	return Vector3f(_x, _y, _z);
}

float Vector3f::Dot(const Vector3f& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3f& Vector3f::Normalize()
{
	const float Length = sqrtf(x * x + y * y + z * z);

	x /= Length;
	y /= Length;
	z /= Length;

	return *this;
}

void Vector3f::Rotate(float Angle, const Vector3f& Axe)
{
	const float SinHalfAngle = sinf(ToRadian(Angle / 2));
	const float CosHalfAngle = cosf(ToRadian(Angle / 2));

	const float Rx = Axe.x * SinHalfAngle;
	const float Ry = Axe.y * SinHalfAngle;
	const float Rz = Axe.z * SinHalfAngle;
	const float Rw = CosHalfAngle;
	Quaternion RotationQ(Rx, Ry, Rz, Rw);

	Quaternion ConjugateQ = RotationQ.Conjugate();
	//  ConjugateQ.Normalize();
	Quaternion W = RotationQ * (*this) * ConjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
}

Vector3f Vector3f::RotateBy(const Matrix4f& m) const
{
	
	Vector3f r;
	
	r.x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z;
	r.y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z;
	r.z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z;
	
	return r;
}

Vector3f Vector3f::TranslateBy(const Matrix4f& m) const
{
	Vector3f r;
	
	r.x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
	r.y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
	r.z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
	
	return r;
}

//David Speare!
float Vector3f::Angle(Vector3f v1, Vector3f v2)
{
	//normalize in case we arn't
	v1.Normalize();
	v2.Normalize();
	return acos(v1.Dot(v2));
}

void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
{
	m[0][0] = ScaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
	m[1][0] = 0.0f;   m[1][1] = ScaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
	m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = ScaleZ; m[2][3] = 0.0f;
	m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void Matrix4f::InitScaleTransform(Vector3f Scale)
{
	m[0][0] = Scale.x; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
	m[1][0] = 0.0f;   m[1][1] = Scale.y; m[1][2] = 0.0f;   m[1][3] = 0.0f;
	m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = Scale.z; m[2][3] = 0.0f;
	m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void Matrix4f::InitRotateTransform(float RotateX, float RotateY, float RotateZ)
{
	Matrix4f rx, ry, rz;

	const float x = ToRadian(RotateX);
	const float y = ToRadian(RotateY);
	const float z = ToRadian(RotateZ);

	rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f; rx.m[0][2] = 0.0f; rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x); rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f; rx.m[3][2] = 0.0f; rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f; ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y); ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f; ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z); rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f; rz.m[2][1] = 0.0f; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f; rz.m[3][1] = 0.0f; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

	*this = rz * ry * rx;
}

void Matrix4f::InitRotateTransform(Vector3f Rotate)
{
	Matrix4f rx, ry, rz;

	const float x = ToRadian(Rotate.x);
	const float y = ToRadian(Rotate.y);
	const float z = ToRadian(Rotate.z);

	rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f; rx.m[0][2] = 0.0f; rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x); rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f; rx.m[3][2] = 0.0f; rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f; ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y); ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f; ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z); rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f; rz.m[2][1] = 0.0f; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f; rz.m[3][1] = 0.0f; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

	*this = rz * ry * rx;
}

void Matrix4f::InitRotateTransform(const Quaternion& quat)
{
	float yy2 = 2.0f * quat.y * quat.y;
	float xy2 = 2.0f * quat.x * quat.y;
	float xz2 = 2.0f * quat.x * quat.z;
	float yz2 = 2.0f * quat.y * quat.z;
	float zz2 = 2.0f * quat.z * quat.z;
	float wz2 = 2.0f * quat.w * quat.z;
	float wy2 = 2.0f * quat.w * quat.y;
	float wx2 = 2.0f * quat.w * quat.x;
	float xx2 = 2.0f * quat.x * quat.x;
	m[0][0] = -yy2 - zz2 + 1.0f;
	m[0][1] = xy2 + wz2;
	m[0][2] = xz2 - wy2;
	m[0][3] = 0;
	m[1][0] = xy2 - wz2;
	m[1][1] = -xx2 - zz2 + 1.0f;
	m[1][2] = yz2 + wx2;
	m[1][3] = 0;
	m[2][0] = xz2 + wy2;
	m[2][1] = yz2 - wx2;
	m[2][2] = -xx2 - yy2 + 1.0f;
	m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1.0f;
}

void Matrix4f::InitTranslationTransform(float x, float y, float z)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::InitTranslationTransform(Vector3f Translate)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = Translate.x;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = Translate.y;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = Translate.z;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}


void Matrix4f::InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
{
	Vector3f N = Target;
	N.Normalize();
	Vector3f U = Up;
	U.Normalize();
	U = U.Cross(N);
	Vector3f V = N.Cross(U);

	m[0][0] = U.x;   m[0][1] = U.y;   m[0][2] = U.z;   m[0][3] = 0.0f;
	m[1][0] = V.x;   m[1][1] = V.y;   m[1][2] = V.z;   m[1][3] = 0.0f;
	m[2][0] = N.x;   m[2][1] = N.y;   m[2][2] = N.z;   m[2][3] = 0.0f;
	m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;
}

void Matrix4f::InitPersProjTransform(const PersProjInfo& p)
{
	const float ar = p.Width / p.Height;
	const float zRange = p.zNear - p.zFar;
	const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));

	m[0][0] = 1.0f / (tanHalfFOV * ar); m[0][1] = 0.0f;            m[0][2] = 0.0f;            m[0][3] = 0.0;
	m[1][0] = 0.0f;                   m[1][1] = 1.0f / tanHalfFOV; m[1][2] = 0.0f;            m[1][3] = 0.0;
	m[2][0] = 0.0f;                   m[2][1] = 0.0f;            m[2][2] = (-p.zNear - p.zFar) / zRange; m[2][3] = 2.0f*p.zFar*p.zNear / zRange;
	m[3][0] = 0.0f;                   m[3][1] = 0.0f;            m[3][2] = 1.0f;            m[3][3] = 0.0;
}


void Matrix4f::InitOrthoProjTransform(const PersProjInfo& p)
{
	const float zRange = p.zFar - p.zNear;

	m[0][0] = 2.0f / p.Width; m[0][1] = 0.0f;          m[0][2] = 0.0f;        m[0][3] = 0.0;
	m[1][0] = 0.0f;         m[1][1] = 2.0f / p.Height; m[1][2] = 0.0f;        m[1][3] = 0.0;
	m[2][0] = 0.0f;         m[2][1] = 0.0f;          m[2][2] = 2.0f / zRange; m[2][3] = (-p.zFar - p.zNear) / zRange;
	m[3][0] = 0.0f;         m[3][1] = 0.0f;          m[3][2] = 0.0f;        m[3][3] = 1.0;
}

//how to do this taken from http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/
void Matrix4f::InitFromToRotation(Vector3f from, Vector3f to) {
	//normalize in case we arn't
	from.Normalize();
	to.Normalize();

	Vector3f axisOfRotation = from.Cross(to);

	if (axisOfRotation.x == 0 && axisOfRotation.y == 0 && axisOfRotation.z == 0) {
		//if we're rotating from a vector to the same vector just become an identity matrix
		//TODO: make this function able to tell if the vectors are pointing in oposit directions and deal with that properly
		InitIdentity();
		return;
	}

	axisOfRotation.Normalize();

	float rotationAngle = Vector3f::Angle(from, to);

	float c = cos(rotationAngle);
	float s = sin(rotationAngle);
	float t = 1.0f - c;

	m[0][0] = c + axisOfRotation.x*axisOfRotation.x*t;
	m[1][1] = c + axisOfRotation.y*axisOfRotation.y*t;
	m[2][2] = c + axisOfRotation.z*axisOfRotation.z*t;

	float temp1 = axisOfRotation.x*axisOfRotation.y*t;
	float temp2 = axisOfRotation.z*s;

	m[1][0] = temp1 + temp2;
	m[0][1] = temp1 - temp2;

	temp1 = axisOfRotation.x*axisOfRotation.z*t;
	temp2 = axisOfRotation.y*s;

	m[2][0] = temp1 - temp2;
	m[0][2] = temp1 + temp2;

	temp1 = axisOfRotation.y*axisOfRotation.z*t;
	temp2 = axisOfRotation.x * s;

	m[2][1] = temp1 + temp2;
	m[1][2] = temp1 - temp2;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][3] = 1;
}

float Matrix4f::Determinant() const
{
	return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3]
		+ m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3]
		- m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2]
		+ m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1]
		+ m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1]
		- m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
}


Matrix4f& Matrix4f::Inverse()
{
	// Compute the reciprocal determinant
	float det = Determinant();
	if (det == 0.0f)
	{
		// Matrix not invertible. Setting all elements to nan is not really
		// correct in a mathematical sense but it is easy to debug for the
		// programmer.
		/*const float nan = std::numeric_limits<float>::quiet_NaN();
		*this = Matrix4f(
		nan,nan,nan,nan,
		nan,nan,nan,nan,
		nan,nan,nan,nan,
		nan,nan,nan,nan);*/
		assert(0);
		return *this;
	}

	float invdet = 1.0f / det;

	Matrix4f res;
	res.m[0][0] = invdet  * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
	res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
	res.m[0][2] = invdet  * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
	res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
	res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
	res.m[1][1] = invdet  * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
	res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
	res.m[1][3] = invdet  * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
	res.m[2][0] = invdet  * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[2][2] = invdet  * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
	res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
	res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[3][1] = invdet  * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
	res.m[3][3] = invdet  * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
	*this = res;

	return *this;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void Quaternion::Normalize()
{
	float Length = sqrtf(x * x + y * y + z * z + w * w);

	x /= Length;
	y /= Length;
	z /= Length;
	w /= Length;
}


Quaternion Quaternion::Conjugate()
{
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
	const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
	const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
	const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
	const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

	Quaternion ret(x, y, z, w);

	return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
	const float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	Quaternion ret(x, y, z, w);

	return ret;
}


Vector3f Quaternion::ToDegrees()
{
	float f[3];

	f[0] = atan2(x * z + y * w, x * w - y * z);
	f[1] = acos(-x * x - y * y - z * z - w * w);
	f[2] = atan2(x * z - y * w, x * w + y * z);

	f[0] = ToDegree(f[0]);
	f[1] = ToDegree(f[1]);
	f[2] = ToDegree(f[2]);

	return Vector3f(f);
}


float RandomFloat()
{
	float Max = RAND_MAX;
	return ((float)rand() / Max);
}

