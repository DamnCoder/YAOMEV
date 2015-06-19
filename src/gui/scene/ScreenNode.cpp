/*
 * ScreenNode.cpp
 *
 *  Created on: 28/10/2010
 *      Author: jorge
 */

#include "gui/scene/ScreenNode.h"

#include "gui/TextureManager.h"

namespace gui {

	CScreenNode::CScreenNode(CStaticModelMd3* model):
		CStaticEntityNode(model),
			_videoServer(0),
			_video(0),
			_screen(0)
	{}

	CScreenNode::~CScreenNode() {
		if(_video)
			_video->stop();
	}

	bool CScreenNode::render(){

		if(!_video) return true;
		if((_video->state() == IVideo::MOVIE_PLAYING
			||
			_video->state() == IVideo::MOVIE_STOPPED)){
			_video->bindVideoTexture();
		}

		CStaticEntityNode::render();
		//glFrontFace(GL_CW);	// Establece el orden de las agujas del reloj
		//glRotatef(180.0f, 1.0f, .0f, .0f);
		//glFrontFace(GL_CCW);	// Establece el orden contrario a las agujas del reloj


		return true;
	}

	bool CScreenNode::setLogicEntity(logic::CScreen* screen){
		if(!CStaticEntityNode::setLogicEntity(screen))
			return false;

		if(_screen)
			_screen->removeListener(this);

		if(!screen->addListener(this))
			return false;

		_screen = screen;

		math::CPositionf pos = screen->position();
		_position.x = screen->position().x;
		_position.y = screen->position().y;
		_position.z = screen->position().z;

		_videoServer = CVideoServer::pointer();

		return true;
	}

	void CScreenNode::playVideoEvent(const string& videoName){
		if(_video)
			_video->stop();
		_video = _videoServer->get(videoName);

		_video->play();
		_video->setVolume(50);

		uint textureID = _video->getTextureID();

		_staticModel->setTexture(textureID);

	}

	void CScreenNode::stopVideoEvent(){
		if(!_video) return;
		_video->stop();
		_video = 0;
	}

	void CScreenNode::pauseVideoEvent(){
		if(!_video) return;
		_video->pause();
	}

	void CScreenNode::resumeVideoEvent(){
		pauseVideoEvent();
	}

}
