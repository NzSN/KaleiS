#ifndef KALEIS_BASE_CHECK_H_
#define KALEIS_BASE_CHECK_H_

#include <string>
#include <exception>

struct FailToCheck : public std::exception {
  FailToCheck(std::string msg):
    msg_{"Fail to check: " + msg} {}
  ~FailToCheck() {}

  const char* what() const noexcept {
    return "Failed to check";
  }

private:
  std::string msg_;
};

#define CHECK(COND)                             \
  ({                                            \
    do {                                        \
      if (!(COND)) {                              \
        throw FailToCheck(#COND);               \
      }                                         \
    } while (0);                                \
  })

#endif /* KALEIS_BASE_CHECK_H_ */
