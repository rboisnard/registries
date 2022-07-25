add_library(service SHARED)
target_sources(service
  PRIVATE
  Registry.cpp
  RegistryImpl.cpp
  Service.cpp
  ServiceList.cpp
  StandardPayload.cpp
  Status.cpp
  TokenPayload.cpp
  TxnStandardPayloadAdapter.cpp
  TxnStatusAdapter.cpp
  TxnTokenPayloadAdapter.cpp
  include/RegistryImpl.h
  include/TxnStandardPayloadAdapter.h
  include/TxnStatusAdapter.h
  include/TxnTokenPayloadAdapter.h

  PUBLIC
  include/svc/IRegistry.h
  include/svc/IStandardWrapper.h
  include/svc/ITokenWrapper.h
  include/svc/Registry.h
  include/svc/Service.h
  include/svc/ServiceList.h
  include/svc/StandardPayload.h
  include/svc/Status.h
  include/svc/TokenPayload.h
)
add_dependencies (service transaction)
target_include_directories(service
  PUBLIC
  include
)
target_link_libraries(service
  transaction
)

add_subdirectory(test)