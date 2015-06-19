/*
 * AnimatedGfxResourceManager.h
 *
 *  Created on: 11/12/2010
 *      Author: jorge
 */

#ifndef ANIMATEDGFXRESOURCEMANAGER_H_
#define ANIMATEDGFXRESOURCEMANAGER_H_

#include "persist/ResourceManager.h"
#include "persist/md3/AnimationLoader.h"

#include "gui/graphicserver/md3/AnimatedModelMD3.h"

namespace persist {

	class CAnimatedGfxCache : public persist::CResourceManager {
	friend class gui::CAnimatedModelMd3;
	public:
		CAnimatedGfxCache(const std::string& resourcesPath);
		~CAnimatedGfxCache();

	private:
		void createNewModel();
		bool load(const std::string& strPath, const std::string& strModel);
		bool importMD3(const std::string& modelPath);
		bool importSkins(const std::string& modelPath);
		bool importAnimations(const std::string& modelPath);
		void link(gui::tModel* pModel, const gui::tModel* pLink, const std::string& tagName);

		gui::CAnimatedModelMd3* loadResource(const std::string& key);

		gui::tModel* 	_head;
		gui::tModel* 	_upper;
		gui::tModel* 	_lower;
		gui::SkinMap	_headSkins;
		gui::SkinMap	_upperSkins;
		gui::SkinMap	_lowerSkins;

	};

}

#endif /* ANIMATEDGFXRESOURCEMANAGER_H_ */
