#include <tl/expected.hpp>

tl::expected<int, const char*> maybe_do_something(int i) {
  if (i < 5) {
    return 0;
  }
  else {
    return tl::make_unexpected("Uh oh");
  }
}

int main(int argc, char** argv) {
  (void)argv;

  return maybe_do_something(0).value_or(-1);
}