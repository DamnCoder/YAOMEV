/*
 * mFontsManager.cpp
 *
 *  Created on: 03/08/2010
 *      Author: jorge
 */

#include "gui/text/FontsManager.h"

namespace gui {

	CFontsCache::CFontsCache() {
	}

	CFontsCache::~CFontsCache() {
	}

	void CFontsCache::releaseAll(){
		TFontsIter font_it, font_end;
		font_end = _fonts.end();

		for(font_it = _fonts.begin(); font_it!=font_end; ++font_it)
			delete (*font_it).second;

		_fonts.clear();
	}

	FTFont *CFontsCache::getFont(const std::string& filename, uint size, EFontType fontType){
		// La combinacion del tipo, con la ruta y con el tamaño de la fuente sera
		// la clave en la tabla FontsList
		char buf[256];
		sprintf(buf, "%i%s%i", fontType, filename.c_str(), size);
		std::string fontKey = std::string(buf);

		// Si encontramos la fuente en el contenedor la devolvemos
		TFontsIter result = _fonts.find(fontKey);
		if(result != _fonts.end()){
			return result->second;
		}

		// Si no, creamos una fuente, la guardamos en el contenedor
		// y la devolvemos

		std::string fullname = _fontsPath + filename;

		//std::cout <<"[CFontsManager::getFont] Ruta: "<<fullname<<"\n";

		FTFont* font = 0;

		switch(fontType){
		case BITMAP:
			font = new FTBitmapFont(fullname.c_str());
			break;
		case PIXMAP:
			font = new FTPixmapFont(fullname.c_str());
			break;
		case POLIGON:
			font = new FTPolygonFont(fullname.c_str());
			break;
		case OUTLINE:
			font = new FTOutlineFont(fullname.c_str());
			break;
		case EXTRUDED:
			font = new FTExtrudeFont(fullname.c_str());
			break;
		case TEXTURED:
			font = new FTTextureFont(fullname.c_str());
			break;
		}

		if(!font->FaceSize(size)){
			safeDelete(font);
			return NULL;
		}

		_fonts[fontKey] = font;

		return font;

	}

	void CFontsCache::releaseFont(const std::string& filename, int size, EFontType fontType){
		char buf[256];
		sprintf(buf, "%i%s%i", fontType, filename.c_str(), size);
		std::string fontKey = std::string(buf);

		_fonts.erase(fontKey);
	}
}
