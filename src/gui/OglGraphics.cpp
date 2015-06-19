/*
 * OglGraphics.cpp
 *
 *  Created on: 06/09/2010
 *      Author: jorge
 */

#include "gui/OglGraphics.h"

namespace gui {

	COglFunctions::COglFunctions() : _sceneManager(0){

	}

	COglFunctions::~COglFunctions() {
	}

	void COglFunctions::drawLine(math::CPositionf init, math::CPositionf end){
		glBegin(GL_LINES);
			glVertex3f(init.x, init.y, init.z);
			glVertex3f(end.x, end.y, end.z);
		glEnd();
	}

	void COglFunctions::drawGrid(int rows, int columns){
		rows*=10;
		columns*=10;
		glBegin(GL_LINES);
		for(int z=-rows; z<=rows; z+=10){
			glVertex3f(-rows, 0,z);
			glVertex3f(rows, 0,z);
		}

		for(int x=-columns; x<=columns; x+=10){
			glVertex3f(x, 0, -columns);
			glVertex3f(x, 0, columns);
		}
		glEnd();
	}

	void COglFunctions::draw3DAxis(float x, float y, float z){
		glEnable(GL_LINE_STIPPLE);
		glLineWidth(2);
		glBegin(GL_LINES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(x,    0.0f, 0.0f);

			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, y,    0.0f);

			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, z);
		glEnd();
		glLineWidth(1);
		glDisable(GL_LINE_STIPPLE);

	}

	void COglFunctions::drawGridWithAxis(){
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(0.2, 0.2, 0.2);
			drawGrid(12,12);
			draw3DAxis(150.0f, 150.0f, 150.0f);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	//void COglGraphics::render(const math::CPosition& position, const TRGBAColor color, uint textureID, const float width, const float height)

}
