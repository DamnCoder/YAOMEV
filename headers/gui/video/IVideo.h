/*
 * IVideo.h
 *
 *  Created on: 30/10/2010
 *      Author: jorge
 */

#ifndef IVIDEO_H_
#define IVIDEO_H_

namespace gui{

class IVideo{

public:

	typedef enum {
		MOVIE_ERROR = -1,
		NO_MOVIE,
		MOVIE_PLAYING,
		MOVIE_STOPPED,
	}EMovieState;

	virtual ~IVideo(){}

	virtual bool bindVideoTexture() = 0;

	virtual void play() = 0;

	virtual void pause() = 0;

	virtual void stop() = 0;

	virtual void setVolume(int vol) = 0;

	virtual EMovieState state() const = 0;

	virtual unsigned int getTextureID() const = 0;

private:

	virtual bool load() = 0;
};

}

#endif /* IVIDEO_H_ */
