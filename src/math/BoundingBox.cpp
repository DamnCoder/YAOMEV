/*
 * CBoundingBox.cpp
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#include "math/BoundingBox.h"

namespace math {

	CBoundingBox::~CBoundingBox(){
	}

	const bool CBoundingBox::isInside2dBox(const math::CVector3f& p){
		return (_lower.x <= p.x) && (p.x <= _upper.x) && (_lower.y <= p.y) && (p.y <= _upper.y);
	}

	const bool CBoundingBox::isInside(const math::CVector3f& p){
		return (_lower.x <= p.x) && (p.x <= _upper.x)
				&&
				(_lower.y <= p.y) && (p.y <= _upper.y)
				&&
				(_lower.z <= p.z) && (p.z <= _upper.z);
	}

}
