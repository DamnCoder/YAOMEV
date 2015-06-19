/*
 * Screen.h
 *
 *  Created on: 28/10/2010
 *      Author: jorge
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "MultimediaFurniture.h"

namespace logic {

	class CScreen : public CMultimediaFurniture {
	public:

		class ScreenListener{
		public:
			virtual ~ScreenListener() {}

			virtual void stopVideoEvent() = 0;
			virtual void pauseVideoEvent() = 0;
			virtual void resumeVideoEvent() = 0;
			virtual void playVideoEvent(const std::string& videoName) = 0;
		};

		CScreen();
		CScreen(const std::string& id,
				float x, float y, float z,
				float orientation,
				bool visible);

		virtual ~CScreen();

		virtual void actualize(float dt);

		//--------------------------------------------------------------------------------------
		// Modificadores
		//--------------------------------------------------------------------------------------
		void setOrientation(const float orientation);

		void playVideo(const std::string& video);
		void stopVideo();
		void pauseVideo();
		void resumeVideo();

		const std::string videoName() const { return _videoName; }

		bool addListener(ScreenListener* newListener);
		bool removeListener(ScreenListener* oldListener);

	private:

		void emitPlayVideo();
		void emitStopVideo();
		void emitPauseVideo();
		void emitResumeVideo();

		std::string								_videoName;			/** Nombre del video en pantalla */
		std::list<ScreenListener*> 				_screenListeners;	/** Listeners de pantalla */
		std::list<ScreenListener*>::iterator	_itscr, _endscr;	/** Iteradores de listeners de pantalla */

	};

}

#endif /* SCREEN_H_ */
