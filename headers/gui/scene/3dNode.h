/*
 * EntityGUI.h
 *
 *  Created on: 07/04/2010
 *      Author: jorge
 */

#ifndef ENTITYGUI_H_
#define ENTITYGUI_H_

#include "SceneNode.h"

#include "logic/entitys/Entity.h"
#include "utilitys/utils.h"

#include "math/BoundingBox.h"

namespace gui {

	using namespace logic;

	class C3dNode :
		public CSceneNode,
		public CEntity::EntityListener{

	public:
		C3dNode();
		virtual ~C3dNode();

		virtual bool render() = 0;

		virtual bool setLogicEntity(CEntity* logicEntity);

		virtual int numTris() = 0;

		//--------------------------------------------------------------------------------------
		// Metodos implementados del observador EntityListener
		//--------------------------------------------------------------------------------------
		virtual void changedPosition(const CEntity *entity, float x, float y, float z);
		virtual void changedOrientation(const CEntity* entity, float newOrientation);
		virtual void changedVisibility(const CEntity *entity, bool visible);
		virtual void changedSkin(const std::string& skin);
		virtual void changedScale(const float scale);

		//--------------------------------------------------------------------------------------
		// Accesores
		//--------------------------------------------------------------------------------------
		const math::CBoundingBox 	boundingBox() const { return _bb; };
		const math::CBoundingSphere boundingSphere() const { return _bs; };

	protected:
		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		math::CBoundingBox 		_bb;
		math::CBoundingSphere 	_bs;
		math::CPositionf		_position;
		float 					_orientation;
		bool 					_visible;
		std::string				_skin;
		float					_scale;
		CEntity*				_logicEntity;

	};

}

#endif /* ENTITYGUI_H_ */
