/*
 * mFontsManager.h
 *
 *  Created on: 03/08/2010
 *      Author: jorge
 */

#ifndef MFONTSMANAGER_H_
#define MFONTSMANAGER_H_

#include "utilitys/Singleton.h"
#include "utilitys/utils.h"

#include <FTGL/ftgl.h>

namespace gui {

	enum EFontType{
		BITMAP,
		PIXMAP,
		POLIGON,
		OUTLINE,
		EXTRUDED,
		TEXTURED,
	};

	class CFontsCache : public CSingleton<CFontsCache> {

	friend class CSingleton<CFontsCache>;

	public:

		void init(const std::string& fontsPath){
			_fontsPath = fontsPath;
		}

		void releaseAll();

		FTFont* getFont(const std::string& filename, uint size, EFontType fontType);

		void releaseFont(const std::string& filename, int size, EFontType fontType);

	protected:

		CFontsCache();

		virtual ~CFontsCache();

	private:

		/**
		 * Tabla hash que contendra la ruta
		 * y el objeto fuente correspondiente
		 */
		typedef std::map<std::string, FTFont*> TFontsMap;

		/**
		 * Redefinicion del iterador para FontsList
		 */
		typedef TFontsMap::const_iterator TFontsIter;

		/**
		 * Contenedor de fuentes.
		 */
		TFontsMap 	_fonts;

		/**
		 * Ruta donde se hayan las fuentes
		 */
		std::string _fontsPath;

	};

}

#endif /* MFONTSMANAGER_H_ */
