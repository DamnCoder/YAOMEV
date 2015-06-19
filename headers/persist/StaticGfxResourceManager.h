/*
 * StaticGfxResourceManager.h
 *
 *  Created on: 25/11/2010
 *      Author: jorge
 */

#ifndef STATICGFXRESOURCEMANAGER_H_
#define STATICGFXRESOURCEMANAGER_H_

#include "persist/ResourceManager.h"
#include "gui/graphicserver/md3/StaticModelMd3.h"

#include <string>

namespace persist {

	class CStaticMd3Cache : public CResourceManager {

	public:

		CStaticMd3Cache(const std::string& resourcesPath);

		virtual ~CStaticMd3Cache();

	private:

		gui::CStaticModelMd3* loadResource(const std::string& filename);

	};

}

#endif /* STATICGFXRESOURCEMANAGER_H_ */
