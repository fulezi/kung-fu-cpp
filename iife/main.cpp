
#include <cstdlib>
#include <string>

/**
 * This is the common case where you want to get a string but the content
 * depends on some inputs. Here you may think that the string cannot be constant
 * (while you actually don't have to modify it afterward).
 */
static void
string_non_const()
{
  std::string s;

  const int i = std::rand() % 3;
  switch (i) {
    case 1: s = "The number is odd"; break;
    case 2: s = "The number is even"; break;
    case 0: s = "The number is zero"; break;
  }
}

/**
 * But you can use IIFE (Immediately-invoked Function Expressions) or Lambda
 * created and called in place. Here the lambda does not leave longer than the
 * assignment operation.
 *
 * But...
 */
static void
string_with_const()
{
  const int         i = std::rand() % 3;
  const std::string s = [&i]() {
    switch (i) {
      case 1: return "The number is odd";
      case 2: return "The number is even";
      default: return "The number is zero";
    }
  }();
}

/**
 * ... You can even do more optimized. On the previous function the lambda was
 * returning a char*. To avoid any useless conversion you may specify the lambda
 * returns type.
 */
static void
string_with_const_optimized()
{
  const int         i = std::rand() % 3;
  const std::string s = [&i]() -> std::string {
    switch (i) {
      case 1: return "The number is odd";
      case 2: return "The number is even";
      default: return "The number is zero";
    }
  }();
}

int
main(int argc, char* argv[])
{
  string_non_const();

  string_with_const();

  string_with_const_optimized();

  return 0;
}
