﻿#pragma once

#include "testing_utilities/trajectory_factories.hpp"

#include "geometry/frame.hpp"
#include "geometry/grassmann.hpp"
#include "geometry/named_quantities.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "quantities/elementary_functions.hpp"
#include "quantities/si.hpp"
#include "testing_utilities/almost_equals.hpp"
#include "testing_utilities/vanishes_before.hpp"

namespace principia {
namespace testing_utilities {

using geometry::Frame;
using geometry::Handedness;
using geometry::Inertial;
using geometry::InnerProduct;
using geometry::Instant;
using geometry::Position;
using geometry::Velocity;
using quantities::Sqrt;
using quantities::si::Metre;
using quantities::si::Radian;
using quantities::si::Second;

class TrajectoryFactoriesTest : public ::testing::Test {
 protected:
  using World = Frame<serialization::Frame::TestTag,
                      Inertial,
                      Handedness::Right,
                      serialization::Frame::TEST>;
};

TEST_F(TrajectoryFactoriesTest, NewLinearTrajectory) {
  auto const trajectory = NewLinearTrajectory<World>(
      /*v=*/Velocity<World>(
          {6 * Metre / Second, 5 * Metre / Second, 4 * Metre / Second}),
      /*Δt=*/0.1 * Second,
      /*t1=*/Instant() + 4 * Second,
      /*t2=*/Instant() + 42 * Second);

  for (auto const& [time, degrees_of_freedom] : *trajectory) {
    Position<World> const& position = degrees_of_freedom.position();
    Velocity<World> const& velocity = degrees_of_freedom.velocity();

    EXPECT_THAT(
        (position - World::origin).Norm(),
        AlmostEquals((time - Instant()) * Sqrt(77) * Metre / Second, 0, 1));
    EXPECT_THAT(velocity.Norm(), AlmostEquals(Sqrt(77) * Metre / Second, 0, 0));
  }
  EXPECT_THAT(trajectory->begin()->time,
              AlmostEquals(Instant() + 4 * Second, 0));
  EXPECT_THAT(trajectory->back().time,
              AlmostEquals(Instant() + 41.9 * Second, 46));
  EXPECT_EQ(380, trajectory->Size());
}

TEST_F(TrajectoryFactoriesTest, NewCircularTrajectory) {
  auto const trajectory = NewCircularTrajectory<World>(
      /*ω=*/3 * Radian / Second,
      /*r=*/2 * Metre,
      /*Δt=*/0.1 * Second,
      /*t1=*/Instant() + 4 * Second,
      /*t2=*/Instant() + 42 * Second);

  for (auto const& [time, degrees_of_freedom] : *trajectory) {
    Position<World> const& position = degrees_of_freedom.position();
    Velocity<World> const& velocity = degrees_of_freedom.velocity();

    EXPECT_THAT((position - World::origin).Norm(),
                AlmostEquals(2 * Metre, 0, 1));
    EXPECT_THAT(InnerProduct(position - World::origin, velocity),
                VanishesBefore(1 * Metre * Metre / Second, 0, 8));
  }
  EXPECT_THAT(trajectory->begin()->time,
              AlmostEquals(Instant() + 4 * Second, 0));
  EXPECT_THAT(trajectory->back().time,
              AlmostEquals(Instant() + 41.9 * Second, 46));
  EXPECT_EQ(380, trajectory->Size());
}

}  // namespace testing_utilities
}  // namespace principia