/*
 * COctreeNode.cpp
 *
 *  Created on: 12/06/2011
 *      Author: jorge
 */

#include "gui/octreescene/COctree.h"

#include "gui/graphicserver/md3/StaticModelMd3.h"

namespace gui {

	///--------------------------------------------------------------------------------
	void COctree::addModel(CStaticEntityNode* node) {
		_staticModels.push_back(node);
		calculateCenter();
		calculateWidthOfCube();
		calculateTris();

		//std::cout<<"Centro ["<<_center.x<<", "<<_center.y<<", "<<_center.z<<"]\n";
		//std::cout<<"Ancho "<<_width<<"\n";
		//std::cout<<"Ancho "<<_tris<<"\n";

		createChilds();

	}

	void COctree::calculateCenter() {
		int numberOfVerts = 0;
		int numVertsModel = 0;

		statIt = _staticModels.begin();
		statEnd = _staticModels.end();
		for(;statIt!=statEnd; ++statIt){

			numVertsModel = (*statIt)->model()->numVerts();
			numberOfVerts += numVertsModel;

			for(int m=0; m<(*statIt)->model()->numMeshes(); ++m){
				const tModel* model = (*statIt)->model()->model();
				const tMesh* mesh = &model->meshes[m];
				for(int v=0; v<mesh->numVerts; ++v)
					_center += mesh->pVerts[v];
			}
		}

		_center/=numberOfVerts;
	}

	void COctree::calculateWidthOfCube() {
		float currentWidth=0, currentHeight=0, currentDepth=0;
		float maxWidth=0, maxHeight=0, maxDepth=0;
		statIt = _staticModels.begin();
		statEnd = _staticModels.end();
		for(;statIt!=statEnd; ++statIt){
			for(int m=0; m<(*statIt)->model()->numMeshes(); ++m){
				const tModel* model = (*statIt)->model()->model();
				const tMesh* mesh = &model->meshes[m];
				for(int v=0; v<mesh->numVerts; ++v) {
					currentWidth = fabsf(_center.x - mesh->pVerts[v].x);
					currentHeight = fabsf(_center.y - mesh->pVerts[v].y);
					currentDepth = fabsf(_center.z - mesh->pVerts[v].z);

					if(currentWidth>maxWidth) maxWidth = currentWidth;
					if(currentHeight>maxHeight) maxHeight= currentHeight;
					if(currentDepth>maxDepth) maxDepth = currentDepth;
				}
			}
		}

		maxWidth *= 2.0f;
		maxHeight *= 2.0f;
		maxDepth *= 2.0f;

		if(maxWidth > maxHeight && maxWidth > maxDepth)
			_width = maxWidth;
		else if(maxHeight > maxWidth && maxHeight > maxDepth)
			_width = maxHeight;
		else
			_width = maxDepth;
	}

	void COctree::calculateTris() {
		_tris = 0;
		statIt = _staticModels.begin();
		statEnd = _staticModels.end();
		for(;statIt!=statEnd; ++statIt)
			_tris += (*statIt)->numTris();
	}

	void COctree::createChilds() {
		// Comprobamos si se cumple la condicion de parada
		if( (_tris > _maxTris) && (_depth < _maxDepth) ) {

		}
	}

}
