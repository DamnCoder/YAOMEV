/*
 * CreationDestroyListener.h
 *
 *  Created on: 03/09/2011
 *      Author: jorge
 */

#ifndef CREATIONDESTROYLISTENER_H_
#define CREATIONDESTROYLISTENER_H_

namespace logic{

class CScenario;
class CAvatar;
class CEntity;
class CScreen;

class CFrame;
class CButton;
class CLabel;
class CTextBox;
class CUiComponent;

/**
 * Observador de creacion/destruccion de los
 * elementos graficos que intervienen en la partida
 */
class CreationDestroyListener{
public:
	virtual ~CreationDestroyListener(){}

	virtual void addGfxComponent(CScenario* scenario) = 0;
	virtual void addGfxComponent(CAvatar* avatar) = 0;
	virtual void addGfxComponent(CEntity* entity) = 0;
	virtual void addGfxComponent(CScreen* screen) = 0;

	virtual void addGfxComponent(CFrame* frame) = 0;
	virtual void addGfxComponent(CButton* button) = 0;
	virtual void addGfxComponent(CLabel* label) = 0;
	virtual void addGfxComponent(CTextBox* textLayout) = 0;

	virtual void removeGfxComponent(CUiComponent* uiComponent) = 0;
	virtual void removeGfxComponent(CFrame* frame) = 0;

	virtual void removeGfxComponent(CAvatar* avatar) = 0;
	virtual void removeGfxComponent(CEntity* entity) = 0;
	virtual void removeGfxComponent(CScenario* scenario) = 0;
};

}

#endif /* CREATIONDESTROYLISTENER_H_ */
