/*
 * mTextLayout.h
 *
 *  Created on: 05/08/2010
 *      Author: jorge
 */

#ifndef MFTGLTEXTLAYOUT_H_
#define MFTGLTEXTLAYOUT_H_

#include <FTGL/ftgl.h>

#include <string>

#include "math/BoundingBox.h"

#include "FontsManager.h"

namespace gui {

	class COglTextLayout {

	public:

		enum EMTextAlignment{
			CENTER,
			RIGHT,
			LEFT,
			JUSTIFY,
		};

		COglTextLayout();

		virtual ~COglTextLayout();

		bool render();

		bool loadResource(const std::string& fontName, int size, EFontType fontType);

		void setLineLength(const float lineSize);
		void setAlignment(const int alignment);
		void setPosition(float x, float y, float z){
			_position.x = x;
			_position.y = y;
			_position.z = z;
		}

		void setOrientation(float orientation){ _orientation = orientation; }
		void setText(const std::string& text){ _text = text; }
		void setVisible(bool visible){ _visible = visible; }

		const float					lineLength()	const { return _layout->GetLineLength(); }
		const math::CPositionf 		position() 		const { return _position; }
		const std::string 			text() 			const { return _text; }
		const bool	 				visible() 		const { return _visible; }
		const math::CBoundingBox	boundingBox();

		void drawBoundingBox();

	protected:

		FTSimpleLayout* _layout;

		FTFont*			_font;

		std::string 	_text;

		math::CPositionf	_position;

		float			_orientation;

		bool			_visible;

	};

}

#endif /* MFTGLTEXTLAYOUT_H_ */
