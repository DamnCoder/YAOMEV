/*
 * WindowManager.cpp
 *
 *  Created on: 27/07/2010
 *      Author: jorge
 */

#include "gui/WindowManager.h"

#include <cassert>

// Includes de las librerias SDL
#include <SDL/SDL_image.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>

// Includes de las librerias OpenGL
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

namespace gui {

	CWindowManager::CWindowManager():
			_screen(0),
			_sdlInitHere(false),
			_sdlSubsitemInitHere(false),
			_sdlttfInitHere(false)
	{}

	CWindowManager::~CWindowManager() {
		stop();
	}

	//--------------------------------------------------------------------------------------
	// Metodos de arranque y parada de OpenGL y SDL
	//--------------------------------------------------------------------------------------

	bool CWindowManager::init(const tDisplayMode& displayMode){

		//_screen = 0;
		_displayMode = displayMode;

		if(!initSDL())
			return false;

		if(!initGL())
			return false;

		return true;
	}

	void CWindowManager::stop() {

		SDL_FreeSurface(_screen);

		if (_sdlInitHere)
			SDL_Quit();
		else if (_sdlSubsitemInitHere)
			SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

		if(_sdlttfInitHere)
			TTF_Quit();
	}

	bool CWindowManager::initSDL() {

		// Inicializamos la libreria SDL
		if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
			if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
				std::cerr<<"[CWindowManager::initSDL][ERROR] "<<SDL_GetError()<<"\n";
				if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
					std::cerr<<"[CWindowManager::initSDL][ERROR] "<<SDL_GetError()<<"\n";
					return false;
				}
				else
					_sdlInitHere = true;
			}
			else
				_sdlSubsitemInitHere = true;
		} // if que miraba si el video estaba inicializado.

		// Miramos el estado del motor de fuentes de SDL.
		if (!TTF_WasInit()) {
			// Nos toca inicializar el motor de texto SDL.
			if (TTF_Init()==-1)
				return false;
			_sdlttfInitHere = true;
		}

		return setDisplayMode(_displayMode);

	}

	bool CWindowManager::initGL(){
		//Establecemos el color de fondo
		// 0,0,0 NEGRO
		// 1,1,1 BLANCO

		// Habilitamos Smooth Shading
		glShadeModel( GL_SMOOTH );

		// Establecemos el buffer de produndidad (o Z-Buffer)
		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);

		// Stencil Buffer Setup
		glClearStencil(0);

		// Establecemos el CULLING de la escena
		glEnable(GL_CULL_FACE);

		glEnable(GL_LIGHTING);	    						//se activa la iluminacion
		glEnable(GL_COLOR_MATERIAL);						//Se activa los materiales de color


		//Parametros de calidad
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
		//glHint( GL_LINE_SMOOTH_HINT, 			GL_NICEST );
		//glHint( GL_POINT_SMOOTH_HINT, 		GL_NICEST );
		glHint( GL_POLYGON_SMOOTH_HINT, 		GL_NICEST );

		// Establecemos color de fondo
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClearColor(.0f, .0f, .0f, .0f);


		glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);  	//Se desean de tipo ambiente y difusión (tambien incluyen specular)

		oglResizeWindow(_displayMode._width, _displayMode._height);

		return true;
	}

	bool CWindowManager::setDisplayMode(const tDisplayMode& displayMode){

		this->_displayMode = displayMode;

		// Establecemos el nombre de la ventana
		setWindowName(_displayMode._name);

		// Cargamos icono de la ventana
		setWindowIcon("");

		// Obtenemos informacion sobre las capacidades de video
		const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();

		//std::cout<<"[CWindowManager::setDisplayMode] Anchura pantalla: "<<videoInfo->current_w<<" Altura pantalla: "<<videoInfo->current_h<<"\n"<<std::endl;

		if(!videoInfo)
			return false;

		//Establecemos los flags para el SDL_SetVideoMode
		_videoFlags  = SDL_HWSURFACE;		//Habilitamos que se use la memoria de la tarjeta de video
		_videoFlags |= SDL_OPENGL;			//Habilitamos OpenGL en SDL
		_videoFlags |= SDL_GL_DOUBLEBUFFER;	//Habilitamos el double buffering
		_videoFlags |= SDL_HWPALETTE;		//Guardamos la paleta en hardware
		_videoFlags |= SDL_RESIZABLE;		//Permitimos que la ventana pueda redimensionarse

		if(videoInfo->blit_hw)
			_videoFlags |= SDL_HWACCEL;

		if (_displayMode._fullscreen){
			_videoFlags |= SDL_FULLSCREEN;
			_displayMode._width = videoInfo->current_w;
			_displayMode._height = videoInfo->current_h;
		}

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );

		// Intentamos establecer los parametros de video
		_screen = SDL_SetVideoMode(_displayMode._width, _displayMode._height, _displayMode._bpp, _videoFlags);
		if ( _screen == NULL ) {

			// Probamos una configuracion mas ligera
			_videoFlags = SDL_SWSURFACE | SDL_OPENGL| SDL_GL_DOUBLEBUFFER;

			if (_displayMode._fullscreen)
				_videoFlags |= SDL_FULLSCREEN;

			_screen = SDL_SetVideoMode(_displayMode._width, _displayMode._height, _displayMode._bpp, _videoFlags);

			// Si definitivamente no podemos conseguir establecer los parametros, devolvemos false y terminamos
			if ( _screen == NULL )
				return false;
		}
/*
		int i = 0;
		SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &i);
		//std::cout<<"Tenemos Stencil buffer o que? "<<i<<"\n"<<std::endl;
*/

		return true;



	}

	//--------------------------------------------------------------------------------------
	// UTILIDADES DE OPENGL
	//--------------------------------------------------------------------------------------

	void CWindowManager::clearScreen() {
		assert(_screen);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void CWindowManager::swapBuffers() {
		glFlush();
		SDL_GL_SwapBuffers();
	}

	void CWindowManager::enable2DDrawing(){

		int vPort[4];

		glGetIntegerv(GL_VIEWPORT, vPort);

		// Clear Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		// Depth testing and lighting are disabled  for 2D rendering until
		// we are finished this mode
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		// Set up orthogonal projection onto window's screen space
		glOrtho(0.0f, vPort[2], 0.0f, vPort[3], -1.0f, 1.0f);

		// Clear model transform
		glMatrixMode (GL_MODELVIEW);
		glPushMatrix ();
		glLoadIdentity ();

	}

	void CWindowManager::disable2DDrawing(){

		// Restore previous model/projection transformation state
		glPopMatrix ();
		glMatrixMode (GL_PROJECTION);

		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

		glPopMatrix ();
		glMatrixMode (GL_MODELVIEW);
	}

	//--------------------------------------------------------------------------------------
	// METODOS RELACIONADOS CON LA REDIMENSION DE LA PANTALLA
	//--------------------------------------------------------------------------------------

	bool CWindowManager::resizeWindow(int width, int height){

		// Nos aseguramos de que al calcular el ratio no haya una division por cero
		if(height == 0)
			height = 1;

		// Indicamos a SDL que redimensione la surface principal
		if(!sdlResizeWindow(width, height))
			return false;

		// Indicamos a OpenGL que redimensione la pantalla
		if(!oglResizeWindow(width, height))
			return false;

		// Guardamos las nuevas dimensiones en la variable displayMode
		_displayMode._width = width;
		_displayMode._height = height;

		return true;
	}

	bool CWindowManager::sdlResizeWindow(int width, int height){
		assert(_screen);
		_screen = SDL_SetVideoMode(width, height, _displayMode._bpp, _videoFlags );

		if (!_screen)
			return false;

		return true;
	}

	bool CWindowManager::oglResizeWindow(int width, int height)
	{
		GLfloat ratio = ( GLfloat )width / ( GLfloat )height;

		glViewport(0, 0, ( GLsizei )width, ( GLsizei )height); // Establecemos el viewport con el tamaño de la ventana

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, ratio, 0.1f, 100.0f); // Queremos dibujar usando perspectiva

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		return true;
	}

	bool CWindowManager::setFullScreen(){
		if(_screen == NULL)
			return false;
		else{
			const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();
			SDL_WM_ToggleFullScreen(_screen);
			_displayMode._width = videoInfo->current_w;
			_displayMode._height = videoInfo->current_h;
		}
		return true;
	}

	void CWindowManager::setWindowName(const std::string& name){
		_displayMode._name = name;
		// Establecemos el nombre de la ventana
		SDL_WM_SetCaption(_displayMode._name.c_str(), NULL);
	}

	void CWindowManager::setWindowIcon(const std::string& iconpath){
		SDL_Surface *icono;
		icono = SDL_LoadBMP("Data/imagenes/icono.bmp");
		if ((icono != NULL) && (SDL_SetColorKey(icono, SDL_SRCCOLORKEY, SDL_MapRGB(icono->format, 255, 255, 255)) == 0))
			SDL_WM_SetIcon(icono, NULL);
	}

}	// gui

