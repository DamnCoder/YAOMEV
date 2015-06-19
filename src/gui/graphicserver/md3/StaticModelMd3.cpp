/*
 * StaticModelMd3.cpp
 *
 *  Created on: 23/08/2010
 *      Author: jorge
 */

#include "gui/graphicserver/md3/StaticModelMd3.h"

#include "gui/TextureManager.h"
#include "gui/renderer/ModelRenderer.h"

#include "persist/md3/LoadMD3.h"
#include "persist/md3/SkinLoader.h"

#include "utilitys/Log.h"

namespace gui {

	CStaticModelMd3::CStaticModelMd3(const std::string& filename):
			CResource(filename) {
		memset(&_model,  0, sizeof(tModel));
	}

	CStaticModelMd3::~CStaticModelMd3() {
		destroyModel(&_model);
	}

	bool CStaticModelMd3::render(
			const math::CPositionf& position,
			const float orientation,
			const float scale){
		CModelRenderer::instance().render(&_model, position, orientation, scale);
		return true;

	}

	bool CStaticModelMd3::castTransparency(
			const math::CPositionf& position,
			const float orientation,
			const float scale,
			TRGBAColor transpColor){

		CModelRenderer::instance().renderTransparency(&_model, position, orientation, scale, transpColor);

		return true;

	}

	void CStaticModelMd3::setTexture(uint textureID){

		tSkin* currentSkin = _model.currentSkin;
		MaterialMap::iterator it, end;
		it = currentSkin->materials.begin();
		end = currentSkin->materials.end();
		for(; it!=end; ++it)
			(*it).second.textureId = textureID;

	}

	void CStaticModelMd3::skin(const std::string& skin){
		_model.setSkin(skin);
	}

	unsigned int CStaticModelMd3::numTris() const {
		unsigned int numTris = 0;
		for (int i = 0; i < _model.numMeshes; ++i)
			numTris += _model.meshes[i].numFaces;

		return numTris;
	}

	const int CStaticModelMd3::numVerts() const {
		int numVerts = 0;
		for(int i=0; i<_model.numMeshes; ++i)
			numVerts += _model.meshes[i].numVerts;
		return numVerts;
	}

	bool CStaticModelMd3::loadModel(const std::string& path, const std::string& modelName, bool dl, bool shadow){

		if(path.empty() && modelName.empty())
			return false;

		persist::CLoadMD3 md3Loader;			// Cargador de archivos .md3
		persist::CSkinLoader skinLoader;	// Cargador de archivos .skin

		std::string modelpath = path+modelName+(std::string)".md3";
		std::string skinpath = path+modelName+(std::string)".skin";

		//std::cout<<"[StaticModelMd3::loadModel]Ruta: "<<path<<"\n";
		//std::cout<<"[StaticModelMd3::loadModel]Nombre modelo: "<<modelName<<"\n";

		//std::cout<<"[StaticModelMd3::loadModel]Ruta al modelo: "<<modelpath<<"\n";
		//std::cout<<"[StaticModelMd3::loadModel]Ruta a la textura: "<<skinpath<<"\n";
		_model.scale = 1;

		if(!md3Loader.ImportMD3(&_model, modelpath.c_str(), _model.scale))
			return false;

		if(!skinLoader.importSkin(&_model, path, modelName))
			return false;

		_model.setSkin("default");

		return true;
	}

	void CStaticModelMd3::destroyModel(tModel *pModel){
		for(int i = 0; i < pModel->numMeshes; i++)
		{
			if(pModel->meshes[i].pFaces)		delete [] pModel->meshes[i].pFaces;
			if(pModel->meshes[i].pNormals)		delete [] pModel->meshes[i].pNormals;
			if(pModel->meshes[i].pVerts)		delete [] pModel->meshes[i].pVerts;
			if(pModel->meshes[i].pTexVerts)		delete [] pModel->meshes[i].pTexVerts;
		}

		deleteVector(pModel->tags);
		if(pModel->pLinks)		free(pModel->pLinks);
	}




}
