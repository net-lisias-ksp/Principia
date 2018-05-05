﻿
#include "physics/body_centred_body_direction_dynamic_frame.hpp"

#include <memory>

#include "astronomy/frames.hpp"
#include "geometry/frame.hpp"
#include "geometry/grassmann.hpp"
#include "geometry/named_quantities.hpp"
#include "geometry/rotation.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "integrators/methods.hpp"
#include "integrators/symplectic_runge_kutta_nyström_integrator.hpp"
#include "physics/ephemeris.hpp"
#include "physics/mock_continuous_trajectory.hpp"
#include "physics/mock_ephemeris.hpp"
#include "physics/solar_system.hpp"
#include "quantities/constants.hpp"
#include "quantities/quantities.hpp"
#include "quantities/si.hpp"
#include "serialization/geometry.pb.h"
#include "serialization/physics.pb.h"
#include "testing_utilities/almost_equals.hpp"
#include "testing_utilities/numerics.hpp"
#include "testing_utilities/vanishes_before.hpp"

namespace principia {
namespace physics {
namespace internal_body_centred_body_direction_dynamic_frame {

using astronomy::ICRFJ2000Equator;
using base::check_not_null;
using geometry::Barycentre;
using geometry::Bivector;
using geometry::Frame;
using geometry::Instant;
using geometry::Rotation;
using geometry::Vector;
using integrators::SymplecticRungeKuttaNyströmIntegrator;
using integrators::methods::McLachlanAtela1992Order4Optimal;
using quantities::SIUnit;
using quantities::Sqrt;
using quantities::Time;
using quantities::si::Kilo;
using quantities::si::Metre;
using quantities::si::Milli;
using quantities::si::Radian;
using quantities::si::Second;
using testing_utilities::AbsoluteError;
using testing_utilities::AlmostEquals;
using testing_utilities::VanishesBefore;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::IsNull;
using ::testing::Lt;
using ::testing::Not;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::_;

namespace {

char constexpr big[] = "Big";
char constexpr small[] = "Small";

}  // namespace

class BodyCentredBodyDirectionDynamicFrameTest : public ::testing::Test {
 protected:
  // The rotating frame centred on the big body and directed to the small one.
  using BigSmallFrame = Frame<serialization::Frame::TestTag,
                              serialization::Frame::TEST, /*inertial=*/false>;
  using MockFrame = Frame<serialization::Frame::TestTag,
                          serialization::Frame::TEST1, /*inertial=*/false>;

  BodyCentredBodyDirectionDynamicFrameTest()
      : period_(10 * π * sqrt(5.0 / 7.0) * Second),
        solar_system_(SOLUTION_DIR / "astronomy" /
                          "test_gravity_model_two_bodies.proto.txt",
                      SOLUTION_DIR / "astronomy" /
                          "test_initial_state_two_bodies_circular.proto.txt"),
        t0_(solar_system_.epoch()),
        ephemeris_(solar_system_.MakeEphemeris(
            /*fitting_tolerance=*/1 * Milli(Metre),
            Ephemeris<ICRFJ2000Equator>::FixedStepParameters(
                SymplecticRungeKuttaNyströmIntegrator<
                    McLachlanAtela1992Order4Optimal,
                    Position<ICRFJ2000Equator>>(),
                /*step=*/10 * Milli(Second)))),
        big_(solar_system_.massive_body(*ephemeris_, big)),
        big_initial_state_(solar_system_.degrees_of_freedom(big)),
        big_gravitational_parameter_(
            solar_system_.gravitational_parameter(big)),
        small_(solar_system_.massive_body(*ephemeris_, small)),
        small_initial_state_(solar_system_.degrees_of_freedom(small)),
        small_gravitational_parameter_(
            solar_system_.gravitational_parameter(small)) {
    EXPECT_CALL(mock_ephemeris_,
                trajectory(solar_system_.massive_body(*ephemeris_, big)))
        .WillOnce(Return(&mock_big_trajectory_));
    EXPECT_CALL(mock_ephemeris_,
                trajectory(solar_system_.massive_body(*ephemeris_, small)))
        .WillOnce(Return(&mock_small_trajectory_));
    mock_frame_ = std::make_unique<
        BodyCentredBodyDirectionDynamicFrame<ICRFJ2000Equator, MockFrame>>(
        &mock_ephemeris_, big_, small_);

    ephemeris_->Prolong(t0_ + 2 * period_);
    big_small_frame_ = std::make_unique<
        BodyCentredBodyDirectionDynamicFrame<ICRFJ2000Equator, BigSmallFrame>>(
        ephemeris_.get(), big_, small_);
  }

  Time const period_;
  SolarSystem<ICRFJ2000Equator> solar_system_;
  Instant const t0_;
  std::unique_ptr<Ephemeris<ICRFJ2000Equator>> const ephemeris_;
  MassiveBody const* big_;
  DegreesOfFreedom<ICRFJ2000Equator> big_initial_state_;
  GravitationalParameter big_gravitational_parameter_;
  MassiveBody const* small_;
  DegreesOfFreedom<ICRFJ2000Equator> small_initial_state_;
  GravitationalParameter small_gravitational_parameter_;
  StrictMock<MockEphemeris<ICRFJ2000Equator>> mock_ephemeris_;

  std::unique_ptr<
      BodyCentredBodyDirectionDynamicFrame<ICRFJ2000Equator, MockFrame>>
      mock_frame_;
  std::unique_ptr<
      BodyCentredBodyDirectionDynamicFrame<ICRFJ2000Equator, BigSmallFrame>>
          big_small_frame_;
  StrictMock<MockContinuousTrajectory<ICRFJ2000Equator>> mock_big_trajectory_;
  StrictMock<MockContinuousTrajectory<ICRFJ2000Equator>> mock_small_trajectory_;
};


TEST_F(BodyCentredBodyDirectionDynamicFrameTest, ToBigSmallFrameAtTime) {
  int const steps = 100;

  for (Instant t = t0_; t < t0_ + 1 * period_; t += period_ / steps) {
    auto const to_big_small_frame_at_t = big_small_frame_->ToThisFrameAtTime(t);

    // Check that the bodies don't move and are at the right locations.
    DegreesOfFreedom<ICRFJ2000Equator> const big_in_inertial_frame_at_t =
        solar_system_.trajectory(*ephemeris_, big).
            EvaluateDegreesOfFreedom(t);
    DegreesOfFreedom<ICRFJ2000Equator> const small_in_inertial_frame_at_t =
        solar_system_.trajectory(*ephemeris_, small).
            EvaluateDegreesOfFreedom(t);

    DegreesOfFreedom<BigSmallFrame> const big_in_big_small_at_t =
        to_big_small_frame_at_t(big_in_inertial_frame_at_t);
    DegreesOfFreedom<BigSmallFrame> const small_in_big_small_at_t =
        to_big_small_frame_at_t(small_in_inertial_frame_at_t);
    EXPECT_THAT(AbsoluteError(big_in_big_small_at_t.position(),
                              BigSmallFrame::origin),
                Lt(1.0e-6 * Metre));
    EXPECT_THAT(AbsoluteError(big_in_big_small_at_t.velocity(),
                              Velocity<BigSmallFrame>()),
                Lt(1.0e-4 * Metre / Second));
    EXPECT_THAT(AbsoluteError(small_in_big_small_at_t.position(),
                              Displacement<BigSmallFrame>({
                                  5.0 * Kilo(Metre),
                                  0 * Kilo(Metre),
                                  0 * Kilo(Metre)}) + BigSmallFrame::origin),
                Lt(1.0e-5 * Metre));
    EXPECT_THAT(AbsoluteError(small_in_big_small_at_t.velocity(),
                              Velocity<BigSmallFrame>()),
                Lt(1.0e-4 * Metre / Second));
  }
}

TEST_F(BodyCentredBodyDirectionDynamicFrameTest, Inverse) {
  int const steps = 100;
  for (Instant t = t0_; t < t0_ + 1 * period_; t += period_ / steps) {
    auto const from_big_small_frame_at_t =
        big_small_frame_->FromThisFrameAtTime(t);
    auto const to_big_small_frame_at_t = big_small_frame_->ToThisFrameAtTime(t);
    auto const small_initial_state_transformed_and_back =
        from_big_small_frame_at_t(to_big_small_frame_at_t(
            small_initial_state_));
    EXPECT_THAT(
        AbsoluteError(small_initial_state_transformed_and_back.position(),
                      small_initial_state_.position()),
        Lt(1.0e-11 * Metre));
    EXPECT_THAT(
        AbsoluteError(small_initial_state_transformed_and_back.velocity(),
                      small_initial_state_.velocity()),
        Lt(1.0e-11 * Metre / Second));
  }
}

// The test point is at the origin and in motion.  The acceleration is purely
// due to Coriolis.
TEST_F(BodyCentredBodyDirectionDynamicFrameTest, CoriolisAcceleration) {
  Instant const t = t0_ + 0 * Second;
  // The velocity is opposed to the motion and away from the centre.
  DegreesOfFreedom<MockFrame> const point_dof =
      {Displacement<MockFrame>({0 * Metre, 0 * Metre, 0 * Metre}) +
           MockFrame::origin,
       Velocity<MockFrame>({10 * Metre / Second,
                            20 * Metre / Second,
                            30 * Metre / Second})};
  DegreesOfFreedom<ICRFJ2000Equator> const big_dof =
      {Displacement<ICRFJ2000Equator>({0 * Metre, 0 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>()};
  DegreesOfFreedom<ICRFJ2000Equator> const small_dof =
      {Displacement<ICRFJ2000Equator>({3 * Metre, 4 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>({40 * Metre / Second,
                                   -30 * Metre / Second,
                                   0 * Metre / Second})};

  EXPECT_CALL(mock_big_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(big_dof));
  EXPECT_CALL(mock_small_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(small_dof));
  {
    InSequence s;
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(big_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             0 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(small_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             -300 * Metre / Pow<2>(Second),
                             -400 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMasslessBody(_, t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>()));
  }

  // The Coriolis acceleration is towards the centre and opposed to the motion.
  EXPECT_THAT(mock_frame_->GeometricAcceleration(t, point_dof),
              AlmostEquals(Vector<Acceleration, MockFrame>({
                               400 * Metre / Pow<2>(Second),
                               -200 * Metre / Pow<2>(Second),
                               0 * Metre / Pow<2>(Second)}), 0));
}

// The test point doesn't move so the acceleration is purely centrifugal.
TEST_F(BodyCentredBodyDirectionDynamicFrameTest, CentrifugalAcceleration) {
  Instant const t = t0_ + 0 * Second;
  DegreesOfFreedom<MockFrame> const point_dof =
      {Displacement<MockFrame>({10 * Metre, 20 * Metre, 30 * Metre}) +
           MockFrame::origin,
       Velocity<MockFrame>({0 * Metre / Second,
                            0 * Metre / Second,
                            0 * Metre / Second})};
  DegreesOfFreedom<ICRFJ2000Equator> const big_dof =
      {Displacement<ICRFJ2000Equator>({0 * Metre, 0 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>({0 * Metre / Second,
                                   0 * Metre / Second,
                                   0 * Metre / Second})};
  DegreesOfFreedom<ICRFJ2000Equator> const small_dof =
      {Displacement<ICRFJ2000Equator>({3 * Metre, 4 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>({40 * Metre / Second,
                                   -30 * Metre / Second,
                                   0 * Metre / Second})};

  EXPECT_CALL(mock_big_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(big_dof));
  EXPECT_CALL(mock_small_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(small_dof));
  {
    InSequence s;
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(big_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             0 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(small_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             -300 * Metre / Pow<2>(Second),
                             -400 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMasslessBody(_, t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>()));
  }

  EXPECT_THAT(mock_frame_->GeometricAcceleration(t, point_dof),
              AlmostEquals(Vector<Acceleration, MockFrame>({
                               1e3 * Metre / Pow<2>(Second),
                               2e3 * Metre / Pow<2>(Second),
                               0 * Metre / Pow<2>(Second)}), 0));
}

// A tangential acceleration that increases the rotational speed.  The test
// point doesn't move.  The resulting acceleration combines centrifugal and
// Euler.
TEST_F(BodyCentredBodyDirectionDynamicFrameTest, EulerAcceleration) {
  Instant const t = t0_ + 0 * Second;
  DegreesOfFreedom<MockFrame> const point_dof =
      {Displacement<MockFrame>({10 * Metre, 20 * Metre, 30 * Metre}) +
           MockFrame::origin,
       Velocity<MockFrame>({0 * Metre / Second,
                            0 * Metre / Second,
                            0 * Metre / Second})};
  DegreesOfFreedom<ICRFJ2000Equator> const big_dof =
      {Displacement<ICRFJ2000Equator>({0 * Metre, 0 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>({0 * Metre / Second,
                                   0 * Metre / Second,
                                   0 * Metre / Second})};
  DegreesOfFreedom<ICRFJ2000Equator> const small_dof =
      {Displacement<ICRFJ2000Equator>({3 * Metre, 4 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>({40 * Metre / Second,
                                   -30 * Metre / Second,
                                   0 * Metre / Second})};
  EXPECT_CALL(mock_big_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(big_dof));
  EXPECT_CALL(mock_small_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(small_dof));
  {
    // The acceleration is centripetal + tangential.
    InSequence s;
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(big_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             0 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(small_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             (-300 + 400) * Metre / Pow<2>(Second),
                             (-400 - 300) * Metre / Pow<2>(Second),
                             0 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMasslessBody(_, t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>()));
  }

  // The acceleration is centrifugal + Euler.
  EXPECT_THAT(mock_frame_->GeometricAcceleration(t, point_dof),
              AlmostEquals(Vector<Acceleration, MockFrame>({
                               (1e3 + 2e3) * Metre / Pow<2>(Second),
                               (2e3 - 1e3) * Metre / Pow<2>(Second),
                               0 * Metre / Pow<2>(Second)}), 0));
}

// A linear acceleration identical for both bodies.  The test point doesn't
// move.  The resulting acceleration combines centrifugal and linear.
TEST_F(BodyCentredBodyDirectionDynamicFrameTest, LinearAcceleration) {
  Instant const t = t0_ + 0 * Second;
  DegreesOfFreedom<MockFrame> const point_dof =
      {Displacement<MockFrame>({10 * Metre, 20 * Metre, 30 * Metre}) +
           MockFrame::origin,
       Velocity<MockFrame>({0 * Metre / Second,
                            0 * Metre / Second,
                            0 * Metre / Second})};
  DegreesOfFreedom<ICRFJ2000Equator> const big_dof =
      {Displacement<ICRFJ2000Equator>({0 * Metre, 0 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>({0 * Metre / Second,
                                   0 * Metre / Second,
                                   0 * Metre / Second})};
  DegreesOfFreedom<ICRFJ2000Equator> const small_dof =
      {Displacement<ICRFJ2000Equator>({3 * Metre, 4 * Metre, 0 * Metre}) +
           ICRFJ2000Equator::origin,
       Velocity<ICRFJ2000Equator>({40 * Metre / Second,
                                   -30 * Metre / Second,
                                   0 * Metre / Second})};

  EXPECT_CALL(mock_big_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(big_dof));
  EXPECT_CALL(mock_small_trajectory_, EvaluateDegreesOfFreedom(t))
      .Times(2)
      .WillRepeatedly(Return(small_dof));
  {
    // The acceleration is linear + centripetal.
    InSequence s;
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(big_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             -160 * Metre / Pow<2>(Second),
                             120 * Metre / Pow<2>(Second),
                             300 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMassiveBody(
                    check_not_null(small_), t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>({
                             (-160 - 300) * Metre / Pow<2>(Second),
                             (120 - 400) * Metre / Pow<2>(Second),
                             300 * Metre / Pow<2>(Second)})));
    EXPECT_CALL(mock_ephemeris_,
                ComputeGravitationalAccelerationOnMasslessBody(_, t))
        .WillOnce(Return(Vector<Acceleration, ICRFJ2000Equator>()));
  }

  // The acceleration is linear + centrifugal.
  EXPECT_THAT(mock_frame_->GeometricAcceleration(t, point_dof),
              AlmostEquals(Vector<Acceleration, MockFrame>({
                               1e3 * Metre / Pow<2>(Second),
                               (200 + 2e3) * Metre / Pow<2>(Second),
                               300 * Metre / Pow<2>(Second)}), 0));
}

TEST_F(BodyCentredBodyDirectionDynamicFrameTest, GeometricAcceleration) {
  Instant const t = t0_ + period_;
  DegreesOfFreedom<BigSmallFrame> const point_dof =
      {Displacement<BigSmallFrame>({10 * Metre, 20 * Metre, 30 * Metre}) +
           BigSmallFrame::origin,
       Velocity<BigSmallFrame>({3 * Metre / Second,
                                2 * Metre / Second,
                                1 * Metre / Second})};
  // We trust the functions to compute the values correctly, but this test
  // ensures that we don't get NaNs.
  EXPECT_THAT(big_small_frame_->GeometricAcceleration(t, point_dof),
              AlmostEquals(Vector<Acceleration, BigSmallFrame>({
                  -9.54502614154908457e5 * Metre / Pow<2>(Second),
                  -1.90900949256416853e6 * Metre / Pow<2>(Second),
                  -2.86351378905829182e6 * Metre / Pow<2>(Second)}), 0));
}

TEST_F(BodyCentredBodyDirectionDynamicFrameTest, Serialization) {
  serialization::DynamicFrame message;
  big_small_frame_->WriteToMessage(&message);

  EXPECT_TRUE(message.HasExtension(
      serialization::BodyCentredBodyDirectionDynamicFrame::extension));
  auto const extension = message.GetExtension(
      serialization::BodyCentredBodyDirectionDynamicFrame::extension);
  EXPECT_TRUE(extension.has_primary());
  EXPECT_TRUE(extension.has_secondary());
  EXPECT_EQ(0, extension.primary());
  EXPECT_EQ(1, extension.secondary());

  auto const read_big_small_frame =
      DynamicFrame<ICRFJ2000Equator, BigSmallFrame>::ReadFromMessage(
          message, ephemeris_.get());
  EXPECT_THAT(read_big_small_frame, Not(IsNull()));

  Instant const t = t0_ + period_;
  DegreesOfFreedom<BigSmallFrame> const point_dof =
      {Displacement<BigSmallFrame>({10 * Metre, 20 * Metre, 30 * Metre}) +
           BigSmallFrame::origin,
       Velocity<BigSmallFrame>({3 * Metre / Second,
                                2 * Metre / Second,
                                1 * Metre / Second})};
  EXPECT_EQ(big_small_frame_->GeometricAcceleration(t, point_dof),
            read_big_small_frame->GeometricAcceleration(t, point_dof));
}

TEST_F(BodyCentredBodyDirectionDynamicFrameTest, ConstructFromOneBody) {
  // A discrete trajectory that remains motionless at the barycentre.  Since
  // both bodies don't have the same mass, this means it has an intrinsic
  // acceleration.
  DiscreteTrajectory<ICRFJ2000Equator> barycentre_trajectory;
  for (Time t; t <= period_; t += period_ / 16) {
    auto const big_dof =
        ephemeris_->trajectory(big_)->EvaluateDegreesOfFreedom(t0_ + t);
    auto const small_dof =
        ephemeris_->trajectory(small_)->EvaluateDegreesOfFreedom(t0_ + t);
    auto const barycentre =
        Barycentre<DegreesOfFreedom<ICRFJ2000Equator>, GravitationalParameter>(
            {big_dof, small_dof},
            {big_->gravitational_parameter(),
             small_->gravitational_parameter()});
    EXPECT_THAT(barycentre.velocity().Norm(),
                VanishesBefore(1 * Kilo(Metre) / Second, 0, 45));
    barycentre_trajectory.Append(t0_ + t, barycentre);
  }
  BodyCentredBodyDirectionDynamicFrame<ICRFJ2000Equator, BigSmallFrame>
      barycentric_from_discrete{
          ephemeris_.get(),
          [&t = barycentre_trajectory]() -> auto& { return t; },
          small_};
  BarycentricRotatingDynamicFrame<ICRFJ2000Equator, BigSmallFrame>
      barycentric_from_both_bodies{ephemeris_.get(), big_, small_};
  for (Time t = period_ / 32; t <= period_ / 2; t += period_ / 32) {
    auto const dof_from_discrete =
        barycentric_from_discrete.ToThisFrameAtTime(t0_ + t)(
            {ICRFJ2000Equator::origin, Velocity<ICRFJ2000Equator>{}});
    auto const dof_from_both_bodies =
        barycentric_from_both_bodies.ToThisFrameAtTime(t0_ + t)(
            {ICRFJ2000Equator::origin, Velocity<ICRFJ2000Equator>{}});
    EXPECT_THAT(
        (dof_from_discrete.position() - dof_from_both_bodies.position()).Norm(),
        VanishesBefore(1 * Kilo(Metre), 0, 15));
    EXPECT_THAT(
        (dof_from_discrete.velocity() - dof_from_both_bodies.velocity()).Norm(),
        VanishesBefore(1 * Kilo(Metre) / Second, 0, 93));
    // For the moment, the |BodyCentredBodyDirectionDynamicFrame| assumes that
    // its reference trajectories are free-falling, and gives us the wrong
    // geometric acceleration when this is not the case.
    auto const intrinsic_acceleration =
        ephemeris_->ComputeGravitationalAccelerationOnMasslessBody(
            ICRFJ2000Equator::origin +
                Displacement<ICRFJ2000Equator>({0 * Kilo(Metre),
                                                10.0 / 7.0 * Kilo(Metre),
                                                0 * Kilo(Metre)}),
            t0_ + t);
    EXPECT_THAT(
        (barycentric_from_discrete.GeometricAcceleration(t0_ + t,
                                                         dof_from_discrete) -
         barycentric_from_both_bodies.GeometricAcceleration(
             t0_ + t,
             dof_from_both_bodies)).Norm(),
         AlmostEquals(intrinsic_acceleration.Norm(), 0, 142));
  }
}

}  // namespace internal_body_centred_body_direction_dynamic_frame
}  // namespace physics
}  // namespace principia