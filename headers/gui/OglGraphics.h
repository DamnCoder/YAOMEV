/*
 * OglGraphics.h
 *
 *  Created on: 06/09/2010
 *      Author: jorge
 */

#ifndef OGLGRAPHICS_H_
#define OGLGRAPHICS_H_

#include "utilitys/Singleton.h"


#include "SceneManager.h"

// Includes de las librerias OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <stack>

namespace gui {

	typedef float GLvector4f[4];							// Typedef's For VMatMult Procedure
	typedef float GLmatrix16f[16];							// Typedef's For VMatMult Procedure

	enum EAxis{
		X,
		Y,
		Z
	};

	struct TRGBAColor{
		float r;
		float g;
		float b;
		float a;

		TRGBAColor():
			r(1.0f),
			g(1.0f),
			b(1.0f),
			a(1.0f)
		{}

		TRGBAColor(float r, float g, float b, float a):
			r(r),
			g(g),
			b(b),
			a(a)
		{}
	};

	class COglFunctions: public CSingleton<COglFunctions> {

	friend class CSingleton<COglFunctions>;

	public:

		static void backgroundColor(float r, float g, float b, float a) {
			glClearColor(r, g, b, a);
		}

		/**
		 * Dibuja una linea
		 */
		static void drawLine(math::CPositionf init, math::CPositionf end);

		/**
		 * Dibuja un plano con forma de malla
		 */
		static void drawGrid(int rows, int columns);

		/**
		 * Dibuja los ejes XYZ de colores en el origen del mundo 3D
		 */
		static void draw3DAxis(float x, float y, float z);

		static void drawGridWithAxis();

		static void multMatrix(const float* matrix){
			glMultMatrixf((GLfloat*)matrix);
		}

		static void pushMatrix(){
			glPushMatrix();
		}

		static void popMatrix(){
			glPopMatrix();
		}

		void drawRectangle(float x, float y, float z, float width, float height){
			glPushMatrix();
				// Movemos
				glTranslatef(x, y, z);

				glBegin(GL_TRIANGLE_STRIP);

					glVertex3f(0,0,0);
					glVertex3f(width,0,0);
					glVertex3f(0,height,0);
					glVertex3f(width,height,0);

				glEnd();

			glPopMatrix();
		}

		static void rotate(EAxis axis, float degrees){
			switch(axis){
			case X:
				glRotatef(degrees, 1, 0, 0);
				return;
			case Y:
				glRotatef(degrees, 0, 1, 0);
				return;
			case Z:
				glRotatef(degrees, 0, 0, 1);
				return;
			}
		}

		static void translate(float x, float y, float z){
			glTranslatef(x, y, z);
		}

		static void render(
				const math::CPositionf& position,
				const TRGBAColor color,
				unsigned int textureID,
				const float width, const float height){
			glPushMatrix();
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
				glDisable(GL_BLEND);
			glPopMatrix();
		}

		void setSceneManager(CSceneManager* sceneManager){
			_sceneManager = sceneManager;
		}

		void activateStencil(){
			glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT | GL_STENCIL_BUFFER_BIT );

				glDisable(GL_LIGHTING);
				glDepthMask(GL_FALSE);
				glDepthFunc(GL_LEQUAL);

				// Habilitamos el stencil test
				glEnable(GL_STENCIL_TEST);

		}

		void deactivateStencil() {
				glEnable(GL_LIGHTING);
			glPopAttrib();
		}

		void enableLight() {
			glEnable(GL_LIGHTING);
		}

		void disableLight() {
			glDisable(GL_LIGHTING);
		}

		void enableBlending(){
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		}

		void disableBlending(){
			glDisable(GL_BLEND);
			glColor4f(1.0f,1.0f,1.0f,1.0f);
		}

		void enable2D(){

			int vPort[4];

			glGetIntegerv(GL_VIEWPORT, vPort);

			// Clear Projection Matrix
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();

			// Depth testing and lighting are disabled  for 2D rendering until
			// we are finished this mode
			glDisable(GL_LIGHTING);
			glDisable(GL_DEPTH_TEST);

			// Set up orthogonal projection onto window's screen space
			glOrtho(0.0f, vPort[2], 0.0f, vPort[3], -1.0f, 1.0f);

			// Clear model transform
			glMatrixMode (GL_MODELVIEW);
			glPushMatrix ();
			glLoadIdentity ();

		}

		void disable2D(){

			// Restore previous model/projection transformation state
			glPopMatrix ();
			glMatrixMode (GL_PROJECTION);

			glEnable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);

			glPopMatrix ();
			glMatrixMode (GL_MODELVIEW);
		}


	private:

		COglFunctions();

		virtual ~COglFunctions();

		CSceneManager* _sceneManager;


	};

}

#endif /* OGLGRAPHICS_H_ */
