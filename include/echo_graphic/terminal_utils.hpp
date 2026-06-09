#pragma once

#include <cstddef>
#include <deque>
#include <optional>
#include <string>
#include <vector>

namespace echo_graphic
{

bool command_exists(const char * command);
std::optional<double> get_value(const std::vector<double> & values, size_t index);
std::string format_number(std::optional<double> value, int width, int precision);
std::string range_bar(std::optional<double> position, size_t width = 6);
std::string sparkline(const std::deque<double> & values, size_t width = 9);

}  // namespace echo_graphic
