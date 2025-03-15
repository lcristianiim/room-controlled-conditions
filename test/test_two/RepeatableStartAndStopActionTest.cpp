#include <Arduino.h>
#include <unity.h>


void setUp(void) {

}

void a()
{
    TEST_ASSERT_FALSE(false);
}

void setup()
{
    delay(1000); // service delay
    UNITY_BEGIN();

    RUN_TEST(a);

    UNITY_END(); // stop unit testing
}

void loop()
{
}