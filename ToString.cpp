#include <string>
#include <sstream>
#include <iomanip>
#include "ToString.h"

std::wstring ToString (int num)
{
  std::basic_ostringstream<wchar_t> oss;
  oss << std::setprecision(6) << num;
  return oss.str();
}
