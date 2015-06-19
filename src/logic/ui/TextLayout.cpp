/*
 * mTextLayout.cpp
 *
 *  Created on: 06/08/2010
 *      Author: jorge
 */

#include "logic/ui/TextLayout.h"

namespace logic {

	CTextBox::CTextBox(float x, float y):
			CUiComponent(x, y, 0.0f, 0.0f),
			_font("arial.ttf"),
			_fontSize(35),
			_lineSize(250),
			_alignment(mCENTER),
			_hasBackground(false)
	{
		_id = "transparent.png";
	}

	CTextBox::~CTextBox() {
		_tbListeners.clear();
	}

	void CTextBox::setBackground(bool hasBackground){
		_hasBackground = hasBackground;
	}

	void CTextBox::setText(const std::string& text){
		_text = text;
		emitChangedText();
	}

	void CTextBox::setText(const std::string& text, float x, float y){
		_text = text;
		_position.x = x;
		_position.y = y;
		emitChangedText();
		emitChangedPosition();
	}

	void CTextBox::setFont(const std::string& font){
		_font = font;
		emitFontAtribChanged();
	}

	void CTextBox::setAlignment(const EMTextAlignment alignType){
		_alignment = alignType;
		emitChangedAlignment();
	}

	void CTextBox::setFontSize(const int fontSize){
		_fontSize = fontSize;
		emitFontAtribChanged();
	}

	void CTextBox::setLineSize(const float lineSize){
		_lineSize = lineSize;
		emitFontAtribChanged();
	}

	bool CTextBox::addListener(TextBoxListener* newOb){
		_tbListeners.push_back(newOb);
		return true;
	}

	bool CTextBox::removeListener(TextBoxListener* oldOb){
		_tbListeners.remove(oldOb);
		return true;
	}

	void CTextBox::emitChangedText(){
		std::list<CTextBox::TextBoxListener*>::const_iterator it;
		for(it=_tbListeners.begin(); it!=_tbListeners.end(); ++it)
			(*it)->textChanged(_text);
	}

	void CTextBox::emitChangedAlignment(){
		std::list<CTextBox::TextBoxListener*>::const_iterator it;
		for(it=_tbListeners.begin(); it!=_tbListeners.end(); ++it)
			(*it)->alignmentChanged(_alignment);
	}

	void CTextBox::emitFontAtribChanged(){
		std::list<CTextBox::TextBoxListener*>::const_iterator it;
		for(it=_tbListeners.begin(); it!=_tbListeners.end(); ++it)
			(*it)->fontAtribChanged(_font, _fontSize, _lineSize);
	}
}
