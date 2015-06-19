/*
 * StaticGfxResourceManager.cpp
 *
 *  Created on: 25/11/2010
 *      Author: jorge
 */

#include "persist/StaticGfxResourceManager.h"

namespace persist {

	CStaticMd3Cache::CStaticMd3Cache(const std::string& resourcesPath):
			CResourceManager(resourcesPath)
	{}

	CStaticMd3Cache::~CStaticMd3Cache() {}

	gui::CStaticModelMd3* CStaticMd3Cache::loadResource(const std::string& filename){

		gui::CStaticModelMd3* md3Model = new gui::CStaticModelMd3(filename);

		if(!md3Model->loadModel(this->resourcesPath(), filename, true, true)){
			std::cerr<<"[CStaticMd3ResourceManager::loadResource]No se ha podido cargar el modelo "<<this->resourcesPath()<<""<<filename<<"\n";
			delete md3Model;
			md3Model = 0;
			return 0;
		}

		return md3Model;
	}


}
