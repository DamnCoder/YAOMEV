/*
 * MD3structs.h
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#ifndef MD3STRUCTS_H_
#define MD3STRUCTS_H_

#define kLower	0			// This stores the ID for the legs model
#define kUpper	1			// This stores the ID for the torso model
#define kHead	2			// This stores the ID for the head model
#define kWeapon	3			// This stores the ID for the weapon model

#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>

#include <iostream>
#include "math/Mathlib.h"
#include "math/BoundingBox.h"

namespace gui{

	/**
	 * Estructuras correspondientes al formato MD3
	 */

	// Definicion de constantes
	const int 	MAX_QPATH 		= 64;
	const int 	MD3_MAX_FRAMES 	= 1024;
	const int 	MD3_MAX_TAGS 	= 16;
	const int 	MD3_MAX_MESHES 	= 32;
	const int 	MD3_MAX_SHADERS = 256;
	const int 	MD3_MAX_FACES 	= 8192;
	const int 	MD3_MAX_VERTICES = 4096;
	const float MD3_SCALE_FACTOR = 1.0f / 64.0f;

	// This enumeration stores all the animations in order from the config file (.cfg).
	typedef enum
	{
		// If one model is set to one of the BOTH_* animations, the other one should be too,
		// otherwise it looks really bad and confusing.

		BOTH_DEATH1 = 0,		// The first twirling death animation
		BOTH_DEAD1,				// The end of the first twirling death animation
		BOTH_DEATH2,			// The second twirling death animation
		BOTH_DEAD2,				// The end of the second twirling death animation
		BOTH_DEATH3,			// The back flip death animation
		BOTH_DEAD3,				// The end of the back flip death animation

		// The next block is the animations that the upper body performs

		TORSO_GESTURE,			// The torso's gesturing animation

		TORSO_ATTACK,			// The torso's attack1 animation
		TORSO_ATTACK2,			// The torso's attack2 animation

		TORSO_DROP,				// The torso's weapon drop animation
		TORSO_RAISE,			// The torso's weapon pickup animation

		TORSO_STAND,			// The torso's idle stand animation
		TORSO_STAND2,			// The torso's idle stand2 animation

		// The final block is the animations that the legs perform

		LEGS_WALKCR,			// The legs's crouching walk animation
		LEGS_WALK,				// The legs's walk animation
		LEGS_RUN,				// The legs's run animation
		LEGS_BACK,				// The legs's running backwards animation
		LEGS_SWIM,				// The legs's swimming animation

		LEGS_JUMP,				// The legs's jumping animation
		LEGS_LAND,				// The legs's landing animation

		LEGS_JUMPB,				// The legs's jumping back animation
		LEGS_LANDB,				// The legs's landing back animation

		LEGS_IDLE,				// The legs's idle stand animation
		LEGS_IDLECR,			// The legs's idle crouching animation

		LEGS_TURN,				// The legs's turn animation

		MAX_ANIMATIONS			// The define for the maximum amount of animations
	} eAnimations;

	/**
	 * Contiene la informacion de la cabecera del archivo MD3
	 * que es leida al comienzo del mismo.
	 */
	struct tMd3Header
	{
		char	ident[4];			// Id del archivo (debe ser "IDP3")
		int		version;			// Version del archivo (debe ser 15)
		char	name[MAX_QPATH];	// Nombre del archivo
		int		flags;				// ??? (no se usa)
		int		numFrames;			// Numero de frames
		int		numTags;			// Numero de tags
		int		numMeshes;			// Numero de mallas del modelo
		int		numShaders;			// Numero de shaders (skins) del modelo
		int		ofsFrames;			// Offset que indica donde comienzan los frames
		int		ofsTags;			// Offset que indica donde comienzan los tags
		int		ofsMesh;			// Offset que indica donde comienzan las mallas
		int		ofsEOF;				// Offset que indica donde acaba el archivo
	};

	/**
	 * Propiedades de un frame de animacion.
	 * Contiene la informacion de la bounding box, asi como
	 * de la bounding sphere del modelo.
	 */
	struct tMd3Frame
	{
		float	minBounds[3];	// Primera esquina de la bounding box
		float	maxBounds[3];	// Segunda esquina de la bounding box
		float	localOrigin[3];	// Origen local, centro de la bounding sphere
		float	radius;			// Radio de la bounding sphere
		char	name[16];		// Nombre del frame
	};

	/**
	 * Punto de anclaje con otro modelo MD3
	 * Indica la posicion y rotacion en cada frame
	 * del modelo hijo anclado.
	 */
	struct tMd3Tag
	{
		char			name[MAX_QPATH];	// Nombre del tag Ej: "tag_torso"
		math::CVector3f	origin;				// Posicion del modelo hijo
		float			axis[3][3];			// Matriz 3x3 con la rotacion del modelo hijo
	};

	/**
	 * Informacion de una malla del modelo MD3.
	 */
	struct tMd3MeshHeader
	{
		char	ident[4];			// Id de la malla (debe ser "IDP3")
		char	name[MAX_QPATH];	// Nombre de la malla
		int 	flags;				// ??? No se usa
		int		numFrames;			// Numero de frames
		int		numShaders;			// Numero de skins de la malla
		int     numVerts;			// Numero de vertices
		int		numFaces;			// Numero de caras (triangulos) de la malla
		int		ofsFaces;			// Offset que indica donde comienzan las caras
		int		ofsShaders;			// Offset que indica donde comienzan los skins
		int     ofsUV;				// Offset que indica donde comienzan las coordenadas UV
		int		ofsVert;			// Offset que indica donde comienzan los vertices
		int		ofsEnd;				// Offset que indica donde acaba la malla
	};
	/**
	 * Informacion sobre la textura de la malla.
	 */
	struct tMd3Shader
	{
		char 	name[MAX_QPATH];	// Nombre de la textura
		int		shaderIndex;
	};

	/**
	 * Indices a los arrays de vertices y coordenadas de textura
	 * que indican cuales forman un triangulo.
	 */
	struct tMd3Face
	{
	   int indices[3];
	};

	/**
	 * Coordenada UV de textura.
	 */
	struct tMd3TexCoord
	{
	   float uv[2];
	};

	/**
	 * Vertice compuesto por la posicion y normal del mismo.
	 */
	struct tMd3Vertex
	{
	   signed short	 	coord[3];	// Coordenada del vertice (escalado por 1/64)
	   unsigned char 	normal[2];	// Normales en forma polar, hace falta decodificarlas para poder usarlas
	   	   	   	   	   	   	   		// como un vector normal.
	};
}

#endif /* MD3STRUCTS_H_ */
