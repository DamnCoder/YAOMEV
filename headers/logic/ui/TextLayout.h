/*
 * mTextLayout.h
 *
 *  Created on: 06/08/2010
 *      Author: jorge
 */

#ifndef MTEXTLAYOUT_H_
#define MTEXTLAYOUT_H_

#include "CUiComponent.h"

namespace logic {

	class CTextBox: public logic::CUiComponent {

	public:

		enum EMTextAlignment{
			mCENTER,
			mRIGHT,
			mLEFT,
			mJUSTIFY,
		};

		class TextBoxListener{
		public:
			virtual void textChanged(const std::string& text) = 0;
			virtual void fontAtribChanged(const std::string& font, const int fontSize, const float lineSize) = 0;
			virtual void alignmentChanged(const int alignType) = 0;
		};

		CTextBox(float x, float y);
		virtual ~CTextBox();

		void setBackground(bool hasBackground);
		void setText(const std::string& text);
		void setText(const std::string& text, float x, float y);
		void setFont(const std::string& font);
		void setAlignment(const EMTextAlignment alignType);
		void setFontSize(const int fontSize);
		void setLineSize(const float lineSize);

		const std::string& 	font()			const { return _font; }
		const std::string&	text() 			const { return _text; }
		const int 			alignment() 	const { return _alignment; }
		const int	 		fontSize() 		const { return _fontSize; }
		const float			lineSize() 		const { return _lineSize; }
		const bool 			hasBackground() const { return _hasBackground; }

		bool addListener(TextBoxListener* newOb);
		bool removeListener(TextBoxListener* oldOb);

	protected:
		std::string 		_text;			/** Texto a representarse */
		std::string			_font;			/** Fuente para el texto */
		int					_fontSize;		/** Tamaño de la fuente */
		float				_lineSize;		/** Tamaño de maximo de la linea */
		EMTextAlignment		_alignment;		/** Tipo de alineacion del texto */
		bool				_hasBackground;

		// Tipo de espaciado

		// Color de fondo

		// Borde

		//

	private:
		void emitChangedText();
		void emitChangedAlignment();
		void emitFontAtribChanged();

		std::list<TextBoxListener*> _tbListeners;
	};

}

#endif /* MTEXTLAYOUT_H_ */
