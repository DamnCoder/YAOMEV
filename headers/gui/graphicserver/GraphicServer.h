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

#ifndef GRAPHICSERVER_H_
#define GRAPHICSERVER_H_

#include "utilitys/Singleton.h"

#include "persist/StaticGfxResourceManager.h"
#include "persist/AnimatedGfxResourceManager.h"
#include "persist/SpriteManager.h"
#include "persist/ButtonManager.h"

namespace gui {

	class COglStaticMd3;
	class COglAnimatedMd3;
	class COglSprite;
	class COglButton;
	class COglCamera;

	enum {
		ANIMATED_GFX,
		STATIC_GFX,
	};

	class CGraphicServer : public CSingleton<CGraphicServer> {

	friend class CSingleton<CGraphicServer>;

	public:

		//--------------------------------------------------------------------------------------
		// METODOS PARA LA CREACION DE OBJETOS GRAFICOS
		//--------------------------------------------------------------------------------------

		CStaticModelMd3*	getStaticGfx(const std::string& id) const;
		CAnimatedModelMd3*	getAnimatedGfx(const std::string& id) const;
		COglSprite* 		getSprite(const std::string& id) const;
		COglButton* 		getButton(const std::string& id) const;

		COglCamera* 		newCamera(const math::CVector3f& position, int camProjection) const;
		//--------------------------------------------------------------------------------------
		// METODOS PARA LA DESTRUCCION DE OBJETOS GRAFICOS
		//--------------------------------------------------------------------------------------

		void removeStaticGfx(const std::string& id);
		void removeAnimatedGfx(const std::string& id);
		void removeSprite(const std::string& id);
		void removeButton(const std::string& id);

		//--------------------------------------------------------------------------------------
		// METODOS DE CARGA DE RECURSOS EN LOS GESTORES DE RECURSOS
		//--------------------------------------------------------------------------------------
		bool loadSprites(const std::string& path);
		bool loadButtons(const std::string& path);
		bool loadAnimatedGfx(const std::string& path);
		bool loadStaticGfx(const std::string& path);

	private:
		CGraphicServer();
		~CGraphicServer();

		void finish();

		std::string	_animatedGfxPath;
		std::string _staticGfxPath;
		std::string _spriteGfxPath;
		std::string _buttonGfxPath;

		persist::CStaticMd3Cache*		_staticGfxCache;
		persist::CAnimatedGfxCache*		_animatedGfxCache;
		persist::CSpriteCache*			_spriteGfxCache;
		persist::CButtonCache*			_buttonGfxCache;

	};

}

#endif /* GRAPHICSERVER_H_ */
