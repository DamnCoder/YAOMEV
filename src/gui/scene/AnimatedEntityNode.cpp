/*
 * AnimatedEntity.cpp
 *
 *  Created on: 07/04/2010
 *      Author: jorge
 */

#include "gui/scene/AnimatedEntityNode.h"

#include "app/Application.h"

#include "utilitys/utils.h"

#include "gui/graphicserver/GraphicServer.h"

namespace gui {

	CAnimatedEntityNode::CAnimatedEntityNode(CAnimatedModelMd3* model):
		C3dNode(),
		_animatedModel(model),
		_logicAvatar(0)
	{
	}

	CAnimatedEntityNode::~CAnimatedEntityNode() {
		if(_logicAvatar)
			_logicAvatar->removeListener(this);
	}

	bool CAnimatedEntityNode::render(){
		if(!_visible) return true;

		updateAnimation();

		_animatedModel->skin(_skin);
		_animatedModel->animation(_lowerAnimState, _upperAnimState, _headAnimState);
		_animatedModel->render(_position, _orientation, _scale);
		return true;
	}

	bool CAnimatedEntityNode::setLogicEntity(CAvatar* logicAvatar){
		if(!C3dNode::setLogicEntity((CEntity*)logicAvatar))
			return false;

		if(_logicAvatar)
			_logicAvatar->removeAnimationListener(this);

		// Nos añadimos como observador y si fallamos devolvemos false
		if(!logicAvatar->addAnimationListener(this))
			return false;

		_logicAvatar = logicAvatar;

		legsAnimation(logicAvatar->legsAnimation());
		torsoAnimation(logicAvatar->torsoAnimation());
		headAnimation(logicAvatar->headAnimation());

		return true;
	}

	void CAnimatedEntityNode::legsAnimationChanged(const std::string& animation){
		_lowerAnimState = _animatedModel->legsAnimation(animation);
	}

	void CAnimatedEntityNode::torsoAnimationChanged(const std::string& animation){
		_upperAnimState = _animatedModel->torsoAnimation(animation);
	}

	void CAnimatedEntityNode::headAnimationChanged(const std::string& animation){
		_headAnimState = _animatedModel->headAnimation(animation);
	}

	int CAnimatedEntityNode::numTris(){
		return _animatedModel->tris();
	}

	void CAnimatedEntityNode::legsAnimation(const std::string& animation){
		_lowerAnimState = _animatedModel->legsAnimation(animation);
	}

	void CAnimatedEntityNode::torsoAnimation(const std::string& animation){
		_upperAnimState = _animatedModel->torsoAnimation(animation);
	}

	void CAnimatedEntityNode::headAnimation(const std::string& animation){
		_headAnimState = _animatedModel->headAnimation(animation);
	}

	void CAnimatedEntityNode::updateAnimation() {
		float dt = (float)app::CApplication::getApp()->getAppTime();
/*
		if(_lowerAnimState.end()) _logicAvatar->setAnimationEnd(true);
		if(_upperAnimState.end()) _logicAvatar->setAnimationEnd(true);
		if(_headAnimState.end()) _logicAvatar->setAnimationEnd(true);
*/
		_lowerAnimState.update(dt);
		_upperAnimState.update(dt);
		_headAnimState.update(dt);
	}

//----------------------------------------------------------------------------------------

	bool CAnimatedEntityShadowNode::render(){
		if(!_visible) return true;
		return true;
		//return _animatedModel->castShadow();
	}



}
