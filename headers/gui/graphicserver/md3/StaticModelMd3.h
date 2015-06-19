/*
 * StaticModelMd3.h
 *
 *  Created on: 23/08/2010
 *      Author: jorge
 */

#ifndef STATICMODELMD3_H_
#define STATICMODELMD3_H_

#include "persist/Resource.h"

#include "gui/OglGraphics.h"

#include "gui/graphicserver/md3/MD3structs.h"
#include "gui/graphicserver/md3/Model.h"

namespace persist{
	class CResourceManager;
	class CStaticMd3Cache;
}

namespace gui {

	//struct TRGBAColor;

	class CStaticModelMd3 : public persist::CResource{

	friend class persist::CResourceManager;
	friend class persist::CStaticMd3Cache;

	public:
		bool render(const math::CPositionf& position, const float orientation, const float scale);
		bool castTransparency(const math::CPositionf& position, const float orientation, const float scale, TRGBAColor transpColor);

		void setTexture(uint textureID);
		void skin(const std::string& skin);

		unsigned int	numTris() const;
		const float 	scale() const { return _model.scale; }
		const int 		numMeshes() const { return _model.numMeshes; }
		const int 		numVerts() const;
		const tModel* 	model() const { return &_model; }
		const tBoundingVolumes boundingVolumes() const { return _model.volumes[0]; }

		bool loadModel(const std::string& path, const std::string& modelName, bool dl, bool shadow);

	protected:
		CStaticModelMd3(const std::string& filename);
		virtual ~CStaticModelMd3();

	private:
		void destroyModel(tModel *pModel);

		tModel			_model;
		gui::SkinMap	_skins;

	};

}

#endif /* STATICMODELMD3_H_ */
