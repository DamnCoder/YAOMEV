/*
 * EntityBehaviors.h
 *
 *  Created on: 06/06/2011
 *      Author: jorge
 */

#ifndef ENTITYBEHAVIORS_H_
#define ENTITYBEHAVIORS_H_

#include "Behavior.h"

namespace logic {

class CEntityBehavior : public CBehavior {
public:
	CEntityBehavior(CEntity* entity, CGame* game):
			CBehavior(game),
			entity(entity){}
	virtual ~CEntityBehavior(){};

	virtual void activate() = 0;
	virtual void actualize(float dt) = 0;

protected:
	CEntity*	entity;
};

class CAvatarBehavior : public CEntityBehavior {
public:
	CAvatarBehavior(CAvatar* avatar, CGame* game):
			CEntityBehavior((CEntity*)avatar, game),
			_avatar(avatar){}
	virtual ~CAvatarBehavior(){};

	virtual void activate() = 0;
	virtual void actualize(float dt) = 0;

protected:
	CAvatar*	_avatar;
};

}

#endif /* ENTITYBEHAVIORS_H_ */
