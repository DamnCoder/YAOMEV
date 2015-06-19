/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Mathlib.h -- Copyright (c) 2005-2006 David Henry
// last modification: feb. 19, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Declarations for 3D maths object and functions to use with OpenGL.
//
// Provide vector, matrix and quaternion operations.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MATHLIBMOD_H__
#define __MATHLIBMOD_H__

#include <cmath>
#include <cassert>

namespace math {

	// Forward declarations
	template <typename Real> class Vector3;
	template <typename Real> class Matrix4x4;
	template <typename Real> class Quaternion;

	// Type definitions
	enum Axis {
	  kXaxis, kYaxis, kZaxis
	};

	// Declare a global constant for pi and a few multiples.
	const float kPi = 3.14159265358979323846f;
	const float k2Pi = kPi * 2.0f;
	const float kPiOver2 = kPi / 2.0f;
	const float k1OverPi = 1.0f / kPi;
	const float k1Over2Pi = 1.0f / k2Pi;
	const float kPiOver180 = kPi / 180.0f;	// Grados a radianes
	const float k180OverPi = 180.0f / kPi;	// Radianes a grados

	// "Wrap" an angle in range -pi...pi by adding the correct multiple
	// of 2 pi
	template <typename Real>
	Real wrapPi (Real theta);

	// "Safe" inverse trig functions
	template <typename Real>
	Real safeAcos (Real x);

	// Set the Euler angle triple to its "canonical" value
	template <typename Real>
	void canonizeEulerAngles (Real &roll, Real &pitch, Real &yaw);

	// Convert between degrees and radians
	template <typename Real>
	inline Real degToRad (Real deg) { return deg * kPiOver180; }

	template <typename Real>
	inline Real radToDeg (Real rad) { return rad * k180OverPi; }

	// Convert between "field of view" and "zoom".
	// The FOV angle is specified in radians.
	template <typename Real>
	inline Real fovToZoom (Real fov) { return 1.0f / std::tan (fov * 0.5f); }

	template <typename Real>
	inline Real zoomToFov (Real zoom) { return 2.0f * std::atan (1.0f / zoom); }


	/////////////////////////////////////////////////////////////////////////////
	//
	// class Vector2<Real> - A simple 2D vector class.
	//
	/////////////////////////////////////////////////////////////////////////////

	template <typename Real>
	class Vector2
	{
	public:
		Vector2() : x (0), y (0) {}
		Vector2(Real x, Real y)
			: x(x), y(y) {}

		union
		{
			struct
			{
				Real x, y;
			};
			Real v[2];
		};
	};

	// Predefined Vector3 types
	typedef Vector2<float> Vector2f;
	typedef Vector2<float> CVector2f;
	typedef Vector2<float> UvCoordf;

	typedef Vector2<double> Vector2d;
	typedef Vector2<double> CVector2d;

	/////////////////////////////////////////////////////////////////////////////
	//
	// class Vector4<Real> - A simple 4D vector class.
	//
	/////////////////////////////////////////////////////////////////////////////

	template <typename Real>
	class Vector4
	{
	public:
		Vector4() : x (0), y (0), z(0), w(0) {}
		Vector4(Real x, Real y, Real z, Real w)
			: x(x), y(y), z(z), w(w) {}

	public:
		void normalize ();

		union {
			struct {
				Real x, y, z, w;
			};
			Real v[4];
		};
	};

	// Predefined Vector3 types
	typedef Vector4<float> Vec4;
	typedef Vector4<float> Vector4f;
	typedef Vector4<float> CVector4f;
	typedef Vector4<float> CPlanef;

	typedef Vector4<double> Vector4d;
	typedef Vector4<double> CVector4d;

	//
	// Nonmember Vector4 functions
	//
	template <typename Real>
	bool IsFacingTo (const Vector4<Real> plane, const Vector3<Real> &v);

	template <typename Real>
	bool IsFacingTo (const Vector4<Real> plane, const Vector3<Real> &v, Real radius);

	//////////////////////////////////////////////////
	//
	// class Vector3<Real> - A simple 3D vector class.
	//
	/////////////////////////////////////////////////////////////////////////////

	template <typename Real>
	class Vector3
	{
	public:
	  // Constructors
	  Vector3 () : x(0), y(0), z(0) {}
	  Vector3 (Real x, Real y, Real z = 0):x(x), y(y), z(z) {}

	  void fromPolarAngles(Real azimuth, Real zenith);

	public:
	  // Vector comparison
	  bool operator== (const Vector3<Real> &v) const;
	  bool operator!= (const Vector3<Real> &v) const;

	  // Vector negation
	  Vector3<Real> operator- () const;

	  // Vector operations
	  Vector3<Real> operator+ (const Vector3<Real> &v) const;
	  Vector3<Real> operator- (const Vector3<Real> &v) const;
	  Vector3<Real> operator* (Real s) const;
	  Vector3<Real> operator/ (Real s) const;

	  // Combined assignment operators to conform to
	  // C notation convention
	  Vector3<Real> &operator+= (const Vector3<Real> &v);
	  Vector3<Real> &operator-= (const Vector3<Real> &v);
	  Vector3<Real> &operator*= (Real s);
	  Vector3<Real> &operator/= (Real s);

	  // Accessor.  This allows to use the vector object
	  // like an array of Real. For example:
	  // Vector3<float> v (...);
	  // float f = v[1]; // access to _y
	  operator const Real *() { return v; }

	public:
	  // Other vector operations
	  bool isZero ();
	  void normalize ();

	  Real length();

	  void rotate (float degrees, float distance);

	public:
	  // Member variables
	  union {
		struct {
		  Real x, y, z;
		};

		Real v[3];
	  };
	};


	// Predefined Vector3 types
	typedef Vector3<float> Vector3f;
	typedef Vector3<float> CVector3f;
	typedef Vector3<float> CPositionf;

	typedef Vector3<double> Vector3d;
	typedef Vector3<double> CVector3d;
	typedef Vector3<double> CPositiond;

	// We provide a global constant zero vector
	static const Vector3f kZeroVectorf (0.0f, 0.0f, 0.0f);
	static const Vector3d kZeroVectord (0.0, 0.0, 0.0);


	//
	// Nonmember Vector3 functions
	//

	template <typename Real>
	Vector3<Real> operator* (Real k, Vector3<Real> v);

	template <typename Real>
	Real VectorMag (const Vector3<Real> &v);

	template <typename Real>
	Real DotProduct (const Vector3<Real> &a, const Vector3<Real> &b);

	template <typename Real>
	Vector3<Real> CrossProduct (const Vector3<Real> &a, const Vector3<Real> &b);

	template <typename Real>
	Vector3<Real> ComputeNormal (const Vector3<Real> &p1,
		 const Vector3<Real> &p2, const Vector3<Real> &p3);

	template <typename Real>
	Real Distance (const Vector3<Real> &a, const Vector3<Real> &b);

	template <typename Real>
	Real DistanceSquared (const Vector3<Real> &a, const Vector3<Real> &b);

	template <typename Real>
	Vector3<Real> Lerp(const Vector3<Real> &a, const Vector3<Real> &b, const Real t);

	template <typename Real>
	Vector3<Real> UnitVectorFromOrientation(float degrees);


	/////////////////////////////////////////////////////////////////////////////
	//
	// class Matrix4x4<Real> - Implement a 4x4 Matrix class that can represent
	// any 3D affine transformation.
	//
	/////////////////////////////////////////////////////////////////////////////

	template <typename Real>
	class Matrix4x4 {
	public:
		// Constructor - Initialize the last (never used) row of the matrix
		// so that we can do any operation on matrices on the 3x4 portion
		// and forget that line which will (and should) never change.
		Matrix4x4 () : h14 (0.0f), h24 (0.0f), h34 (0.0f), tw (1.0f) { }

		// Note that we don't define the copy constructor and let the compiler
		// doing it itself because such initialization is not necessary
		// since the source matrix has its last row already initialized...

	public:
		// Public interface
		void identity ();
		void transpose ();
		void invert ();
		void setTranslation (const Vector3<Real> &v);

		void transform (Vector3<Real> &v) const;
		void rotate (Vector3<Real> &v) const;
		void inverseRotate (Vector3<Real> &v) const;
		void inverseTranslate (Vector3<Real> &v) const;

		void fromQuaternion (const Quaternion<Real> &q);

		// Matrix <-> Euler conversions; XYZ rotation order; angles in radians
		void fromEulerAngles (Real x, Real y, Real z);
		void toEulerAngles (Real &x, Real &y, Real &z) const;

		// Return a base vector from the matrix
		Vector3<Real> rightVector () const;
		Vector3<Real> upVector () const;
		Vector3<Real> forwardVector () const;
		Vector3<Real> translationVector () const;

		// Accessor.  This allows to use the matrix object
		// like an array of Real. For example:
		// Matrix4x4<float> mat;
		// float f = mat[4]; // access to _m21
		operator const Real *() { return m; }

	public:
		// Member variables

		// The values of the matrix.  Basically the upper 3x3 portion
		// contains a linear transformation, and the last column is the
		// translation portion. Here data is transposed, see the Mathlib.inl
		// for more details.
		union {
			struct {
				Real m11, m12, m13, h14;
				Real m21, m22, m23, h24;
				Real m31, m32, m33, h34;
				Real tx,  ty,  tz,  tw;
			};

			// Access to raw packed matrix data (usefull for
			// glLoadMatrixf () and glMultMatrixf ())
			Real m[16];
		};
	};


	// Predefined Matrix4x4 types
	typedef Matrix4x4<float> Matrix4x4f;
	typedef Matrix4x4<double> Matrix4x4d;


	//
	// Nonmember Matrix4x4 functions
	//

	// Matrix concatenation
	template <typename Real>
	Matrix4x4<Real> operator* (const Matrix4x4<Real> &a, const Matrix4x4<Real> &b);

	template <typename Real>
	Matrix4x4<Real> &operator*= (Matrix4x4<Real> &a, const Matrix4x4<Real> &b);

	// Vector transformation
	template <typename Real>
	Vector3<Real> operator* (const Matrix4x4<Real> &m, const Vector3<Real> &p);

	// Transpose matrix
	template <typename Real>
	Matrix4x4<Real> Transpose (const Matrix4x4<Real> &m);

	// Invert matrix
	template <typename Real>
	Matrix4x4<Real> Invert (const Matrix4x4<Real> &m);

	//
	// Matrix-builder functions
	//

	template <typename Real>
	Matrix4x4<Real> RotationMatrix (Axis axis, Real theta);

	template <typename Real>
	Matrix4x4<Real> RotationMatrix (const Vector3<Real> &axis, Real theta);

	template <typename Real>
	Matrix4x4<Real> TranslationMatrix (Real x, Real y, Real z);

	template <typename Real>
	Matrix4x4<Real> TranslationMatrix (const Vector3<Real> &v);

	template <typename Real>
	Matrix4x4<Real> ScaleMatrix (const Vector3<Real> &s);

	template <typename Real>
	Matrix4x4<Real> ScaleAlongAxisMatrix (const Vector3<Real> &axis, Real k);

	template <typename Real>
	Matrix4x4<Real> ShearMatrix (Axis axis, Real s, Real t);

	template <typename Real>
	Matrix4x4<Real> ProjectionMatrix (const Vector3<Real> &n);

	template <typename Real>
	Matrix4x4<Real> ReflectionMatrix (Axis axis, Real k);

	template <typename Real>
	Matrix4x4<Real> AxisReflectionMatrix (const Vector3<Real> &n);


	template <typename Real>
	Matrix4x4<Real> LookAtMatrix (
			const Vector3<Real> &camPos,
			const Vector3<Real> &target,
			const Vector3<Real> &camUp);

	template <typename Real>
	Matrix4x4<Real> FrustumMatrix (Real l, Real r, Real b, Real t, Real n, Real f);

	template <typename Real>
	Matrix4x4<Real> PerspectiveMatrix (Real fovY, Real aspect, Real n, Real f);

	template <typename Real>
	Matrix4x4<Real> OrthoMatrix (Real l, Real r, Real b, Real t, Real n, Real f);

	template <typename Real>
	Matrix4x4<Real> OrthoNormalMatrix (
			const Vector3<Real> &xdir,
			const Vector3<Real> &ydir,
			const Vector3<Real> &zdir);


	/////////////////////////////////////////////////////////////////////////////
	//
	// class Quaternion<Real> - Implement a quaternion, for purposes of
	// representing an angular displacement (orientation) in 3D.
	//
	/////////////////////////////////////////////////////////////////////////////

	template <typename Real>
	class Quaternion
	{
	public:
	  // Constructors
	  Quaternion () { }
	  Quaternion (Real w, Real x, Real y, Real z)
		: w (w), x (x), y (y), z (z) { }

	public:
	  // Public interface
	  void identity ();
	  void normalize ();
	  void computeW ();
	  void rotate (Vector3<Real> &v) const;

	  void fromMatrix (const Matrix4x4<Real> &m);

	  // Quaternion <-> Euler conversions; XYZ rotation order; angles in radians
	  void fromEulerAngles (Real x, Real y, Real z);
	  void toEulerAngles (Real &x, Real &y, Real &z) const;

	  Real rotationAngle () const;
	  Vector3<Real> rotationAxis () const;

	  // Quaternion operations
	  Quaternion<Real> operator+ (const Quaternion<Real> &q) const;
	  Quaternion<Real> &operator+= (const Quaternion<Real> &q);

	  Quaternion<Real> operator- (const Quaternion<Real> &q) const;
	  Quaternion<Real> &operator-= (const Quaternion<Real> &q);

	  Quaternion<Real> operator* (const Quaternion<Real> &q) const;
	  Quaternion<Real> &operator*= (const Quaternion<Real> &q);

	  Quaternion<Real> operator* (Real k) const;
	  Quaternion<Real> &operator*= (Real k);

	  Quaternion<Real> operator* (const Vector3<Real> &v) const;
	  Quaternion<Real> &operator*= (const Vector3<Real> &v);

	  Quaternion<Real> operator/ (Real k) const;
	  Quaternion<Real> &operator/= (Real k);

	  Quaternion<Real> operator~ () const; // Quaternion conjugate
	  Quaternion<Real> operator- () const; // Quaternion negation

	public:
	  // Member variables

	  // The 4 values of the quaternion.  Normally, it will not
	  // be necessary to manipulate these directly.  However,
	  // we leave them public, since prohibiting direct access
	  // makes some operations, such as file I/O, unnecessarily
	  // complicated.

	  union
	  {
		struct
		{
		  Real w, x, y, z;
		};

		Real q[4];
	  };
	};


	// Predefined Quaternion types
	typedef Quaternion<float> Quaternionf;
	typedef Quaternion<float> CQuaternionf;

	typedef Quaternion<double> Quaterniond;
	typedef Quaternion<double> CQuaterniond;

	// A global "identity" quaternion constant
	static const Quaternionf kQuaternionIdentityf (1.0f, 0.0f, 0.0f, 0.0f);
	static const Quaterniond kQuaternionIdentityd (1.0f, 0.0f, 0.0f, 0.0f);


	//
	// Nonmember Matrix4x functions
	//

	template <typename Real>
	Quaternion<Real> operator* (Real k, const Quaternion<Real> &q);

	template <typename Real>
	Real DotProduct (const Quaternion<Real> &a, const Quaternion<Real> &b);

	template <typename Real>
	Quaternion<Real> Conjugate (const Quaternion<Real> &q);

	template <typename Real>
	Quaternion<Real> Inverse (const Quaternion<Real> &q);

	template <typename Real>
	Quaternion<Real> RotationQuaternion (Axis axis, Real theta);

	template <typename Real>
	Quaternion<Real> RotationQuaternion (const Vector3<Real> &axis, Real theta);

	template <typename Real>
	Quaternion<Real> Log (const Quaternion<Real> &q);
	template <typename Real>
	Quaternion<Real> Exp (const Quaternion<Real> &q);
	template <typename Real>
	Quaternion<Real> Pow (const Quaternion<Real> &q, Real exponent);

	template <typename Real>
	Quaternion<Real> Slerp (const Quaternion<Real> &q0, const Quaternion<Real> &q1, Real t);

	template <typename Real>
	Quaternion<Real> Squad (const Quaternion<Real> &q0, const Quaternion<Real> &qa,
				const Quaternion<Real> &qb, const Quaternion<Real> &q1, Real t);

	template <typename Real>
	inline void Intermediate (const Quaternion<Real> &qprev, const Quaternion<Real> &qcurr,
				  const Quaternion<Real> &qnext, Quaternion<Real> &qa,
				  Quaternion<Real> &qb);

	/* -*- c++ -*- */
	/////////////////////////////////////////////////////////////////////////////
	//
	// Mathlib.inl -- Copyright (c) 2005-2006 David Henry
	// last modification: feb. 1, 2006
	//
	// -------------------------------------------------------------------
	// Portions Copyright (c) Dante Treglia II and Mark A. DeLoura, 2000.
	// Portions Copyright (c) Fletcher Dunn and Ian Parberry, 2002.
	// -------------------------------------------------------------------
	//
	// This software is provided "as is" without express or implied
	// warranties. You may freely copy and compile this source into
	// applications you distribute provided that the copyright text
	// below is included in the resulting source code.
	//
	// Implementation of a math library to use with OpenGL.
	//
	// Provide vector, matrix and quaternion operations.
	//
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//
	// Global functions
	//
	/////////////////////////////////////////////////////////////////////////////

	// --------------------------------------------------------------------------
	// wrapPi
	//
	// "Wrap" an angle in range -pi...pi by adding the correct multiple
	// of 2 pi
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Real
	wrapPi (Real theta)
	{
	  theta += kPi;
	  theta -= std::floor (theta * k1Over2Pi) * k2Pi;
	  theta -= kPi;
	  return theta;
	}


	// --------------------------------------------------------------------------
	// safeAcos
	//
	// Same as acos(x), but if x is out of range, it is "clamped" to the nearest
	// valid value. The value returned is in range 0...pi, the same as the
	// standard C acos() function
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Real
	safeAcos (Real x)
	{
	  // Check limit conditions
	  if (x <= -1.0)
	    return kPi;

	  if (x >= 1.0)
	    return 0.0;

	  // value is in the domain - use standard C function
	  return std::acos (x);
	}


	// --------------------------------------------------------------------------
	// canonizeEulerAngles
	//
	// Set the Euler angle triple to its "canonical" value.  This does not change
	// the meaning of the Euler angles as a representation of Orientation in 3D,
	// but if the angles are for other purposes such as angular velocities, etc,
	// then the operation might not be valid.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	canonizeEulerAngles (Real &roll, Real &pitch, Real &yaw)
	{
	  // First, wrap pitch in range -pi ... pi
	  pitch = wrapPi (pitch);

	  // Now, check for "the back side" of the matrix, pitch outside
	  // the canonical range of -pi/2 ... pi/2
	  if (pitch < -kPiOver2)
	    {
	      roll += kPi;
	      pitch = -kPi - pitch;
	      yaw += kPi;
	    }
	  else if (pitch > kPiOver2)
	    {
	      roll += kPi;
	      pitch = kPi - pitch;
	      yaw += kPi;
	    }

	  // OK, now check for the Gimbal lock case (within a slight
	  // tolerance)

	  if (std::fabs (pitch) > kPiOver2 - 1e-4)
	    {
	      // We are in gimbal lock.  Assign all rotation
	      // about the vertical axis to heading
	      yaw += roll;
	      roll = 0.0;
	    }
	  else
	    {
	      // Not in gimbal lock.  Wrap the bank angle in
	      // canonical range
	      roll = wrapPi (roll);
	    }

	  // Wrap heading in canonical range
	  yaw = wrapPi (yaw);
	}

	/////////////////////////////////////////////////////////////////////////////
	//
	// class Vector4<Real> implementation.
	//
	/////////////////////////////////////////////////////////////////////////////

	template <typename Real>
	inline void
	Vector4<Real>::normalize()
	{
		Real magSq = (x * x) + (y * y) + (z * z);

		if (magSq > 0.0)
	    {
			// check for divide-by-zero
			Real oneOverMag = 1.0 / std::sqrt (magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
			w *= oneOverMag;
	    }
	}

	// Decide if a plane is facing a point
	template <typename Real>
	inline bool
	IsFacingTo (const Vector4<Real> plane, const Vector3<Real> &v)
	{
	  return ((plane.x*v.x) + (plane.y*v.y) + (plane.z*v.z) + (plane.w))>0;
	}

	// Decide if a plane is facing a sphere
	template <typename Real>
	inline bool
	IsFacingTo (const Vector4<Real> plane, const Vector3<Real> &v, Real radius)
	{
	  return ((plane.x*v.x) + (plane.y*v.y) + (plane.z*v.z) + (plane.w))>-radius;
	}

	/////////////////////////////////////////////////////////////////////////////
	//
	// class Vector3<Real> implementation.
	//
	/////////////////////////////////////////////////////////////////////////////

	/**
	 * Decodifica las normales en forma polar y devuelve un vector normal
	 * @param azimuth
	 * @param zenith
	 * @return
	 */
	template <typename Real>
	inline void
	Vector3<Real>::fromPolarAngles(Real azimuth, Real zenith){
		Real lat = zenith * (k2Pi)/255.0;
		Real lng = azimuth * (k2Pi)/255.0;

		x = cos(lat) * sin(lng);
		y = sin(lat) * sin(lng);
		z = cos(lng);
	}

	// --------------------------------------------------------------------------
	// Vector3::isZero
	//
	// Return true if is zero vector.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline bool
	Vector3<Real>::isZero ()
	{
	  return (x == 0.0) && (y == 0.0) && (z == 0.0);
	}


	// --------------------------------------------------------------------------
	// Vector3::normalize
	//
	// Set vector length to 1.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Vector3<Real>::normalize()
	{
	  Real magSq = (x * x) + (y * y) + (z * z);

	  if (magSq > 0.0)
	    {
	      // check for divide-by-zero
	      Real oneOverMag = 1.0 / std::sqrt (magSq);
	      x *= oneOverMag;
	      y *= oneOverMag;
	      z *= oneOverMag;
	    }
	}

	template <typename Real>
	inline Real
	Vector3<Real>::length()
	{
		return (Real)std::sqrt( (x*x)+(y*y)+(z*z));
	}

	/**
	 * Situa el vector en el vertice más alejado
	 * de la hipotenusa de un triangulo rectangulo
	 * con catetos x = cos(degrees) y z = sin (degrees)
	 *
	 *		  Eje Z				 * (vector resultado)
	 *			^			    /|
	 *			|	          /  |
	 *			|	  		/	 |
	 *			|	      /		 |
	 *			|	    /		 |	sin(degrees)
	 *			|     /			 |
	 *			|   /			 |
	 *			| /	] degrees 	 |
	 * (origen) *----------------|-----> Eje X
	 *				cos(degrees)
	 */

	template <typename Real>
	inline void
	Vector3<Real>::rotate(float degrees, float distance)
	{
		float rads = degToRad(degrees);
		x += std::cos(rads) * distance;
		z -= std::sin(rads) * distance;
	}

	// --------------------------------------------------------------------------
	// Vector3 operators
	//
	// Operator overloading for basic vector operations.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline bool
	Vector3<Real>::operator== (const Vector3<Real> &v) const
	{
	  return ((x == v.x) && (y == v.y) && (z == v.z));
	}

	template <typename Real>
	inline bool
	Vector3<Real>::operator!= (const Vector3<Real> &v) const
	{
	  return ((x != v.x) || (y != v.y) || (z != v.z));
	}

	template <typename Real>
	inline Vector3<Real>
	Vector3<Real>::operator- () const
	{
	  return Vector3<Real> (-x, -y, -z);
	}

	template <typename Real>
	inline Vector3<Real>
	Vector3<Real>::operator+ (const Vector3<Real> &v) const
	{
	  return Vector3<Real> (x + v.x, y + v.y, z + v.z);
	}

	template <typename Real>
	inline Vector3<Real>
	Vector3<Real>::operator- (const Vector3<Real> &v) const
	{
	  return Vector3<Real> (x - v.x, y - v.y, z - v.z);
	}

	template <typename Real>
	inline Vector3<Real>
	Vector3<Real>::operator* (Real s) const
	{
	  return Vector3<Real> (x * s, y * s, z * s);
	}

	template <typename Real>
	inline Vector3<Real>
	Vector3<Real>::operator/ (Real s) const
	{
	  Real oneOverS = 1.0 / s; // Note: no check for divide by zero
	  return Vector3<Real> (x * oneOverS, y * oneOverS, z * oneOverS);
	}

	template <typename Real>
	inline Vector3<Real> &
	Vector3<Real>::operator+= (const Vector3<Real> &v)
	{
	  x += v.x; y += v.y; z += v.z;
	  return *this;
	}

	template <typename Real>
	inline Vector3<Real> &
	Vector3<Real>::operator-= (const Vector3<Real> &v)
	{
	  x -= v.x; y -= v.y; z -= v.z;
	  return *this;
	}

	template <typename Real>
	inline Vector3<Real> &
	Vector3<Real>::operator*= (Real s)
	{
	  x *= s; y *= s; z *= s;
	  return *this;
	}

	template <typename Real>
	inline Vector3<Real> &
	Vector3<Real>::operator/= (Real s)
	{
	  Real oneOverS = 1.0 / s; // Note: no check for divide by zero!
	  x *= oneOverS; y *= oneOverS ; z *= oneOverS;
	  return *this;
	}


	// --------------------------------------------------------------------------
	//
	// Nonmember Vector3<Real> functions
	//
	// --------------------------------------------------------------------------

	// Scalar on the left multiplication, for symmetry
	template <typename Real>
	inline Vector3<Real>
	operator* (Real k, Vector3<Real> v)
	{
	  return Vector3<Real> (k * v.x, k * v.y, k * v.z);
	}

	// Compute vector lenght
	template <typename Real>
	inline Real
	VectorMag (const Vector3<Real> &v)
	{
	  return std::sqrt ((v.x * v.x) +  (v.y * v.y) +  (v.z * v.z));
	}

	// Vector3 dot product
	template <typename Real>
	inline Real
	DotProduct (const Vector3<Real> &a, const Vector3<Real> &b)
	{
	  return ((a.x * b.x) +  (a.y * b.y) +  (a.z * b.z));
	}

	// Vector3 cross product
	template <typename Real>
	inline Vector3<Real>
	CrossProduct (const Vector3<Real> &a, const Vector3<Real> &b)
	{
	  return Vector3<Real> (
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
	   );
	}

	// Compute normal plane given three points
	template <typename Real>
	inline Vector3<Real>
	ComputeNormal (const Vector3<Real> &p1, const Vector3<Real> &p2, const Vector3<Real> &p3)
	{
	  Vector3<Real> vec1 (p1 - p2);
	  Vector3<Real> vec2 (p1 - p3);

	  Vector3<Real> result (CrossProduct (vec1, vec2));
	  result.normalize ();

	  return result;
	}

	// Compute distance between two points
	template <typename Real>
	inline Real
	Distance (const Vector3<Real> &a, const Vector3<Real> &b)
	{
	  Real dx = a.x - b.x;
	  Real dy = a.y - b.y;
	  Real dz = a.z - b.z;
	  return std::sqrt ((dx * dx) + (dy * dy) + (dz * dz));
	}

	// Compute squared distance between two points.
	// Useful when comparing distances, since we don't need
	// to square the result.
	template <typename Real>
	inline Real
	DistanceSquared (const Vector3<Real> &a, const Vector3<Real> &b)
	{
	  Real dx = a.x - b.x;
	  Real dy = a.y - b.y;
	  Real dz = a.z - b.z;
	  return ((dx * dx) + (dy * dy) + (dz * dz));
	}

	/**
	 * Interpolacion lineal de vectores en funcion de un parametro
	 * porcentual t.
	 * Siendo t el porcentaje de interpolacion entre un vector y el otro.
	 * Si t = 0, no hay interpolacion, si t = 1 la interpolacion seria
	 * el vector final
	 */
	 template <typename Real>
	 inline Vector3<Real>
	 Lerp(const Vector3<Real>& a, const Vector3<Real>& b, const Real t)
	 {
	 	return (a + t*(b - a));
	 }

	 /**
	  * Devuelve el vector unidad que apunta en la
	  * orientacion pasada como argumento, en el
	  * plano X,Y
	  */
	 template <typename Real>
	 inline Vector3<Real>
	 UnitVectorFromOrientation(float degrees)
	 {
	 	return Vector3<Real>(
	 		std::sin(degToRad(degrees)),
	 		-cos(degToRad(degrees)),
	 		0);
	 }

	/////////////////////////////////////////////////////////////////////////////
	//
	// class Matrix4x4<Real> implementation.
	//
	// --------------------------------------------------------------------------
	//
	// MATRIX ORGANIZATION
	//
	// The purpose of this class is so that a user might perform transformations
	// without fiddling with plus or minus signs or transposing the matrix
	// until the output "looks right".  But of course, the specifics of the
	// internal representation is important.  Not only for the implementation
	// in this file to be correct, but occasionally direct access to the
	// matrix variables is necessary, or beneficial for optimization.  Thus,
	// we document our matrix conventions here.
	//
	// Strict adherance to linear algebra rules dictates that the
	// multiplication of a 4x4 matrix by a 3D vector is actually undefined.
	// To circumvent this, we can consider the input and output vectors as
	// having an assumed fourth coordinate of 1.  Also, since the rightmost
	// column is [ 0 0 0 1 ], we can simplificate calculations ignoring
	// this last column. This is shown below:
	//
	//         | m11 m12 m13 0 | | x |   | x'|
	//         | m21 m22 m23 0 | | y | = | y'|
	//         | m31 m32 m33 0 | | z |   | z'|
	//         | tx  ty  tz  1 | | 1 |   | 1 |
	//
	// We use row vectors to represent the right, up and forward vectors
	// in the 4x4 matrix.  OpenGL uses column vectors, but the elements of
	// an OpenGL matrix are ordered in columns so that m[i][j] is in row j
	// and column i.  This is the reverse of the standard C convention in
	// which m[i][j] is in row i and column j.  The matrix should be
	// transposed before being sent to OpenGL.
	//
	//   | m11 m21 m31 tx |    |  m0  m4  m8 m12 |    |  m0  m1  m2  m3 |
	//   | m12 m22 m32 ty |    |  m1  m5  m9 m13 |    |  m4  m5  m6  m7 |
	//   | m13 m23 m33 tz |    |  m2  m6 m10 m14 |    |  m8  m9 m10 m11 |
	//   |  0   0   0  tw |    |  m3  m7 m11 m15 |    | m12 m13 m14 m15 |
	//
	//      OpenGL style          OpenGL matrix            standard C
	//                             arrangement             convention
	//
	// Fortunately, accessing to the raw matrix data via the m[] array gives
	// us the transpose matrix; i.e. in OpenGL form, so that we can directly use
	// it with glLoadMatrix{fd}() or glMultMatrix{fd}().
	//
	// Also, since the rightmost column (in standard C form) should always
	// be [ 0 0 0 1 ], and sice these values (h14, h24, h34 and tw) are
	// initialized in constructors, we don't need to modify them in our
	// matrix operations, so we don't perform useless calculations...
	//
	// The right-hand rule is used to define "positive" rotation.
	//
	//               +y                          +x'
	//                |                           |
	//                |                           |
	//                | +x        +y' |
	//               /                            /
	//              /                            /
	//             +z                          +z'
	//
	//          initial position      Positive rotation of
	//                                 pi/2 around z-axis
	//
	/////////////////////////////////////////////////////////////////////////////


	// --------------------------------------------------------------------------
	// Matrix4x4::identity
	//
	// Set matrix to identity.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::identity ()
	{
	  m11 = 1.0; m21 = 0.0; m31 = 0.0; tx = 0.0;
	  m12 = 0.0; m22 = 1.0; m32 = 0.0; ty = 0.0;
	  m13 = 0.0; m23 = 0.0; m33 = 1.0; tz = 0.0;
	  h14 = 0.0; h24 = 0.0; h34 = 0.0; tw = 1.0;
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::transpose
	//
	// Transpose the current matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::transpose ()
	{
	  *this = Transpose (*this);
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::invert
	//
	// Invert the current matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::invert ()
	{
	  *this = Invert (*this);
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::setTranslation
	//
	// Set the translation portion of the matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::setTranslation (const Vector3<Real> &v)
	{
	  tx = v.x; ty = v.y; tz = v.z;
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::transform
	//
	// Transform a point by the matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::transform (Vector3<Real> &v) const
	{
	  // Grind through the linear algebra.
	  v = Vector3<Real> (
		(v.x * m11) + (v.y * m21) + (v.z * m31) + tx,
		(v.x * m12) + (v.y * m22) + (v.z * m32) + ty,
		(v.x * m13) + (v.y * m23) + (v.z * m33) + tz
	   );
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::rotate
	//
	// Rotate a point by the 3x3 upper left portion of the matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::rotate (Vector3<Real> &v) const
	{
	  v = Vector3<Real> (
		(v.x * m11) + (v.y * m21) + (v.z * m31),
		(v.x * m12) + (v.y * m22) + (v.z * m32),
		(v.x * m13) + (v.y * m23) + (v.z * m33)
	   );
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::inverseRotate
	//
	// Rotate a point by the inverse 3x3 upper left portion of the matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::inverseRotate (Vector3<Real> &v) const
	{
	  v = Vector3<Real> (
		(v.x * m11) + (v.y * m12) + (v.z * m13),
		(v.x * m21) + (v.y * m22) + (v.z * m23),
		(v.x * m31) + (v.y * m32) + (v.z * m33)
	   );
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::inverseRotate
	//
	// Translate a point by the inverse matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::inverseTranslate (Vector3<Real> &v) const
	{
	  v.x -= tx;
	  v.y -= ty;
	  v.z -= tz;
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::fromQuaternion
	//
	// Convert a quaternion to a matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::fromQuaternion (const Quaternion<Real> &q)
	{
	  // Compute a few values to optimize common subexpressions
	  Real ww = 2.0 * q.w;
	  Real xx = 2.0 * q.x;
	  Real yy = 2.0 * q.y;
	  Real zz = 2.0 * q.z;

	  // Set the matrix elements.  There is still a little more
	  // opportunity for optimization due to the many common
	  // subexpressions.  We'll let the compiler handle that...
	  m11 = 1.0 - (yy * q.y) - (zz * q.z);
	  m12 = (xx * q.y) + (ww * q.z);
	  m13 = (xx * q.z) - (ww * q.y);

	  m21 = (xx * q.y) - (ww * q.z);
	  m22 = 1.0 - (xx * q.x) - (zz * q.z);
	  m23 = (yy * q.z) + (ww * q.x);

	  m31 = (xx * q.z) + (ww * q.y);
	  m32 = (yy * q.z) - (ww * q.x);
	  m33 = 1.0 - (xx * q.x) - (yy * q.y);

	  // Reset the translation portion
	  tx = ty = tz = 0.0;
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::fromEulerAngles
	//
	// Setup a rotation matrix, given three X-Y-Z rotation angles. The
	// rotations are performed first on x-axis, then y-axis and finaly z-axis.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::fromEulerAngles (Real x, Real y, Real z)
	{
	  // Fetch sine and cosine of angles
	  Real cx = std::cos (x);
	  Real sx = std::sin (x);
	  Real cy = std::cos (y);
	  Real sy = std::sin (y);
	  Real cz = std::cos (z);
	  Real sz = std::sin (z);

	  Real sxsy = sx * sy;
	  Real cxsy = cx * sy;

	  // Fill in the matrix elements
	  m11 =  (cy * cz);
	  m12 =  (sxsy * cz) + (cx * sz);
	  m13 = -(cxsy * cz) + (sx * sz);

	  m21 = -(cy * sz);
	  m22 = -(sxsy * sz) + (cx * cz);
	  m23 =  (cxsy * sz) + (sx * cz);

	  m31 =  (sy);
	  m32 = -(sx * cy);
	  m33 =  (cx * cy);

	  // Reset the translation portion
	  tx = ty = tz = 0.0;
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::toEulerAngles
	//
	// Setup the euler angles in radians, given a rotation matrix. The rotation
	// matrix could have been obtained from euler angles given the expression:
	//   M = X.Y.Z
	// where X, Y and Z are rotation matrices about X, Y and Z axes.
	// This is the "opposite" of the fromEulerAngles function.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Matrix4x4<Real>::toEulerAngles (Real &x, Real &y, Real &z) const
	{
	  // Compute Y-axis angle
	  y = std::asin (m31);

	  // Compute cos and one over cos for optimization
	  Real cy = std::cos (y);
	  Real oneOverCosY = 1.0 / cy;

	  if (std::fabs (cy) > 0.001)
	    {
	      // No gimball lock
	      x = std::atan2 (-m32 * oneOverCosY, m33 * oneOverCosY);
	      z = std::atan2 (-m21 * oneOverCosY, m11 * oneOverCosY);
	    }
	  else
	    {
	      // Gimbal lock case
	      x = 0.0;
	      z = std::atan2 (m12, m22);
	    }
	}


	// --------------------------------------------------------------------------
	// Matrix4x4::rightVector
	// Matrix4x4::upVector
	// Matrix4x4::forwardVector
	// Matrix4x4::translationVector
	//
	// Return a base vector from the matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Vector3<Real>
	Matrix4x4<Real>::rightVector () const
	{
	  return Vector3<Real> (m11, m12, m13);
	}

	template <typename Real>
	inline Vector3<Real>
	Matrix4x4<Real>::upVector () const
	{
	  return Vector3<Real> (m21, m22, m23);
	}

	template <typename Real>
	inline Vector3<Real>
	Matrix4x4<Real>::forwardVector () const
	{
	  return Vector3<Real> (m31, m32, m33);
	}

	template <typename Real>
	inline Vector3<Real>
	Matrix4x4<Real>::translationVector () const
	{
	  return Vector3<Real> (tx, ty, tz);
	}


	// --------------------------------------------------------------------------
	//
	// Nonmember Matrix4x4<Real> functions
	//
	// --------------------------------------------------------------------------


	// --------------------------------------------------------------------------
	// Matrix4x4 * Matrix4x4
	//
	// Matrix concatenation.
	//
	// We also provide a *= operator, as per C convention.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	operator* (const Matrix4x4<Real> &a, const Matrix4x4<Real> &b)
	{
	  Matrix4x4<Real> res;

	  // Compute the left 4x3 (linear transformation) portion
	  res.m11 = (a.m11 * b.m11) + (a.m21 * b.m12) + (a.m31 * b.m13);
	  res.m12 = (a.m12 * b.m11) + (a.m22 * b.m12) + (a.m32 * b.m13);
	  res.m13 = (a.m13 * b.m11) + (a.m23 * b.m12) + (a.m33 * b.m13);

	  res.m21 = (a.m11 * b.m21) + (a.m21 * b.m22) + (a.m31 * b.m23);
	  res.m22 = (a.m12 * b.m21) + (a.m22 * b.m22) + (a.m32 * b.m23);
	  res.m23 = (a.m13 * b.m21) + (a.m23 * b.m22) + (a.m33 * b.m23);

	  res.m31 = (a.m11 * b.m31) + (a.m21 * b.m32) + (a.m31 * b.m33);
	  res.m32 = (a.m12 * b.m31) + (a.m22 * b.m32) + (a.m32 * b.m33);
	  res.m33 = (a.m13 * b.m31) + (a.m23 * b.m32) + (a.m33 * b.m33);

	  // Compute the translation portion
	  res.tx = (a.m11 * b.tx) + (a.m21 * b.ty) + (a.m31 * b.tz) + a.tx;
	  res.ty = (a.m12 * b.tx) + (a.m22 * b.ty) + (a.m32 * b.tz) + a.ty;
	  res.tz = (a.m13 * b.tx) + (a.m23 * b.ty) + (a.m33 * b.tz) + a.tz;

	  return res;
	}

	template <typename Real>
	inline Matrix4x4<Real> &
	operator*= (Matrix4x4<Real> &a, const Matrix4x4<Real> &b)
	{
	  a = a * b;
	  return a;
	}


	// --------------------------------------------------------------------------
	// Matrix4x4 * Vector3
	//
	// Transform a point by a matrix.  This makes using the vector class look
	// like it does with linear algebra notation on paper.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Vector3<Real>
	operator* (const Matrix4x4<Real> &m, const Vector3<Real> &p)
	{
	  Vector3<Real> res (p);
	  m.transform (res);
	  return res;
	}


	// --------------------------------------------------------------------------
	// Transpose
	//
	// Return the transpose matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	Transpose (const Matrix4x4<Real> &m)
	{
	  Matrix4x4<Real> res;

	  res.m11 = m.m11; res.m21 = m.m12; res.m31 = m.m13; res.tx = m.h14;
	  res.m12 = m.m21; res.m22 = m.m22; res.m32 = m.m23; res.ty = m.h24;
	  res.m13 = m.m31; res.m23 = m.m32; res.m33 = m.m33; res.tz = m.h34;
	  res.h14 = m.tx;  res.h24 = m.ty;  res.h34 = m.tz;  res.tw = m.tw;

	  return res;
	}


	// --------------------------------------------------------------------------
	// Determinant
	//
	// Compute the determinant of the 3x3 portion of the matrix.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline static Real
	Determinant3x3 (const Matrix4x4<Real> &m)
	{
	  return m.m11 * ((m.m22 * m.m33) - (m.m23 * m.m32))
	    + m.m12 * ((m.m23 * m.m31) - (m.m21 * m.m33))
	    + m.m13 * ((m.m21 * m.m32) - (m.m22 * m.m31));
	}


	// --------------------------------------------------------------------------
	// Invert
	//
	// Compute the inverse of a matrix.  We use the classical adjoint divided
	// by the determinant method.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	Invert (const Matrix4x4<Real> &m)
	{
	  // Compute the determinant of the 3x3 portion
	  Real det = Determinant3x3 (m);

	  // If we're singular, then the determinant is zero and there's
	  // no inverse
	  assert (std::fabs (det) > 0.000001);

	  // Compute one over the determinant, so we divide once and
	  // can *multiply* per element
	  Real oneOverDet = 1.0 / det;

	  // Compute the 3x3 portion of the inverse, by
	  // dividing the adjoint by the determinant
	  Matrix4x4<Real> res;

	  res.m11 = ((m.m22 * m.m33) - (m.m23 * m.m32)) * oneOverDet;
	  res.m12 = ((m.m13 * m.m32) - (m.m12 * m.m33)) * oneOverDet;
	  res.m13 = ((m.m12 * m.m23) - (m.m13 * m.m22)) * oneOverDet;

	  res.m21 = ((m.m23 * m.m31) - (m.m21 * m.m33)) * oneOverDet;
	  res.m22 = ((m.m11 * m.m33) - (m.m13 * m.m31)) * oneOverDet;
	  res.m23 = ((m.m13 * m.m21) - (m.m11 * m.m23)) * oneOverDet;

	  res.m31 = ((m.m21 * m.m32) - (m.m22 * m.m31)) * oneOverDet;
	  res.m32 = ((m.m12 * m.m31) - (m.m11 * m.m32)) * oneOverDet;
	  res.m33 = ((m.m11 * m.m22) - (m.m12 * m.m21)) * oneOverDet;

	  // Compute the translation portion of the inverse
	  res.tx = -((m.tx * res.m11) + (m.ty * res.m21) + (m.tz * res.m31));
	  res.ty = -((m.tx * res.m12) + (m.ty * res.m22) + (m.tz * res.m32));
	  res.tz = -((m.tx * res.m13) + (m.ty * res.m23) + (m.tz * res.m33));

	  // Return it.
	  return res;
	}


	// --------------------------------------------------------------------------
	// RotationMatrix
	//
	// Setup the matrix to perform a rotation about one of the three cardinal
	// X-Y-Z axes.
	//
	// The axis of rotation is specified by the 1-based "axis" index.
	//
	// theta is the amount of rotation, in radians.  The right-hand rule is
	// used to define "positive" rotation.
	//
	// The translation portion is reset.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	RotationMatrix (Axis axis, Real theta)
	{
	  Matrix4x4<Real> res;

	  // Get sin and cosine of rotation angle
	  Real s = std::sin (theta);
	  Real c = std::cos (theta);

	  // Check which axis they are rotating about
	  switch (axis)
	    {
	    case kXaxis: // Rotate about the x-axis
	      res.m11 = 1.0; res.m21 = 0.0; res.m31 = 0.0;
	      res.m12 = 0.0; res.m22 = c;   res.m32 = -s;
	      res.m13 = 0.0; res.m23 = s;   res.m33 =  c;
	      break;

	    case kYaxis: // Rotate about the y-axis
	      res.m11 = c;   res.m21 = 0.0; res.m31 = s;
	      res.m12 = 0.0; res.m22 = 1.0; res.m32 = 0.0;
	      res.m13 = -s;  res.m23 = 0.0; res.m33 = c;
	      break;

	    case kZaxis: // Rotate about the z-axis
	      res.m11 = c;   res.m21 = -s;  res.m31 = 0.0;
	      res.m12 = s;   res.m22 =  c;  res.m32 = 0.0;
	      res.m13 = 0.0; res.m23 = 0.0; res.m33 = 1.0;
	      break;

	    default:
	      // bogus axis index
	      assert (false);
	    }

	  // Reset the translation portion
	  res.tx = res.ty = res.tz = 0.0;

	  return res;
	}


	//---------------------------------------------------------------------------
	// AxisRotationMatrix
	//
	// Setup the matrix to perform a rotation about an arbitrary axis.
	// The axis of rotation must pass through the origin.
	//
	// axis defines the axis of rotation, and must be a unit vector.
	//
	// theta is the amount of rotation, in radians.  The right-hand rule is
	// used to define "positive" rotation.
	//
	// The translation portion is reset.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	RotationMatrix (const Vector3<Real> &axis, Real theta)
	{
	  Matrix4x4<Real> res;

	  // Quick sanity check to make sure they passed in a unit vector
	  // to specify the axis
	  assert (std::fabs (DotProduct (axis, axis) - 1.0) < 0.001);

	  // Get sin and cosine of rotation angle
	  Real s = std::sin (theta);
	  Real c = std::cos (theta);

	  // Compute 1 - cos(theta) and some common subexpressions
	  Real a = 1.0 - c;
	  Real ax = a * axis.x;
	  Real ay = a * axis.y;
	  Real az = a * axis.z;

	  // Set the matrix elements.  There is still a little more
	  // opportunity for optimization due to the many common
	  // subexpressions.  We'll let the compiler handle that...
	  res.m11 = (ax * axis.x) + c;
	  res.m12 = (ax * axis.y) + (axis.z * s);
	  res.m13 = (ax * axis.z) - (axis.y * s);

	  res.m21 = (ay * axis.x) - (axis.z * s);
	  res.m22 = (ay * axis.y) + c;
	  res.m23 = (ay * axis.z) + (axis.x * s);

	  res.m31 = (az * axis.x) + (axis.y * s);
	  res.m32 = (az * axis.y) - (axis.x * s);
	  res.m33 = (az * axis.z) + c;

	  // Reset the translation portion
	  res.tx = res.ty = res.tz = 0.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// TranslationMatrix
	//
	// Build a translation matrix given a translation vector.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	TranslationMatrix (Real x, Real y, Real z)
	{
	  return TranslationMatrix (Vector3<Real> (x, y, z));
	}

	template <typename Real>
	inline Matrix4x4<Real>
	TranslationMatrix (const Vector3<Real> &v)
	{
	  Matrix4x4<Real> res;

	  res.m11 = 1.0; res.m21 = 0.0; res.m31 = 0.0; res.tx = v.x;
	  res.m12 = 0.0; res.m22 = 1.0; res.m32 = 0.0; res.ty = v.y;
	  res.m13 = 0.0; res.m23 = 0.0; res.m33 = 1.0; res.tz = v.z;

	  return res;
	}


	// --------------------------------------------------------------------------
	// ScaleMatrix
	//
	// Setup the matrix to perform scale on each axis.  For uniform scale by k,
	// use a vector of the form Vector3( k, k, k ).
	//
	// The translation portion is reset.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	ScaleMatrix (const Vector3<Real> &s)
	{
	  Matrix4x4<Real> res;

	  // Set the matrix elements.  Pretty straightforward
	  res.m11 = s.x; res.m21 = 0.0;  res.m31 = 0.0;
	  res.m12 = 0.0;  res.m22 = s.y; res.m32 = 0.0;
	  res.m13 = 0.0;  res.m23 = 0.0;  res.m33 = s.z;

	  // Reset the translation portion
	  res.tx = res.ty = res.tz = 0.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// ScaleAlongAxisMatrix
	//
	// Setup the matrix to perform scale along an arbitrary axis.
	//
	// The axis is specified using a unit vector.
	//
	// The translation portion is reset.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	ScaleAlongAxisMatrix (const Vector3<Real> &axis, Real k)
	{
	  Matrix4x4<Real> res;

	  // Quick sanity check to make sure they passed in a unit vector
	  // to specify the axis
	  assert (std::fabs (DotProduct (axis, axis) - 1.0) < 0.001);

	  // Compute k-1 and some common subexpressions
	  Real a = k - 1.0;
	  Real ax = a * axis.x;
	  Real ay = a * axis.y;
	  Real az = a * axis.z;

	  // Fill in the matrix elements.  We'll do the common
	  // subexpression optimization ourselves here, since diagonally
	  // opposite matrix elements are equal
	  res.m11 = (ax * axis.x) + 1.0;
	  res.m22 = (ay * axis.y) + 1.0;
	  res.m32 = (az * axis.z) + 1.0;

	  res.m12 = res.m21 = (ax * axis.y);
	  res.m13 = res.m31 = (ax * axis.z);
	  res.m23 = res.m32 = (ay * axis.z);

	  // Reset the translation portion
	  res.tx = res.ty = res.tz = 0.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// ShearMatrix
	//
	// Setup the matrix to perform a shear
	//
	// The type of shear is specified by the 1-based "axis" index.  The effect
	// of transforming a point by the matrix is described by the pseudocode
	// below:
	//
	//	xAxis  =>  y += s * x, z += t * x
	//	yAxis  =>  x += s * y, z += t * y
	//	zAxis  =>  x += s * z, y += t * z
	//
	// The translation portion is reset.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	ShearMatrix (Axis axis, Real s, Real t)
	{
	  Matrix4x4<Real> res;

	  // Check which type of shear they want
	  switch (axis)
	    {
	    case kXaxis: // Shear y and z using x
	      res.m11 = 1.0; res.m21 = 0.0; res.m31 = 0.0;
	      res.m12 = s;   res.m22 = 1.0; res.m32 = 0.0;
	      res.m13 = t;   res.m23 = 0.0; res.m33 = 1.0;
	      break;

	    case kYaxis: // Shear x and z using y
	      res.m11 = 1.0; res.m21 = s;   res.m31 = 0.0;
	      res.m12 = 0.0; res.m22 = 1.0; res.m32 = 0.0;
	      res.m13 = 0.0; res.m23 = t;   res.m33 = 1.0;
	      break;

	    case kZaxis: // Shear x and y using z
	      res.m11 = 1.0; res.m21 = 0.0; res.m31 = s;
	      res.m12 = 0.0; res.m22 = 1.0; res.m32 = t;
	      res.m13 = 0.0; res.m23 = 0.0; res.m33 = 1.0;
	      break;

	    default:
	      // bogus axis index
	      assert (false);
	    }

	  // Reset the translation portion
	  res.tx = res.ty = res.tz = 0.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// ProjectionMatrix
	//
	// Setup the matrix to perform a projection onto a plane passing
	// through the origin.  The plane is perpendicular to the
	// unit vector n.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	ProjectionMatrix (const Vector3<Real> &n)
	{
	  Matrix4x4<Real> res;

	  // Quick sanity check to make sure they passed in a unit vector
	  // to specify the axis
	  assert (std::fabs (DotProduct (n, n) - 1.0) < 0.001);

	  // Fill in the matrix elements.  We'll do the common
	  // subexpression optimization ourselves here, since diagonally
	  // opposite matrix elements are equal
	  res.m11 = 1.0 - (n.x * n.x);
	  res.m22 = 1.0 - (n.y * n.y);
	  res.m33 = 1.0 - (n.z * n.z);

	  res.m12 = res.m21 = -(n.x * n.y);
	  res.m13 = res.m31 = -(n.x * n.z);
	  res.m23 = res.m32 = -(n.y * n.z);

	  // Reset the translation portion
	  res.tx = res.ty = res.tz = 0.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// ReflectionMatrix
	//
	// Setup the matrix to perform a reflection about a plane parallel
	// to a cardinal plane.
	//
	// axis is a 1-based index which specifies the plane to project about:
	//
	//	xAxis => reflect about the plane x=k
	//	yAxis => reflect about the plane y=k
	//	zAxis => reflect about the plane z=k
	//
	// The translation is set appropriately, since translation must occur if
	// k != 0
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	ReflectionMatrix (Axis axis, Real k)
	{
	  Matrix4x4<Real> res;

	  // Check which plane they want to reflect about
	  switch (axis)
	    {
	    case kXaxis: // Reflect about the plane x=k
	      res.m11 = -1.0; res.m21 =  0.0; res.m31 =  0.0; res.tx = 2.0 * k;
	      res.m12 =  0.0; res.m22 =  1.0; res.m32 =  0.0; res.ty = 0.0;
	      res.m13 =  0.0; res.m23 =  0.0; res.m33 =  1.0; res.tz = 0.0;
	      break;

	    case kYaxis: // Reflect about the plane y=k
	      res.m11 =  1.0; res.m21 =  0.0; res.m31 =  0.0; res.tx = 0.0;
	      res.m12 =  0.0; res.m22 = -1.0; res.m32 =  0.0; res.ty = 2.0 * k;
	      res.m13 =  0.0; res.m23 =  0.0; res.m33 =  1.0; res.tz = 0.0;
	      break;

	    case kZaxis: // Reflect about the plane z=k
	      res.m11 =  1.0; res.m21 =  0.0; res.m31 =  0.0; res.tx = 0.0;
	      res.m12 =  0.0; res.m22 =  1.0; res.m32 =  0.0; res.ty = 0.0;
	      res.m13 =  0.0; res.m23 =  0.0; res.m33 = -1.0; res.tz = 2.0 * k;
	      break;

	    default:
	      // bogus axis index
	      assert (false);
	    }

	  return res;
	}


	// --------------------------------------------------------------------------
	// AxisReflectionMatrix
	//
	// Setup the matrix to perform a reflection about an arbitrary plane
	// through the origin.  The unit vector n is perpendicular to the plane.
	//
	// The translation portion is reset.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	AxisReflectionMatrix (const Vector3<Real> &n)
	{
	  Matrix4x4<Real> res;

	  // Quick sanity check to make sure they passed in a unit vector
	  // to specify the axis
	  assert (std::fabs (DotProduct (n, n) - 1.0) < 0.001);

	  // Compute common subexpressions
	  Real ax = -2.0 * n.x;
	  Real ay = -2.0 * n.y;
	  Real az = -2.0 * n.z;

	  // Fill in the matrix elements.  We'll do the common
	  // subexpression optimization ourselves here, since diagonally
	  // opposite matrix elements are equal
	  res.m11 = 1.0 + (ax * n.x);
	  res.m22 = 1.0 + (ay * n.y);
	  res.m32 = 1.0 + (az * n.z);

	  res.m12 = res.m21 = (ax * n.y);
	  res.m13 = res.m31 = (ax * n.z);
	  res.m23 = res.m32 = (ay * n.z);

	  // Reset the translation portion
	  res.tx = res.ty = res.tz = 0.00;

	  return res;
	}


	// --------------------------------------------------------------------------
	// LookAtMatrix
	//
	// Setup the matrix to perform a "Look At" transformation like a first
	// person camera.
	// --------------------------------------------------------------------------
	template <typename Real>
	inline Matrix4x4<Real>
	LookAtMatrix (const Vector3<Real> &camPos, const Vector3<Real> &target,
		      const Vector3<Real> &camUp)
	{
	  Matrix4x4<Real> rot, trans;

	  Vector3<Real> forward (camPos - target);
	  forward.normalize ();

	  Vector3<Real> right (CrossProduct (camUp, forward));
	  Vector3<Real> up (CrossProduct (forward, right));

	  right.normalize ();
	  up.normalize ();

	  rot.m11 = right.x;
	  rot.m21 = right.y;
	  rot.m31 = right.z;

	  rot.m12 = up.x;
	  rot.m22 = up.y;
	  rot.m32 = up.z;

	  rot.m13 = forward.x;
	  rot.m23 = forward.y;
	  rot.m33 = forward.z;

	  rot.tx  = 0.0;
	  rot.ty  = 0.0;
	  rot.tz  = 0.0;

	  trans = TranslationMatrix (-camPos);

	  return (rot * trans);
	}


	// --------------------------------------------------------------------------
	// FrustumMatrix
	//
	// Setup a frustum matrix given the left, right, bottom, top, near, and far
	// values for the frustum boundaries.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	FrustumMatrix (Real l, Real r, Real b, Real t, Real n, Real f)
	{
	  assert (n >= 0.0);
	  assert (f >= 0.0);

	  Matrix4x4<Real> res;

	  Real width  = r - l;
	  Real height = t - b;
	  Real depth  = f - n;

	  res.m[0] = (2 * n) / width;
	  res.m[1] = 0.0;
	  res.m[2] = 0.0;
	  res.m[3] = 0.0;

	  res.m[4] = 0.0;
	  res.m[5] = (2 * n) / height;
	  res.m[6] = 0.0;
	  res.m[7] = 0.0;

	  res.m[8] = (r + l) / width;
	  res.m[9] = (t + b) / height;
	  res.m[10]= -(f + n) / depth;
	  res.m[11]= -1.0;

	  res.m[12]= 0.0;
	  res.m[13]= 0.0;
	  res.m[14]= -(2 * f * n) / depth;
	  res.m[15]= 0.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// PerspectiveMatrix
	//
	// Setup a perspective matrix given the field-of-view in the Y direction
	// in degrees, the aspect ratio of Y/X, and near and far plane distances.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	PerspectiveMatrix (Real fovY, Real aspect, Real n, Real f)
	{
	  Matrix4x4<Real> res;

	  Real angle;
	  Real cot;

	  angle = fovY / 2.0;
	  angle = degToRad (angle);

	  cot = std::cos (angle) / std::sin (angle);

	  res.m[0] = cot / aspect;
	  res.m[1] = 0.0;
	  res.m[2] = 0.0;
	  res.m[3] = 0.0;

	  res.m[4] = 0.0;
	  res.m[5] = cot;
	  res.m[6] = 0.0;
	  res.m[7] = 0.0;

	  res.m[8] = 0.0;
	  res.m[9] = 0.0;
	  res.m[10]= -(f + n) / (f - n);
	  res.m[11]= -1.0;

	  res.m[12]= 0.0;
	  res.m[13]= 0.0;
	  res.m[14]= -(2 * f * n) / (f - n);
	  res.m[15]= 0.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// OrthoMatrix
	//
	// Setup an orthographic Matrix4x4 given the left, right, bottom, top, near,
	// and far values for the frustum boundaries.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	OrthoMatrix (Real l, Real r, Real b, Real t, Real n, Real f)
	{
	  Matrix4x4<Real> res;

	  Real width  = r - l;
	  Real height = t - b;
	  Real depth  = f - n;

	  res.m[0] =  2.0 / width;
	  res.m[1] =  0.0;
	  res.m[2] =  0.0;
	  res.m[3] =  0.0;

	  res.m[4] =  0.0;
	  res.m[5] =  2.0 / height;
	  res.m[6] =  0.0;
	  res.m[7] =  0.0;

	  res.m[8] =  0.0;
	  res.m[9] =  0.0;
	  res.m[10]= -2.0 / depth;
	  res.m[11]=  0.0;

	  res.m[12]= -(r + l) / width;
	  res.m[13]= -(t + b) / height;
	  res.m[14]= -(f + n) / depth;
	  res.m[15]=  1.0;

	  return res;
	}


	// --------------------------------------------------------------------------
	// OrthoNormalMatrix
	//
	// Setup an orientation matrix using 3 basis normalized vectors.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Matrix4x4<Real>
	OrthoNormalMatrix (const Vector3<Real> &xdir, const Vector3<Real> &ydir,
			   const Vector3<Real> &zdir)
	{
	  Matrix4x4<Real> res;

	  res.m[0] = xdir.x; res.m[4] = ydir.x; res.m[8] = zdir.x; res.m[12] = 0.0;
	  res.m[1] = xdir.y; res.m[5] = ydir.y; res.m[9] = zdir.y; res.m[13] = 0.0;
	  res.m[2] = xdir.z; res.m[6] = ydir.z; res.m[10]= zdir.z; res.m[14] = 0.0;
	  res.m[3] = 0.0;    res.m[7] = 0.0;    res.m[11]= 0.0;    res.m[15] = 1.0;

	  return res;
	}


	/////////////////////////////////////////////////////////////////////////////
	//
	// class Quaternion<Real> implementation.
	//
	/////////////////////////////////////////////////////////////////////////////

	// --------------------------------------------------------------------------
	// Quaternion::identity
	//
	// Set to identity
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Quaternion<Real>::identity ()
	{
	  w = 1.0; x = y = z = 0.0;
	}


	// --------------------------------------------------------------------------
	// Quaternion::normalize
	//
	// "Normalize" a quaternion.  Note that normally, quaternions
	// are always normalized (within limits of numerical precision).
	//
	// This function is provided primarily to combat floating point "error
	// creep", which can occur when many successive quaternion operations
	// are applied.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Quaternion<Real>::normalize ()
	{
	  // Compute magnitude of the quaternion
	  Real mag = std::sqrt ((w * w) + (x * x) + (y * y) + (z * z));

	  // Check for bogus length, to protect against divide by zero
	  if (mag > 0.0)
	    {
	      // Normalize it
	      Real oneOverMag = 1.0 / mag;

	      w *= oneOverMag;
	      x *= oneOverMag;
	      y *= oneOverMag;
	      z *= oneOverMag;
	    }
	}


	// --------------------------------------------------------------------------
	// Quaternion<Real>::computeW
	//
	// Compute the W component of a unit quaternion given its x,y,z components.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Quaternion<Real>::computeW ()
	{
	  Real t = 1.0 - (x * x) - (y * y) - (z * z);

	  if (t < 0.0)
	    w = 0.0;
	  else
	    w = -std::sqrt (t);
	}


	// --------------------------------------------------------------------------
	// Quaternion<Real>::rotate
	//
	// Rotate a point by quaternion.  v' = q.p.q*, where p = <0, v>.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Quaternion<Real>::rotate (Vector3<Real> &v) const
	{
	  Quaternion<Real> qf = *this * v * ~(*this);
	  v.x = qf.x;
	  v.y = qf.y;
	  v.z = qf.z;
	}


	// --------------------------------------------------------------------------
	// Quaternion::fromMatrix
	//
	// Setup the quaternion to perform a rotation, given the angular displacement
	// in matrix form.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Quaternion<Real>::fromMatrix (const Matrix4x4<Real> &m)
	{
	  Real trace = m.m11 + m.m22 + m.m33 + 1.0;

	  if (trace > 0.0001)
	    {
	      Real s = 0.5 / std::sqrt (trace);
	      w = 0.25 / s;
	      x = (m.m23 - m.m32) * s;
	      y = (m.m31 - m.m13) * s;
	      z = (m.m12 - m.m21) * s;
	    }
	  else
	    {
	      if ((m.m11 > m.m22) && (m.m11 > m.m33))
		{
		  Real s = 0.5 / std::sqrt (1.0 + m.m11 - m.m22 - m.m33);
		  x = 0.25 / s;
		  y = (m.m21 + m.m12) * s;
		  z = (m.m31 + m.m13) * s;
		  w = (m.m32 - m.m23) * s;
		}
	      else if (m.m22 > m.m33)
		{
		  Real s = 0.5 / std::sqrt (1.0 + m.m22 - m.m11 - m.m33);
		  x = (m.m21 + m.m12) * s;
		  y = 0.25 / s;
		  z = (m.m32 + m.m23) * s;
		  w = (m.m31 - m.m13) * s;
		}
	      else
		{
		  Real s = 0.5 / std::sqrt (1.0 + m.m33 - m.m11 - m.m22);
		  x = (m.m31 + m.m13) * s;
		  y = (m.m32 + m.m23) * s;
		  z = 0.25 / s;
		  w = (m.m21 - m.m12) * s;
		}
	    }
	}


	// --------------------------------------------------------------------------
	// Quaternion::fromEulerAngles
	//
	// Setup the quaternion to perform an object->inertial rotation, given the
	// orientation in XYZ-Euler angles format.  x,y,z parameters must be in
	// radians.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Quaternion<Real>::fromEulerAngles (Real x, Real y, Real z)
	{
	  // Compute sine and cosine of the half angles
	  Real sr = std::sin (x * 0.5);
	  Real cr = std::cos (x * 0.5);
	  Real sp = std::sin (y * 0.5);
	  Real cp = std::cos (y * 0.5);
	  Real sy = std::sin (z * 0.5);
	  Real cy = std::cos (z * 0.5);

	  // Compute values
	  w =  (cy * cp * cr) + (sy * sp * sr);
	  x = -(sy * sp * cr) + (cy * cp * sr);
	  y =  (cy * sp * cr) + (sy * cp * sr);
	  z = -(cy * sp * sr) + (sy * cp * cr);
	}


	// --------------------------------------------------------------------------
	// Quaternion::toEulerAngles
	//
	// Setup the Euler angles, given an object->inertial rotation quaternion.
	// Returned x,y,z are in radians.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Quaternion<Real>::toEulerAngles (Real &x, Real &y, Real &z) const
	{
	  // Compute Y-axis angle
	  y = std::asin (2.0 * ((x * z) + (w * y)));

	  // Compute cos and one over cos for optimization
	  Real cy = std::cos (y);
	  Real oneOverCosY = 1.0 / cy;

	  if (std::fabs (cy) > 0.001)
	    {
	      // No gimball lock
	      x = std::atan2 (2.0 * ((w * x) - (y * z)) * oneOverCosY,
			      (1.0 - 2.0 * (x*x + y*y)) * oneOverCosY);
	      z = std::atan2 (2.0 * ((w * z) - (x * y)) * oneOverCosY,
			      (1.0 - 2.0 * (y*y + z*z)) * oneOverCosY);
	    }
	  else
	    {
	      // Gimbal lock case
	      x = 0.0;
	      z = std::atan2 (2.0 * ((x * y) + (w * z)),
			      1.0 - 2.0 * (x*x + z*z));
	    }
	}


	// --------------------------------------------------------------------------
	// Quaternion::getRotationAngle
	//
	// Return the rotation angle theta (in radians).
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Real
	Quaternion<Real>::rotationAngle () const
	{
	  // Compute the half angle.  Remember that w = cos(theta / 2)
	  Real thetaOver2 = safeAcos (w);

	  // Return the rotation angle
	  return thetaOver2 * 2.0;
	}


	// --------------------------------------------------------------------------
	// Quaternion::getRotationAxis
	//
	// Return the rotation axis.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Vector3<Real>
	Quaternion<Real>::rotationAxis () const
	{
	  // Compute sin^2(theta/2).  Remember that w = cos(theta/2),
	  // and sin^2(x) + cos^2(x) = 1
	  Real sinThetaOver2Sq = 1.0 - (w * w);

	  // Protect against numerical imprecision
	  if (sinThetaOver2Sq <= 0.0)
	    {
	      // Identity quaternion, or numerical imprecision.  Just
	      // return any valid vector, since it doesn't matter

	      return Vector3<Real> (1.0, 0.0, 0.0);
	    }

	  // Compute 1 / sin(theta/2)
	  Real oneOverSinThetaOver2 = 1.0 / std::sqrt (sinThetaOver2Sq);

	  // Return axis of rotation
	  return Vector3<Real> (
		x * oneOverSinThetaOver2,
		y * oneOverSinThetaOver2,
		z * oneOverSinThetaOver2
	   );
	}


	// --------------------------------------------------------------------------
	// Quaternion operators
	//
	// Operator overloading for basic quaternion operations.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator+ (const Quaternion<Real> &q) const
	{
	  return Quaternion<Real> (w + q.w, x + q.x, y + q.y, z + q.z);
	}

	template <typename Real>
	inline Quaternion<Real> &
	Quaternion<Real>::operator+= (const Quaternion<Real> &q)
	{
	  w += q.w; x += q.x; y += q.y; z += q.z;
	  return *this;
	}

	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator- (const Quaternion<Real> &q) const
	{
	  return Quaternion<Real> (w - q.w, x - q.x, y - q.y, z - q.z);
	}

	template <typename Real>
	inline Quaternion<Real> &
	Quaternion<Real>::operator-= (const Quaternion<Real> &q)
	{
	  w -= q.w; x -= q.x; y -= q.y; z -= q.z;
	  return *this;
	}

	// Quaternion multiplication.  The order of multiplication, from left
	// to right, corresponds to the order of concatenated rotations.
	// NOTE: Quaternion multiplication is NOT commutative, p * q != q * p
	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator* (const Quaternion<Real> &q) const
	{
	  // We use the Grassman product formula:
	  // pq = <w1w2 - dot(v1, v2), w1v2 + w2v1 + cross(v1, v2)>
	  return Quaternion<Real> (
		(w * q.w) - (x * q.x) - (y * q.y) - (z * q.z),
		(x * q.w) + (w * q.x) + (y * q.z) - (z * q.y),
		(y * q.w) + (w * q.y) + (z * q.x) - (x * q.z),
		(z * q.w) + (w * q.z) + (x * q.y) - (y * q.x)
	   );
	}

	template <typename Real>
	inline Quaternion<Real> &
	Quaternion<Real>::operator*= (const Quaternion<Real> &q)
	{
	  *this = *this * q;
	  return *this;
	}

	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator* (const Vector3<Real> &v) const
	{
	  // q * v = q * p where p = <0,v>
	  // Thus, we can simplify the operations.
	  return Quaternion<Real> (
		- (x * v.x) - (y * v.y) - (z * v.z),
		  (w * v.x) + (y * v.z) - (z * v.y),
		  (w * v.y) + (z * v.x) - (x * v.z),
		  (w * v.z) + (x * v.y) - (y * v.x)
	   );
	}

	template <typename Real>
	inline Quaternion<Real> &
	Quaternion<Real>::operator*= (const Vector3<Real> &v)
	{
	  *this = *this * v;
	  return *this;
	}

	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator* (Real k) const
	{
	  return Quaternion<Real> (w * k, x * k, y * k, z * k);
	}

	template <typename Real>
	inline Quaternion<Real> &
	Quaternion<Real>::operator*= (Real k)
	{
	  w *= k; x *= k; y *= k; z *= k;
	  return *this;
	}

	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator/ (Real k) const
	{
	  Real oneOverK = 1.0 / k;
	  return Quaternion<Real> (w * oneOverK, x * oneOverK, y * oneOverK, z * oneOverK);
	}

	template <typename Real>
	inline Quaternion<Real> &
	Quaternion<Real>::operator/= (Real k)
	{
	  Real oneOverK = 1.0 / k;
	  w *= oneOverK; x *= oneOverK; y *= oneOverK; z *= oneOverK;
	  return *this;
	}

	// Quaternion conjugate
	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator~ () const
	{
	  return Quaternion<Real> (w, -x, -y, -z);
	}


	// Quaternion negation
	template <typename Real>
	inline Quaternion<Real>
	Quaternion<Real>::operator- () const
	{
	  return Quaternion<Real> (-w, -x, -y, -z);
	}


	// --------------------------------------------------------------------------
	//
	// Nonmember Quaternion functions
	//
	// --------------------------------------------------------------------------

	// Scalar on left multiplication
	template <typename Real>
	inline Quaternion<Real>
	operator* (Real k, const Quaternion<Real> &q)
	{
	  return Quaternion<Real> (q.w * k, q.x * k, q.y * k, q.z * k);
	}

	// Quaternion dot product
	template <typename Real>
	inline Real
	DotProduct (const Quaternion<Real> &a, const Quaternion<Real> &b)
	{
	  return ((a.w * b.w) + (a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	}

	// Compute the quaternion conjugate.  This is the quaternian
	// with the opposite rotation as the original quaternion.
	template <typename Real>
	inline Quaternion<Real>
	Conjugate (const Quaternion<Real> &q)
	{
	  return Quaternion<Real> (q.w, -q.x, -q.y, -q.z);
	}


	// Compute the inverse quaternion (for unit quaternion only).
	template <typename Real>
	inline Quaternion<Real>
	Inverse (const Quaternion<Real> &q)
	{
	  // Assume this is a unit quaternion! No check for this!
	  Quaternion<Real> res (q.w, -q.x, -q.y, -q.z);
	  res.normalize ();
	  return res;
	}


	// --------------------------------------------------------------------------
	// RotationQuaternion
	//
	// Setup the quaternion to rotate about the specified axis.  theta must
	// be in radians.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Quaternion<Real>
	RotationQuaternion (Axis axis, Real theta)
	{
	  Quaternion<Real> res;

	  // Compute the half angle
	  Real thetaOver2 = theta * 0.5;

	  // Set the values
	  switch (axis)
	    {
	    case kXaxis:
	      res.w = std::cos (thetaOver2);
	      res.x = std::sin (thetaOver2);
	      res.y = 0.0;
	      res.z = 0.0;
	      break;

	    case kYaxis:
	      res.w = std::cos (thetaOver2);
	      res.x = 0.0;
	      res.y = std::sin (thetaOver2);
	      res.z = 0.0;
	      break;

	    case kZaxis:
	      res.w = std::cos (thetaOver2);
	      res.x = 0.0;
	      res.y = 0.0;
	      res.z = std::sin (thetaOver2);
	      break;

	    default:
	      // Bad axis
	      assert (false);
	  }

	  return res;
	}

	template <typename Real>
	inline Quaternion<Real>
	RotationQuaternion (const Vector3<Real> &axis, Real theta)
	{
	  Quaternion<Real> res;

	  // The axis of rotation must be normalized
	  assert (std::fabs (DotProduct (axis, axis) - 1.0) < 0.001);

	  // Compute the half angle and its sin
	  Real thetaOver2 = theta * 0.5;
	  Real sinThetaOver2 = std::sin (thetaOver2);

	  // Set the values
	  res.w = std::cos (thetaOver2);
	  res.x = axis.x * sinThetaOver2;
	  res.y = axis.y * sinThetaOver2;
	  res.z = axis.z * sinThetaOver2;

	  return res;
	}


	// --------------------------------------------------------------------------
	// Log
	//
	// Unit quaternion logarithm. log(q) = log(cos(theta) + n*sin(theta))
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Quaternion<Real>
	Log (const Quaternion<Real> &q)
	{
	  Quaternion<Real> res;
	  res.w = 0.0;

	  if (std::fabs (q.w) < 1.0)
	    {
	      Real theta = std::acos (q.w);
	      Real sintheta = std::sin (theta);

	      if (std::fabs (sintheta) > 0.00001)
		{
		  Real thetaOverSinTheta = theta / sintheta;
		  res.x = q.x * thetaOverSinTheta;
		  res.y = q.y * thetaOverSinTheta;
		  res.z = q.z * thetaOverSinTheta;
		  return res;
		}
	    }

	  res.x = q.x;
	  res.y = q.y;
	  res.z = q.z;

	  return res;
	}


	// --------------------------------------------------------------------------
	// Exp
	//
	// Quaternion exponential.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Quaternion<Real>
	Exp (const Quaternion<Real> &q)
	{
	  Real theta = std::sqrt (DotProduct (q, q));
	  Real sintheta = std::sin (theta);

	  Quaternion<Real> res;
	  res.w = std::cos (theta);

	  if (std::fabs (sintheta) > 0.00001)
	    {
	      Real sinThetaOverTheta = sintheta / theta;
	      res.x = q.x * sinThetaOverTheta;
	      res.y = q.y * sinThetaOverTheta;
	      res.z = q.z * sinThetaOverTheta;
	    }
	  else
	    {
	      res.x = q.x;
	      res.y = q.y;
	      res.z = q.z;
	    }

	  return res;
	}


	// --------------------------------------------------------------------------
	// Pow
	//
	// Quaternion exponentiation.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Quaternion<Real>
	Pow (const Quaternion<Real> &q, Real exponent)
	{
	  // Check for the case of an identity quaternion.
	  // This will protect against divide by zero
	  if (std::fabs (q.w) > 0.9999)
	    return q;

	  // Extract the half angle alpha (alpha = theta/2)
	  Real alpha = std::acos (q.w);

	  // Compute new alpha value
	  Real newAlpha = alpha * exponent;

	  // Compute new quaternion
	  Vector3<Real> n (q.x, q.y, q.z);
	  n *= std::sin (newAlpha) / std::sin (alpha);

	  return Quaternion<Real> (std::cos (newAlpha), n);
	}


	// --------------------------------------------------------------------------
	// Slerp
	//
	// Spherical linear interpolation.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Quaternion<Real>
	Slerp (const Quaternion<Real> &q0, const Quaternion<Real> &q1, Real t)
	{
	  // Check for out-of range parameter and return edge points if so
	  if (t <= 0.0) return q0;
	  if (t >= 1.0) return q1;

	  // Compute "cosine of angle between quaternions" using dot product
	  Real cosOmega = DotProduct (q0, q1);

	  // If negative dot, use -q1.  Two quaternions q and -q
	  // represent the same rotation, but may produce
	  // different slerp.  We chose q or -q to rotate using
	  // the acute angle.
	  Real q1w = q1.w;
	  Real q1x = q1.x;
	  Real q1y = q1.y;
	  Real q1z = q1.z;

	  if (cosOmega < 0.0)
	    {
	      q1w = -q1w;
	      q1x = -q1x;
	      q1y = -q1y;
	      q1z = -q1z;
	      cosOmega = -cosOmega;
	    }

	  // We should have two unit quaternions, so dot should be <= 1.0
	  assert (cosOmega < 1.1);

	  // Compute interpolation fraction, checking for quaternions
	  // almost exactly the same
	  Real k0, k1;

	  if (cosOmega > 0.9999)
	    {
	      // Very close - just use linear interpolation,
	      // which will protect againt a divide by zero

	      k0 = 1.0 - t;
	      k1 = t;
	    }
	  else
	    {
	      // Compute the sin of the angle using the
	      // trig identity sin^2(omega) + cos^2(omega) = 1
	      Real sinOmega = std::sqrt (1.0 - (cosOmega * cosOmega));

	      // Compute the angle from its sin and cosine
	      Real omega = std::atan2 (sinOmega, cosOmega);

	      // Compute inverse of denominator, so we only have
	      // to divide once
	      Real oneOverSinOmega = 1.0 / sinOmega;

	      // Compute interpolation parameters
	      k0 = std::sin ((1.0 - t) * omega) * oneOverSinOmega;
	      k1 = std::sin (t * omega) * oneOverSinOmega;
	    }

	  // Interpolate and return new quaternion
	  return Quaternion<Real> (
		(k0 * q0.w) + (k1 * q1w),
		(k0 * q0.x) + (k1 * q1x),
		(k0 * q0.y) + (k1 * q1y),
		(k0 * q0.z) + (k1 * q1z)
	   );
	}


	// --------------------------------------------------------------------------
	// Squad
	//
	// Spherical cubic interpolation.
	// squad = slerp (slerp (q0, q1, t), slerp (qa, qb, t), 2t(1 - t)).
	// --------------------------------------------------------------------------

	template <typename Real>
	inline Quaternion<Real>
	Squad (const Quaternion<Real> &q0, const Quaternion<Real> &qa,
	       const Quaternion<Real> &qb, const Quaternion<Real> &q1, Real t)
	{
	  Real slerpt = 2.0 * t * (1.0 - t);

	  Quaternion<Real> slerpq0 = Slerp (q0, q1, t);
	  Quaternion<Real> slerpq1 = Slerp (qa, qb, t);

	  return Slerp (slerpq0, slerpq1, slerpt);
	}


	// --------------------------------------------------------------------------
	// Intermediate
	//
	// Compute intermediate quaternions for building spline segments.
	// --------------------------------------------------------------------------

	template <typename Real>
	inline void
	Intermediate (const Quaternion<Real> &qprev, const Quaternion<Real> &qcurr,
		      const Quaternion<Real> &qnext, Quaternion<Real> &qa, Quaternion<Real> &qb)
	{
	  // We should have unit quaternions
	  assert (DotProduct (qprev, qprev) <= 1.0001);
	  assert (DotProduct (qcurr, qcurr) <= 1.0001);

	  Quaternion<Real> invprev = Conjugate (qprev);
	  Quaternion<Real> invcurr = Conjugate (qcurr);

	  Quaternion<Real> p0 = invprev * qcurr;
	  Quaternion<Real> p1 = invcurr * qnext;

	  Quaternion<Real> arg = (Log (p0) - Log (p1)) * 0.25;

	  qa = qcurr * Exp ( arg);
	  qb = qcurr * Exp (-arg);
	}


}

#endif // __MATHLIBMOD_H__
