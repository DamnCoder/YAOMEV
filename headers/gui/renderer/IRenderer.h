/*
 * IRenderer.h
 *
 *  Created on: 13/02/2011
 *      Author: jorge
 */

#ifndef IRENDERER_H_
#define IRENDERER_H_

#include "gui/graphicserver/OglButton.h"
#include "gui/graphicserver/OglSprite.h"
#include "gui/text/OglText.h"

namespace gui{

	class IRenderer {
	public:
		virtual ~IRenderer(){}

		virtual bool render(
				COglButton* button,
				COglButton::EButtonStatus status,
				const std::string& text,
				const float alpha,
				const math::CVector3f& spritePosition,
				const math::CVector3f& fontPosition,
				float width, float height)
		{
			return true;
		}

		virtual bool render(
				COglSprite* gfxSprite,
				const math::CVector3f& position,
				float width, float height)
		{
			return true;
		}

		virtual bool render(
				COglText* gfxText,
				const std::string& text,
				const float alpha,
				const math::CVector3f& position
				){
			return true;
		}

		virtual bool render(
				COglText* gfxText,
				const std::string& text,
				const math::CVector3f& position,
				float orientation){
			return true;
		}
	};

}


#endif /* IRENDERER_H_ */
