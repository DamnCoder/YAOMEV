/*
 * CButtonNode.cpp
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#include "gui/scene/ButtonNode.h"

#include "utilitys/utils.h"

#include "gui/graphicserver/GraphicServer.h"

namespace gui {

	CButtonNode::CButtonNode():
			CUINode(),
			_button(0),
			_logicButton(0),
			_text(""),
			_fontName("mekaniklet.ttf"),
			_fontSize(35),
			_status(COglButton::NORMAL){
	}

	CButtonNode::~CButtonNode() {
		//safeDelete(_button);
	}

	bool CButtonNode::render(){

		if(!_visible)
			return true;

		_button->getSprite(_status)->setAlpha(_alpha);
		_button->setFontType(_fontName, _fontSize);
		_renderer->render(_button, _status, _text, _alpha, _position, _fontPosition, _width, _height);

		return true;//_button->render();
	}

	void CButtonNode::load(const std::string& id){
		_button = CGraphicServer::instance().getButton(id);
	}

	bool CButtonNode::setLogicEntity(logic::CButton* logicButton){
		// Si no asociamos ninguna entidad logica, terminamos con exito
		if(!CUINode::setLogicEntity(logicButton))
			return false;

		// Si ya hemos asociado una representacion logica,
		// borramos la antigua
		if(_logicButton){
			_logicButton->removeListener(this);
			safeDelete(_logicButton);
		}

		// Nos añadimos como observador y si fallamos devolvemos false
		if(!logicButton->addListener(this))
			return false;

		// Asociamos la entidad logica
		_logicButton = logicButton;

		// Asignamos al boton los atributos
		_status = (COglButton::EButtonStatus)logicButton->status();

		textChanged(logicButton->text(), _logicButton->fontName(), _logicButton->fontSize());
		return true;

	}

	void CButtonNode::positionChanged(const math::CVector3f& newPos) {
		CUINode::positionChanged(newPos);
		_button->setFontType(_fontName, _fontSize);
		_button->setText(_text);
		_button->setBounds(newPos.x, newPos.y, _width, _height);
		_fontPosition = _button->fontPosition();
	}

	void CButtonNode::pressedButton(){
		_status = COglButton::PRESSED;
	}

	void CButtonNode::releasedButton(){
		_status = COglButton::NORMAL;
	}

	void CButtonNode::highlightedButton(){
		_status = COglButton::HIGHLIGHTED;
	}

	void CButtonNode::textChanged(const std::string& text, const std::string& font, int size) {
		_text = text;
		_fontName = font;
		_fontSize = size;

		_button->setFontType(_fontName, _fontSize);
		_button->setText(text);
		_button->setBounds(_position.x,	_position.y, _width, _height);
		_fontPosition = _button->fontPosition();
	}
}
