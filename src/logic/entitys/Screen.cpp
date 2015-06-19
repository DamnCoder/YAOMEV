/*
 * Screen.cpp
 *
 *  Created on: 28/10/2010
 *      Author: jorge
 */

#include "logic/entitys/Screen.h"

namespace logic {

	CScreen::CScreen() : CMultimediaFurniture()
	{}

	CScreen::CScreen(
			const std::string& id,
			float x, float y, float z,
			float orientation,
			bool visible):
			CMultimediaFurniture(id, x, y, z, orientation, visible)
	{}

	CScreen::~CScreen() {
		_screenListeners.clear();
	}

	void CScreen::actualize(float dt) {
		//CMultimediaFurniture::actualize(dt);
	}

	//--------------------------------------------------------------------------------------
	// Modificadores
	//--------------------------------------------------------------------------------------
	void CScreen::setOrientation(const float orientation) {
		CEntity::setOrientation(orientation);
	}

	void CScreen::playVideo(const std::string& video) {
		_videoName = video;
		emitPlayVideo();
	}

	void CScreen::stopVideo() {
		emitStopVideo();
	}

	void CScreen::pauseVideo() {
		emitPauseVideo();
	}

	void CScreen::resumeVideo() {
		emitResumeVideo();
	}

	//--------------------------------------------------------------------------------------
	// Escuchadores
	//--------------------------------------------------------------------------------------
	bool CScreen::addListener(ScreenListener* newListener){
		_screenListeners.push_back(newListener);
		return true;
	}

	bool CScreen::removeListener(ScreenListener* oldListener){
		_screenListeners.remove(oldListener);
		return true;
	}

	void CScreen::emitPlayVideo(){
		_itscr = _screenListeners.begin();
		_endscr = _screenListeners.end();
		for(; _itscr!=_endscr; ++_itscr)
			(*_itscr)->playVideoEvent(_videoName);
	}

	void CScreen::emitStopVideo(){
		_itscr = _screenListeners.begin();
		_endscr = _screenListeners.end();
		for(; _itscr!=_endscr; ++_itscr)
			(*_itscr)->stopVideoEvent();
	}

	void CScreen::emitPauseVideo(){
		_itscr = _screenListeners.begin();
		_endscr = _screenListeners.end();
		for(; _itscr!=_endscr; ++_itscr)
			(*_itscr)->pauseVideoEvent();
	}

	void CScreen::emitResumeVideo(){
		_itscr = _screenListeners.begin();
		_endscr = _screenListeners.end();
		for(; _itscr!=_endscr; ++_itscr)
			(*_itscr)->resumeVideoEvent();
	}
}
