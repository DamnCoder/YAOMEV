/*
 * OglButton.cpp
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#include "gui/graphicserver/OglButton.h"

#include "utilitys/utils.h"

#include "gui/graphicserver/GraphicServer.h"
#include "gui/TextureManager.h"
//#include

namespace gui {

	COglButton::~COglButton() {

		_buttonStates.clear();
	}

	bool COglButton::render(){
		return true;
	}

	void COglButton::setBounds(float x, float y, float width, float height){
		_spritePosition = math::CVector3f(x, y, 0);
		_width = width;
		_height = height;

		// Centro del boton
		float x_font = x + (width/2.0f);
		float y_font = y + (height/2.0f);

		math::CVector3f upper = _gfxText->getBoundingBox().upper();

		x_font = x_font - (upper.x/2.0f);
		y_font = y_font - (upper.y/2.0f);

		_fontPosition = math::CVector3f(x_font, y_font, 0);

		_gfxText->setPosition(x_font, y_font);
	}

	void COglButton::setPosition(float x, float y){
		_spritePosition  = math::CVector3f(x, y, 0);

		// Centro del boton
		float x_font = _buttonStates[_currentState]->getWidth()/2.0f;
		float y_font = _buttonStates[_currentState]->getHeight()/2.0f;

		_fontPosition = math::CVector3f(x_font, y_font, 0);

		_gfxText->setPosition(x_font, y_font);
	}

	void COglButton::setText(const std::string& text){
		_strText = text;
		_gfxText->setText(text);
	}

	void COglButton::setFontType(const std::string& fontName, uint fontSize){
		_fontType = fontName;
		_fontSize = fontSize;
		_gfxText->setFont(_fontType, _fontSize, TEXTURED);
	}

	void COglButton::doPressed(){
		_currentState = PRESSED;
	}

	void COglButton::doReleased(){
		_currentState = NORMAL;
	}

	void COglButton::doHighlighted(){
		_currentState = HIGHLIGHTED;
	}

}
