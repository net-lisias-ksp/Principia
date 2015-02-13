
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "base/hexadecimal.hpp"
#include "base/not_null.hpp"

// Must come last to avoid conflicts when defining the CHECK macros.
#include "benchmark/benchmark.h"

using principia::base::not_null;
using principia::base::HexadecimalDecode;
using principia::base::HexadecimalEncode;

namespace principia {
namespace benchmarks {

static char const kPiHexadecimalDigits[] =
"3243f6a8885a308d313198a2e03707344a4093822299f31d0082efa98ec4e6c89452821e63"
"8d01377be5466cf34e90c6cc0ac29b7c97c50dd3f84d5b5b54709179216d5d98979fb1bd13"
"10ba698dfb5ac2ffd72dbd01adfb7b8e1afed6a267e96ba7c9045f12c7f9924a19947b3916"
"cf70801f2e2858efc16636920d871574e69a458fea3f4933d7e0d95748f728eb658718bcd5"
"882154aee7b54a41dc25a59b59c30d5392af26013c5d1b023286085f0ca417918b8db38ef8"
"e79dcb0603a180e6c9e0e8bb01e8a3ed71577c1bd314b2778af2fda55605c60e65525f3aa5"
"5ab945748986263e8144055ca396a2aab10b6b4cc5c341141e8cea15486af7c72e993b3ee1"
"411636fbc2a2ba9c55d741831f6ce5c3e169b87931eafd6ba336c24cf5c7a3253812895867"
"73b8f48986b4bb9afc4bfe81b6628219361d809ccfb21a991487cac605dec8032ef845d5de"
"98575b1dc262302eb651b8823893e81d396acc50f6d6ff383f442392e0b4482a484200469c"
"8f04a9e1f9b5e21c66842f6e96c9a670c9c61abd388f06a51a0d2d8542f68960fa728ab513"
"3a36eef0b6c137a3be4ba3bf0507efb2a98a1f1651d39af017666ca593e82430e888cee861"
"9456f9fb47d84a5c33b8b5ebee06f75d885c12073401a449f56c16aa64ed3aa62363f77061"
"bfedf72429b023d37d0d724d00a1248db0fead3";

static char const kPiBytes[] =
"\x32\x43\xf6\xa8\x88\x5a\x30\x8d\x31\x31\x98\xa2\xe0\x37\x07\x34\x4a\x40"
"\x93\x82\x22\x99\xf3\x1d\x00\x82\xef\xa9\x8e\xc4\xe6\xc8\x94\x52\x82\x1e"
"\x63\x8d\x01\x37\x7b\xe5\x46\x6c\xf3\x4e\x90\xc6\xcc\x0a\xc2\x9b\x7c\x97"
"\xc5\x0d\xd3\xf8\x4d\x5b\x5b\x54\x70\x91\x79\x21\x6d\x5d\x98\x97\x9f\xb1"
"\xbd\x13\x10\xba\x69\x8d\xfb\x5a\xc2\xff\xd7\x2d\xbd\x01\xad\xfb\x7b\x8e"
"\x1a\xfe\xd6\xa2\x67\xe9\x6b\xa7\xc9\x04\x5f\x12\xc7\xf9\x92\x4a\x19\x94"
"\x7b\x39\x16\xcf\x70\x80\x1f\x2e\x28\x58\xef\xc1\x66\x36\x92\x0d\x87\x15"
"\x74\xe6\x9a\x45\x8f\xea\x3f\x49\x33\xd7\xe0\xd9\x57\x48\xf7\x28\xeb\x65"
"\x87\x18\xbc\xd5\x88\x21\x54\xae\xe7\xb5\x4a\x41\xdc\x25\xa5\x9b\x59\xc3"
"\x0d\x53\x92\xaf\x26\x01\x3c\x5d\x1b\x02\x32\x86\x08\x5f\x0c\xa4\x17\x91"
"\x8b\x8d\xb3\x8e\xf8\xe7\x9d\xcb\x06\x03\xa1\x80\xe6\xc9\xe0\xe8\xbb\x01"
"\xe8\xa3\xed\x71\x57\x7c\x1b\xd3\x14\xb2\x77\x8a\xf2\xfd\xa5\x56\x05\xc6"
"\x0e\x65\x52\x5f\x3a\xa5\x5a\xb9\x45\x74\x89\x86\x26\x3e\x81\x44\x05\x5c"
"\xa3\x96\xa2\xaa\xb1\x0b\x6b\x4c\xc5\xc3\x41\x14\x1e\x8c\xea\x15\x48\x6a"
"\xf7\xc7\x2e\x99\x3b\x3e\xe1\x41\x16\x36\xfb\xc2\xa2\xba\x9c\x55\xd7\x41"
"\x83\x1f\x6c\xe5\xc3\xe1\x69\xb8\x79\x31\xea\xfd\x6b\xa3\x36\xc2\x4c\xf5"
"\xc7\xa3\x25\x38\x12\x89\x58\x67\x73\xb8\xf4\x89\x86\xb4\xbb\x9a\xfc\x4b"
"\xfe\x81\xb6\x62\x82\x19\x36\x1d\x80\x9c\xcf\xb2\x1a\x99\x14\x87\xca\xc6"
"\x05\xde\xc8\x03\x2e\xf8\x45\xd5\xde\x98\x57\x5b\x1d\xc2\x62\x30\x2e\xb6"
"\x51\xb8\x82\x38\x93\xe8\x1d\x39\x6a\xcc\x50\xf6\xd6\xff\x38\x3f\x44\x23"
"\x92\xe0\xb4\x48\x2a\x48\x42\x00\x46\x9c\x8f\x04\xa9\xe1\xf9\xb5\xe2\x1c"
"\x66\x84\x2f\x6e\x96\xc9\xa6\x70\xc9\xc6\x1a\xbd\x38\x8f\x06\xa5\x1a\x0d"
"\x2d\x85\x42\xf6\x89\x60\xfa\x72\x8a\xb5\x13\x3a\x36\xee\xf0\xb6\xc1\x37"
"\xa3\xbe\x4b\xa3\xbf\x05\x07\xef\xb2\xa9\x8a\x1f\x16\x51\xd3\x9a\xf0\x17"
"\x66\x6c\xa5\x93\xe8\x24\x30\xe8\x88\xce\xe8\x61\x94\x56\xf9\xfb\x47\xd8"
"\x4a\x5c\x33\xb8\xb5\xeb\xee\x06\xf7\x5d\x88\x5c\x12\x07\x34\x01\xa4\x49"
"\xf5\x6c\x16\xaa\x64\xed\x3a\xa6\x23\x63\xf7\x70\x61\xbf\xed\xf7\x24\x29"
"\xb0\x23\xd3\x7d\x0d\x72\x4d\x00\xa1\x24\x8d\xb0\xfe\xad";

template<typename Container>
std::enable_if_t<
    std::is_convertible<typename Container::value_type, uint8_t>::value,
    void>
HexadecimalEncodeNoMemcpy(Container const& input, not_null<Container*> output) {
  Container const& bytes = input;
  Container digits;
  digits.resize(bytes.size() * 2);
  // The following was undefined behaviour pre-C++11, but it is now well-defined
  // even when |digits.size() == 0|.  We do not use |digits.data()| because this
  // only works for |std::vector| (it is read-only in a |std::basic_string|).
  char* digit = &digits[0];
  for (uint8_t const byte : bytes) {
    // The following is four times faster than copying both bytes by hand.
    const char* reference_digit = base::kByteToHexadecimalDigits[byte];
    *digit = *reference_digit;
    *++digit = *++reference_digit;
    ++digit;
  }
  *output = std::move(digits);
}

void EncodePiNoMemcpy(not_null<benchmark::State*> const state,
              not_null<bool*> const correct) {
  state->PauseTiming();
  std::string const pi_bytes(kPiBytes, 500);
  std::string digits;
  state->ResumeTiming();
  HexadecimalEncodeNoMemcpy<std::string>(pi_bytes, &digits);
  state->PauseTiming();
  *correct = digits == kPiHexadecimalDigits;
  state->ResumeTiming();
}

void BM_EncodePiNoMemcpy(benchmark::State& state) {  // NOLINT(runtime/references)
  bool correct;
  while (state.KeepRunning()) {
    EncodePiNoMemcpy(&state, &correct);
  }
  std::stringstream ss;
  ss << correct;
  state.SetLabel(ss.str());
}

BENCHMARK(BM_EncodePiNoMemcpy);

void EncodePi(not_null<benchmark::State*> const state,
              not_null<bool*> const correct) {
  state->PauseTiming();
  std::string const pi_bytes(kPiBytes, 500);
  std::string digits;
  state->ResumeTiming();
  HexadecimalEncode<std::string>(pi_bytes, &digits);
  state->PauseTiming();
  *correct = digits == kPiHexadecimalDigits;
  state->ResumeTiming();
}

void BM_EncodePi(benchmark::State& state) {  // NOLINT(runtime/references)
  bool correct;
  while (state.KeepRunning()) {
    EncodePi(&state, &correct);
  }
  std::stringstream ss;
  ss << correct;
  state.SetLabel(ss.str());
}

BENCHMARK(BM_EncodePi);

}  // namespace benchmarks
}  // namespace principia
