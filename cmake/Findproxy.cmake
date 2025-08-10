include(FetchContent)
FetchContent_Declare(
  proxy
  GIT_TAG main
  GIT_REPOSITORY https://github.com/microsoft/proxy.git
  GIT_SHALLOW TRUE
  )
FetchContent_MakeAvailable(proxy)
