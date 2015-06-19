/*
 * ButtonManager.h
 *
 *  Created on: 09/02/2011
 *      Author: jorge
 */

#ifndef BUTTONMANAGER_H_
#define BUTTONMANAGER_H_


#include "persist/ResourceManager.h"

#include "gui/graphicserver/OglButton.h"

namespace persist {

	class CButtonCache : public CResourceManager {
	public:
		CButtonCache(const std::string& resourcesPath);
		~CButtonCache();

		void add(const std::string& key, const std::string& fontName, uint fontSize);

	private:
		gui::COglButton* loadResource(const std::string& filename);

		std::string _fontName;
		uint 		_fontSize;

	};

}

#endif /* BUTTONMANAGER_H_ */
