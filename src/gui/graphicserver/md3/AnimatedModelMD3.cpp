/*
 * CModelMD3.cpp
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#include "gui/graphicserver/md3/AnimatedModelMD3.h"

#include "gui/renderer/ModelRenderer.h"
#include "gui/TextureManager.h"

#include "utilitys/utils.h"

#include <iostream>

namespace gui {

	void CAnimatedModelMd3::render(
			const math::CPositionf& position,
			const float orientation,
			const float scale)
	{
		CModelRenderer::instance().render(_lower, position, orientation, scale);
	}

	bool CAnimatedModelMd3::castShadow(const math::CPositionf& position, const float orientation){
		//updateModel(_lower);
		//updateModel(_upper);
		//COglGraphics::getInstance().renderAnimated(_lower, position, orientation);
		return true;

	}

	//----------------------------------------------------------------------------------
	// Modificadores
	//----------------------------------------------------------------------------------
	tAnimationState CAnimatedModelMd3::legsAnimation(const std::string& animation)
	{
		for(int i = 0; i < _lower->numOfAnimations; i++)
			if( !strcmp(_lower->animations[i].name, animation.c_str()) ){
				tAnimation* animation = &(_lower->animations[i]);
				_lowerAnimState.setup(animation);

				return _lowerAnimState;
			}

		printf("No se ha encontrado la animacion: %s\n",animation.c_str());

		return _lowerAnimState;
	}

	tAnimationState CAnimatedModelMd3::torsoAnimation(const std::string& animation){
		for(int i = 0; i < _upper->numOfAnimations; i++)
			if( !strcmp(_upper->animations[i].name, animation.c_str()) ){
				tAnimation* animation = &(_upper->animations[i]);
				_upperAnimState.setup(animation);

				return _upperAnimState;
			}

		printf("No se ha encontrado la animacion: %s\n",animation.c_str());
		return _upperAnimState;
	}

	tAnimationState CAnimatedModelMd3::headAnimation(const std::string& animation) {
		for(int i = 0; i < _head->numOfAnimations; i++)
			if( !strcmp(_head->animations[i].name, animation.c_str()) ){
				tAnimation* animation = &(_head->animations[i]);
				_headAnimState.setup(animation);

				return _headAnimState;
			}

		printf("No se ha encontrado la animacion: %s\n",animation.c_str());
		return _headAnimState;
	}

	void CAnimatedModelMd3::skin(const std::string& skin){
		_lower->setSkin(skin);
		_upper->setSkin(skin);
		_head->setSkin(skin);
	}

	void CAnimatedModelMd3::animation(
			const tAnimationState& lowerAnim,
			const tAnimationState& upperAnim,
			const tAnimationState& headAnim){
		_lower->animationState = lowerAnim;
		_upper->animationState = upperAnim;
		_head->animationState = headAnim;
	}

	//----------------------------------------------------------------------------------
	// Accesores
	//----------------------------------------------------------------------------------
	const tModel* CAnimatedModelMd3::get(int whichPart) const{
		switch(whichPart){
		case MODEL_LOWER:
			return _lower;
		case MODEL_UPPER:
			return _upper;
		case MODEL_HEAD:
			return _head;
		}
		return 0;

	}

	const int CAnimatedModelMd3::tris() const {
		unsigned int numTris = 0;
		for (int i = 0; i < _head->numMeshes; ++i)
			numTris += _head->meshes[i].numFaces;

		for (int i = 0; i < _upper->numMeshes; ++i)
			numTris += _upper->meshes[i].numFaces;

		for (int i = 0; i < _lower->numMeshes; ++i)
			numTris += _lower->meshes[i].numFaces;

		return numTris;
	}

	//----------------------------------------------------------------------------------
	// METODOS PROTEGIDOS
	//----------------------------------------------------------------------------------

	CAnimatedModelMd3::CAnimatedModelMd3(
			const std::string& filename,
			tModel* head,
			tModel* upper,
			tModel* lower):
				CResource(filename),
				_lower(lower),
				_upper(upper),
				_head(head),
				_lowerSkins(lower->skins),
				_upperSkins(upper->skins),
				_headSkins(head->skins)
	{
		getSkinNames();
	}

	CAnimatedModelMd3::~CAnimatedModelMd3()
	{
		destroy(_head);
		destroy(_upper);
		destroy(_lower);
	}

	void CAnimatedModelMd3::destroy(tModel *pModel)
	{
		for(int i = 0; i < pModel->numMeshes; i++)
		{
			if(pModel->meshes[i].pFaces)		delete [] pModel->meshes[i].pFaces;
			if(pModel->meshes[i].pNormals)		delete [] pModel->meshes[i].pNormals;
			if(pModel->meshes[i].pVerts)		delete [] pModel->meshes[i].pVerts;
			if(pModel->meshes[i].pTexVerts)	delete [] pModel->meshes[i].pTexVerts;
		}

		deleteVector(pModel->tags);
		if(pModel->pLinks)		free(pModel->pLinks);

		delete _head;
		delete _upper;
		delete _lower;
	}

	void CAnimatedModelMd3::getSkinNames() {
		 _skinNames.reserve(_lowerSkins.size());

		 SkinMap::iterator it(_lowerSkins.begin()), end(_lowerSkins.end());
		 for( ; it!=end; ++it)
			 _skinNames.push_back((*it).first);

	}

}
