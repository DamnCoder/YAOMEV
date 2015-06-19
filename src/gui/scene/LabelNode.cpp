/*
 * LabelNode.cpp
 *
 *  Created on: 12/11/2010
 *      Author: jorge
 */

#include "gui/scene/LabelNode.h"

#include <GL/gl.h>

namespace gui {

	CLabelNode::~CLabelNode() {
	}

	bool CLabelNode::render(){
		if(!_visible || !_gfxText)
			return true;
		return _renderer->render(_gfxText, _logicLabel->getText(), _alpha, _position);
	}

	bool CLabelNode::setLogicEntity(logic::CLabel* label){
		// Si no asociamos ninguna entidad logica, terminamos con exito
		if(!CUINode::setLogicEntity(label))
			return false;

		// Si ya hemos asociado una representacion logica,
		// borramos la antigua
		if(_logicLabel){
			_logicLabel->removeListener(this);
			safeDelete(_logicLabel);
		}

		if(!label->addListener(this))
			return false;

		_logicLabel = label;

		_gfxText->setFont(_logicLabel->getFontName(), label->getTextSize(), TEXTURED);

		return true;
	}

	void CLabelNode::textChanged(const logic::CLabel* label, const string& text){
		//cout<<"Label con id:"<<label->getID()<<" cambia el texto desde la logica\n";
		_gfxText->setText(text);
	}

	void CLabelNode::fontSizeChanged(int size){
		_gfxText->setSize(size);
	}
	void CLabelNode::fontChanged(const std::string& font){
		_gfxText->setFont(_text,_fontSize, TEXTURED);
	}
}
