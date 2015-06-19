/*
 * Spline.h
 *
 *  Created on: 16/02/2011
 *      Author: jorge
 */

#ifndef SPLINE_H_
#define SPLINE_H_

#include <cstdio>
#include <cstdlib>

#include <vector>
#include "math/Mathlib.h"

#include "utilitys/utils.h"

namespace math{

	class Spline{
	public:

		Spline() {}

		Spline(uint numSeg, std::vector<CVector3f> points):
			_numControlPoints(points.size()),
			_m(points.size()-1),
			_numSegments(numSeg),
			_controlPoints(points)
		{
			_gam = new double[_numControlPoints];
			_der = new CVector3f[_numControlPoints];
			_ome = new CVector3f[_numControlPoints];

			// Calculamos el valor de gamma (sera el mismo en X y en Y)
			_gam[0] = .5;
			for (uint i=1; (uint)i<_m; ++i)
				_gam[i] = 1./(4.-_gam[i-1]);

			_gam[_m] = 1./(2.-_gam[_m-1]);

			// Calculamos el valor de omega para abcisas (X) y ordenadas (Y)
			_ome[0] = (_controlPoints[1] - _controlPoints[0])*3. * _gam[0];
			for (uint i=1; (uint)i<_m; ++i)
				_ome[i] = ((_controlPoints[i+1] - _controlPoints[i-1])*3. - _ome[i-1])*_gam[i];

			_ome[_m] = ((_controlPoints[_m] - _controlPoints[_m-1])*3. - _ome[_m-1]) * _gam[_m];

			// Valor de la primera derivada en los puntos (eje X, eje Y)
			_der[_m] = _ome[_m];
			for (int i=_m-1; i>=0; i=i-1)
				_der[i] = _ome[i] - _der[i+1]*_gam[i];
		}

		~Spline(){
			//delete[] _gam;
			//delete[] _der;
			//delete[] _ome;
		}

		std::vector<CVector3f> naturalCubicSpline ();

		CVector3f getPointOfSpline(uint n);

	private:

		uint					_numControlPoints;
		uint					_m;
		uint 					_numSegments;
		std::vector<CVector3f> 	_controlPoints;

		double*					_gam;
		CVector3f*				_der;
		CVector3f*				_ome;
	};

}
#endif /* SPLINE_H_ */
