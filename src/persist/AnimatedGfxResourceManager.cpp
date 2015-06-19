/*
 * AnimatedGfxResourceManager.cpp
 *
 *  Created on: 11/12/2010
 *      Author: jorge
 */

#include "persist/AnimatedGfxResourceManager.h"

#include "utilitys/utils.h"

#include "persist/md3/LoadMD3.h"
#include <dirent.h>

namespace persist {

	CAnimatedGfxCache::CAnimatedGfxCache(const std::string& resourcesPath):
			CResourceManager(resourcesPath)
	{}

	CAnimatedGfxCache::~CAnimatedGfxCache()
	{}

	void CAnimatedGfxCache::createNewModel(){
		_head = new gui::tModel();
		_upper = new gui::tModel();
		_lower= new gui::tModel();
		memset(_head,  0, sizeof(gui::tModel));
		memset(_upper, 0, sizeof(gui::tModel));
		memset(_lower, 0, sizeof(gui::tModel));
	}

	gui::CAnimatedModelMd3* CAnimatedGfxCache::loadResource(const std::string& key){

		createNewModel();

		string foldername = splitAndReturnFirstPart('@', key);

		if(!load(this->resourcesPath(), foldername)){
			delete _head;
			delete _upper;
			delete _lower;
			return 0;
		}

		return new gui::CAnimatedModelMd3(foldername, _head, _upper, _lower);
	}

	bool CAnimatedGfxCache::load(const std::string& path, const std::string& modelName){

		if(!path.c_str() || !modelName.c_str()) return false;

		std::string modelPath = path+modelName+(std::string)"/";
		//std::cout<<"[CAnimatedGfxManager::load] Ruta "<<modelPath<<"\n";

		// Importamos los archivos .MD3
		if(!importMD3(modelPath)){
			#ifdef _DEBUG
			std::cerr<<"[CAnimatedGfxManager::loadModel][ERROR] No se han podido cargar los ficheros MD3 a partir de la ruta: "<<modelPath<<"\n";
			#endif
			return false;
		}

		// Importamos los archivos .skin
		if(!importSkins(modelPath)){
			#ifdef _DEBUG
			std::cerr<<"[CAnimatedGfxManager::loadModel][ERROR] No se han podido cargar los ficheros Skin a partir de la ruta: "<<modelPath<<"\n";
			#endif
			return false;
		}

		// Importamos animaciones
		if(!importAnimations(modelPath)){
			#ifdef _DEBUG
			std::cerr<<"[CAnimatedGfxManager::loadModel][ERROR] No se han podido importar animaciones a partir de la ruta: "<<modelPath<<"\n";
			#endif
			return false;
		}

		link(_lower, _upper, "tag_torso");
		link(_upper, _head, "tag_head");

		_lower->setSkin("default");
		_upper->setSkin("default");
		_head->setSkin("default");

		return true;
	}

	bool CAnimatedGfxCache::importMD3(const std::string& modelPath){
		persist::CLoadMD3 loadMd3;

		std::string lowerModelPath = modelPath + (std::string)"lower.md3";
		std::string upperModelPath = modelPath + (std::string)"upper.md3";
		std::string headModelPath = modelPath + (std::string)"head.md3";

		if(!loadMd3.ImportMD3(_head,  headModelPath.c_str(), _head->scale))
			return false;

		if(!loadMd3.ImportMD3(_upper, upperModelPath.c_str(), _upper->scale))
			return false;

		if(!loadMd3.ImportMD3(_lower, lowerModelPath.c_str(), _lower->scale))
			return false;

		return true;
	}

	bool CAnimatedGfxCache::importSkins(const std::string& modelPath){
		persist::CLoadMD3 loadMd3;

		std::string lowerSkinPath = modelPath + (std::string)"lower_";
		std::string upperSkinPath = modelPath + (std::string)"upper_";
		std::string headSkinPath = modelPath + (std::string)"head_";

		// Abrimos el directorio
		DIR *dd = opendir (modelPath.c_str ());
		if (!dd)
			return false;

		dirent *dit;

		// Leemos el directorio para buscar las texturas
		while ((dit = readdir (dd)) != NULL)
		{
			const string filename (dit->d_name);
			const string fileext (".skin");
			const string pattern ("head_");

			// Filtramos los archivos ".skin"
			if (filename.length () - fileext.length () == filename.find (fileext)){
				// Solo nos quedamos con el tipo de skin
				// El formato de nombre es por ejemplo:
				// - head_default.skin, upper_default.skin, lower_default.skin
				// En este caso el skin seria tipo default

				// Filtramos solo "head_*.skin" y guardamos el nombre que habria en *
				// que sera el tipo
				if (filename.compare (0, pattern.length (), pattern) == 0){
					// Extract skin name from filename
					const string skinType (filename, pattern.length (), filename.find (fileext) - pattern.length ());

					gui::tSkin skin;

					if(!loadMd3.LoadSkin(_lower, &skin, (lowerSkinPath+skinType+fileext), skinType))
						return false;
					_lowerSkins[skinType] = skin;

					if(!loadMd3.LoadSkin(_upper, &skin, (upperSkinPath+skinType+fileext), skinType))
						return false;
					_upperSkins[skinType] = skin;

					if(!loadMd3.LoadSkin(_head, &skin, (headSkinPath+skinType+fileext), skinType))
						return false;
					_headSkins[skinType] = skin;

					_lower->skins = _lowerSkins;
					_upper->skins = _upperSkins;
					_head->skins = _headSkins;
				}
			}
		}

		// Close directory
		closedir (dd);

		return true;
	}

	bool CAnimatedGfxCache::importAnimations(const std::string& modelPath)
	{
		persist::CAnimationLoader animLoader;

		if(!animLoader.importAnimations(modelPath))
			return false;

		_lower->animations = animLoader.lowerAnimations();
		_upper->animations = animLoader.upperAnimations();
		_head->animations = animLoader.headAnimations();

		_lower->numOfAnimations = (int)_lower->animations.size();
		_upper->numOfAnimations = (int)_upper->animations.size();
		_head->numOfAnimations = (int)_head->animations.size();

		return true;
	}

	void  CAnimatedGfxCache::link(gui::tModel* pModel, const gui::tModel* pLink, const std::string& tagName)
	{
		if(!pModel || !pLink || !tagName.c_str()) return;

		for(int i = 0; i < pModel->numTags; i++){
			if( pModel->tags[i]->name == tagName ){
				pModel->pLinks[i] = pLink;
				return;
			}
		}

	}


}
