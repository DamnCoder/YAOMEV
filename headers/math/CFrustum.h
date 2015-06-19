/*
 * CFrustum.h
 *
 *  Created on: 13/06/2011
 *      Author: jorge
 */

#ifndef CFRUSTUM_H_
#define CFRUSTUM_H_

#include "Mathlib.h"

namespace math {

	enum eFrustumSide {
		NEAR,
		FAR,
		BOTTOM,
		TOP,
		LEFT,
		RIGHT

	};
	class CFrustum {
	public:
		CFrustum();
		virtual ~CFrustum();

		void calculate(
				const Matrix4x4f& projection,
				const Matrix4x4f& modelview);

		const bool isSphereInside(const CVector3f& center, float radius);
		const bool isCubeInside(const CVector3f& center, float size);

	private:
		CPlanef _frustum[6];
	};

}

#endif /* CFRUSTUM_H_ */
