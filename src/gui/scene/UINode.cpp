/*
 * UINode.cpp
 *
 *  Created on: 17/11/2010
 *      Author: jorge
 */

#include "gui/scene/UINode.h"

#include "utilitys/utils.h"

namespace gui {

	bool CUINode::setLogicEntity(logic::CUiComponent* logicComponent){
		// Si no asociamos ninguna entidad logica, terminamos con exito
		if(!logicComponent)
			return false;

		// Si ya hemos asociado una representacion logica,
		// borramos la antigua
		if(_logicComponent){
			_logicComponent->removeListener(this);
			safeDelete(_logicComponent);
		}

		if(!logicComponent->addPropertyListener(this))
			return false;

		_logicComponent = logicComponent;


		_alpha = logicComponent->alpha();
		_position = logicComponent->position();
		_width = logicComponent->width();
		_height = logicComponent->height();
		_visible = logicComponent->visible();

		return true;
	}

	void CUINode::alphaChanged(float newAlpha){
		_alpha = newAlpha;
	}

	void CUINode::positionChanged(const math::CVector3f& newPos){
		_position = newPos;
	}

	void CUINode::dimensionsChanged(float newWidth, float newHeight){
		_width = newWidth;
		_height = newHeight;
	}

	void CUINode::visibilityChanged(bool newVisibility){
		_visible = newVisibility;
	}

	void CUINode::idChanged(const std::string& id) {
		_id = id;
	}
}
