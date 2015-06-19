/*
 *  CGuiManager.h
 *
 *
 *	Clase encargada de la gestion de la escena grafica.
 *	Esta clase es la responsable de añadir, eliminar, hacer visible o invisible
 *	los nodos de la escena.
 *
 *	Para ello es observadora de todos los eventos de creacion o destruccion.
 *  Created on: 05/04/2010
 *      Author: jorge
 */

#ifndef CGUIMGMT_H_
#define CGUIMGMT_H_

#include "scene/Scene.h"
#include "logic/listener/CreationDestroyListener.h"
#include "gui/graphicserver/OglLight.h"

#include <map>
#include <vector>

namespace gui {

	class CSpriteNode;
	class CLabelNode;
	class CTextLayoutNode;
	class CUINode;

	class CScreenNode;
	class CStaticEntityNode;
	class CAnimatedEntityNode;
	class CTransparentNode;

	class IRenderer;

	class CCameraManager;
	class CAbstractCamera;

	class CSceneManager : public logic::CreationDestroyListener {

	public:

		typedef std::map<logic::CEntity*, CStaticEntityNode*>::iterator 	TStaticGfxIterator;
		typedef std::map<logic::CAvatar*, CAnimatedEntityNode*>::iterator 	TAnimatedGfxIterator;
		typedef std::map<logic::CEntity*, CScreenNode*>::iterator			TScreenGfxIterator;
		typedef std::map<logic::CEntity*, CStaticEntityNode*>::iterator		TTransparentIterator;
		typedef std::map<logic::CUiComponent*, CUINode*>::iterator 			TUITableIterator;

		CSceneManager();
		~CSceneManager();

		/**
		 * Ordena dibujar todos los nodos de la escena.
		 * Devuelve true si se realizo correctamente
		 */
		bool render(float dt);
		bool render2dFirst(float dt);

		//--------------------------------------------------------------------------------------
		// Metodos implementados del observador CreationDestroyListener
		//--------------------------------------------------------------------------------------

		void addCamera(gui::CAbstractCamera* camera);
		void addLight(COglLight* light);

		void addGfxComponent(logic::CEntity* entity);
		void addGfxComponent(logic::CAvatar* avatar);
		void addGfxComponent(logic::CScenario* scenario);
		void addGfxComponent(logic::CScreen* screen);

		void addGfxComponent(logic::CFrame* frame);
		void addGfxComponent(logic::CButton* button);
		void addGfxComponent(logic::CLabel* label);
		void addGfxComponent(logic::CTextBox* textBox);

		void removeGfxComponent(logic::CEntity* entity);
		void removeGfxComponent(logic::CAvatar* avatar);
		void removeGfxComponent(logic::CScenario* scenario);
		void removeGfxComponent(logic::CScreen* screen);

		void removeGfxComponent(logic::CUiComponent* uiComponent);
		void removeGfxComponent(logic::CButton* button);
		void removeGfxComponent(logic::CLabel* label);
		void removeGfxComponent(logic::CTextBox* textBox);
		void removeGfxComponent(logic::CFrame* frame);

		std::vector<COglLight*> 	getLights() 		const { return _lights; }
		const unsigned int			getTrisInScene() 	const { return _trisInScene; }
		CCameraManager*				getCameraManager() 	const { return _cameraManager; }

	protected:
		void createTransparentNode(logic::CEntity* entity);

		void destroyTransparentNode(logic::CEntity* entity);

		void addUiComponent(logic::CButton* button, const int z);
		void addUiComponent(logic::CLabel* label, const int z);
		void addUiComponent(logic::CTextBox* textLayout, const int z);

		void addUiNode(CUINode* uiNode, logic::CUiComponent* uiComponent);

		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		CScene*										_3dNodes;
		//CFrustumCullingScene*						_3dNodes;
		CScene*										_2dNodes;
		CScene*										_invertedNodes;
		CScene* 									_transparentNodes;

		std::map<logic::CEntity*, CStaticEntityNode*>	_transparentTable;
		std::map<logic::CEntity*, CScreenNode*>			_screenGfxTable;
		std::map<logic::CEntity*, CStaticEntityNode*>	_staticGfxTable;
		std::map<logic::CAvatar*, CAnimatedEntityNode*>	_animatedGfxTable;
		std::map<logic::CUiComponent*, CUINode*>		_uiTable;		// Tabla para elementos de la interfaz de usuario

		std::vector<COglLight*> 					_lights;
		unsigned int								_numLights;

		IRenderer* 									_renderer;
		CCameraManager*								_cameraManager;

	private:

		bool renderTransparentModels();
		bool renderReflectedModels();
		bool render3dModels();
		bool render2dModels();

		void actualizeLights();

		unsigned int	_trisInScene;

		std::vector<COglLight*>::iterator _itlight, _endlight;

	};

}

#endif /* CGUIMGMT_H_ */
