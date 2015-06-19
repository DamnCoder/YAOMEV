/*
 * mLabel.cpp
 *
 *  Created on: 03/08/2010
 *      Author: jorge
 */

#include "logic/ui/Label.h"

namespace logic {

	CLabel::CLabel():
		CUiComponent(0, 0, 0, 0),
		_text(""),
		_fontName("arial.ttf"),
		_fontSize(25)
	{}

	CLabel::CLabel(float x, float y, const std::string& text) :
				CUiComponent(x, y, 0, 0),
				_text(text),
				_fontName("arial.ttf"),
				_fontSize(25)
	{}

	CLabel::~CLabel() {
		//std::cout<<"[delete:button] Quedan "<<_labelListeners.size()<<" listeners de boton\n";
		_labelListeners.clear();
	}

	void CLabel::setText(const std::string& text){
		// Solo emitimos el cambio si el texto ha cambiado
		if(_text!=text){
			_text = text;
			emitTextChange();
		}
	}

	void CLabel::setFont(const std::string& font){
		if(_fontName != font){
			_fontName = font;
			emitFontChange();
		}
	}

	void CLabel::setTextSize(int size) {
		if(_fontSize!=size){
			_fontSize = size;
			//emitFontSizeChange();
		}
	}

	bool CLabel::addListener(LabelListener* newListener){
		_labelListeners.push_back(newListener);
		return true;
	}

	bool CLabel::removeListener(LabelListener* oldListener){
		_labelListeners.remove(oldListener);
		return true;
	}

	void CLabel::emitTextChange(){
		std::list<CLabel::LabelListener*>::const_iterator
			it(_labelListeners.begin()),
			end(_labelListeners.end());
		for(; it!=end; ++it)
			(*it)->textChanged(this, _text);
	}

	void CLabel::emitFontSizeChange(){
		std::list<CLabel::LabelListener*>::const_iterator
			it(_labelListeners.begin()),
			end(_labelListeners.end());
		for(; it!=end; ++it)
			(*it)->fontSizeChanged(_fontSize);
	}

	void CLabel::emitFontChange(){
		std::list<CLabel::LabelListener*>::const_iterator
			it(_labelListeners.begin()),
			end(_labelListeners.end());
		for(; it!=end; ++it)
			(*it)->fontChanged(_fontName);
	}
}
