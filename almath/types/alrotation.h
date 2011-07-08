/*
** Author(s):
**  - Chris Kilner
**  - Cyrille Collette
**  - David Gouaillier
**
** Copyright (C) 2011 Aldebaran Robotics
*/

#pragma once

#ifndef _LIB_ALMATH_ALMATH_ALROTATION_H_
#define _LIB_ALMATH_ALMATH_ALROTATION_H_

#include <vector>

namespace AL {
  namespace Math {

  /// <summary>
  /// A 3*3 rotation matrix.
  ///
  /// </summary>
  /// <A HREF="http://en.wikipedia.org/wiki/Rotation_matrix">more information</A>
  /// \ingroup Types
    struct Rotation
    {
      float r1_c1, r1_c2, r1_c3,
        r2_c1, r2_c2, r2_c3,
        r3_c1, r3_c2, r3_c3;

      /// <summary>
      /// Create a Rotation initialized to identity.
      /// </summary>
      Rotation(): r1_c1(1.0f), r1_c2(0.0f), r1_c3(0.0f),
        r2_c1(0.0f), r2_c2(1.0f), r2_c3(0.0f),
        r3_c1(0.0f), r3_c2(0.0f), r3_c3(1.0f){}

      /// <summary>
      /// Create a Rotation with an std::vector.
      /// </summary>
      /// <param name="pFloats">
      /// An std::vector<float> of size 9, 12 or 16 for respectively:
      ///
      /// For std::vector<float> of size 9
      ///
      /// \f$ \left[\begin{array}{cccc}r1c1 & r1c2 & r1c3 \\ r2c1 & r2c2 & r2c3 \\ r3c1 & r3c2 & r3c3 \end{array}\right] = \left[\begin{array}{cccc}pFloats[0] & pFloats[1] & pFloats[2] \\ pFloats[3] & pFloats[4] & pFloats[5] \\ pFloats[6] & pFloats[7] & pFloats[8] \end{array}\right]\f$
      ///
      /// For std::vector<float> of size 12 or 16
      ///
      /// \f$ \left[\begin{array}{cccc}r1c1 & r1c2 & r1c3 \\ r2c1 & r2c2 & r2c3 \\ r3c1 & r3c2 & r3c3 \end{array}\right] = \left[\begin{array}{cccc}pFloats[0] & pFloats[1] & pFloats[2] \\ pFloats[4] & pFloats[5] & pFloats[6] \\ pFloats[8] & pFloats[9] & pFloats[10] \end{array}\right]\f$
      /// </param>
      Rotation (const std::vector<float>& pFloats)
      {
        if (pFloats.size() == 9)
        {
          r1_c1 = pFloats[0];
          r1_c2 = pFloats[1];
          r1_c3 = pFloats[2];
          r2_c1 = pFloats[3];
          r2_c2 = pFloats[4];
          r2_c3 = pFloats[5];
          r3_c1 = pFloats[6];
          r3_c2 = pFloats[7];
          r3_c3 = pFloats[8];
        }
        else if ((pFloats.size() == 12) || (pFloats.size() == 16))
        {
          // if we give a transform, it take rotation part
          r1_c1 = pFloats[0];
          r1_c2 = pFloats[1];
          r1_c3 = pFloats[2];

          r2_c1 = pFloats[4];
          r2_c2 = pFloats[5];
          r2_c3 = pFloats[6];

          r3_c1 = pFloats[8];
          r3_c2 = pFloats[9];
          r3_c3 = pFloats[10];
        }
        else
        {
          r1_c1 = 1.0f;
          r1_c2 = 0.0f;
          r1_c3 = 0.0f;

          r2_c1 = 0.0f;
          r2_c2 = 1.0f;
          r2_c3 = 0.0f;

          r3_c1 = 0.0f;
          r3_c2 = 0.0f;
          r3_c3 = 1.0f;
        }
      }

      /// <summary>
      /// Overloading of operator *= for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      Rotation& operator*= (const Rotation& pRot2);

      /// <summary>
      /// Overloading of operator * for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      Rotation operator* (const Rotation& pRot2) const;

      /// <summary>
      /// Overloading of operator == for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      bool operator==(const Rotation& pRot2) const;

      /// <summary>
      /// Overloading of operator != for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      bool operator!=(const Rotation& pRot2) const;

      /// <summary>
      /// Check if the actual Rotation is near the one
      /// give in argument.
      ///
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      /// <param name="pEpsilon"> an optionnal epsilon distance: default: 0.0001 </param>
      /// <returns>
      /// true if the distance between the two rotations is less than pEpsilon
      /// </returns>
      bool isNear(
        const Rotation& pRot2,
        const float&    pEpsilon=0.0001f) const;

      /// <summary>
      /// Compute the rotation transpose (inverse) of the actual Rotation:
      /// </summary>
      /// <returns>
      /// the Rotation transpose
      /// </returns>
      Rotation transpose() const;

      /// <summary>
      /// Compute the determinant of the Rotation:
      ///
      /// \f$pRot.r1c1*pRot.r2c2*pRot.r3c3 + pRot.r1c2*pRot.r2c3*pRot.r3c1 + pRot.r1c3*pRot.r2c1*pRot.r3c2 - pRot.r1c1*pRot.r2c3*pRot.r3c2 - pRot.r1c2*pRot.r2c1*pRot.r3c3 - pRot.r1c3*pRot.r2c2*pRot.r3c1\f$
      /// </summary>
      /// <returns>
      /// the float determinant of the Rotation
      /// </returns>
      float determinant() const;

      /// <summary>
      /// Creates a 3*3 Rotation Matrix from a normalized quaternion ( |a + bi + cj + dk| = 1).
      /// </summary>
      /// <param name="pA"> Coefficient a of the normalized quaternion </param>
      /// <param name="pB"> Coefficient b of the normalized quaternion </param>
      /// <param name="pC"> Coefficient c of the normalized quaternion </param>
      /// <param name="pD"> Coefficient d of the normalized quaternion </param>
      static Rotation fromQuaternion(
        const float pA,
        const float pB,
        const float pC,
        const float pD);


      /// <summary>
      /// Creates a 3*3 Rotation Matrix from a an angle and a normalized direction( |pX, pY, pZ| = 1).
      /// </summary>
      /// <param name="pAngle"> the float value of angle in radian </param>
      /// <param name="pX"> the X direction of the vector of the rotation </param>
      /// <param name="pY"> the Y direction of the vector of the rotation </param>
      /// <param name="pZ"> the Z direction of the vector of the rotation </param>
      static Rotation fromAngleDirection(
        const float pAngle,
        const float pX,
        const float pY,
        const float pZ);

      /// <summary>
      /// Create a Rotation initialized with explicit rotation around x axis.
      ///
      /// \f$ pRot = \left[\begin{array}{cccc}1.0 & 0.0 & 0.0 \\ 0.0 & cos(pRotX) & -sin(pRotX) \\ 0.0 & sin(pRotX) & cos(pRotX) \end{array}\right]\f$
      ///
      /// </summary>
      /// <param name="pRotX"> the float value for angle rotation in radian around x axis </param>
      static Rotation fromRotX(const float pRotX);

      /// <summary>
      /// Create a Rotation initialized with explicit rotation around y axis.
      ///
      /// \f$ pT = \left[\begin{array}{cccc} cos(pRotY) & 0.0 & sin(pRotY) \\ 0.0 & 1.0 & 0.0 \\ -sin(pRotY) & 0.0 & cos(pRotY) \end{array}\right]\f$
      ///
      /// </summary>
      /// <param name="pRotY"> the float value for angle rotation in radian around y axis </param>
      static Rotation fromRotY(const float pRotY);

      /// <summary>
      /// Create a Rotation initialized with explicit rotation around z axis.
      ///
      /// \f$ pT = \left[\begin{array}{cccc} cos(pRotZ) & -sin(pRotZ) & 0.0 \\ sin(pRotZ) & cos(pRotZ) & 0.0 \\ 0.0 & 0.0 & 1.0 \end{array}\right]\f$
      ///
      /// </summary>
      /// <param name="pRotZ"> the float value for angle rotation in radian around z axis </param>
      static Rotation fromRotZ(const float pRotZ);

      /// <summary>
      /// Create a Rotation initialized with euler angle.
      ///
      /// Rot = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
      ///
      /// </summary>
      /// <param name="pWX"> the float value for euler angle x in radian </param>
      /// <param name="pWY"> the float value for euler angle y in radian </param>
      /// <param name="pWZ"> the float value for euler angle z in radian </param>
      static Rotation from3DRotation(
        const float& pWX,
        const float& pWY,
        const float& pWZ);

      /// <summary>
      /// Return the Rotation as a vector of float:
      ///
      /// \f$ \begin{array}{cccc} [r1c1, & r1c2, & r1c3, \\ r2c1, & r2c2, & r2c3, \\ r3c1, & r3c2, & r3c3] \end{array}\f$
      /// </summary>
      std::vector<float> toVector() const;

    }; // end struct

    /// <summary>
    /// Compute the transpose rotation of
    /// the one given in argument:
    /// </summary>
    /// <param name="pRot"> the rotation matrix </param>
    /// <returns>
    /// the rotation transposed
    /// </returns>
        /// \ingroup Types
    Rotation transpose(const Rotation& pRot);


    /// <summary>
    /// Compute the determinant of the given Rotation:
    ///
    /// \f$pRot.r1c1*pRot.r2c2*pRot.r3c3 + pRot.r1c2*pRot.r2c3*pRot.r3c1 + pRot.r1c3*pRot.r2c1*pRot.r3c2 - pRot.r1c1*pRot.r2c3*pRot.r3c2 - pRot.r1c2*pRot.r2c1*pRot.r3c3 - pRot.r1c3*pRot.r2c2*pRot.r3c1\f$
    /// </summary>
    /// <param name="pRot"> the given Rotation </param>
    /// <returns>
    /// the float determinant of Rotation
    /// </returns>
    /// \ingroup Types
    float determinant(const Rotation& pRot);


    /// <summary>
    /// Creates a 3*3 Rotation Matrix from a normalized quaternion ( |a + bi + cj + dk| = 1).
    /// </summary>
    /// <param name="pA"> Coefficient a of the normalized quaternion </param>
    /// <param name="pB"> Coefficient b of the normalized quaternion </param>
    /// <param name="pC"> Coefficient c of the normalized quaternion </param>
    /// <param name="pD"> Coefficient d of the normalized quaternion </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromQuaternion(
      const float pA,
      const float pB,
      const float pC,
      const float pD);

    /// <summary>
    /// Creates a 3*3 Rotation Matrix from a an angle and a normalized direction( |pX, pY, pZ| = 1).
    /// </summary>
    /// <param name="pAngle"> the float value of angle in radian </param>
    /// <param name="pX"> the X direction of the vector of the rotation </param>
    /// <param name="pY"> the Y direction of the vector of the rotation </param>
    /// <param name="pZ"> the Z direction of the vector of the rotation </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromAngleDirection(
      const float pAngle,
      const float pX,
      const float pY,
      const float pZ);

    /// <summary>
    /// Apply Rotation to a 3D point.
    /// </summary>
    /// <param name="pRot"> the given rotation </param>
    /// <param name="pX"> the X position of the 3D point after rotation </param>
    /// <param name="pY"> the Y position of the 3D point after rotation </param>
    /// <param name="pZ"> the Z position of the 3D point after rotation </param>
    /// \ingroup Types
    void applyRotation(
      const AL::Math::Rotation& pRot,
      float&                    pX,
      float&                    pY,
      float&                    pZ);

    /// <summary>
    /// Create a Rotation initialized with explicit rotation around x axis.
    ///
    /// \f$ pRot = \left[\begin{array}{cccc}1.0 & 0.0 & 0.0 \\ 0.0 & cos(pRotX) & -sin(pRotX) \\ 0.0 & sin(pRotX) & cos(pRotX) \end{array}\right]\f$
    ///
    /// </summary>
    /// <param name="pRotX"> the float value for angle rotation in radian around x axis </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromRotX(const float pRotX);

    /// <summary>
    /// Create a Rotation initialized with explicit rotation around y axis.
    ///
    /// \f$ pT = \left[\begin{array}{cccc} cos(pRotY) & 0.0 & sin(pRotY) \\ 0.0 & 1.0 & 0.0 \\ -sin(pRotY) & 0.0 & cos(pRotY) \end{array}\right]\f$
    ///
    /// </summary>
    /// <param name="pRotY"> the float value for angle rotation in radian around y axis </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromRotY(const float pRotY);

    /// <summary>
    /// Create a Rotation initialized with explicit rotation around z axis.
    ///
    /// \f$ pT = \left[\begin{array}{cccc} cos(pRotZ) & -sin(pRotZ) & 0.0 \\ sin(pRotZ) & cos(pRotZ) & 0.0 \\ 0.0 & 0.0 & 1.0 \end{array}\right]\f$
    ///
    /// </summary>
    /// <param name="pRotZ"> the float value for angle rotation in radian around z axis </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromRotZ(const float pRotZ);

    /// <summary>
    /// Create a Rotation initialized with euler angle.
    /// Rot = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
    ///
    /// </summary>
    /// <param name="pWX"> the float value for euler angle x in radian </param>
    /// <param name="pWY"> the float value for euler angle y in radian </param>
    /// <param name="pWZ"> the float value for euler angle z in radian </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFrom3DRotation(
      const float& pWX,
      const float& pWY,
      const float& pWZ);

  }
}
#endif  // _LIB_ALMATH_ALMATH_ALROTATION_H_
