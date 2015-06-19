/*
 * SmpegMovie.cpp
 *
 *  Created on: 02/11/2010
 *      Author: jorge
 */

#include "gui/video/SmpegMovie.h"
#include "gui/WindowManager.h"

#include <SDL/SDL_mixer.h>
#include <iostream>

namespace gui {

CSmpegMovie::CSmpegMovie(const string& path):
			_moviePath(path),
			_movieSurface(0),
			_mpeg(0)
{
	_rotation = 0.0f;
	_needsUpdate = false;
}

CSmpegMovie::~CSmpegMovie() {
	// Antes de borrar la pelicula, hay que pararla
	stop();
	// Y eliminar el enlace con SDL_mixer
	Mix_HookMusic(NULL, NULL);

	glDeleteLists(_dl, 1);
	glDeleteTextures(1, &_frameTextureID);
}

bool CSmpegMovie::bindVideoTexture(){
/*
	glPushMatrix();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
*/
		glBindTexture( GL_TEXTURE_2D, _frameTextureID );
		glTexSubImage2D(
			GL_TEXTURE_2D, 0, 0, 0,
			_mpegInfo.width,
			_mpegInfo.height,
			GL_RGBA, GL_UNSIGNED_BYTE,
			(GLubyte*)_movieSurface->pixels );
/*
		glCallList(_dl);

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

	glPopMatrix();
*/
	return true;
}

void CSmpegMovie::play(){
	if(!_mpeg)
		load();
	SMPEG_play(_mpeg);
}

void CSmpegMovie::pause(){
	SMPEG_stop(_mpeg);
}

void CSmpegMovie::stop(){
	if(_mpeg){
		SMPEG_stop(_mpeg);
		SMPEG_delete(_mpeg);
		_mpeg = 0;
	}
	if(_movieSurface){
		SDL_FreeSurface(_movieSurface);
		_movieSurface = 0;
	}
}

void CSmpegMovie::setVolume(int vol){
	SMPEG_setvolume(_mpeg, vol);
}

bool CSmpegMovie::load(){
	// Cargamos la pelicula y almacenamos la informacion correspondiente a ella

	_mpeg = SMPEG_new(_moviePath.c_str(), &_mpegInfo, 0);

	// Configuracion para usar SDL_mixer
	SMPEG_enableaudio(_mpeg, 0);

	SDL_AudioSpec audiofmt;
	Uint16 format;
	int freq, channels;

	// Le decimos a SMPEG que formato de audio hay.
	Mix_QuerySpec(&freq, &format, &channels);
	audiofmt.format = format;
	audiofmt.freq = freq;
	audiofmt.channels = channels;
	SMPEG_actualSpec(_mpeg, &audiofmt);

	//SMPEG_enablevideo(_movie, true);
	//SMPEG_setvolume(_movie, 80);

	_movieSurface = SDL_AllocSurface(
	    		SDL_SWSURFACE,
	    		_mpegInfo.width,
	    		_mpegInfo.height,
	    		32,
	    		0x000000FF,0x0000FF00,0x00FF0000,0xFF000000 );

	SMPEG_setdisplay (_mpeg, _movieSurface, 0, 0 );

	// Creamos la textura que contendra la imagen de cada frame
	createFrameTexture();

	// Creamos un plano como DL que sera el que contenga la pelicula
	createDL();

	return true;
}

IVideo::EMovieState CSmpegMovie::state() const {
	if(!_mpeg) return NO_MOVIE;

	EMovieState movieStatus;
	switch(SMPEG_status(_mpeg)){
	case SMPEG_PLAYING:
		movieStatus = MOVIE_PLAYING;
		break;
	case SMPEG_STOPPED:
		movieStatus = MOVIE_STOPPED;
		break;
	default:
		movieStatus = MOVIE_ERROR;
	}
	return movieStatus;
}

void CSmpegMovie::createFrameTexture(){
	// Para la textura de video
	// Creamos un buffer para guardar los pixeles de una imagen del video
	GLubyte* pixels = (GLubyte*)malloc(_mpegInfo.width * _mpegInfo.height * 4);

	// Establecemos todos los bytes a cero
	memset(pixels, 0, _mpegInfo.width * _mpegInfo.height * 4);

	// Asociamos la textura
	glGenTextures(1,&_frameTextureID);
	glBindTexture( GL_TEXTURE_2D, _frameTextureID);

	// Establecemos un filtro linear para la textura
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	// Creamos la textura, con id _frameTextureID, a partir del buffer de pixels
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			_mpegInfo.width,
			_mpegInfo.height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			pixels
	);
	free( pixels );
}

void CSmpegMovie::createDL(){
	_dl = glGenLists(1);              			// generate display list
	glNewList(_dl, GL_COMPILE);			  	// fill display list
	glBegin(GL_QUADS);								// Begin Drawing A Plane
		glTexCoord2f(0,1); glVertex3f(0, 0, 0);
		glTexCoord2f(1,1); glVertex3f(150, 0, 0);
		glTexCoord2f(1,0); glVertex3f(150, 150, 0);
		glTexCoord2f(0,0); glVertex3f(0, 150, 0);
	glEnd();
	glEndList();
}

}
