/*
 * StaticCamera.cpp
 *
 *  Created on: 18/10/2010
 *      Author: jorge
 */

#include "gui/cam/StaticCamera.h"

namespace gui {

	CStaticCamera::CStaticCamera(
			const std::string& id,
			CVector3f position,
			CVector3f lookAt):
				CAbstractCamera(id),
				_position(position),
				_lookAt(lookAt) {}

	CVector3f CStaticCamera::getNewPosition(
			const CVector3f &currentPosition,
			const CVector3f &currentLookAt,
			const CVector3f &displacement){
		return _position;
	}

	CVector3f CStaticCamera::getNewForward(
			const CVector3f &currentPosition,
			const CVector3f &currentLookAt,
			const CVector3f &displacement){
		return _lookAt;
	}

}
