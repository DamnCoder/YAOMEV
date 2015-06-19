/*
 * mWindowManager.h
 *
 *  Created on: 27/07/2010
 *      Author: jorge
 */

#ifndef CWINDOWMANAGER_H_
#define CWINDOWMANAGER_H_

#include "utilitys/Singleton.h"

#include <string>

#include <SDL/SDL.h>

namespace gui {

	/**
	 * Estructura que contiene la informacion sobre la ventana de
	 * la aplicacion.
	 */
	struct tDisplayMode{

		unsigned int 	_width;
		unsigned int 	_height;
		unsigned int	_bpp;
		int				_fullscreen;
		std::string 	_name;

		tDisplayMode():
			_width(800),
			_height(600),
			_bpp(16),
			_fullscreen(0),
			_name("PRUEBA") {}

		tDisplayMode(	unsigned int width,
						unsigned int height,
						unsigned int bpp,
						int fullscreen,
						std::string name) :
							_width(width),
							_height(height),
							_bpp(bpp),
							_fullscreen(fullscreen),
							_name(name){}
	};

	class CWindowManager : public CSingleton<CWindowManager> {
	friend class CSingleton<CWindowManager>;
	public:

		//--------------------------------------------------------------------------------------
		// Metodos de arranque y parada de OpenGL y SDL
		//--------------------------------------------------------------------------------------
		bool init(const tDisplayMode& displayMode);
		void stop();

		//--------------------------------------------------------------------------------------
		// UTILIDADES DE OPENGL
		//--------------------------------------------------------------------------------------
		void clearScreen();
		void swapBuffers();

		void enable2DDrawing();
		void disable2DDrawing();

		//--------------------------------------------------------------------------------------
		// METODOS RELACIONADOS CON LA REDIMENSION DE LA PANTALLA
		//--------------------------------------------------------------------------------------
		bool resizeWindow(int scrwidth, int scrheight);
		bool setFullScreen();

		tDisplayMode getScreenConfig() const { return _displayMode; }

		int width() const{ return _displayMode._width; }
		int height() const{ return _displayMode._height; }

		bool setDisplayMode(const tDisplayMode& displayMode);
		void setWindowName(const std::string& name);
		void setWindowIcon(const std::string& iconpath);

	private:
		CWindowManager();
		virtual ~CWindowManager();

		//--------------------------------------------------------------------------------------
		// Metodos de inicio de OpenGL y SDL
		//--------------------------------------------------------------------------------------
		bool initSDL();
		bool initGL();

		bool sdlResizeWindow(int width, int height);
		bool oglResizeWindow(int width, int height);

		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		SDL_Surface* 	_screen;
		tDisplayMode	_displayMode;
		unsigned int	_videoFlags;

		// Flags para saber en que momento se inicializan las librerias SDL
		bool 			_sdlInitHere;
		bool 			_sdlSubsitemInitHere;
		bool			_sdlttfInitHere;

	};

}	// gui

#endif /* MWINDOWMANAGER_H_ */
