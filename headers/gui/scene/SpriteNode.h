/*
 * SpriteNode.h
 *
 *  Created on: 06/10/2010
 *      Author: jorge
 */

#ifndef SPRITENODE_H_
#define SPRITENODE_H_

#include "UINode.h"

#include "logic/ui/Frame.h"

namespace gui {

	class COglSprite;

	class CSpriteNode: public CUINode{

	public:

		CSpriteNode();

		virtual ~CSpriteNode();

		bool render();

		void load(const std::string& id);

		bool setLogicEntity(logic::CFrame* frame);

		virtual void alphaChanged(float newAlpha);
		virtual void idChanged(const std::string& id);

	private:

		COglSprite* 	_sprite;

		logic::CFrame*	_logicFrame;

	};

}

#endif /* SPRITENODE_H_ */
