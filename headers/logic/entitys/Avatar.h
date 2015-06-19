/*
 * Avatar.h
 *
 *  Created on: 12/04/2010
 *      Author: jorge
 */

#ifndef AVATAR_H_
#define AVATAR_H_

#include "Entity.h"

#include <vector>

namespace logic {

	class CAvatar: public logic::CEntity {
	public:

		class CAvatarListener{
		public:
			virtual void legsAnimationChanged(const std::string& animation) = 0;
			virtual void torsoAnimationChanged(const std::string& animation) = 0;
			virtual void headAnimationChanged(const std::string& animation) = 0;
		};

		CAvatar(const std::string& id,
				const std::string& name,
				float x, float y, float z,
				float orientation, bool visible,
				float scale = 1,
				const std::string& skin = "default");

		virtual ~CAvatar();

		virtual void actualize(float dt);

		// Modificadores
		void setName(const std::string& name);
		void setAnimationEnd(const bool end ) { _animationEnd = end; }

		void setLegsAnimation(const std::string& animation);
		void setTorsoAnimation(const std::string& animation);
		void setHeadAnimation(const std::string& animation);

		// Accesores
		const std::string 	legsAnimation()		const { return _legsAnimation; }
		const std::string 	torsoAnimation()	const { return _torsoAnimation; }
		const std::string 	headAnimation()		const { return _headAnimation; }
		const std::string 	name()				const { return _name; }
		const bool			animationEnd()		const { return _animationEnd; }

		bool addAnimationListener(CAvatarListener* newListener);
		bool removeAnimationListener(CAvatarListener* oldListener);

	protected:

		std::string 		_name;
		std::string 		_legsAnimation;
		std::string 		_torsoAnimation;
		std::string 		_headAnimation;

		bool		_changeAnimation;
		bool		_animationEnd;

		float		_elapsedTime;
		float		_timeBeforeChangeAnimation;
	private:

		void emitLegsAnimationChange();
		void emitTorsoAnimationChange();
		void emitHeadAnimationChange();


		typedef std::list<CAvatarListener*>::iterator TAvatarLisIterator;

		std::list<CAvatarListener*> _avatarListeners;

	};

}

#endif /* AVATAR_H_ */
