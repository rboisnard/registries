//#include <dlfcn.h>
#include <gtest/gtest.h>

#include "txn/Registry.h"

TEST(DirectRegistry, CreateRegistry) {
  txn::Registry* pRegistry = new txn::Registry();
  EXPECT_TRUE(pRegistry != nullptr);
  delete pRegistry;
}

//int main(
//  [[maybe_unused]] int argc,
//  [[maybe_unused]] char* argv[]
//) {
//  // TODO: get lib name from config
//  void* handle = dlopen("libservice.so", RTLD_NOW);
//  if (!handle) {
//    return 1;
//  }
//  dlerror();  // reset errors
//
//  // TODO: get init function name from config
//  txn::initializer_t initializer = (txn::initializer_t)dlsym(handle, "lib_init");
//  if (dlerror()) {
//    dlclose(handle);
//    return 1;
//  }
//
//  txn::Registry registry;
//  initializer(registry);
//}