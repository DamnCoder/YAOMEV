/**
 * @file CBTAState.cpp
 *
 * Contiene la declaración de la clase que representa un estado de la
 * aplicación BitThemAll.
 * <br>
 * Todos los estados de este tipo de aplicación, deberán heredar de esta
 * clase, e implementar los métodos virtuales.
 *
 * @see aplicacion::CEstadoAplicacion
 * @see aplicacion::CAplicacion
 *
 * @author Jorge Lopez Gonzalez
 * @date Septiembre, 2010
 */
#include "app/controllers/YaoController.h"

namespace app {

	CYaoController::CYaoController(CYaoApp* app):
			CApplicationState(app),
			_yaoApp(app),
			_inputManager(0),
			_sceneManager(0),
			_cameraManager(0),
			_window(0),
			_gfxActive(false)
	{}

	CYaoController::~CYaoController() {
	}

	void CYaoController::onCreate(){
		CApplicationState::onCreate();

		// Creamos el gestor de entrada del usuario
		_inputManager = new ui::CInputManager();
		_inputManager->addListener((event::WindowListener*)this);
		_inputManager->addListener((event::KeyListener*)this);

		// Recuperamos las instancias del gestor de audio y del gestor de ventanas
		_window = _yaoApp->getWindow();
		_audioManager = _yaoApp->getAudioManager();

	}

	void CYaoController::onDestroy(){
		CApplicationState::onDestroy();

		_inputManager->removeListener((event::WindowListener*)this);
		_inputManager->removeListener((event::KeyListener*)this);

		safeDelete(_inputManager);
	}

	void CYaoController::activateGfxManagers(){
		if(_gfxActive)
			return;

		// Creamos nuevas instancias del gestor de escena 3D y del gestor de escena 2D
		_sceneManager = new gui::CSceneManager();
		_cameraManager = _sceneManager->getCameraManager();

		_gfxActive = true;
	}

	void CYaoController::deactivateGfxManagers(){

		if(_gfxActive){
			// Eliminamos las instancias del gestor de escena 3D
			safeDelete(_sceneManager);

			_gfxActive = false;
		}

	}

	void CYaoController::onRun(float dt){
		CApplicationState::onRun(dt);

		processUserInput();
		executeLogic(dt);
		render(dt);
	}


	void CYaoController::processUserInput(){
		_inputManager->processUserInput();
	}

}
