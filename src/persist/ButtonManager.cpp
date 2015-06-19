/*
 * ButtonManager.cpp
 *
 *  Created on: 09/02/2011
 *      Author: jorge
 */

#include "persist/ButtonManager.h"

#include "gui/graphicserver/GraphicServer.h"

namespace persist {

	CButtonCache::CButtonCache(const std::string& resourcesPath):
			CResourceManager(resourcesPath),
			_fontName(""),
			_fontSize(0)
	{}

	CButtonCache::~CButtonCache()
	{
	}

	void CButtonCache::add(const std::string& key, const std::string& fontName, uint fontSize){
		// Primero guardamos la fuente que queremos usar y su tamaño
		_fontName = fontName;
		_fontSize = fontSize;

		// Segundo añadimos el recurso, con los datos de la fuente ya guardados
		CResourceManager::add(key);

		// Anulamos los valores previos, por si acaso alguien usara add(nombre) la siguiente vez
		_fontName = "";
		_fontSize = 0;
	}

    gui::COglButton* CButtonCache::loadResource(const std::string& filename) {
		// A partir del ID cargar el estilo
    	std::string pathToTexture = resourcesPath()+filename+(std::string)"/"+filename;
/*
    	gui::COglSprite* normal = gui::CGraphicServer::instance().getSprite(pathToTexture+(std::string)"_normal.tga");
		gui::COglSprite* pressed = gui::CGraphicServer::instance().getSprite(pathToTexture+(std::string)"_pressed.tga");
		gui::COglSprite* highlighted = gui::CGraphicServer::instance().getSprite(pathToTexture+(std::string)"_highlighted.tga");
*/
    	//std::cout<<"[CButtonManager::loadResource] id: "<<filename<<"\n";

    	gui::COglSprite* normal = gui::CGraphicServer::instance().getSprite(filename+(std::string)"_normal");
		gui::COglSprite* pressed = gui::CGraphicServer::instance().getSprite(filename+(std::string)"_pressed");
		gui::COglSprite* highlighted = gui::CGraphicServer::instance().getSprite(filename+(std::string)"_highlighted");

		gui::COglButton* button = new gui::COglButton(filename);
		button->setSprite(normal, gui::COglButton::NORMAL);
		button->setSprite(pressed, gui::COglButton::PRESSED);
		button->setSprite(highlighted, gui::COglButton::HIGHLIGHTED);

		if(_fontName != "" && _fontSize>0)
			button->setFontType(_fontName, _fontSize);

    	return button;
    }
}
