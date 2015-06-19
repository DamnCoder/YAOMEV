/*
 * Spline.cpp
 *
 *  Created on: 20/02/2011
 *      Author: jorge
 */

#include "math/Spline.h"

namespace math{

	std::vector<CVector3f> Spline::naturalCubicSpline (){

		// Polinomio
		CVector3f a[_numControlPoints];
		CVector3f b[_numControlPoints];
		CVector3f c[_numControlPoints];
		CVector3f d[_numControlPoints];

		// Sustituimos los valores de gamma, omega y la primera derivada
		// para calcular los coeficientes a, b, c y d
		for (uint i=0; i<_m; ++i) {
			a[i] = _controlPoints[i];
			b[i] = _der[i];
			c[i] = (_controlPoints[i+1] - _controlPoints[i])*3. - _der[i]*2. - _der[i+1];
			d[i] = (_controlPoints[i] - _controlPoints[i+1])*2. + _der[i] + _der[i+1];
		}

		// En esta parte, se dibujara la curva por segmentos de lineas
		// rectas; si NUM_SEG es un valor alto, la grafica se dibujara
		// con mayor precision.

		// ds es la delta de incremento. Es la cantidad de espacio que hay entre un segmento y otro.
		double ds = 1./(double) _numSegments;

		std::vector<CVector3f> solPoints;
		CVector3f splinePoint;
		uint s = 0;
		double t;
		// Por cada intervalo (punto de control)
		for (uint i=0; (uint)i<_m; ++i) {
			// Hacemos 20 segmentos
			for (s=0, t=ds; s<_numSegments; ++s, t+=ds) {
				splinePoint = a[i] + b[i]*t + c[i]*t*t + d[i]*t*t*t;
				solPoints.push_back(splinePoint);
			}
		}

		return solPoints;
	}

	CVector3f Spline::getPointOfSpline(uint n){
		// Polinomio
		CVector3f a[_numControlPoints];
		CVector3f b[_numControlPoints];
		CVector3f c[_numControlPoints];
		CVector3f d[_numControlPoints];

		// Sustituimos los valores de gamma, omega y la primera derivada
		// para calcular los coeficientes a, b, c y d
		for (uint i=0; i<_m; ++i) {
			a[i] = _controlPoints[i];
			b[i] = _der[i];
			c[i] = (_controlPoints[i+1] - _controlPoints[i])*3. - _der[i]*2. - _der[i+1];
			d[i] = (_controlPoints[i] - _controlPoints[i+1])*2. + _der[i] + _der[i+1];
		}

		CVector3f splinePoint;

		// ds es la delta de incremento. Es la cantidad de espacio que hay entre un segmento y otro.
		double ds = 1./(double) _numSegments;
		double t = n*ds;

		//uint totalSplinePoints = _m*_numSegments;

		int i = n / _numSegments;
		//std::cout<<"Para n "<<n<<" el punto de control es "<<i<<"\n";
		splinePoint = a[i] + b[i]*t + c[i]*t*t + d[i]*t*t*t;
		return splinePoint;
	}

}
