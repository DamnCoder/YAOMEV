/*
 * StaticEntityGUI.cpp
 *
 *  Created on: 01/10/2010
 *      Author: jorge
 */

#include "gui/scene/StaticEntityNode.h"

#include "utilitys/utils.h"
#include "utilitys/Log.h"

#include "gui/graphicserver/md3/StaticModelMd3.h"
#include "gui/graphicserver/GraphicServer.h"

namespace gui {

	CStaticEntityNode::CStaticEntityNode(CStaticModelMd3* model):
		C3dNode(),
		_staticModel(model)
	{
		_bb = _staticModel->boundingVolumes().bb;
		_bs = _staticModel->boundingVolumes().bs;
	}

	CStaticEntityNode::~CStaticEntityNode() {
	}

	bool CStaticEntityNode::render(){
		if(!_visible) return true;

		//_bs.setCenter(_position);
		_staticModel->skin(_skin);
		_staticModel->render(_position, _orientation, _scale);
		return true;
	}

	bool CStaticEntityNode::setLogicEntity(CEntity* entity){
		// Si no queremos asociar una entidad devolvemos true
		if(!entity) return false;

		if(!C3dNode::setLogicEntity(entity))
			return false;

		_color = TRGBAColor(
				entity->color().r,
				entity->color().g,
				entity->color().b,
				entity->color().a);

		_bs.setCenter(_position);
		_bs.setRadius(_bs.radius()*_scale);

		//std::cout<<"[CStaticEntityNode::CStaticEntityNode] Bounding sphere center: "<<_bs.center().x<<", "<<_bs.center().y<<", "<<_bs.center().z<<" ";
		//std::cout<<"radio: "<<_bs.radius()<<"\n";
		return true;

	}

	int CStaticEntityNode::numTris(){
		return _staticModel->numTris();
	}

	//----------------------------------------------------------------------------------
	// IMPLEMENTACION DEL NODO REFLEJADO
	//----------------------------------------------------------------------------------

	CTransparentNode::CTransparentNode(CStaticModelMd3* model):
			CStaticEntityNode(model)
	{}

	bool CTransparentNode::render(){
		if(!_visible) return true;
		//return true;
		return _staticModel->castTransparency(_position, _orientation, _scale, _color);
	}

	//----------------------------------------------------------------------------------
	// IMPLEMENTACION DEL NODO CAMBIA PIELES REFLEJADO
	//----------------------------------------------------------------------------------

	CSkinShifterTransparentNode::CSkinShifterTransparentNode(CStaticModelMd3* model):
		CStaticEntityNode(model)
	{}

	bool CSkinShifterTransparentNode::render(){
		if(!_visible) return true;
		_staticModel->skin(_skin);
		return _staticModel->castTransparency(_position, _orientation, _scale, _color);
	}
}
