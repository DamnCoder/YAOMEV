/*
 * TextLayoutNode.cpp
 *
 *  Created on: 12/11/2010
 *      Author: jorge
 */

#include "gui/scene/TextLayoutNode.h"

#include "gui/graphicserver/OglSprite.h"
#include "gui/graphicserver/GraphicServer.h"

#include <GL/gl.h>

namespace gui {

	CTextLayoutNode::~CTextLayoutNode() {
		safeDelete(_textLayout);
	}

	bool CTextLayoutNode::render(){
		if(!_visible || !_textLayout)
			return true;

		bool result(true);


		if(_sprite){
			math::CBoundingBox bbox = _textLayout->boundingBox();
			//_sprite->setBounds(bbox.lower().x, bbox.lower().y, bbox.upper().x, bbox.upper().y);
			//_sprite->setWidth(bbox.upper().x);
			//_sprite->setHeight(bbox.upper().y);
			result &= _sprite->render();
			// Asociamos textura
			//glBindTexture(GL_TEXTURE_2D, _background->getTextureID());
			//_guiTL->drawBoundingBox();
		}

		result &= _textLayout->render();


		//std::cout<<"[CTextLayoutNode::render] Resultado:"<<(result?"true":"false")<<"\n";
		return result;
	}

	bool CTextLayoutNode::setLogicEntity(logic::CTextBox* logicTL){
		// Si no asociamos ninguna entidad logica, terminamos
		if(!CUINode::setLogicEntity(logicTL))
			return false;

		// Si ya hemos asociado una representacion logica,
		// borramos la antigua
		if(_logicTL){
			_logicTL->removeListener(this);
			safeDelete(_logicTL);
		}

		if(!logicTL->addListener(this))
			return false;

		_logicTL = logicTL;

		_textLayout->loadResource(logicTL->font(), logicTL->fontSize(), TEXTURED);
		_textLayout->setPosition(_position.x, _position.y, _position.z);
		_textLayout->setAlignment(logicTL->alignment());
		_textLayout->setLineLength(_logicTL->lineSize());
		_textLayout->setText(logicTL->text());

		if(_logicTL->hasBackground()){
/*
			math::CBoundingBox bbox = _guiTL->getBoundingBox();
			math::CVector3f lower = bbox.getLowerVertex();
			math::CVector3f upper = bbox.getUpperVertex();
			float width = upper.x - lower.x;
			float height = upper.y - lower.y;
*/
			_sprite = CGraphicServer::instance().getSprite(logicTL->id());
			_sprite->setBounds(_position.x-20, _position.y-200, logicTL->lineSize()+40, 260);

			//_background->setBounds(lower.x, lower.y, logicTL->lineSize(), height);
			_background = true;
		}


		return true;
	}

	void CTextLayoutNode::positionChanged(const math::CVector3f& newPos) {
		_position = newPos;
		_textLayout->setPosition(newPos.x, newPos.y, newPos.z);
		_sprite->setBounds(_position.x-20, _position.y-200, _textLayout->lineLength()+40, 260);
	}

	void CTextLayoutNode::textChanged(const std::string& text){
		_textLayout->setText(text);
	}

	void CTextLayoutNode::fontAtribChanged(const std::string& font, const int fontSize, const float lineSize){
		_textLayout->loadResource(font, 35, TEXTURED);
		_textLayout->setLineLength(lineSize);
	}

	void CTextLayoutNode::alignmentChanged(const int alignType){
		_textLayout->setAlignment(alignType);
	}

}
