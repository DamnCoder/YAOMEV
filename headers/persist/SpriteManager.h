/*
 * SpriteManager.h
 *
 *  Created on: 09/02/2011
 *      Author: jorge
 */

#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include "persist/ResourceManager.h"

#include "gui/graphicserver/OglSprite.h"

namespace persist {

	class CSpriteCache : public CResourceManager {
	public:
		CSpriteCache(const std::string& resourcesPath);
		~CSpriteCache();

		void add(const std::string& key, const std::string filepath);

	private:
		gui::COglSprite* loadResource(const std::string& filename);

		std::string _filepath;
	};

}

#endif /* SPRITEMANAGER_H_ */
