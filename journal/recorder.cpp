﻿
#include "journal/recorder.hpp"

#include <filesystem>

#include "base/array.hpp"
#include "base/hexadecimal.hpp"
#include "glog/logging.h"

namespace principia {

using base::HexadecimalEncode;
using base::UniqueBytes;

namespace journal {

Recorder::Recorder(std::filesystem::path const& path)
    : stream_(path, std::ios::out) {
  CHECK(!stream_.fail()) << path;
}

Recorder::~Recorder() {
  stream_.close();
}

void Recorder::Write(serialization::Method const& method) {
  CHECK_LT(0, method.ByteSize()) << method.DebugString();
  UniqueBytes bytes(method.ByteSize());
  method.SerializeToArray(bytes.data.get(), static_cast<int>(bytes.size));

  auto const hexadecimal = HexadecimalEncode(bytes.get(),
                                             /*null_terminated=*/true);
  stream_ << hexadecimal.data.get() << "\n";
  stream_.flush();
}

void Recorder::Activate(base::not_null<Recorder*> const journal) {
  CHECK(active_recorder_ == nullptr);
  active_recorder_ = journal;
}

void Recorder::Deactivate() {
  CHECK(active_recorder_ != nullptr);
  delete active_recorder_;
  active_recorder_ = nullptr;
}

bool Recorder::IsActivated() {
  return active_recorder_ != nullptr;
}

thread_local Recorder* Recorder::active_recorder_ = nullptr;

}  // namespace journal
}  // namespace principia