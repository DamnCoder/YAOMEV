/*
 * OglInmediateRenderer.h
 *
 *  Created on: 13/02/2011
 *      Author: jorge
 */

#ifndef OGLINMEDIATERENDERER_H_
#define OGLINMEDIATERENDERER_H_

#include "IRenderer.h"

// Includes de las librerias OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

namespace gui {

	class COglInmediateRenderer : public IRenderer {
	public:

		virtual ~COglInmediateRenderer() {}

		bool render(
				COglButton* button,
				COglButton::EButtonStatus status,
				const std::string& text,
				const float alpha,
				const math::CVector3f& spritePosition,
				const math::CVector3f& fontPosition,
				float width, float height){

			bool succesful = true;
			succesful &= render(button->getSprite(status), spritePosition, width, height);
			succesful &= render(button->getGfxText(), text, alpha, fontPosition);
			return succesful;
		}

		bool render(COglText* gfxText,
				const std::string& text,
				const float alpha,
				const math::CVector3f& position
				){

			FTFont* font = gfxText->font();

			glPushMatrix();

				// Habilitamos transparencia y el modo para texturas 2D
				glEnable(GL_BLEND);
				// Aplicamos transparencia
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				// Establecemos color con canal alpha
				glColor4f(1.0f, 1.0f, 1.0f, alpha);
				font->Render(text.c_str(), -1, FTPoint(position.x, position.y, position.z));
				glColor4f(1.0f,1.0f,1.0f,1.0f);
				// Deshabilitamos la transparencia
				glDisable(GL_BLEND);

				//renderBB(gfxText, text, position);

			glPopMatrix();

			return true;
		}

		bool renderBB(COglText* gfxText, const std::string& text, const math::CVector3f& position) {
			FTBBox bbox = gfxText->font()->BBox(text.c_str(), -1, FTPoint(position.x, position.y));
			//FTBBox bbox = _font->BBox(_text.c_str());
			float x1, y1, z1, x2, y2, z2;

			x1 = bbox.Lower().Xf(); y1 = bbox.Lower().Yf(); z1 = bbox.Lower().Zf();
			x2 = bbox.Upper().Xf(); y2 = bbox.Upper().Yf(); z2 = bbox.Upper().Zf();
			// Draw the bounding box
			glEnable(GL_LINE_SMOOTH);

			glColor3f(0.0, 1.0, 0.0);
			// Draw the front face
			glBegin(GL_LINE_LOOP);
				glVertex3f(x1, y1, z1);
				glVertex3f(x1, y2, z1);
				glVertex3f(x2, y2, z1);
				glVertex3f(x2, y1, z1);
			glEnd();

			glColor3f(1.0f, 1.0f, 1.0f);

			glDisable(GL_LINE_SMOOTH);
			return true;
		}

		bool render(
				COglText* gfxText,
				const std::string& text,
				const math::CVector3f& position,
				float orientation){

			glPushMatrix();
				glTranslatef(position.x, position.y, position.z);
				glRotatef(orientation, 0, 1, 0);
				FTFont* font = gfxText->font();
				font->Render(text.c_str());
			glPopMatrix();

			return true;
		}

		bool render(COglSprite* gfxSprite,  const math::CVector3f& position, float width, float height){
			TRGBAColor color = gfxSprite->getColor();
			uint textureID = gfxSprite->getTextureID();

			if(color.a>0){
				glPushMatrix();
					// Habilitamos transparencia y el modo para texturas 2D
					glEnable(GL_BLEND);
					// Aplicamos transparencia
					glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					// Movemos
					glTranslatef(position.x,position.y,position.z);

					// Establecemos color con canal alpha
					glColor4f(color.r, color.g, color.b, color.a);

					// Asociamos textura
					glBindTexture(GL_TEXTURE_2D, textureID);

					// Dibujamos el rectangulo
					glBegin(GL_TRIANGLE_STRIP);
						glTexCoord2f(0,0);
						glVertex3f(0,0,0);			// V0

						glTexCoord2f(1,0);
						glVertex3f(width,0,0);		// V2

						glTexCoord2f(0,1);
						glVertex3f(0,height,0);		// V1

						glTexCoord2f(1,1);
						glVertex3f(width,height,0);	// V3
					glEnd();

					glColor4f(1.0f,1.0f,1.0f,1.0f);

					// Deshabilitamos la transparencia y el modo de texturas 2D
					glDisable(GL_BLEND);

				glPopMatrix();
			}

			return true;
		}
	};
}


#endif /* OGLINMEDIATERENDERER_H_ */
