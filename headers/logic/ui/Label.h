/*
 * mLabel.h
 *
 *  Created on: 03/08/2010
 *      Author: jorge
 */

#ifndef MLABEL_H_
#define MLABEL_H_

#include "CUiComponent.h"

namespace logic {

	class CLabel: public CUiComponent {
	public:

		class LabelListener{
		public:
			virtual void textChanged(const CLabel* label, const std::string& text) = 0;
			virtual void fontSizeChanged(int size) = 0;
			virtual void fontChanged(const std::string& font) = 0;
		};

		CLabel();
		CLabel(float x, float y, const std::string& text);
		virtual ~CLabel();

		// Accesores
		std::string getText() 		const { return _text; }
		std::string getFontName() 	const { return _fontName; }
		const int 	getTextSize() 	const { return _fontSize; }

		// Modificadores
		void setText(const std::string& text);
		void setFont(const std::string& font);
		void setTextSize(int size);

		bool addListener(LabelListener* newListener);
		bool removeListener(LabelListener* oldListener);

	protected:

		void emitTextChange();
		void emitFontSizeChange();
		void emitFontChange();

		std::list<LabelListener*>		_labelListeners;

		std::string 					_text;		// Texto de la etiqueta
		std::string						_fontName;	// Fuente aplicada en la etiqueta
		int								_fontSize;	// Tamaño de la fuente

	};



}

#endif /* MLABEL_H_ */
