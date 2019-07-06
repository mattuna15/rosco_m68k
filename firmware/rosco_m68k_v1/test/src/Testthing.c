#include "unity.h"
#include "thing.h"

void test_Thing() {
  TEST_ASSERT_EQUAL_HEX16(8, add(4,4));
  TEST_ASSERT_EQUAL_HEX16(3, add(1,2));
  TEST_ASSERT_EQUAL_HEX16(3, add(2,1));
}


void test_Fails() {
  TEST_ASSERT_EQUAL_HEX16(10, add(2,1));
}


int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_Thing);
  RUN_TEST(test_Fails);
  
  return UNITY_END();
}

