#include <gtest/gtest.h>
#include <cmath>
#include <stdio.h>

#include "ert/ert.h"
#include "ert/fixed_point.h"

TEST(FixedPointTests, Convert) { 
    ASSERT_EQ(98304, Fixed32_FromFloat(1.5));
    ASSERT_EQ(205915, Fixed32_FromFloat(3.142));
}