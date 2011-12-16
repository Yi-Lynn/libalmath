/*
 * Copyright (c) 2012, Aldebaran Robotics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Aldebaran Robotics nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Aldebaran Robotics BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <almath/types/alvelocity3d.h>

#include <gtest/gtest.h>
#include <stdexcept>

TEST(ALVelocity3DTest, variousOperator)
{
  //Velocity3D operator+ (a=b+c) (const Velocity3D& pVel2) const;
  AL::Math::Velocity3D pVIn1 = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  AL::Math::Velocity3D pVIn2 = AL::Math::Velocity3D(1.5f, 1.3f, 1.1f);
  AL::Math::Velocity3D pVIn3 = AL::Math::Velocity3D();
  pVIn3 = pVIn1 + pVIn2;

  AL::Math::Velocity3D pVOut = AL::Math::Velocity3D(2.0f, 1.6f, 1.2f);
  EXPECT_TRUE(pVIn3.isNear(pVOut, 0.0001f));

  //Velocity3D operator+ (a = +b) (const Velocity3D& pVel2) const;
  pVIn1 = AL::Math::Velocity3D(0.5f, -0.3f, 0.1f);
  pVIn3 = AL::Math::Velocity3D();
  pVIn3 = +pVIn1;

  pVOut = AL::Math::Velocity3D(0.5f, -0.3f, 0.1f);
  EXPECT_TRUE(pVIn3.isNear(pVOut, 0.0001f));

  //Velocity3D& operator+= (const Velocity3D& pVel2);
  pVIn1 = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  pVIn2 = AL::Math::Velocity3D(1.5f, 1.3f, 1.1f);
  pVIn1 += pVIn2;
  pVOut = AL::Math::Velocity3D(2.0f, 1.6f, 1.2f);
  EXPECT_TRUE(pVIn1.isNear(pVOut, 0.0001f));


  //Velocity3D operator- (a = b-c) (const Velocity3D& pVel2) const;
  pVIn1 = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  pVIn2 = AL::Math::Velocity3D(1.5f, 1.3f, 1.1f);
  pVIn3 = AL::Math::Velocity3D();
  pVIn3 = pVIn2 - pVIn1;
  pVOut = AL::Math::Velocity3D(1.0f, 1.0f, 1.0f);
  EXPECT_TRUE(pVIn3.isNear(pVOut, 0.0001f));


  //Velocity3D operator- (a = -b) (const Velocity3D& pVel2) const;
  pVIn1 = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  pVIn3 = AL::Math::Velocity3D();
  pVIn3 = -pVIn1;
  pVOut = AL::Math::Velocity3D(-0.5f, -0.3f, -0.1f);
  EXPECT_TRUE(pVIn3.isNear(pVOut, 0.0001f));

  //Velocity3D& operator-= (const Velocity3D& pVel2);
  pVIn1 = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  pVIn2 = AL::Math::Velocity3D(1.5f, 1.3f, 1.1f);
  pVIn1 -= pVIn2;
  pVOut = AL::Math::Velocity3D(-1.0f, -1.0f, -1.0f);
  EXPECT_TRUE(pVIn1.isNear(pVOut, 0.0001f));

  //Velocity3D operator* (const float pM) const;
  float K = 10.0f;
  pVIn1 = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  pVIn2 = AL::Math::Velocity3D();
  pVIn2 = pVIn1*K;
  pVOut = AL::Math::Velocity3D(5.0f, 3.0f, 1.0f);
  EXPECT_TRUE(pVIn2.isNear(pVOut, 0.0001f));

  //Velocity3D operator/ (const float pM) const;
  K = 10.0f;
  pVIn1 = AL::Math::Velocity3D(5.0f, 3.0f, 1.0f);
  pVIn2 = AL::Math::Velocity3D();
  pVIn2 = pVIn1/K;
  pVOut = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  EXPECT_TRUE(pVIn2.isNear(pVOut, 0.0001f));

  pVIn1 = AL::Math::Velocity3D(5.0f, 3.0f, 1.0f);
  ASSERT_THROW(pVIn1/0.0f, std::runtime_error);

  //Velocity3D& operator*= (const float pM);
  K = 10.0f;
  pVIn1 = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  pVIn1 *= K;
  pVOut = AL::Math::Velocity3D(5.0f, 3.0f, 1.0f);
  EXPECT_TRUE(pVIn1.isNear(pVOut, 0.0001f));

  //Velocity3D& operator/= (const float pM);
  K = 10.0f;
  pVIn1 = AL::Math::Velocity3D(5.0f, 3.0f, 1.0f);
  pVIn1 /= K;
  pVOut = AL::Math::Velocity3D(0.5f, 0.3f, 0.1f);
  EXPECT_TRUE(pVIn1.isNear(pVOut, 0.0001f));

  pVIn1 = AL::Math::Velocity3D(5.0f, 3.0f, 1.0f);
  ASSERT_THROW(pVIn1/=0.0f, std::runtime_error);
}

TEST(ALVelocity3DTest, isNear)
{
  AL::Math::Velocity3D pV = AL::Math::Velocity3D();

//bool isNear(
//            const Velocity3D& pVel,
//            const float&      pEpsilon=0.0001f) const;
}


//float norm () const;
TEST(ALVelocity3DTest, norm)
{
  float kEpsilon = 0.0001f;
  AL::Math::Velocity3D pVel3D1 = AL::Math::Velocity3D();
  EXPECT_NEAR(AL::Math::norm(pVel3D1), 0.0f, kEpsilon);

  pVel3D1 = AL::Math::Velocity3D(1.0f, 0.0f, 0.0f);
  EXPECT_NEAR(AL::Math::norm(pVel3D1), 1.0f, kEpsilon);
}

//Velocity3D normalize() const;
TEST(ALVelocity3DTest, normalize)
{
  AL::Math::Velocity3D pVel3D1 = AL::Math::Velocity3D(0.5f, 0.0f, 0.0f);
  EXPECT_TRUE(AL::Math::normalize(pVel3D1).isNear(AL::Math::Velocity3D(1.0f, 0.0f, 0.0f)));

  pVel3D1 = AL::Math::Velocity3D(1.0f, -1.0f, 0.0f);
  EXPECT_TRUE(AL::Math::normalize(pVel3D1).isNear(AL::Math::Velocity3D(0.70710678118655f, -0.70710678118655f, 0.0f)));

  pVel3D1 = AL::Math::Velocity3D(0.0f, 0.0f, 0.0f);
  ASSERT_THROW(AL::Math::normalize(pVel3D1), std::runtime_error);
}


TEST(ALVelocity3DTest, Divers)
{
  AL::Math::Velocity3D pVel3D1 = AL::Math::Velocity3D(+1.2f, 1.3f, 0.2f);
  AL::Math::Velocity3D pVel3D2 = AL::Math::Velocity3D(-0.5f, 0.2f, 0.4f);
  EXPECT_TRUE((pVel3D2-pVel3D1).isNear(AL::Math::Velocity3D(-1.7f, -1.1f, 0.2f)));

  pVel3D1 = AL::Math::Velocity3D(+1.2f, 1.3f, 0.2f);
  pVel3D2 = AL::Math::Velocity3D(-0.5f, 0.2f, 0.4f);
  EXPECT_TRUE((pVel3D1+pVel3D2).isNear(AL::Math::Velocity3D(0.7f, 1.5f, 0.6f)));

  pVel3D1 = AL::Math::Velocity3D(1.0f, 1.0f, 1.0f);
  EXPECT_TRUE((pVel3D1*2.0f).isNear(AL::Math::Velocity3D(2.0f, 2.0f, 2.0f)));

  pVel3D1 = AL::Math::Velocity3D(1.0f, 1.0f, 1.0f);
  EXPECT_TRUE((2.0f*pVel3D1).isNear(AL::Math::Velocity3D(2.0f, 2.0f, 2.0f)));

  pVel3D1 = AL::Math::Velocity3D(2.0f, 2.0f, 2.0f);
  EXPECT_TRUE((pVel3D1/2.0f).isNear(AL::Math::Velocity3D(1.0f, 1.0f, 1.0f)));

  pVel3D1 = AL::Math::Velocity3D(2.0f, 2.0f, 2.0f);
  ASSERT_THROW((pVel3D1/0.0f), std::runtime_error);
}
