/**
 * @file ScreenNode.h
 *
 *	Contiene la declaración de un nodo de escena
 *	que representa una entidad 3D estatica
 *	que puede usar video como textura.
 *	<br>
 *	Esta clase es una especializacion de gui::CStaticEntityNode,
 *	se encarga de representar una pantalla.
 *	Desacopla al objeto logico logic::CScreen de
 *	su representacion.
 *	<br>
 *
 *	@see gui::CStaticEntityNode
 *	@see logic::CScreen::ScreenListener
 *
 * @author Jorge Lopez Gonzalez
 * @date Octubre, 2010
 */

#ifndef SCREENNODE_H_
#define SCREENNODE_H_

#include "StaticEntityNode.h"

#include "gui/graphicserver/GraphicServer.h"
#include "gui/video/VideoServer.h"

#include "logic/entitys/Screen.h"

namespace gui {

	class CScreenNode :
		public CStaticEntityNode,
		public logic::CScreen::ScreenListener
		{

	public:

		CScreenNode(CStaticModelMd3* model);
		virtual ~CScreenNode();

		bool render();

		bool setLogicEntity(logic::CScreen* screen);

		//--------------------------------------------------------------------------------------
		// Metodos implementados del observador ScreenListener
		//--------------------------------------------------------------------------------------
		void playVideoEvent(const string& videoName);
		void stopVideoEvent();
		void pauseVideoEvent();
		void resumeVideoEvent();

	protected:
		CVideoServer*	 	_videoServer;
		IVideo* 			_video;

		logic::CScreen* 	_screen;

	};

}

#endif /* SCREENNODE_H_ */
