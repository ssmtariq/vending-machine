add_executable(
    WeatherService
    WeatherService.cpp
    ${THRIFT_GEN_CPP_DIR}/WeatherService.cpp
    ${THRIFT_GEN_CPP_DIR}/vending_machine_types.cpp
)

target_include_directories(
	WeatherService PRIVATE
)

target_link_libraries(
    WeatherService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
)

install(TARGETS WeatherService DESTINATION ./)
