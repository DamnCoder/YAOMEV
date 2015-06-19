/*
 * StaticEntityGUI.h
 *
 *  Created on: 01/10/2010
 *      Author: jorge
 */

#ifndef STATICENTITYGUI_H_
#define STATICENTITYGUI_H_

#include "3dNode.h"

#include "gui/OglGraphics.h"

#include "logic/entitys/MultimediaFurniture.h"

namespace gui {

	class CStaticModelMd3;

	class CStaticEntityNode : public C3dNode {
	public:

		CStaticEntityNode(CStaticModelMd3* model);
		virtual ~CStaticEntityNode();

		virtual bool render();
		bool setLogicEntity(CEntity* logicEntity);
		int numTris();
		CStaticModelMd3* model() const { return _staticModel; }

	protected:

		CStaticModelMd3* 	_staticModel;
		TRGBAColor			_color;

	};

	class CTransparentNode : public CStaticEntityNode {
	public:
		CTransparentNode(CStaticModelMd3* model);
		bool render();
	};

	class CSkinShifterTransparentNode : public CStaticEntityNode {
	public:
		CSkinShifterTransparentNode(CStaticModelMd3* model);
		bool render();
	};

}

#endif /* STATICENTITYGUI_H_ */
