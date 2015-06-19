/*
 * SpriteManager.cpp
 *
 *  Created on: 09/02/2011
 *      Author: jorge
 */

#include "persist/SpriteManager.h"

#include "gui/TextureManager.h"

namespace persist {

	CSpriteCache::CSpriteCache(const std::string& resourcesPath):
			CResourceManager(resourcesPath)
	{}

	CSpriteCache::~CSpriteCache() {
	}

	void CSpriteCache::add(const std::string& key, const std::string filepath) {
		_filepath = filepath;
		CResourceManager::add(key);
		_filepath = "";
	}

    gui::COglSprite* CSpriteCache::loadResource(const std::string& filename) {

    	std::string pathToTexture = resourcesPath()+_filepath;

    	//std::cout<<"[CSpriteManager::loadResource]"<<pathToTexture<<" id: "<<filename<<"\n";
    	uint textureID = gui::CTextureCache::instance().loadTexture(pathToTexture);

    	gui::COglSprite* sprite = new gui::COglSprite(_filepath);
    	sprite->setTextureId(textureID);

    	return sprite;
    }

}
