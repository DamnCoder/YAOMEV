/*
 * 3dNode.cpp
 *
 *  Created on: 14/08/2011
 *      Author: jorge
 */

#include "gui/scene/3dNode.h"

namespace gui {

	C3dNode::C3dNode():
		CSceneNode(),
		_position(),
		_orientation(0),
		_visible(true),
		_skin("default"),
		_scale(1.0f),
		_logicEntity(0){}

	C3dNode::~C3dNode(){
		if(_logicEntity)
			_logicEntity->removeListener(this);
	}

	bool C3dNode::setLogicEntity(CEntity* logicEntity){
		// Si no asociamos ninguna entidad logica, terminamos con exito
		if(!logicEntity)
			return true;

		// Si ya hemos asociado una representacion logica,
		// borramos la antigua
		if(_logicEntity)
			_logicEntity->removeListener(this);


		// Nos añadimos como observador y si fallamos devolvemos false
		if(!logicEntity->addListener(this))
			return false;

		_logicEntity = logicEntity;

		_orientation = logicEntity->orientation();
		_position = logicEntity->position();
		_visible = logicEntity->visible();
		_skin = logicEntity->skin();
		_scale = logicEntity->scale();

		//cout<<"[EntityGuiNode::setLogicEntity] Posicion "<<_position<<"\n";

		return true;

	}

	//--------------------------------------------------------------------------------------
	// Metodos implementados del observador EntityListener
	//--------------------------------------------------------------------------------------

	void C3dNode::changedPosition(const CEntity *entidad, float x, float y, float z){
		_position.x = x;
		_position.y = y;
		_position.z = z;
	}

	void C3dNode::changedOrientation(const CEntity* entity, float newOrientation){
		_orientation = newOrientation;
	}

	void C3dNode::changedVisibility(const CEntity *entidad, bool visible){
		_visible = visible;
	}

	void C3dNode::changedSkin(const string& skin){
		_skin = skin;
	}

	void C3dNode::changedScale(const float scale) {
		_scale = scale;
	}


}
