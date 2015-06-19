/*
 * YaoApp.cpp
 *
 *  Created on: 17/06/2011
 *      Author: jorge
 */

#include "app/YaoApp.h"

#include "gui/text/FontsManager.h"
#include "gui/graphicserver/GraphicServer.h"
#include "gui/TextureManager.h"

#include "persist/IDao.h"

#include "utilitys/Log.h"
#include "utilitys/Random.h"

#include "utilitys/timers/TimerFactory.h"

const char* logPath = "./data/log.txt";

namespace app {

	CYaoApp::CYaoApp() :
			CApplication(),
			_windowManager(0),
			_fontsCache(0),
			_textureCache(0),
			_videoServer(0),
			_logManager(0),
			_randomizer(0),
			_audioManager(0),
			_timer(0){ }

	CYaoApp::~CYaoApp() { }

	void CYaoApp::initTimer(){
		_timer->start();
	}

	bool CYaoApp::init(){

		if(!CApplication::init())
			return false;

		// Solicitamos un temporizador
		_timer = temp::CTimersFactory::getNewTimer(temp::UNIX_TIMER);

		// Recuperamos la instancias de los sistemas singleton
		_randomizer 	= utils::CRandom::pointer();
		_logManager 	= utils::CLog::pointer();

		_graphicServer	= gui::CGraphicServer::pointer();
		_windowManager	= gui::CWindowManager::pointer();
		_fontsCache		= gui::CFontsCache::pointer();
		_textureCache	= gui::CTextureCache::pointer();
		_videoServer	= gui::CVideoServer::pointer();

		_audioManager 	= audio::CAudioManager::pointer();


		// Iniciamos SDL y OpenGL
		if(!_windowManager->init(loadInitDisplayMode()))
			return false;

		// Iniciamos aquellos sistemas que haga uso de lazy inicialization
		_randomizer->init();		// Iniciamos la semilla del generador de numeros aleatorios
		_logManager->init(logPath);	// Iniciamos el log;

		// Los sistemas de video y audio deben inicializarse despues de SDL y el de audio antes que el de video
		_audioManager->init();
		_videoServer->init("./data/export/videos/");

		// Inicializamos el tiempo (importante hacerlo despues de iniciar SDL si usamos el temporizador SDL)
		initTimer();

		return true;
	}

	void CYaoApp::end(){
		//cout<<"Terminamos la aplicacion CYaoApp...\n";
		CApplication::end();

		_textureCache->freeAll();
		_logManager->end();

		gui::CVideoServer::destroyInstance();
		_videoServer = 0;

		_audioManager->end();
		audio::CAudioManager::destroyInstance();
		_audioManager = 0;

		_graphicServer->destroyInstance();
		_windowManager->destroyInstance();
		_fontsCache->destroyInstance();
		_textureCache->destroyInstance();
		_logManager->destroyInstance();

		_logManager = 0;
		_windowManager = 0;
		_fontsCache = 0;
		_textureCache = 0;

		safeDelete(_timer);

		//cout<<"Terminada aplicacion CYaoApp!!\n";
	}

	void CYaoApp::updateTimer(){
		_dt = _timer->getElapsedTimeInMilliSec();
		_timer->stop();

		if (_pauseTimer)
			_dt = 0;

		_timeApp += _dt;

		checkFPS(3);
	}

	void CYaoApp::checkFPS(int secs){
		if((_timeApp - _lastTimeApp) >= secs*1000.0f){
			char title[255];
			_fps/=secs;
			sprintf(title, "FPS [%d] [%f]",_fps, _dt);
			//_windowManager->setWindowName(title);
			_fps = 0;
			_lastTimeApp = _timeApp;
		}

		++_fps;
	}

}
