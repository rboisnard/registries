add_library(transaction SHARED)
target_sources(transaction
  PRIVATE
  Registry.cpp
  RegistryImpl.cpp
  StandardPayload.cpp
  StandardService.cpp
  Status.cpp
  TokenPayload.cpp
  TokenService.cpp
  include/RegistryImpl.h

  PUBLIC
  include/txn/IRegistry.h
  include/txn/IStandardWrapper.h
  include/txn/ITokenWrapper.h
  include/txn/Registry.h
  include/txn/StandardPayload.h
  include/txn/StandardService.h
  include/txn/Status.h
  include/txn/TokenPayload.h
  include/txn/TokenService.h
)
target_include_directories(transaction
  PUBLIC
  include
)
target_compile_options(transaction PRIVATE
  -Wall -Wextra -Werror
)

add_subdirectory(test)