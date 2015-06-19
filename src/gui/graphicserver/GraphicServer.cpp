/**
 * 	@file GraphicServer.cpp
 *
 * 	El servidor grafico se encarga de la tarea de envolver las funcionalidades de
 * 	OpenGL y SDL para facilitar su uso.
 * 	Se encarga de iniciar OpenGL y SDL y tambien de su finalizacion.
 * 	Se encarga también de suministrar los objetos graficos.
 *
 * 	Esta implementado como una factoria abstracta y un singleton.
 *
 *	@see gui::CGraphicServer
 *
 *  @date Octubre, 2009
 *  @author Jorge
 */

#include "gui/graphicserver/GraphicServer.h"

#include "gui/graphicserver/OglButton.h"
#include "gui/graphicserver/OglSprite.h"
#include "gui/graphicserver/OglCamera.h"

#include <tinyxml/tinyxml.h>

#include <cassert>

namespace gui {

	CGraphicServer::CGraphicServer():
			_staticGfxCache(0),
			_animatedGfxCache(0),
			_spriteGfxCache(0),
			_buttonGfxCache(0)
	{}

	CGraphicServer::~CGraphicServer(){ finish(); }

	void CGraphicServer::finish(){
		safeDelete(_staticGfxCache);
		safeDelete(_animatedGfxCache);
		safeDelete(_spriteGfxCache);
		safeDelete(_buttonGfxCache);
	}

	//--------------------------------------------------------------------------------------
	// METODOS PARA LA CREACION DE OBJETOS GRAFICOS
	//--------------------------------------------------------------------------------------

	CStaticModelMd3* CGraphicServer::getStaticGfx(const std::string& id) const{
		//cout<<"[CGraphicServer::getStaticGfx] Cargamos "<<id<<"\n";
		//assert(_staticGfxManager);
		return (CStaticModelMd3*)_staticGfxCache->get(id);
	}

	CAnimatedModelMd3* CGraphicServer::getAnimatedGfx(const std::string& id) const{
		//cout<<"[CGraphicServer::getAnimatedGfx] Cargamos "<<id<<"\n";
		//assert(_animatedGfxManager);
		return (CAnimatedModelMd3*)_animatedGfxCache->get(id);
	}

	COglSprite* CGraphicServer::getSprite(const std::string& id) const{
		//assert(_spriteGfxManager);
		return (gui::COglSprite*)_spriteGfxCache->get(id);
	}

	COglButton* CGraphicServer::getButton(const std::string& id) const{
		//assert(_buttonGfxManager);
		return (gui::COglButton*)_buttonGfxCache->get(id);
	}

	void CGraphicServer::removeStaticGfx(const std::string& id){
		_staticGfxCache->remove(id);
	}

	void CGraphicServer::removeAnimatedGfx(const std::string& id){
		_animatedGfxCache->remove(id);
	}

	void CGraphicServer::removeSprite(const std::string& id){
		_spriteGfxCache->remove(id);
	}

	void CGraphicServer::removeButton(const std::string& id){
		_buttonGfxCache->remove(id);
	}

	COglCamera* CGraphicServer::newCamera(const math::CVector3f& position, int camProjection) const {
		return new COglCamera(position, camProjection);
	}

	//--------------------------------------------------------------------------------------
	// METODOS DE CARGA DE RECURSOS EN LOS GESTORES DE RECURSOS
	//--------------------------------------------------------------------------------------

	bool CGraphicServer::loadSprites(const std::string& path){
		if(_spriteGfxCache)
			return false;

		TiXmlDocument doc(path.c_str());
		if(!doc.LoadFile())
			return false;

		TiXmlHandle	hDoc(&doc);
		// Recuperamos el elemento del nodo raiz
		TiXmlElement* pElem = hDoc.FirstChildElement().Element();

		_spriteGfxPath = pElem->Attribute("path");
		_spriteGfxCache = new persist::CSpriteCache(_spriteGfxPath);

		TiXmlHandle hRoot(pElem);
		while(pElem){
			TiXmlElement* pTextureGfxElement = hRoot.FirstChild("texture").Element();
			while(pTextureGfxElement){
				const std::string file = pTextureGfxElement->Attribute("file");
				const std::string id = pTextureGfxElement->Attribute("id");
				_spriteGfxCache->add(id, file);
				pTextureGfxElement = pTextureGfxElement->NextSiblingElement("texture");
			}
			pElem = pElem->NextSiblingElement();

		}
		return true;
	}

	bool CGraphicServer::loadButtons(const std::string& path){
		if(_buttonGfxCache)
			return false;

		TiXmlDocument doc(path.c_str());
		if(!doc.LoadFile())
			return false;

		TiXmlHandle	hDoc(&doc);
		// Recuperamos el elemento del nodo raiz
		TiXmlElement* pElem = hDoc.FirstChildElement().Element();

		_buttonGfxPath = pElem->Attribute("path");
		_buttonGfxCache = new persist::CButtonCache(_buttonGfxPath);

		TiXmlHandle hRoot(pElem);
		while(pElem){
			TiXmlElement* pButtonGfxElement = hRoot.FirstChild("button").Element();
			while(pButtonGfxElement){
				std::string key = pButtonGfxElement->Attribute("id");
				std::string fontName = pButtonGfxElement->Attribute("font");
				int fontSize = 0;
				pButtonGfxElement->QueryIntAttribute("size", &fontSize);
				_buttonGfxCache->add(key, fontName, (uint)fontSize);
				pButtonGfxElement = pButtonGfxElement->NextSiblingElement("button");
			}
			pElem = pElem->NextSiblingElement();
		}
		return true;
	}

	bool CGraphicServer::loadAnimatedGfx(const std::string& path){

		if(_animatedGfxCache)
			return false;

		TiXmlDocument doc(path.c_str());
		if(!doc.LoadFile())
			return false;

		TiXmlHandle	hDoc(&doc);
		// Recuperamos el elemento del nodo raiz
		TiXmlElement* pElem = hDoc.FirstChildElement().Element();

		_animatedGfxPath = pElem->Attribute("path");
		_animatedGfxCache = new persist::CAnimatedGfxCache(_animatedGfxPath);

		TiXmlHandle hRoot(pElem);
		while(pElem){
			TiXmlElement* pAnimGfxElement = hRoot.FirstChild("animated").Element();
			std::string foldername;
			while(pAnimGfxElement){
				foldername = pAnimGfxElement->Attribute("foldername");
				_animatedGfxCache->add(foldername);
				pAnimGfxElement = pAnimGfxElement->NextSiblingElement("animated");
			}
			pElem = pElem->NextSiblingElement();
		}
		return true;
	}

	bool CGraphicServer::loadStaticGfx(const std::string& path){

		if(_staticGfxCache)
			return false;

		TiXmlDocument doc(path.c_str());
		if(!doc.LoadFile())
			return false;

		TiXmlHandle	hDoc(&doc);
		// Recuperamos el elemento del nodo raiz
		TiXmlElement* pElem = hDoc.FirstChildElement().Element();

		_staticGfxPath = pElem->Attribute("path");

		TiXmlHandle hRoot(pElem);
		_staticGfxCache = new persist::CStaticMd3Cache(_staticGfxPath);

		while(pElem){
			TiXmlElement* pStaticGfxElement = hRoot.FirstChild("static").Element();
			while(pStaticGfxElement){
				std::string id = pStaticGfxElement->Attribute("id");
				std::string filename = pStaticGfxElement->Attribute("filename");
				_staticGfxCache->add(filename);
				pStaticGfxElement = pStaticGfxElement->NextSiblingElement("static");
			}
			pElem = pElem->NextSiblingElement();
		}
		return true;
	}

}
