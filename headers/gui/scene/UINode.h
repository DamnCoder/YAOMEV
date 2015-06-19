/*
 * UINode.h
 *
 *  Created on: 17/11/2010
 *      Author: jorge
 */

#ifndef UINODE_H_
#define UINODE_H_

#include "SceneNode.h"

#include "logic/ui/CUiComponent.h"

namespace gui {

	class CUINode: 	public CSceneNode,
					public logic::CUiComponent::UiPropertyListener{

	public:

		CUINode(): _logicComponent(0){}

		virtual ~CUINode(){}

		virtual bool render() = 0;

		virtual void load(const std::string& id){}

		virtual bool setLogicEntity(logic::CUiComponent* logicComponent);

		//--------------------------------------------------------------------------------------
		// Metodos sobreescritos del UiPropertyListener
		//--------------------------------------------------------------------------------------
		virtual void alphaChanged(float newAlpha);
		virtual void positionChanged(const math::CVector3f& newPos);
		void dimensionsChanged(float newWidth, float newHeight);
		void visibilityChanged(bool newVisibility);

		virtual void idChanged(const std::string& id);

	protected:

		bool					_visible;
		math::CVector3f			_position;
		float 					_width;
		float					_height;
		float					_alpha;

		std::string				_id;

		logic::CUiComponent*	_logicComponent;

	};

}

#endif /* UINODE_H_ */
