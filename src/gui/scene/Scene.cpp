/*
 * Scene.cpp
 *
 *  Clase contenedora de la escena grafica.
 *  Los nodos son elementos graficos a dibujarse en el juego.
 *  Contiene todos los elementos graficos a dibujarse en un frame y
 *  es la responsable de dibujarlos.
 *
 *  Created on: 05/04/2010
 *      Author: jorge
 */

#include "gui/scene/Scene.h"

#include "gui/scene/SceneNode.h"
#include "gui/scene/3dNode.h"

#include <GL/gl.h>
#include <GL/glu.h>

namespace gui {

	bool CScene::render(){
		_nodes.sort(CSceneNode::LessThanPtrs());

		_end = _nodes.end();
		for(_it=_nodes.begin(); _it!=_end; ++_it){
			if(!(*_it)->render())
				return false;
		}
		return true;
	}

	bool CScene::inverseRender(){
		_nodes.sort(CSceneNode::LessThanPtrs());
		_it = _nodes.begin();
		_end = --_nodes.end();
		for(; _it!=_end; --_end){
			if(!(*_end)->render())
				return false;
		}
		return true;
	}
//------------------------------------------------------------------------------
	bool CFrustumCullingScene::render(){
		_totalNodesDrawn = 0;
		_nodes.sort(CSceneNode::LessThanPtrs());

		glGetFloatv( GL_PROJECTION_MATRIX, _projection.m);
		glGetFloatv( GL_MODELVIEW_MATRIX, _modelview.m );

		_frustum->calculate(_projection, _modelview);

		_end = _nodes.end();
		for(_it=_nodes.begin(); _it!=_end; ++_it){
			const math::CBoundingSphere bs = (*_it)->boundingSphere();

			glPushMatrix();
				glTranslatef(bs.center().x, bs.center().y, bs.center().z);
				drawSphere(bs.radius(), 10, 10);
			glPopMatrix();
			if(_frustum->isSphereInside(bs.center(), bs.radius())){
				++_totalNodesDrawn;
				if(!(*_it)->render())
					return false;
			}
		}


		//std::cout<<"Nodos dibujados: "<<_totalNodesDrawn<<"\n";

		if(_totalNodesDrawn!=_previusNodesDrawn){
			//std::cout<<"Nodos dibujados: "<<_totalNodesDrawn<<"\n";
			_previusNodesDrawn = _totalNodesDrawn;
		}
		return true;
	}

	void CFrustumCullingScene::drawSphere(double r, int lats, int longs) {
		int i, j;
		for(i = 0; i <= lats; i++) {
			double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
			double z0  = sin(lat0);
			double zr0 =  cos(lat0);

			double lat1 = M_PI * (-0.5 + (double) i / lats);
			double z1 = sin(lat1);
			double zr1 = cos(lat1);

			glBegin(GL_QUAD_STRIP);
			for(j = 0; j <= longs; j++) {
				double lng = 2 * M_PI * (double) (j - 1) / longs;
				double x = cos(lng);
				double y = sin(lng);

				glNormal3f(x * zr0, y * zr0, z0);
				glVertex3f(x * zr0, y * zr0, z0);
				glNormal3f(x * zr1, y * zr1, z1);
				glVertex3f(x * zr1, y * zr1, z1);
			}
			glEnd();
		}
	}

}
