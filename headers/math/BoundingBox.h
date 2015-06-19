/*
 * CBoundingBox.h
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#ifndef CBOUNDINGBOX_H_
#define CBOUNDINGBOX_H_

#include "Mathlib.h"

namespace math {

	class CBoundingBox {

	public:

		CBoundingBox(): _lower(), _upper(){}

		CBoundingBox(const CVector3f& lower, const CVector3f& upper):
			_lower(lower),
			_upper(upper)
		{}

		CBoundingBox(float x1, float y1, float z1, float x2, float y2, float z2):
			_lower(CVector3f(x1, y1, z1)),
			_upper(CVector3f(x2, y2, z2))
		{}

		CBoundingBox(float* lower, float* upper) :
			_lower(CVector3f(lower[0], lower[1], lower[2])),
			_upper(CVector3f(upper[0], upper[1], upper[2]))
		{}

		~CBoundingBox();

		const math::CVector3f lower() const { return _lower;}
		const math::CVector3f upper() const { return _upper;}

		/**
		 * Consideramos que lower y upper son coordenadas globales.
		 * Decide si un punto se encuentra dentro de la bounding box
		 * @param p
		 * @return true si el punto esta dentro de la bounding box
		 */
		const bool isInside2dBox(const math::CVector3f& p);
		const bool isInside(const CVector3f& p);

	protected:
		math::CVector3f _lower;
		math::CVector3f _upper;
	};

	class CBoundingSphere {
	public:
		CBoundingSphere() : _radius(0) {}
		CBoundingSphere(float x, float y, float z, float radius) :
			_center(math::CVector3f(x, y, z)),
			_radius(radius) {}
		CBoundingSphere(float* center, float radius) :
			_center(math::CVector3f(center[0] ,center[1], center[2])),
			_radius(radius) {}

		~CBoundingSphere() {}

		const CVector3f	center() const { return _center; }
		const float 	radius() const { return _radius; }

		void setCenter(const CVector3f& newCenter) { _center = newCenter; }
		void setRadius(float radius) { _radius = radius; }

	private:
		CVector3f	_center;
		float		_radius;

	};

}

#endif /* CBOUNDINGBOX_H_ */
