/*
 * CGuiManager.cpp
 *
 *  Created on: 05/04/2010
 *      Author: jorge
 */

#include "gui/SceneManager.h"

#include "gui/WindowManager.h"

#include "logic/entitys/MultimediaFurniture.h"
#include "logic/entitys/Screen.h"
#include "logic/entitys/Avatar.h"
#include "logic/entitys/Scenario.h"
#include "logic/ui/Button.h"
#include "logic/ui/Frame.h"
#include "logic/ui/Label.h"
#include "logic/ui/TextLayout.h"

#include "gui/scene/ButtonNode.h"
#include "gui/scene/SpriteNode.h"
#include "gui/scene/LabelNode.h"
#include "gui/scene/TextLayoutNode.h"
#include "gui/scene/UINode.h"
#include "gui/scene/AnimatedEntityNode.h"
#include "gui/scene/StaticEntityNode.h"
#include "gui/scene/ScreenNode.h"

#include "gui/OglGraphics.h"
#include "gui/renderer/OglInmediateRenderer.h"

#include "gui/cam/CameraManager.h"

#include "gui/octreescene/COctree.h"

namespace gui {

	CSceneManager::CSceneManager():
			_3dNodes(new CScene),
			_2dNodes(new CScene),
			_invertedNodes(new CScene),
			_transparentNodes(new CScene),
			_numLights(0),
			_renderer(new COglInmediateRenderer),
			_cameraManager(new CCameraManager),
			_trisInScene(0)
	{
	}

	CSceneManager::~CSceneManager() {

		//cout<<"[CSceneManager::delete] Elementos 3D en escena al borrar "<<_3dNodes->size()<<"\n";
		//cout<<"[CSceneManager::delete] Elementos 2D en escena al borrar "<<_2dNodes->size()<<"\n";

		safeDelete(_2dNodes);
		safeDelete(_3dNodes);
		safeDelete(_invertedNodes);
		safeDelete(_transparentNodes);
		safeDelete(_renderer);
		safeDelete(_cameraManager);

		_staticGfxTable.clear();
		_animatedGfxTable.clear();
		_lights.clear();
		_uiTable.clear();
	}

	bool CSceneManager::render(float dt){

		bool result = true;

		//actualizeLights();
		_cameraManager->actualize(dt);

		// Renderizado de modelos
		glEnable(GL_TEXTURE_2D);
/*
		// Renderizado de modelos invertidos
		if(_invertedNodes->size())
			result &= renderReflectedModels();
*/
		if(_3dNodes->size())
			result &= render3dModels();
/*
		if(_transparentNodes->size())
			result &= renderTransparentModels();
*/
		if(_2dNodes->size())
			result &= render2dModels();

		glDisable(GL_TEXTURE_2D);


		return result;
	}

	bool CSceneManager::render2dFirst(float dt){

		bool result = true;

		_cameraManager->actualize(dt);

		glEnable(GL_TEXTURE_2D);
		if(_2dNodes->size())
			result &= render2dModels();

		if(_3dNodes->size())
			result &= render3dModels();
		glDisable(GL_TEXTURE_2D);

		return result;
	}

	//--------------------------------------------------------------------------------------
	// Metodos de CREACION implementados del observador CreationDestroyListener
	//--------------------------------------------------------------------------------------

	void CSceneManager::addCamera(gui::CAbstractCamera* camera){
		_cameraManager->addCamera(camera->id(), camera);
	}

	void CSceneManager::addLight(COglLight* light){
		if(_numLights>8) return;
		_lights.push_back(light);
		_numLights = _lights.size();

	}

	void CSceneManager::addGfxComponent(logic::CEntity* entity){
		// Si no es una entidad que refleja, entonces es una entidad que se reflejara sobre alguna superficie
		if(!entity->reflection()){
			CStaticModelMd3* model = CGraphicServer::instance().getStaticGfx(entity->id());
			if(!model)
				return;
			CStaticEntityNode* node = new CStaticEntityNode(model);

			node->setLogicEntity(entity);

			_3dNodes->insertNode(node);
			//_invertedNodes->insertNode(seNode);

			_staticGfxTable[entity] = node;

			_trisInScene += node->numTris();

		}
		else	// Si es una entidad que refleja, entonces tenemos que hacerla transparente
			createTransparentNode(entity);

		//std::cout<<"[CSceneManager::addGfxComponent] Triangulos en escena: "<<_trisInScene<<"\n";


	}

	void CSceneManager::addGfxComponent(logic::CAvatar* avatar){

		CAnimatedModelMd3* model = CGraphicServer::instance().getAnimatedGfx(avatar->id());
		if(!model) return;

		CAnimatedEntityNode* node = new CAnimatedEntityNode(model);
		node->setLogicEntity(avatar);

		_3dNodes->insertNode(node);
		//_invertedNodes->insertNode(aeNode);

		_animatedGfxTable[avatar] = node;

		_trisInScene += node->numTris();

		//std::cout<<"[CSceneManager::addGfxComponent] Modelo: "<<avatar->id()<<" Triangulos en escena: "<<_trisInScene<<"\n";
	}

	void CSceneManager::addGfxComponent(logic::CScenario* scenario){
		logic::CScenario::TEntityList furnitureList = scenario->furniture();
		logic::CScenario::TMultFurnList multFurnitureList = scenario->multFurniture();
		logic::CScenario::TAvatarList audience = scenario->audience();

		// Creo los elementos estaticos
		logic::CScenario::TEntityIterator
			itfur(furnitureList.begin()),
			endfur(furnitureList.end());
		for(; itfur!=endfur; ++itfur){
			addGfxComponent(*itfur);
		}

		// Creo los elementos multimedia
		logic::CScenario::TMultFurIterator
			itmulfur(multFurnitureList.begin()),
			endmulfur(multFurnitureList.end());
		for(; itmulfur!=endmulfur; ++itmulfur){
			addGfxComponent(*itmulfur);
		}

		// Creo el publico
		logic::CScenario::TAvatarIterator
			itaud(audience.begin()),
			endaud(audience.end());

		for(;itaud!=endaud; ++itaud){
			this->addGfxComponent(*itaud);
		}

		// Creo al presentador
		addGfxComponent((logic::CAvatar*)scenario->host());

		// Creo la pantalla
		addGfxComponent(scenario->screen());

		// Creo las camaras
		vector<gui::CAbstractCamera*> cameras = scenario->getCameras();
		vector<gui::CAbstractCamera*>::iterator cam, endCam;
		endCam = cameras.end();
		for(cam=cameras.begin(); cam!=endCam; ++cam){
			addCamera(*cam);
		}
	}

	void CSceneManager::addGfxComponent(logic::CScreen* screen){
		CStaticModelMd3* model = CGraphicServer::instance().getStaticGfx(screen->id());
		if(!model)
			return;

		CScreenNode* node = new CScreenNode(model);
		node->setLogicEntity(screen);
		node->setRenderer(_renderer);

		_3dNodes->insertNode(node);

		_screenGfxTable[screen] = node;

		_trisInScene += node->numTris();
		//std::cout<<"[CSceneManager::addGfxComponent] Triangulos en escena: "<<_trisInScene<<"\n";

	}

	void CSceneManager::addGfxComponent(logic::CFrame* frame){
		CSpriteNode* uiNode = new CSpriteNode;
		uiNode->load(frame->id());
		uiNode->setLogicEntity(frame);
		uiNode->setZ(1);
		addUiNode(uiNode, frame);

		TTextBoxList textBoxes = frame->textBoxes();
		TTextBoxIterator ittb(textBoxes.begin()), endtb(textBoxes.end());
		for(;ittb!=endtb; ++ittb)
			addUiComponent((*ittb), 1);

		TButtonList buttons = frame->buttons();
		TButtonIterator itbutton(buttons.begin()), endbutton(buttons.end());
		for( ; itbutton!=endbutton; ++itbutton)
			addUiComponent((*itbutton), 1);

		TLabelList labels = frame->labels();
		TLabelIterator itlabel(labels.begin()), endlabel(labels.end());
		for( ; itlabel!=endlabel; ++itlabel)
			addUiComponent((*itlabel), 2);

	}

	void CSceneManager::addGfxComponent(logic::CButton* button){
		addUiComponent(button, 2);
	}

	void CSceneManager::addGfxComponent(logic::CLabel* label){
		addUiComponent(label, 2);
	}

	void CSceneManager::addGfxComponent(logic::CTextBox* textBox){
		addUiComponent(textBox, 3);
	}

	//--------------------------------------------------------------------------------------
	// Metodos de DESTRUCCION implementados del observador CreationDestroyListener
	//--------------------------------------------------------------------------------------

	void CSceneManager::removeGfxComponent(logic::CEntity* entity){
		TStaticGfxIterator it = _staticGfxTable.find(entity);
		if(it != _staticGfxTable.end()){
			CGraphicServer::instance().removeStaticGfx(entity->id());

			CStaticEntityNode* seNode = it->second;

			entity->removeListener(seNode);

			_3dNodes->deleteNode(seNode);
			//_invertedNodes->deleteNode(seNode);

			_staticGfxTable.erase(it);
			safeDelete(seNode);

			//cout<<"[CSceneManager::removeGfxComponent] Quitando elemento estatico "<<entity->id()<<" de la escena, quedan "<<_3dNodes->size()<<"\n";
		}

		if(entity->reflection()){
			destroyTransparentNode(entity);
		}

	}

	void CSceneManager::removeGfxComponent(logic::CAvatar* avatar){
		TAnimatedGfxIterator it = _animatedGfxTable.find(avatar);
		if(it != _animatedGfxTable.end()){

			CGraphicServer::instance().removeAnimatedGfx(avatar->id());

			CAnimatedEntityNode* aeNode = it->second;
			avatar->removeListener(aeNode);
			avatar->removeAnimationListener(aeNode);

			_3dNodes->deleteNode(aeNode);
			//_invertedNodes->deleteNode(aeNode);
			_animatedGfxTable.erase(it);
			safeDelete(aeNode);
			//cout<<"[CSceneManager::removeGfxComponent] Quitando elemento avatar "<<avatar->id()<<" de la escena, quedan "<<_3dNodes->size()<<"\n";
		}
	}

	void CSceneManager::removeGfxComponent(logic::CScenario* scenario){
		logic::CScenario::TEntityList furnitureList = scenario->furniture();
		logic::CScenario::TMultFurnList multFurnitureList = scenario->multFurniture();
		logic::CScenario::TAvatarList audience = scenario->audience();

		// Destruyo los elementos estaticos
		logic::CScenario::TEntityIterator
			itfur(furnitureList.begin()),
			endfur(furnitureList.end());
		for(; itfur!=endfur; ++itfur){
			removeGfxComponent(*itfur);
		}

		// Destruyo los elementos multimedia
		logic::CScenario::TMultFurIterator
			itmulfur(multFurnitureList.begin()),
			endmulfur(multFurnitureList.end());
		for(; itmulfur!=endmulfur; ++itmulfur){
			removeGfxComponent(*itmulfur);
		}

		// Destruyo el publico
		logic::CScenario::TAvatarIterator
			itaud(audience.begin()),
			endaud(audience.end());
		for(;itaud!=endaud; ++itaud){
			this->removeGfxComponent(*itaud);
		}

		// Destruyo al presentador
		removeGfxComponent((logic::CAvatar*)scenario->host());

		// Destruyo la pantalla
		removeGfxComponent(scenario->screen());

		//cout<<"[CSceneManager::removeGfxComponent] Quitado escenario "<<scenario->id()<<" de la escena, quedan "<<_3dNodes->size()<<"\n";

	}

	void CSceneManager::removeGfxComponent(logic::CScreen* screen){
		TScreenGfxIterator it = _screenGfxTable.find(screen);
		if(it != _screenGfxTable.end()){

			CGraphicServer::instance().removeStaticGfx(screen->id());

			CScreenNode* seNode = it->second;

			((logic::CEntity*)screen)->removeListener(seNode);
			((logic::CMultimediaFurniture*)screen)->removeListener(seNode);
			screen->removeListener(seNode);

			_3dNodes->deleteNode(seNode);

			_screenGfxTable.erase(it);
			safeDelete(seNode);

			//cout<<"3D: Quitando elemento "<<screen->id()<<" de la escena, quedan "<<_3dNodes->size()<<"\n";
		}
	}

	void CSceneManager::removeGfxComponent(logic::CUiComponent* uiComponent){
		TUITableIterator it = _uiTable.find(uiComponent);
		if(it != _uiTable.end()){
			CUINode* node = it->second;

			//CGraphicServer::instance().removeButton(uiComponent->id());

			uiComponent->removeListener(node);

			_2dNodes->deleteNode(node);
			_uiTable.erase(it);
			safeDelete(node);
			//cout<<"2D: Quitando elemento "<<uiComponent->getID()<<" de la escena, quedan "<<_3dNodes->getSize()<<"\n";
		}
	}

	void CSceneManager::removeGfxComponent(logic::CButton* button) {
		//cout<<"[CSceneManager::removeGfxComponent] Borro boton: "<<button->style()<<"\n";
		CGraphicServer::instance().removeButton(button->style());

		TUITableIterator it = _uiTable.find((logic::CUiComponent*)button);
		if(it != _uiTable.end()){
			CButtonNode* node = (CButtonNode*)it->second;
			button->removeListener(node);
		}
		removeGfxComponent((logic::CUiComponent*)button);
	}

	void CSceneManager::removeGfxComponent(logic::CLabel* label) {
		//cout<<"[CSceneManager::removeGfxComponent] Borro etiqueta: "<<label->style()<<"\n";

		TUITableIterator it = _uiTable.find((logic::CUiComponent*)label);
		if(it != _uiTable.end()){
			CLabelNode* node = (CLabelNode*)it->second;
			label->removeListener(node);
		}
		removeGfxComponent((logic::CUiComponent*)label);
	}

	void CSceneManager::removeGfxComponent(logic::CTextBox* tb) {
		//cout<<"[CSceneManager::removeGfxComponent] Borro text box: "<<tb->id()<<"\n";

		TUITableIterator it = _uiTable.find((logic::CUiComponent*)tb);
		if(it != _uiTable.end()){
			CTextLayoutNode* node = (CTextLayoutNode*)it->second;
			tb->removeListener(node);
		}
		removeGfxComponent((logic::CUiComponent*)tb);
	}


	void CSceneManager::removeGfxComponent(logic::CFrame* frame){
		//cout<<"[CSceneManager::removeGfxComponent] Borro frame: "<<frame->id()<<"\n";
		CGraphicServer::instance().removeSprite(frame->id());

		TButtonList buttons = frame->buttons();
		TButtonIterator itb(buttons.begin()), endb(buttons.end());
		for(;itb!=endb;++itb){
			//cout<<"Borrando componente con id: "<<(*it)->getID()<<"\n";
			removeGfxComponent((logic::CButton*)(*itb));
		}

		TLabelList labels = frame->labels();
		TLabelIterator itl(labels.begin()), endl(labels.end());
		for(;itl!=endl;++itl){
			//cout<<"Borrando componente con id: "<<(*it)->getID()<<"\n";
			removeGfxComponent((*itl));
		}

		TTextBoxList textBoxes = frame->textBoxes();
		TTextBoxIterator ittb(textBoxes.begin()), endtb(textBoxes.end());
		for(;ittb!=endtb;++ittb){
			//cout<<"Borrando componente con id: "<<(*it)->getID()<<"\n";
			removeGfxComponent((*ittb));
		}

		removeGfxComponent((logic::CUiComponent*)frame);
	}

	//--------------------------------------------------------------------------------------
	// METODOS PROTEGIDOS
	//--------------------------------------------------------------------------------------

	void CSceneManager::createTransparentNode(logic::CEntity* entity){

		CStaticModelMd3* model = CGraphicServer::instance().getStaticGfx(entity->id());
		if(!model)
			return;

		CTransparentNode* node = new CTransparentNode(model);

		node->setLogicEntity(entity);
		_transparentNodes->insertNode(node);
		_transparentTable[entity] = node;

		//std::cout<<"[C3DSceneManager::createTransparentNode] Reflejo para "<<entity->id()<<"\n";

	}

	void CSceneManager::destroyTransparentNode(logic::CEntity* entity){
		TTransparentIterator it = _transparentTable.find(entity);
		if(it!=_transparentTable.end()){

			CGraphicServer::instance().removeStaticGfx(entity->id());

			CStaticEntityNode* rNode = it->second;

			entity->removeListener(rNode);
			_transparentNodes->deleteNode(rNode);
			_transparentTable.erase(it);

			safeDelete(rNode);
		}
	}

	void CSceneManager::addUiComponent(logic::CButton* button, const int z){
		CButtonNode* uiNode = new CButtonNode;
		uiNode->load(button->style());
		uiNode->setLogicEntity(button);
		uiNode->setZ(z);
		addUiNode(uiNode, button);
	}

	void CSceneManager::addUiComponent(logic::CLabel* label, const int z){
		CLabelNode* uiNode = new CLabelNode;
		uiNode->setLogicEntity(label);
		uiNode->setZ(z);
		addUiNode(uiNode, label);
	}

	void CSceneManager::addUiComponent(logic::CTextBox* textLayout, const int z){
		CTextLayoutNode* uiNode = new CTextLayoutNode;
		uiNode->setLogicEntity(textLayout);
		uiNode->setZ(z);
		addUiNode(uiNode, textLayout);
	}

	void CSceneManager::addUiNode(CUINode* uiNode, logic::CUiComponent* uiComponent){
		uiNode->setRenderer(_renderer);
		_2dNodes->insertNode(uiNode);
		_uiTable[uiComponent] = uiNode;

		//cout<<"2D: Elementos en escena al renderizar "<<_3dNodes->getSize()<<"\n";
	}

	//--------------------------------------------------------------------------------------
	// METODOS PRIVADOS
	//--------------------------------------------------------------------------------------

	bool CSceneManager::render3dModels(){
		// Renderizado de modelos 3D
		glEnableClientState (GL_VERTEX_ARRAY);
		glEnableClientState (GL_NORMAL_ARRAY);
		glEnableClientState (GL_TEXTURE_COORD_ARRAY);
		bool result = _3dNodes->render();
		glDisableClientState (GL_VERTEX_ARRAY);
		glDisableClientState (GL_NORMAL_ARRAY);
		glDisableClientState (GL_TEXTURE_COORD_ARRAY);
		return result;
	}

	bool CSceneManager::render2dModels(){

		CWindowManager::instance().enable2DDrawing();
		COglFunctions::instance().enableBlending();
		bool result = _2dNodes->render();
		COglFunctions::instance().disableBlending();
		CWindowManager::instance().disable2DDrawing();
		return result;
	}

	bool CSceneManager::renderTransparentModels(){
		bool result = true;

		COglFunctions::instance().disableLight();
		COglFunctions::instance().enableBlending();
		result &= _transparentNodes->render();	// Renderizamos la superfices reflectantes
		COglFunctions::instance().disableBlending();
		COglFunctions::instance().enableLight();
		return result;

	}

	bool CSceneManager::renderReflectedModels(){
		bool result = true;

		COglFunctions::instance().activateStencil();
		// Don't update color
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		// Dibuja 1 en el stencil buffer en aquellos lugares donde hay reflejo
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

		// Ahora dibujamos las superficies transparentes
		result &= _transparentNodes->render();	// Quedan marcadas en el stencil con 1

		// Reabilitamos el color y test de profundidad
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		// Solo se renderiza aquellos lugares en que el stencil este a 1
		glStencilFunc(GL_EQUAL, 1, 0xffffffff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		glCullFace(GL_FRONT);
		glPushMatrix();
			glScalef(1.0, -1.0, 1.0);
			result &= _invertedNodes->render();
			//result &= _invertedNodes->inverseRender();	// Renderizamos los objetos reflejados
												// en la superficie reflectante marcada antes
		glPopMatrix();

		COglFunctions::instance().deactivateStencil();

		return result;

	}

	void CSceneManager::actualizeLights() {
		_itlight = _lights.begin();
		_endlight = _lights.end();
		for(;_itlight!=_endlight;++_itlight)
			(*_itlight)->actualize();
	}

}
