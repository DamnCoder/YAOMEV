/**
 * @file CBTAState.h
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

#ifndef BTASTATE_H_
#define BTASTATE_H_

#include "ApplicationState.h"

#include "app/YaoApp.h"

#include "gui/SceneManager.h"
#include "gui/cam/CameraManager.h"

#include "ui/InputManager.h"
#include "event/WindowListener.h"
#include "event/KeyListener.h"
#include "event/MouseListener.h"

namespace app {

	class CYaoController :
		public CApplicationState,
		public event::WindowListener,
		public event::KeyAdapter,
		public event::MouseAdapter{

	public:

		/**
		 * Constructor de la clase
		 * @param app Aplicacion a la que pertenece el estado.
		 */
		CYaoController(CYaoApp* app);

		/** Destructor de la clase */
		virtual ~CYaoController();

		virtual void onCreate();
		virtual void onDestroy();

		virtual void onRun(float dt);

		void activateGfxManagers();
		void deactivateGfxManagers();

		gui::CSceneManager* sceneManager() const { return _sceneManager; }

		void closeWindowEvent() { _app->askForTermination(); }

	protected:

		/**
		 * Método reimplementado por las clases hijas, y que ejecuta la lógica
		 * asociada a este estado. Es llamada antes del dibujado de la
		 * escena.
		 * @param dt Tiempo transcurrido en milisegundos desde la última
		 * actualización de la lógica
		 */
		virtual void executeLogic(float dt){}

		/**
		 * Método que puede ser reimplementado por las clases hijas y que realiza el dibujado
		 * de la escena
		 * @param dt Tiempo transcurrido en milisegundos desde el último
		 * dibujado.
		 */
		virtual void render(float dt){}

		/**
		 * Método llamado desde el onRun() cuando se estima que hay que
		 * procesar los eventos. Las distintas clases hija implementaran
		 * los eventos que necesiten para procesar la entrada de
		 * usuario
		 */
		virtual void processUserInput();


		/** Puntero a la aplicacion a la que pertenece el estado */
		CYaoApp*				_yaoApp;

		ui::CInputManager*		_inputManager;

		gui::CSceneManager*		_sceneManager;
		gui::CCameraManager*	_cameraManager;
		gui::CWindowManager*	_window;

		audio::CAudioManager*	_audioManager;

	private:

		bool	_gfxActive;	/** Indica si se han inicializado los gestores graficos */

	};

}

#endif /* BTASTATE_H_ */
