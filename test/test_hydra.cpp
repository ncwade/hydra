#include "hydra.hpp"
#include <gtest/gtest.h>

using namespace std::literals;

// Define variables we need for asserts.
std::string dataPublished = "";
const std::string testData = "TEST";
const std::string testPath = "/world/test";

// Define functions we need for testing.
auto publishData (std::atomic<bool> &exit, Hydra<std::string> &parent) {
      parent.push_data(testPath,testData);
      return true;
}

auto get_string (std::string data) {
   dataPublished = data;
   return true;
}

// Define all needed tests.
TEST(TestHydra, SubscribeEnlist) {
   // Object under test.
   Hydra<std::string> vonStrucker(1);

   // Reset variable.
   dataPublished = "";

   vonStrucker.subscribe(testPath, get_string);
   vonStrucker.enlist(publishData);

   // Sleep to allow data to arrive.
   std::this_thread::sleep_for(1ms);

   ASSERT_EQ(testData,dataPublished);
}

TEST(TestHydra, SubscribePush) {
   // Object under test.
   Hydra<std::string> vonStrucker(1);

   // Reset variable.
   dataPublished = "";

   vonStrucker.subscribe(testPath, get_string);
   vonStrucker.push_data(testPath,testData);

   // Sleep to allow data to arrive.
   std::this_thread::sleep_for(1ms);

   ASSERT_EQ(testData,dataPublished);
}
