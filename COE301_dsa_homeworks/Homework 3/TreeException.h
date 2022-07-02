#include <stdexcept>
#include <string>

class TreeException: public std::logic_error {
   public:
      TreeException(const std::string& message = "") : std::logic_error(message.c_str()) {}
};