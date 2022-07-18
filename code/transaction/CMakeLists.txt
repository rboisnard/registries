add_library(transaction SHARED)
target_sources(transaction
  PRIVATE
  Registry.cpp
  RegistryImpl.cpp
  Service.cpp
  StandardPayload.cpp
  Status.cpp
  TokenPayload.cpp
  include/RegistryImpl.h

  PUBLIC
  include/txn/IRegistry.h
  include/txn/IStandardWrapper.h
  include/txn/ITokenWrapper.h
  include/txn/Registry.h
  include/txn/Service.h
  include/txn/StandardPayload.h
  include/txn/Status.h
  include/txn/TokenPayload.h
)
target_include_directories(transaction
  PUBLIC
  include
)

add_subdirectory(test)