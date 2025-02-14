#include "gtest/gtest.h"
#include "rapidcheck.h"
#include "rapidcheck/gtest.h"

#include "ast_generator.h"

namespace Kaleis::AST {

RC_GTEST_PROP(ASTGenerator, Basics, ()) {
  ASTGenerator gen;
}

} // Kaleis::AST
