/*
 * LoadMD3.h
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#ifndef LOADMD3_H_
#define LOADMD3_H_

#include "gui/graphicserver/md3/MD3structs.h"
#include "gui/graphicserver/md3/Model.h"

#include <iostream>

namespace persist {

	class CLoadMD3{

	public:

		CLoadMD3();

		bool ImportMD3(gui::tModel *pModel, const char *strFileName, const float scale);
		bool LoadSkin(gui::tModel *pModel, gui::tSkin* skin, const std::string& path, const std::string& name);

	private:

		void readMD3Data(gui::tModel *pModel, const float scale);
		void convertDataStructures(gui::tModel *pModel, gui::tMd3MeshHeader meshHeader, const float scale);
		void CleanUp();

		FILE *m_FilePointer;

		gui::tMd3Header		m_Header;			// The header data
		gui::tMd3Shader		*m_pSkins;			// The skin name data (not used)
		gui::tMd3TexCoord	*m_pTexCoords;		// The texture coordinates
		gui::tMd3Face		*m_pTriangles;		// Face/Triangle data
		gui::tMd3Vertex		*m_pVertices;		// Vertex/UV indices
		gui::tMd3Frame		*m_pFrames;			// This stores the bone data (not used)
	};

}

#endif /* LOADMD3_H_ */
