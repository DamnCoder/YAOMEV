/**
 * Scene.h
 *
 *  Clase contenedora de la escena grafica.
 *  Los nodos son elementos graficos a dibujarse en el juego.
 *  Contiene todos los elementos graficos a dibujarse en un frame y
 *  es la responsable de dibujarlos.
 *
 *  Created on: 05/04/2010
 *      Author: jorge
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <list>

#include "math/CFrustum.h"

namespace gui {

	class CSceneNode;
	class C3dNode;

	class CScene {
	public:

		typedef std::list<CSceneNode*> TNodeList;

		CScene(){}
		~CScene(){}

		//--------------------------------------------------------------------------------------
		// METODOS DE INSERCION / BORRADO DE NODOS DE LA ESCENA
		//--------------------------------------------------------------------------------------

		bool insertNode(CSceneNode* newNode){
			_nodes.push_back(newNode);
			return true;
		}

		bool deleteNode(CSceneNode* oldNode){
			_nodes.remove(oldNode);
			return true;
		}

		unsigned int size() const { return _nodes.size(); }
		bool render();
		bool inverseRender();

	protected:
		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		TNodeList 			_nodes;
		TNodeList::iterator _it, _end;

	};

	class CFrustumCullingScene {
	public:

		typedef std::list<C3dNode*> T3dNodeList;

		CFrustumCullingScene() :
			_frustum(new math::CFrustum),
			_totalNodesDrawn(0),
			_previusNodesDrawn(0){}

		~CFrustumCullingScene(){ delete _frustum; }

		//--------------------------------------------------------------------------------------
		// METODOS DE INSERCION / BORRADO DE NODOS DE LA ESCENA
		//--------------------------------------------------------------------------------------

		bool insertNode(C3dNode* newNode){
			_nodes.push_back(newNode);
			return true;
		}

		bool deleteNode(C3dNode* oldNode){
			_nodes.remove(oldNode);
			return true;
		}

		unsigned int size() const { return _nodes.size(); }
		bool render();

	protected:
		void drawSphere(double r, int lats, int longs);

		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		T3dNodeList				_nodes;
		T3dNodeList::iterator	_it, _end;

		math::CFrustum*			_frustum;
		math::Matrix4x4f 		_projection, _modelview;

		int _totalNodesDrawn, _previusNodesDrawn;

	};

}

#endif /* SCENE_H_ */
