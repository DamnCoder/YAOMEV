/*
 * Entidad.cpp
 *
 *  Created on: 20/12/2009
 *      Author: jorge
 */

#include "logic/entitys/Entity.h"

namespace logic {

	//--------------------------------------------------------------------------------------
	// Constructores / Destructores
	//--------------------------------------------------------------------------------------

	CEntity::CEntity(float x, float y, float z):
			_behavior(0),
			_id(""),
			_skin("default"),
			_position(x, y, z),
			_orientation(0),
			_scale(1),
			_visible(false),
			_reflection(false)
	{
	}

	CEntity::CEntity(
		const std::string& id,
		float x, float y, float z,
		float orientation,
		bool visible,
		float scale):
			_behavior(0),
			_id(id),
			_skin("default"),
			_position(x, y, z),
			_orientation(orientation),
			_scale(scale),
			_visible(visible),
			_reflection(false)
	{
	}

	CEntity::CEntity(
		const std::string& id,
		const std::string& skin,
		float x, float y, float z,
		float orientation,
		bool visible,
		float scale):
			_behavior(0),
			_id(id),
			_skin(skin),
			_position(x, y, z),
			_orientation(orientation),
			_scale(scale),
			_visible(visible),
			_reflection(false)
	{
	}

	CEntity::~CEntity() {
		//std::cout<<"[~CEntity] "<<_id<<" Listeners restantes "<<_listeners.size()<<"\n";
		_listeners.clear();
	}

	//--------------------------------------------------------------------------------------
	// Setters
	//--------------------------------------------------------------------------------------

	void CEntity::setPosition(float x, float y, float z){
		setPosition(math::CPositionf(x, y, z));
		emitChangedPosition();
	}

	void CEntity::setPosition(const math::CPositionf& newPosition){
		if(_position != newPosition){
			_position = newPosition;
			emitChangedPosition();
		}
	}

	void CEntity::setOrientation(float newOrientation){

		// Si la orientacion no cambia no hacemos nada
		if(_orientation != newOrientation){
			if (newOrientation > 360)
				newOrientation = (float)fmod((double)newOrientation, 360.0);

			if (newOrientation < 0){
				//newOrientation = (-newOrientation);
				newOrientation = (float)fmod((double)newOrientation, 360.0);
			}

			_orientation = newOrientation;
			emitChangedOrientation();
		}
	}

	void CEntity::setVisible(bool visible){
		_visible = visible;
		emitChangedVisibility();
	}

	void CEntity::setSkin(const std::string& skin){
		_skin = skin;
		emitChangedSkin();
	}

	void CEntity::setScale(const float scale) {
		_scale = scale;
		emitChangedScale();
	}

	//--------------------------------------------------------------------------------------
	// Añadir / Quitar obervadores de la entidad
	//--------------------------------------------------------------------------------------

	bool CEntity::addListener(EntityListener* newListener){
		_listeners.push_back(newListener);
		return true;
	}

	bool CEntity::removeListener(EntityListener* oldListener){
		_listeners.remove(oldListener);
		return true;
	}

	//--------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	// Comunicacion de eventos al observador
	//--------------------------------------------------------------------------------------

	void CEntity::emitChangedPosition(){
		std::list<EntityListener*>::const_iterator it;
		for(it=_listeners.begin(); it!=_listeners.end(); ++it){
			(*it)->changedPosition(this, _position.x,_position.y,_position.z);
		}
	}

	void CEntity::emitChangedOrientation(){
		std::list<EntityListener*>::const_iterator it;
		for(it=_listeners.begin(); it!=_listeners.end(); ++it){
			(*it)->changedOrientation(this, _orientation);
		}
	}

	void CEntity::emitChangedVisibility(){
		std::list<CEntity::EntityListener*>::const_iterator it;
		for(it=_listeners.begin(); it!=_listeners.end(); ++it){
			(*it)->changedVisibility(this,_visible);
		}
	}

	void CEntity::emitChangedSkin(){
		std::list<CEntity::EntityListener*>::const_iterator
			it(_listeners.begin()),
			end(_listeners.end());
		for(;it!=end;++it)
			(*it)->changedSkin(_skin);
	}

	void CEntity::emitChangedScale(){
		std::list<CEntity::EntityListener*>::const_iterator
			it(_listeners.begin()),
			end(_listeners.end());
		for(;it!=end;++it)
			(*it)->changedScale(_scale);
	}
	//--------------------------------------------------------------------------------------
}
