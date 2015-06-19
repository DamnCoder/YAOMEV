/*
 * SmpegMovie.h
 *
 *  Created on: 02/11/2010
 *      Author: jorge
 */

#ifndef SMPEGMOVIE_H_
#define SMPEGMOVIE_H_

#include "IVideo.h"

#include <string>

#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL/SDL.h>
#include <smpeg/smpeg.h>

using namespace std;

namespace gui {

	class CSmpegMovie : public IVideo{

	public:

		CSmpegMovie(const string& path);

		virtual ~CSmpegMovie();

		bool bindVideoTexture();

		void play();
		void pause();
		void stop();

		void setVolume(int vol);

		EMovieState state() const;

		uint getTextureID() const {
			return _frameTextureID;
		}

	protected:
		virtual void createDL();

	private:
		bool load();
		void createFrameTexture();

		string 			_moviePath;
		SDL_Surface* 	_movieSurface;
		SMPEG_Info		_mpegInfo;
		SMPEG*			_mpeg;

		float 			_rotation;
		GLuint			_frameTextureID;
		GLuint			_dl;
		bool 			_needsUpdate;

	};

}

#endif /* SMPEGMOVIE_H_ */
