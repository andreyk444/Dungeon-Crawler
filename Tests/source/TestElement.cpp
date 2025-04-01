#include <gtest/gtest.h>

#include <Element/element.h>

using namespace Tramp;



TEST(ConstructorTest, Element){
    Water water("Water");
    Fire fire("Fire");
    Holy holy("Holy");
    Devil devil("Devil");

    ASSERT_EQ(water.getName(), "Water");
    ASSERT_EQ(fire.getName(), "Fire");
    ASSERT_EQ(holy.getName(), "Holy");
    ASSERT_EQ(devil.getName(), "Devil");


    auto waterPtr = std::make_shared<Water>(water);
    WeakElement weakFire(waterPtr, 2.3);


    ASSERT_EQ(weakFire.getMultipleer(), 2.3);
    ASSERT_EQ(weakFire.getElement(), waterPtr);



}