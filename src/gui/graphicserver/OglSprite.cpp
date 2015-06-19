/*
 * SpriteOGL.cpp
 *
 *  Created on: 13/01/2010
 *      Author: jorge
 */

#include "gui/graphicserver/OglSprite.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>

#include "gui/TextureManager.h"

namespace gui {

	//--------------------------------------------------------------------------------------
	// Setters
	//--------------------------------------------------------------------------------------

	void COglSprite::setBounds(float x, float y, float width, float height){

		setPosition(x, y);

		_width = width;
		_height = height;

		// Calculamos el bounding box del sprite
		_bbox = math::CBoundingBox(
				(_position.x ), (_position.y), 0,
				(_position.x+_width), (_position.y+_height), 0
		);
	}

	//--------------------------------------------------------------------------------------
	// Renderizado
	//--------------------------------------------------------------------------------------

	bool COglSprite::render(){

		if (_color.a>0)
			COglFunctions::render(_position, _color, _textureID, _width, _height);


		return true;
	}

	void COglSprite::drawBoundingBox(){
		math::CVector3f lower = _bbox.lower();
		math::CVector3f upper = _bbox.upper();

		// Draw the bounding box
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE); // GL_ONE_MINUS_SRC_ALPHA

			// Movemos
			glTranslatef(lower.x, lower.y, lower.z);

			glColor3f(0.0, 1.0, 0.0);
			// Draw the front face
			glBegin(GL_LINE_LOOP);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(upper.x, 0.0f, 0.0f);
				glVertex3f(upper.x, upper.y, 0.0f);
				glVertex3f(0.0f, upper.y, 0.0f);
			glEnd();

			glColor3f(1.0f, 1.0f, 1.0f);

			glDisable(GL_BLEND);
			glDisable(GL_LINE_SMOOTH);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}

}
