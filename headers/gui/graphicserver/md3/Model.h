/*
 * Model.h
 *
 *  Created on: 12/08/2011
 *      Author: jorge
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "MD3structs.h"

namespace gui {

	//----------------------------------------------------------------------------------------------------------------
	// ESTRUCTURAS PROPIAS PARA LOS MODELOS 3D
	//----------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	// ESTRUCTURAS RELATIVAS A LAS MALLAS
	//-------------------------------------------------------------------------------------------

	/**
	 * Indices a los vertices que forman una cara de un objeto 3D
	 */
	struct tFace {
		unsigned int indices[3];
	};

	struct tMesh {
	public:
		tMesh():
			numVerts(0),
			numFaces(0),
			numTexVerts(0),
			pVerts(0),
			pNormals(0),
			pTexVerts(0),
			pFaces(0)
		{}
	public:
		char 				name[255];		// Nombre de la malla
		int  				numVerts;		// Numero de vertices de la malla
		int  				numFaces;		// Numero de caras de la malla
		int  				numTexVerts;	// Numero de coordenadas de textura

		math::CVector3f*	pVerts;			// Vertices de la malla a lo largo de todos los frames de animacion
		math::CVector3f*	pNormals;		// Normales de la malla a lo largo de todos los frames de animacion
		math::CVector2f*	pTexVerts;		// Coordenadas de textura
		tFace* 				pFaces;			// Caras que forman la malla

		math::CVector3f*	drawVertArray;
		math::CVector3f*	drawNormArray;

	};

	//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	// ESTRUCTURAS RELATIVAS A LAS ANIMACIONES
	//-------------------------------------------------------------------------------------------

	struct tAnimation
	{
		char	name[255];
		int 	startFrame;
		int 	endFrame;
		int 	loopingFrames;
		int 	fps;
	};

	struct tAnimationState{
	public:
		// Constructor
		tAnimationState ();
		void setup (tAnimation* a);
		void update (float dt);
		const bool end() const { return _end; }

	private:
		tAnimation*	animation;		// Puntero a la animacion en marcha
		float 		currTime;
		float 		oldTime;
		bool		_end;

	public:
		int 		currentFrame;
		int 		nextFrame;
		float 		interp;
	};

	//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	// ESTRUCTURAS RELATIVA A LOS TAGS
	//-------------------------------------------------------------------------------------------

	struct tQuatTag {
	public:
		// Constructor
		tQuatTag (const tMd3Tag &tag);

	public:
		std::string 		name;
		math::CVector3f 	origin;
		math::CQuaternionf	orient;
	};

	//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	// ESTRUCTURAS RELATIVA A LOS SKINS DEL MODELO
	//-------------------------------------------------------------------------------------------

	struct tMaterial {
		char  		type[255];			// Nombre de la textura
		char  		filename[255];		// Ruta de la textura
		signed char	color[4];			// Color del material (R, G, B, A)
		int   		textureId;			// Id de la textura
	} ;

	typedef std::map<std::string, tMaterial>	MaterialMap;

	struct tSkin{
	public:
		tSkin(){}
	public:
		MaterialMap		materials;
	};

	typedef std::map<std::string, tSkin> 		SkinMap;

//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	// ESTRUCTURA RELATIVA A LOS VOLUMENES QUE CONTIENEN LAS MALLAS
	//-------------------------------------------------------------------------------------------
	struct tBoundingVolumes {
		math::CBoundingBox bb;
		math::CBoundingSphere bs;
	};

	//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	// ESTRUCTURA QUE REPRESENTA UN MODELO 3D
	//-------------------------------------------------------------------------------------------

	struct tModel {
	public:
		tModel() :
			skins(),
			scale(1)
		{
		}

		void setSkin(const std::string& type);
		void setupVertexArrays();

	public:
		int 					numMeshes;			// The number of objects in the model
		int 					numMaterials;		// The number of materials for the model
		int 					numTags;			// This stores the number of tags in the model

		// Bounding Volumes
		std::vector<tBoundingVolumes>	volumes;

		// Pieles
		SkinMap					skins;
		tSkin*					currentSkin;

		// Mallas
		std::vector<tMesh> 		meshes;				// The object list for our model

		// Enlaces
		std::vector<tQuatTag*>	tags;				// Almacena los tags del modelo
		const tModel**			pLinks;				// This stores a list of pointers that are linked to this model

		// Animaciones
		std::vector<tAnimation> animations; 		// The list of animations
		int 					numOfAnimations;	// The number of animations in this model
		int 					currentAnim;		// The current index into pAnimations list

		tAnimationState			animationState;

		float					scale;
	};


}

#endif /* MODEL_H_ */
