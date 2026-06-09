#include "echo_graphic/dds_transport.hpp"

#include <cstdlib>

namespace echo_graphic
{

void configure_default_dds_transport()
{
  setenv("FASTDDS_BUILTIN_TRANSPORTS", "UDPv4", 0);
}

}  // namespace echo_graphic
