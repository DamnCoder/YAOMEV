/*
 * AnimatedEntity.h
 *
 *  Created on: 07/04/2010
 *      Author: jorge
 */

#ifndef ANIMATEDENTITY_H_
#define ANIMATEDENTITY_H_

#include "3dNode.h"

#include "gui/graphicserver/md3/AnimatedModelMD3.h"
#include "logic/entitys/Avatar.h"

namespace gui {

	class CAnimatedEntityNode :
		public C3dNode,
		public CAvatar::CAvatarListener{

	public:

		CAnimatedEntityNode(CAnimatedModelMd3* model);

		~CAnimatedEntityNode();

		bool render();

		bool setLogicEntity(CAvatar* logicAvatar);

		void legsAnimationChanged(const std::string& animation);
		void torsoAnimationChanged(const std::string& animation);
		void headAnimationChanged(const std::string& animation);

		int numTris();

	protected:

		void setAnimation(const std::string& animation);

		//----------------------------------------------------------------------------------
		// Modificadores
		//----------------------------------------------------------------------------------
		void legsAnimation(const std::string& animation);
		void torsoAnimation(const std::string& animation);
		void headAnimation(const std::string& animation);

		void updateAnimation();

		CAnimatedModelMd3* 	_animatedModel;

		tAnimationState 	_lowerAnimState;
		tAnimationState 	_upperAnimState;
		tAnimationState 	_headAnimState;

		CAvatar*			_logicAvatar;

	};

	class CAnimatedEntityShadowNode : public CAnimatedEntityNode {
	public:
		bool render();
	};
}

#endif /* ANIMATEDENTITY_H_ */
