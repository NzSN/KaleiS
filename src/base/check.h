#ifndef KALEIS_BASE_CHECK_H_
#define KALEIS_BASE_CHECK_H_

#include <string>
#include <exception>

struct FailToCheck : public std::exception {
  FailToCheck(std::string msg):
    msg_{"Fail to check: " + msg} {}
  ~FailToCheck() {}

  const char* what() const noexcept {
    return msg_.c_str();
  }

private:
  std::string msg_;
};

#define CHECK(COND)                                            \
  ({                                                           \
    do {                                                       \
      if (!(COND)) {                                           \
        throw FailToCheck(std::string(#COND) +                 \
                          " at " + std::string{__FILE__} + ":" \
                          + std::to_string(__LINE__));         \
      }                                                        \
    } while (0);                                               \
  })

#endif /* KALEIS_BASE_CHECK_H_ */
