/*
 * Model.cpp
 *
 *  Created on: 17/05/2011
 *      Author: jorge
 */

#include "gui/graphicserver/md3/Model.h"

namespace gui{

	//----------------------------------------------------------------------------------------------------------------
	// Estado de la animacion
	//----------------------------------------------------------------------------------------------------------------

	// Constructor
	tAnimationState::tAnimationState ():
		animation(0),
		currTime (0.0f),
		oldTime (0.0f),
		_end(false),
		currentFrame (0),
		nextFrame (0),
		interp (0.0f)
	{
	}

	void tAnimationState::setup (tAnimation* a){
		if(!a) return;
		animation = a;
		currentFrame = a->startFrame;
		nextFrame = a->startFrame;
		interp = 0.0f;
		_end = false;
	}

	void tAnimationState::update (float dt){
		if(!animation) return ;
		//currTime += dt;	// Esto para cuando le pase el delta real no el tiempo total
		currTime = dt;

		if ((currTime - oldTime) > (1000.0f / animation->fps))
		{
			currentFrame = nextFrame;
			nextFrame++;

			// Fin de animacion, lanzar evento
			if (nextFrame > (animation->endFrame - 1)){
				nextFrame = animation->startFrame;
				_end = true;
			}

			oldTime = currTime;
		}
		interp = animation->fps * (currTime - oldTime) / 1000.0f;
	}

	//----------------------------------------------------------------------------------------------------------------
	// Tag basado en Cuaternios
	//----------------------------------------------------------------------------------------------------------------
	tQuatTag::tQuatTag (const tMd3Tag &tag){

		name = tag.name;

		origin.x = tag.origin.x;
		origin.y = tag.origin.y;
		origin.z = tag.origin.z;

		math::Matrix4x4f m;
		m.m11 = tag.axis[0][0]; m.m12 = tag.axis[0][1]; m.m13 = tag.axis[0][2];
		m.m21 = tag.axis[1][0]; m.m22 = tag.axis[1][1]; m.m23 = tag.axis[1][2];
		m.m31 = tag.axis[2][0]; m.m32 = tag.axis[2][1]; m.m33 = tag.axis[2][2];

		orient.fromMatrix (m);
		orient.normalize ();
	}

	//----------------------------------------------------------------------------------------------------------------
	// Modelo Md3
	//----------------------------------------------------------------------------------------------------------------

	void tModel::setSkin(const std::string& type){
		SkinMap::iterator it = skins.find(type);
		if(it == skins.end())
			currentSkin = &skins["default"];
		else
			currentSkin = &skins[type];
	}

	void tModel::setupVertexArrays() {

	}

}
