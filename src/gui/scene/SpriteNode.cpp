/*
 * SpriteNode.cpp
 *
 *  Created on: 06/10/2010
 *      Author: jorge
 */

#include "gui/scene/SpriteNode.h"

#include "gui/graphicserver/OglSprite.h"
#include "gui/graphicserver/GraphicServer.h"

#include "utilitys/utils.h"

namespace gui {

	CSpriteNode::CSpriteNode() :
		CUINode(),
		_sprite(0),
		_logicFrame(0)
	{
	}

	CSpriteNode::~CSpriteNode() {
	}

	bool CSpriteNode::render(){
		if(!_visible)
			return true;

		return _renderer->render(_sprite, _position, _width, _height);
	}

	void CSpriteNode::load(const std::string& id){
		_sprite = CGraphicServer::instance().getSprite(id);
	}

	bool CSpriteNode::setLogicEntity(logic::CFrame* logicFrame){
		if(!CUINode::setLogicEntity(logicFrame))
			return false;

		_logicFrame = logicFrame;

		_sprite->setBounds(_position.x,	_position.y, _width, _height);

		_sprite->setAlpha(_alpha);

		return true;
	}

	void CSpriteNode::alphaChanged(float newAlpha){
		CUINode::alphaChanged(newAlpha);
		_sprite->setAlpha(newAlpha);
	}

	void CSpriteNode::idChanged(const std::string& id) {
		CUINode::idChanged(id);
		load(id);
	}
}
