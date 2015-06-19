/*
 * SkinLoader.h
 *
 *  Created on: 01/06/2011
 *      Author: jorge
 */

#ifndef SKINLOADER_H_
#define SKINLOADER_H_

#include "gui/graphicserver/md3/MD3structs.h"
#include "gui/graphicserver/md3/Model.h"

#include <string>

namespace persist {

	class CSkinLoader {
	public:
		CSkinLoader();
		~CSkinLoader();

		bool importSkin(gui::tModel* pModel, const std::string& path, const std::string& pattern);

	private:

		bool loadSkin(gui::tModel* pModel, gui::tSkin* skin, const std::string& path, const std::string& name);


	};

}

#endif /* SKINLOADER_H_ */
