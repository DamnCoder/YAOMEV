/*
 * AnimModelRenderer.cpp
 *
 *  Created on: 02/05/2011
 *      Author: jorge
 */

#include "gui/renderer/ModelRenderer.h"

namespace gui {

	CModelRenderer::CModelRenderer() {
	}

	CModelRenderer::~CModelRenderer() {
	}

	bool CModelRenderer::render(
			const tModel *pModel,
			const math::CPositionf& position,
			const float orientation,
			const float scale)
	{
		glPushMatrix();

			glTranslatef(position.x, position.y, position.z);
			glRotatef(orientation, 0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

			drawLink(pModel, scale);

		glPopMatrix();

		return true;
	}

	void CModelRenderer::drawLink(const tModel *pModel, const float scale){

		math::Matrix4x4f m;
		render(pModel, scale);

		for(int tag = 0; tag < pModel->numTags; ++tag){
			const tModel* pLink = pModel->pLinks[tag];

			if(pLink){

				int currentFrame = pModel->animationState.currentFrame;
				int nextFrame = pModel->animationState.nextFrame;
				float interp = pModel->animationState.interp;

				int currentTagIndex = currentFrame * pModel->numTags + tag;
				int nextTagIndex = nextFrame * pModel->numTags + tag;

				const math::CQuaternionf& qA = pModel->tags[currentTagIndex]->orient;
				const math::CQuaternionf& qB = pModel->tags[nextTagIndex]->orient;
				m.fromQuaternion(math::Slerp(qA, qB, interp));

				const math::CVector3f& currPos = pModel->tags[currentTagIndex]->origin;
				const math::CVector3f& nextPos = pModel->tags[nextTagIndex]->origin;
				m.setTranslation(math::Lerp(currPos * scale, nextPos * scale, interp));

				glPushMatrix();
					glMultMatrixf(m);
					drawLink(pLink, scale);
				glPopMatrix();
			}
		}
	}

	void CModelRenderer::render(const tModel* pModel, const float scale){
		//printf("Current: %i, Next: %i\n",currentFrame, nextFrame);

		int currentFrame = pModel->animationState.currentFrame;
		int nextFrame = pModel->animationState.nextFrame;
		float interp = pModel->animationState.interp;

		math::CVector3f coord1, coord2;
		math::CVector3f normal1, normal2;
		math::CVector3f interpCoord1;
		math::CVector3f interpNormal1;

		for(int i = 0; i < pModel->numMeshes; i++) {
			const tMesh* pMesh = &pModel->meshes[i];

			// Recupero el frame actual y el siguiente para interpolarlos
			int currentIndex = currentFrame * pMesh->numVerts;
			int nextIndex = nextFrame * pMesh->numVerts;

			for(int v=0; v<pMesh->numVerts; ++v) {
				coord1 = pMesh->pVerts[currentIndex + v];
				coord2 = pMesh->pVerts[nextIndex + v];

				normal1 = pMesh->pNormals[currentIndex + v];
				normal2 = pMesh->pNormals[nextIndex + v];

				interpCoord1 = math::Lerp(coord1, coord2, interp);
				interpCoord1 *= scale;

				interpNormal1 = math::Lerp(normal1, normal2, interp);

				pMesh->drawVertArray[v] = interpCoord1;
				pMesh->drawNormArray[v] = interpNormal1;

			}

			// Enviamos los arrays a OpenGL
			glVertexPointer		(3, GL_FLOAT, 0, pMesh->drawVertArray);
			glNormalPointer		(GL_FLOAT, 0, pMesh->drawNormArray);
			glTexCoordPointer	(2, GL_FLOAT, 0, pMesh->pTexVerts);

			// Enlazamos la textura a la malla a dibujar
			if(pModel->currentSkin) {
				//printf("Malla: %s, Id textura: %i\n",pObject->name, skin->materials[pObject->name].textureId );
				glBindTexture(GL_TEXTURE_2D, pModel->currentSkin->materials[pMesh->name].textureId);
			}

			// Draw triangles
			glDrawElements (
					GL_TRIANGLES,
					pMesh->numFaces * 3,
					GL_UNSIGNED_INT,
					pMesh->pFaces);


			/*
			if(skin) {
				//printf("Malla: %s, Id textura: %i\n",pObject->name, skin->materials[pObject->name].textureId );
				glBindTexture(GL_TEXTURE_2D, skin->materials[pObject->name].textureId);
			}
			glBegin(GL_TRIANGLES);
			for(int j = 0; j < pObject->numFaces; j++){
				for(int whichVertex = 2; whichVertex > -1; --whichVertex){
					int index = pObject->pFaces[j].indices[whichVertex];

					math::CVector3f coord1 = pObject->pVerts[ currentIndex + index ];
					math::CVector3f coord2 = pObject->pVerts[ nextIndex + index];

					math::CVector3f normal1 = pObject->pNormals[currentIndex + index];
					math::CVector3f normal2 = pObject->pNormals[nextIndex + index];

					math::CVector3f interpCoord = math::Lerp(coord1, coord2, interp);
					interpCoord *= scale;

					const math::CVector3f interpNormal = math::Lerp(normal1, normal2, interp);

					glTexCoord2f(	pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
					glNormal3fv(interpNormal.v);
					glVertex3fv(interpCoord.v);

				}
			}
			glEnd();
			*/
		}
	}

	void CModelRenderer::renderTransparency(
			const tModel* pModel,
			const math::CPositionf& position,
			const float orientation,
			const float scale,
			TRGBAColor color){

		if(pModel->meshes.size() <= 0) return;

		//cout << "Transparencia "<<transpColor.r<<", "<<transpColor.g<<", "<<transpColor.b<<", "<<transpColor.a<<"\n";
		glColor4f(color.r, color.g, color.b, color.a);
		render(pModel, position, orientation, scale);
	}
}
