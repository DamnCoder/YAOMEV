/*
 * Avatar.cpp
 *
 *  Created on: 12/04/2010
 *      Author: jorge
 */

#include "logic/entitys/Avatar.h"

#include "utilitys/utils.h"

namespace logic {

	CAvatar::CAvatar(const std::string& id,
			const std::string& name,
			float x, float y, float z,
			float orientation, bool visible,
			float scale ,
			const std::string& skin):
		CEntity(id, skin, x, y, z, orientation, visible, scale),
		_name(name),
		_legsAnimation("LEGS_STILL"),
		_torsoAnimation("TORSO_STILL"),
		_headAnimation("HEAD_STILL"),
		_changeAnimation(false),
		_elapsedTime(0.0f),
		_timeBeforeChangeAnimation(0.0f)
	{}

	CAvatar::~CAvatar() {
		//std::cout<<"[~CAvatar] "<<_id<<" Listeners restantes "<<_avatarListeners.size()<<"\n";
		_avatarListeners.clear();
	}

	void CAvatar::actualize(float dt){
		_elapsedTime += dt;
		if(_changeAnimation && _elapsedTime > _timeBeforeChangeAnimation){
			_changeAnimation = false;
			_elapsedTime = _timeBeforeChangeAnimation = 0.0f;
		}
	}

	void CAvatar::setName(const std::string& name){
		_name = name;
	}

	void CAvatar::setLegsAnimation(const std::string& animation) {
		_legsAnimation = animation;
		emitLegsAnimationChange();
	}

	void CAvatar::setTorsoAnimation(const std::string& animation) {
		_torsoAnimation = animation;
		emitTorsoAnimationChange();
	}

	void CAvatar::setHeadAnimation(const std::string& animation) {
		_headAnimation = animation;
		emitHeadAnimationChange();
	}

	bool CAvatar::addAnimationListener(CAvatarListener* newListener){
		_avatarListeners.push_back(newListener);
		return true;
	}

	bool CAvatar::removeAnimationListener(CAvatarListener* oldListener){
		_avatarListeners.remove(oldListener);
		return true;
	}

	void CAvatar::emitLegsAnimationChange(){
		TAvatarLisIterator it(_avatarListeners.begin()), end(_avatarListeners.end());
		for(;it!=end;++it)
			(*it)->legsAnimationChanged(_legsAnimation);
	}

	void CAvatar::emitTorsoAnimationChange(){
		TAvatarLisIterator it(_avatarListeners.begin()), end(_avatarListeners.end());
		for(;it!=end;++it)
			(*it)->torsoAnimationChanged(_torsoAnimation);
	}

	void CAvatar::emitHeadAnimationChange(){
		TAvatarLisIterator it(_avatarListeners.begin()), end(_avatarListeners.end());
		for(;it!=end;++it)
			(*it)->headAnimationChanged(_headAnimation);
	}

}
