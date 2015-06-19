/*
 * VideoServer.h
 *
 *  Created on: 30/10/2010
 *      Author: jorge
 */

#ifndef VIDEOSERVER_H_
#define VIDEOSERVER_H_

#include "IVideo.h"

#include "utilitys/Singleton.h"

#include <map>
#include <string>

using namespace std;

namespace gui {

class CVideoServer : public CSingleton<CVideoServer>{

friend class CSingleton<CVideoServer>;

public:

	typedef enum{
		SMPEG,
	} EMovieType;

	void init(const string& videoPaths){
		_videoPaths = videoPaths;
	}

	void add(const string& videoName, EMovieType type);

	IVideo* get(const string& videoName);

private:

	CVideoServer(){}

	virtual ~CVideoServer();

	typedef map<string, IVideo*>::iterator TVideoTableIterator;

	string 					_videoPaths;

	map<string, IVideo*> 	_videoTable;
};

}

#endif /* VIDEOSERVER_H_ */
