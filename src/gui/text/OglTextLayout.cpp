/*
 * mTextLayout.cpp
 *
 *  Created on: 05/08/2010
 *      Author: jorge
 */

#include "gui/text/OglTextLayout.h"

#include "gui/OglGraphics.h"

#include "utilitys/utils.h"

namespace gui {

	COglTextLayout::COglTextLayout(): _layout(new FTSimpleLayout()), _font(0), _visible(true) {
	}

	COglTextLayout::~COglTextLayout() {
		safeDelete(_layout);
	}

	bool COglTextLayout::render(){
		// Si el objeto existe pero no es visible devolvemos true
		if(!_visible)
			return true;

		COglFunctions::pushMatrix();
			COglFunctions::translate(_position.x, _position.y, _position.z);
			_layout->Render(_text.c_str());
		COglFunctions::popMatrix();

		//std::cout << "[CFTGLTextLayout::render] en pos["<<_position.x<<", "<<_position.y<<", "<<_position.z<<"]\n";
		return true;

	}

	bool COglTextLayout::loadResource(const std::string& fontName, int size, EFontType fontType){
		// Si ya hay una fuente cargada la eliminamos
		if(_font)
			safeDelete(_font);

		// Solicitamos al manejador de fuentes la fuente pedida
		_font = CFontsCache::instance().getFont(fontName, size, fontType);

		// Establecemos la fuente en el layout
		_layout->SetFont(_font);

		return true;
	}

	void COglTextLayout::setLineLength(const float lineSize){
		_layout->SetLineLength(lineSize);
	}

	void COglTextLayout::setAlignment(const int alignment){
		FTGL::TextAlignment align_converted;

		switch(alignment){
		case CENTER:
			align_converted = FTGL::ALIGN_CENTER;
			break;

		case RIGHT:
			align_converted = FTGL::ALIGN_RIGHT;
			break;

		case LEFT:
			align_converted = FTGL::ALIGN_LEFT;
			break;

		case JUSTIFY:
			align_converted = FTGL::ALIGN_JUSTIFY;
			break;

		default:
			align_converted = FTGL::ALIGN_CENTER;

		}
		_layout->SetAlignment(align_converted);
	}

	const math::CBoundingBox COglTextLayout::boundingBox(){
		FTBBox bbox = _font->BBox(_text.c_str());
		float x1, y1, z1, x2, y2, z2;

		x1 = bbox.Lower().Xf(); y1 = bbox.Lower().Yf(); z1 = bbox.Lower().Zf();
		x2 = bbox.Upper().Xf(); y2 = bbox.Upper().Yf(); z2 = bbox.Upper().Zf();

		return math::CBoundingBox(
				x1, y1, z1,
				x2, y2, z2);
	}

	void COglTextLayout::drawBoundingBox(){
		FTBBox bbox = _layout->BBox(_text.c_str());
		float x1, y1, z1, x2, y2, z2;

		x1 = bbox.Lower().Xf(); y1 = bbox.Lower().Yf(); z1 = bbox.Lower().Zf();
		x2 = bbox.Upper().Xf(); y2 = bbox.Upper().Yf(); z2 = bbox.Upper().Zf();

		// Draw the bounding box
		glEnable(GL_LINE_SMOOTH);

		glColor3f(0.0, 1.0, 0.0);

		glTranslatef(_position.x, _position.y, _position.z);
		// Draw the front face
		glBegin(GL_LINE_LOOP);
		//glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z1);
			glVertex3f(x1, y2, z1);
			glVertex3f(x2, y1, z1);
		glEnd();

		glColor3f(1.0f, 1.0f, 1.0f);

		glDisable(GL_LINE_SMOOTH);

	}
}
