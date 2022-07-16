add_library(transaction SHARED)

target_sources(transaction
  PRIVATE
  Registry.cpp
  RegistryImpl.cpp
  StandardPayload.cpp
  TokenPayload.cpp
  include/RegistryImpl.h

  PUBLIC
  include/txn/IRegistry.h
  include/txn/IStandardWrapper.h
  include/txn/ITokenWrapper.h
  include/txn/Registry.h
  include/txn/Service.h
  include/txn/StandardPayload.h
  include/txn/TokenPayload.h
)

target_include_directories(transaction
  PUBLIC
  include
)