/*
 * CButton.cpp
 *
 *  Created on: 27/07/2010
 *      Author: jorge
 */

#include "logic/ui/Button.h"

namespace logic {

	CButton::CButton(float x, float y, float width, float height) :
			CUiComponent(x, y, width, height),_status(0),_fontName("arial.ttf"), _fontSize(25) { _style = "webstyle_aqua"; }

	CButton::CButton(const std::string& text, float x, float y):
		CUiComponent(x, y, 0, 0),_status(0), _text(text),_fontName("arial.ttf"), _fontSize(25) {}

	CButton::CButton(const std::string& text, float x, float y, float width, float height):
		CUiComponent(x, y, width, height),_status(0), _text(text),_fontName("arial.ttf"), _fontSize(25) {}

	CButton::~CButton() {
		//std::cout<<"[delete:button] Quedan "<<_blisteners.size()<<" listeners de boton\n";
		_blisteners.clear();
	}

	void CButton::setText(const std::string& text, float x, float y){
		_text = text;
		_position.x = x;
		_position.y = y;
		emitTextChanged();
		emitChangedPosition();
	}

	void CButton::setText(const std::string& text) {
		setText(text, _position.x, _position.y);
	}

	void CButton::setFontSize(const int size) {
		_fontSize = size;
		emitTextChanged();
	}

	void CButton::setFont(const std::string& fontName) {
		_fontName = fontName;
		emitTextChanged();
	}

	void CButton::pressed(){
		_status = 1;
		emitPressedButton();
	}

	void CButton::released(){
		_status = 0;
		emitReleasedButton();
	}

	void CButton::highlighted(){
		_status = 2;
		emitHighlightedButton();
	}

	bool CButton::addListener(ButtonStateListener* newOb){
		_blisteners.push_back(newOb);
		return true;
	}

	bool CButton::removeListener(ButtonStateListener* oldOb){
		_blisteners.remove(oldOb);
		return true;
	}

	void CButton::mousePressed(const event::MouseEvent& e){
		if(e.getSource() == this)
			emitPressedButton();
	}

	void CButton::mouseEntered(const event::MouseEvent& e){
		if(e.getSource() == this)
			emitHighlightedButton();
	}

	void CButton::mouseExited(const event::MouseEvent& e){
		if(e.getSource() == this)
			emitReleasedButton();
	}

	void CButton::mouseReleased(const event::MouseEvent& e){
		if(e.getSource() == this)
			emitReleasedButton();
	}

	void CButton::emitPressedButton(){
		end = _blisteners.end();
		for(it=_blisteners.begin(); it!=end; ++it)
			(*it)->pressedButton();
	}

	void CButton::emitReleasedButton(){
		end = _blisteners.end();
		for(it=_blisteners.begin(); it!=end; ++it)
			(*it)->releasedButton();
	}

	void CButton::emitHighlightedButton(){
		end = _blisteners.end();
		for(it=_blisteners.begin(); it!=end; ++it)
			(*it)->highlightedButton();
	}

	void CButton::emitTextChanged(){
		end = _blisteners.end();
		for(it=_blisteners.begin(); it!=end; ++it)
			(*it)->textChanged(_text, _fontName, _fontSize);
	}
}
