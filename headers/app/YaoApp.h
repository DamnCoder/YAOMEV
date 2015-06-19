/**
 * @file YaoApp.h
 *
 * Contiene la declaración de una clase de aplicacion hecha con YAOMEV.
 * <br>
 * Esta clase es la especializacion de la clase app::CApplication, se encarga de
 * inicializar y finalizar los diferentes módulos de YAOMEV.
 * que ver con su logica o sus controladores.
 * <br>
 *
 * @see app::CApplication
 * @see app::CYaoController
 *
 * @author Jorge Lopez Gonzalez
 * @date Enero, 2010
 */

#ifndef YAOAPP_H_
#define YAOAPP_H_

#include "Application.h"

#include "audio/SdlAudio.h"
#include "gui/video/VideoServer.h"
#include "gui/WindowManager.h"

namespace gui {
	class CFontsCache;
	class CGraphicServer;
	class CTextureCache;
}

namespace utils{
	class CLog;
	class CRandom;
}

namespace temp {
	class Timer;
}

namespace app {

	class CYaoApp : public CApplication{
	public:
		CYaoApp();
		virtual ~CYaoApp();

		bool init();
		void end();

		audio::CAudioManager*	getAudioManager() 	const { return _audioManager; }
		gui::CWindowManager* 	getWindow() 		const { return _windowManager; }

	protected:

		/**
		 * Inicializa el contador de tiempo del juego
		 */
		void initTimer();

		/**
		 * Actualiza el contador de tiempo del juego
		 */
		void updateTimer();
		void checkFPS(int secs);

		virtual gui::tDisplayMode loadInitDisplayMode() = 0;

		// Elementos de la capa grafica
		gui::CWindowManager*	_windowManager;			/** Instancia del gestor de la ventana principal */
		gui::CFontsCache*		_fontsCache;			/** Instancia del gestor de fuentes */
		gui::CTextureCache*		_textureCache;			/** Instancia del gestor de texturas */
		gui::CVideoServer*	 	_videoServer;			/** Instancia del servidor de video */
		gui::CGraphicServer*	_graphicServer;			/** Instancia del servidor grafico */

		// Utilidades
		utils::CLog*			_logManager;			/** Instancia del gestor de Log */
		utils::CRandom*			_randomizer;			/** Instancia del generador de numeros aleatorios */

		// Audio
		audio::CAudioManager*	_audioManager;			/** Instancia del gestor de audio */

		// Temporizador
		temp::Timer*			_timer;					/** Temporizador */
};

}

#endif /* YAOAPP_H_ */
