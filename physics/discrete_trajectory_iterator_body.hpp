#pragma once

#include "physics/discrete_trajectory_iterator.hpp"

#include "geometry/named_quantities.hpp"

namespace principia {
namespace physics {
namespace internal_discrete_trajectory_iterator {

using geometry::Instant;

template<typename Frame>
DiscreteTrajectoryIterator<Frame>&
DiscreteTrajectoryIterator<Frame>::operator++() {
  CHECK(!is_at_end(point_));
  auto& point = iterator(point_);
  Instant const previous_time = point->time;
  do {
    if (point == --segment_->timeline_end()) {
      do {
        ++segment_;
      } while (!segment_.is_end() && segment_->timeline_empty());

      if (segment_.is_end()) {
        point_.reset();
        break;
      } else {
        point = segment_->timeline_begin();
      }
    } else {
      ++point;
    }
  } while (point->time == previous_time);
  return *this;
}

template<typename Frame>
DiscreteTrajectoryIterator<Frame>&
DiscreteTrajectoryIterator<Frame>::operator--() {
  bool const point_is_at_end = is_at_end(point_);
  if (point_is_at_end) {
    // Move the iterator to the end of the last segment.
    segment_ = --segment_.segments().end();
    point_ = segment_->timeline_end();
    // Now proceed with the decrement.
  }
  auto& point = iterator(point_);
  std::optional<Instant> const previous_time =
      point_is_at_end ? std::nullopt : std::make_optional(point->time);
  do {
    if (point == segment_->timeline_begin()) {
      CHECK(!segment_.is_begin());
      --segment_;
      point = --segment_->timeline_end();
    } else {
      --point;
    }
  } while (point->time == previous_time);
  return *this;
}

template<typename Frame>
DiscreteTrajectoryIterator<Frame>
DiscreteTrajectoryIterator<Frame>::operator++(int) {  // NOLINT
  auto const initial = *this;
  ++*this;
  return initial;
}

template<typename Frame>
DiscreteTrajectoryIterator<Frame>
DiscreteTrajectoryIterator<Frame>::operator--(int) {  // NOLINT
  auto const initial = *this;
  --*this;
  return initial;
}

template<typename Frame>
typename internal_discrete_trajectory_types::Timeline<Frame>::value_type const&
DiscreteTrajectoryIterator<Frame>::operator*() const {
  CHECK(!is_at_end(point_));
  return *iterator(point_);
}

template<typename Frame>
typename internal_discrete_trajectory_types::Timeline<Frame>::value_type const*
DiscreteTrajectoryIterator<Frame>::operator->() const {
  CHECK(!is_at_end(point_));
  return &*iterator(point_);
}

template<typename Frame>
bool DiscreteTrajectoryIterator<Frame>::operator==(
    DiscreteTrajectoryIterator const& other) const {
  if (is_at_end(point_)) {
    return segment_ == other.segment_ && is_at_end(other.point_);
  } else if (is_at_end(other.point_)) {
    return false;
  } else {
    return iterator(point_)->time == iterator(other.point_)->time;
  }
}

template<typename Frame>
bool DiscreteTrajectoryIterator<Frame>::operator!=(
    DiscreteTrajectoryIterator const& other) const {
  return !operator==(other);
}

template<typename Frame>
DiscreteTrajectoryIterator<Frame>::DiscreteTrajectoryIterator(
    DiscreteTrajectorySegmentIterator<Frame> const segment,
    OptionalTimelineConstIterator const point)
    : segment_(segment),
      point_(point) {
  bool incremented_segment = false;
  while (!segment_.is_end() && segment_->timeline_empty()) {
    ++segment_;
    incremented_segment = true;
  }
  if (segment_.is_end()) {
    point_.reset();
  } else if (incremented_segment) {
    point_ = segment_->timeline_begin();
  }
}

template<typename Frame>
bool DiscreteTrajectoryIterator<Frame>::is_at_end(
    OptionalTimelineConstIterator const point) {
  return !point.has_value();
}

template<typename Frame>
typename DiscreteTrajectoryIterator<Frame>::Timeline::const_iterator&
DiscreteTrajectoryIterator<Frame>::iterator(
    OptionalTimelineConstIterator& point) {
  DCHECK(point.has_value());
  return point.value();
}

template<typename Frame>
typename DiscreteTrajectoryIterator<Frame>::Timeline::const_iterator const&
DiscreteTrajectoryIterator<Frame>::iterator(
    OptionalTimelineConstIterator const& point) {
  DCHECK(point.has_value());
  return point.value();
}

}  // namespace internal_discrete_trajectory_iterator
}  // namespace physics
}  // namespace principia