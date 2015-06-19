/*
 * CSceneNode.h
 *
 *  Created on: 05/04/2010
 *      Author: jorge
 */

#ifndef CSCENENODE_H_
#define CSCENENODE_H_

#include "gui/renderer/IRenderer.h"

namespace gui {

	class CSceneNode {
	public:
		/**
		 * Clase necesaria para la ordenacion de la lista STL
		 */
		class LessThanPtrs{
		public:
			const bool operator()(CSceneNode* sn1, CSceneNode* sn2) const{
				return *sn1 < *sn2;
			}
		};

		//--------------------------------------------------------------------------------------
		// Constructor / Destructor
		//--------------------------------------------------------------------------------------
		CSceneNode():
			_z(0),
			_renderer(0)
		{}

		virtual ~CSceneNode(){}

		/**
		 * Metodo abstracto que deberan implementar todas las clases
		 * que implementen el nodo de escena.
		 */
		virtual bool render() = 0;

		void setZ(int z){ _z = z; }
		void setRenderer(IRenderer* renderer){ _renderer = renderer; }

		int z() const { return _z; }

		bool operator<(const CSceneNode& snrhs) const { return this->_z < snrhs._z; }

	protected:

		int 		_z;		// Atributo que indica el orden de dibujado
		IRenderer*	_renderer;

	};

}

#endif /* CSCENENODE_H_ */
