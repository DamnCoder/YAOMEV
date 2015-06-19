/*
 * SkinLoader.cpp
 *
 *  Created on: 01/06/2011
 *      Author: jorge
 */

#include "persist/md3/SkinLoader.h"

#include "gui/TextureManager.h"
#include "utilitys/utils.h"

#include <dirent.h>
#include <iostream>

namespace persist {

	CSkinLoader::CSkinLoader() {
	}

	CSkinLoader::~CSkinLoader() {
	}

	/**
	 * Recupera todos los skins asociados a un modelo.
	 * A partir del patron pasado como argumento se recuperan
	 * solo aquellos skins que contengan ese patron al
	 * principio del nombre del archivo.
	 *
	 * @param path
	 * @param pattern
	 * @return
	 */
	bool CSkinLoader::importSkin(gui::tModel* pModel, const std::string& path, const std::string& pattern) {
		gui::SkinMap skins;

		// Abrimos el directorio
		DIR *dd = opendir (path.c_str ());
		if (!dd)
			return false;

		dirent *dit;

		const std::string fileext (".skin");
		const std::string finalPattern = pattern + (std::string)"_";
		//std::cout<<"[CSkinLoader::importSkin] Path: "<<path<<"\n";
		//std::cout<<"[CSkinLoader::importSkin] Pattern: "<<finalPattern<<"\n";

		// Leemos el directorio para buscar las texturas
		while ((dit = readdir (dd)) != NULL)
		{

			const std::string filename (dit->d_name);

			//const std::string pattern ("head_");
			//std::cout<<"[CSkinLoader::importSkin] Pattern: "<<filename<<"\n";

			// Filtramos los archivos ".skin"
			if (filename.length () - fileext.length () == filename.find (fileext)){

				// Filtramos solo "<patron><*>.skin" y guardamos el nombre que habria en *
				// que sera el tipo
				if (filename.compare (0, finalPattern.length (), finalPattern) == 0){
					// Extract skin name from filename
					const std::string skinType (filename, finalPattern.length (), filename.find (fileext) - finalPattern.length ());

					const std::string skinPath = (path + finalPattern + skinType + fileext);

					//std::cout<<"[CSkinLoader::importSkin] Skin path: "<<skinPath<<"\n";

					gui::tSkin skin;
					if(!loadSkin(pModel, &skin, skinPath, skinType))
						return false;

					skins[skinType] = skin;

				}
			}
		}
		// Close directory
		closedir (dd);

		pModel->skins = skins;
		return true;
	}

	/**
	 * Lee el archivo .skin y carga el skin de un modelo
	 * @param pModel
	 * @param path
	 * @param name
	 * @return
	 */
	bool CSkinLoader::loadSkin(gui::tModel* pModel, gui::tSkin* skin, const std::string& path, const std::string& type)
	{
		if(!path.c_str()) return false;

		std::ifstream fin(path.c_str());

		if(fin.fail()) return false;

		std::string strLine;
		while(getline(fin, strLine)) {
			for(int i = 0; i < pModel->numMeshes; i++) {

				// Asociamos un material a una malla
				if(isInString(strLine, pModel->meshes[i].name) ) {
					std::string texturePath = (std::string)"./" + strLine.substr(strLine.find(",")+1, strLine.size());

					gui::tMaterial material;
					strcpy(material.type, type.c_str());
					strcpy(material.filename, texturePath.c_str());
					material.textureId = (int)gui::CTextureCache::instance().loadTexture(texturePath);

					skin->materials[pModel->meshes[i].name] = material;

				}
			}
		}

		fin.close();
		return true;
	}
}
