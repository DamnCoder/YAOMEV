/*
 * VideoServer.cpp
 *
 *  Created on: 30/10/2010
 *      Author: jorge
 */

#include "gui/video/VideoServer.h"
#include "gui/video/SmpegMovie.h"

namespace gui {

CVideoServer::~CVideoServer() {
	TVideoTableIterator it(_videoTable.begin ()),
			end(_videoTable.end());

	for(;it!=end;++it){
		delete (*it).second;
	}

	_videoTable.clear();
}

void CVideoServer::add(const string& videoName, EMovieType type){

	string fullpath = _videoPaths+videoName;

	TVideoTableIterator it = _videoTable.find(fullpath);

	// Si el video existe, no lo añadimos de nuevo
	if(it != _videoTable.end())
		return;

	IVideo* video = 0;

	// Inicializamos el video en funcion de su tipo
	switch(type){
	case SMPEG:
		video = new CSmpegMovie(fullpath);
		break;
	default:
		video = new CSmpegMovie(fullpath);
	}

	// Guardamos el video en la tabla de videos
	_videoTable[fullpath] = video;
}

IVideo* CVideoServer::get(const string& videoName){
	TVideoTableIterator it = _videoTable.find(_videoPaths+videoName);

	// Si el video no esta en la tabla, lo añadimos
	if(it == _videoTable.end()){
		add(videoName, SMPEG);
	}

	return _videoTable[_videoPaths+videoName];
}

}
