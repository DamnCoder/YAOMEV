/*
 * AnimModelRenderer.h
 *
 *  Created on: 02/05/2011
 *      Author: jorge
 */

#ifndef ANIMMODELRENDERER_H_
#define ANIMMODELRENDERER_H_

#include "utilitys/Singleton.h"
#include "gui/OglGraphics.h"
#include "gui/graphicserver/md3/Model.h"

// Includes de las librerias OpenGL
#include <GL/gl.h>
#include <GL/glu.h>

#include <stack>

namespace gui {

	class CModelRenderer: public CSingleton<CModelRenderer> {
	friend class CSingleton<CModelRenderer>;
	public:

		bool render(
				const tModel *pModel,
				const math::CPositionf& position,
				const float orientation,
				const float scale);

		void drawLink(const tModel *pModel, const float scale);

		void render(const tModel* pModel, const float scale);

		void renderTransparency(
				const tModel* pModel,
				const math::CPositionf& position,
				const float orientation,
				const float scale,
				TRGBAColor transpColor);

	private:
		CModelRenderer();
		~CModelRenderer();
	};

}

#endif /* ANIMMODELRENDERER_H_ */
