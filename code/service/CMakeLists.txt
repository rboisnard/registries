add_library(service SHARED)
target_sources(service
  PRIVATE
  Callback.cpp
  Registry.cpp
  RegistryImpl.cpp
  include/RegistryImpl.h

  PUBLIC
  include/svc/Callback.h
  include/svc/ICallbackWrapper.h
  include/svc/IRegistry.h
  include/svc/Payload.h
  include/svc/Registry.h
)
add_dependencies (service transaction)
target_include_directories(service
  PUBLIC
  include
)
target_link_libraries(service
  transaction
)

#add_subdirectory(test)