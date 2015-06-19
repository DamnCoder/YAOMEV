/*
 * CFrustum.cpp
 *
 *  Created on: 13/06/2011
 *      Author: jorge
 */

#include "math/CFrustum.h"

namespace math {

	CFrustum::CFrustum() {
	}

	CFrustum::~CFrustum() {
	}

	void CFrustum::calculate(
			const Matrix4x4f& projection,
			const Matrix4x4f& modelview) {

		Matrix4x4f clip = modelview * projection;

		clip.transpose();

		// Lado izquierdo fila 4 + fila 1
		_frustum[LEFT].x = clip.m[3] + clip.m[0];
		_frustum[LEFT].y = clip.m[7] + clip.m[4];
		_frustum[LEFT].z = clip.m[11] + clip.m[8];
		_frustum[LEFT].w = clip.m[15] + clip.m[12];

		// Lado derecho fila 4 - fila 1
		_frustum[RIGHT].x = clip.m[3] - clip.m[0];
		_frustum[RIGHT].y = clip.m[7] - clip.m[4];
		_frustum[RIGHT].z = clip.m[11] - clip.m[8];
		_frustum[RIGHT].w = clip.m[15] - clip.m[12];

		// Lado inferior fila 4 + fila 2
		_frustum[BOTTOM].x = clip.m[3] + clip.m[1];
		_frustum[BOTTOM].y = clip.m[7] + clip.m[5];
		_frustum[BOTTOM].z = clip.m[11] + clip.m[9];
		_frustum[BOTTOM].w = clip.m[15] + clip.m[13];

		// Lado superior fila 4 - fila 2
		_frustum[TOP].x = clip.m[3] - clip.m[1];
		_frustum[TOP].y = clip.m[7] - clip.m[5];
		_frustum[TOP].z = clip.m[11] - clip.m[9];
		_frustum[TOP].w = clip.m[15] - clip.m[13];

		// Lado cercano fila 4 + fila 3
		_frustum[NEAR].x = clip.m[3] + clip.m[2];
		_frustum[NEAR].y = clip.m[7] + clip.m[6];
		_frustum[NEAR].z = clip.m[11] + clip.m[10];
		_frustum[NEAR].w = clip.m[15] + clip.m[14];

		// Lado lejano fila 4 - fila 3
		_frustum[FAR].x = clip.m[3] - clip.m[2];
		_frustum[FAR].y = clip.m[7] - clip.m[6];
		_frustum[FAR].z = clip.m[11] - clip.m[10];
		_frustum[FAR].w = clip.m[15] - clip.m[14];

		_frustum[RIGHT].normalize();
		_frustum[LEFT].normalize();
		_frustum[BOTTOM].normalize();
		_frustum[TOP].normalize();
		_frustum[FAR].normalize();
		_frustum[NEAR].normalize();

	}

	/**
	 * Una esfera esta dentro del frustum si su centro mas el radio estan
	 * dentro.
	 * @param center
	 * @param radius
	 * @return
	 */
	const bool CFrustum::isSphereInside(const CVector3f& center, float radius) {
		// Miramos todas las caras del frustum
		for(int i = 0; i < 6; i++ )
			if( !IsFacingTo<float>(_frustum[i], center, radius))
				// El punto esta en el reverso del plano a una distancia mayor que el radio, luego esta fuera
				return false;
		return true;
	}

	const bool CFrustum::isCubeInside(const CVector3f& center, float size ) {

		// Los ocho vertices del bounding volume
		math::CVector3f v1(center.x - size, center.y - size, center.z - size);
		math::CVector3f v2(center.x + size, center.y - size, center.z - size);
		math::CVector3f v3(center.x - size, center.y + size, center.z - size);
		math::CVector3f v4(center.x + size, center.y + size, center.z - size);
		math::CVector3f v5(center.x - size, center.y - size, center.z + size);
		math::CVector3f v6(center.x + size, center.y - size, center.z + size);
		math::CVector3f v7(center.x - size, center.y + size, center.z + size);
		math::CVector3f v8(center.x + size, center.y + size, center.z + size);

		for(int i = 0; i < 6; i++ ){
			if(IsFacingTo<float>(_frustum[i], v1))
				continue;
			if(IsFacingTo<float>(_frustum[i], v2))
				continue;
			if(IsFacingTo<float>(_frustum[i], v3))
				continue;
			if(IsFacingTo<float>(_frustum[i], v4))
				continue;
			if(IsFacingTo<float>(_frustum[i], v5))
				continue;
			if(IsFacingTo<float>(_frustum[i], v6))
				continue;
			if(IsFacingTo<float>(_frustum[i], v7))
				continue;
			if(IsFacingTo<float>(_frustum[i], v8))
				continue;

			return false;
		}

		return true;
	}

}
