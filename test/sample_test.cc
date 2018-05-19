#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>


TEST_GROUP(TestGroupName) {
    void setup() { }
    void teardown() {
        mock().clear();
    }
};

/**
 * HAVE Initial environment
 * WHEN Perform an action
 * THEN This happens
 */
TEST(TestGroupName, Test_01) {
    CHECK_EQUAL("Expectation", "Expectation");
}
