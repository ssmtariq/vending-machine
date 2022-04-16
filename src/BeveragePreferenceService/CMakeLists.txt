add_executable(
    BeveragePreferenceService
    BeveragePreferenceService.cpp
    ${THRIFT_GEN_CPP_DIR}/BeveragePreferenceService.cpp
    ${THRIFT_GEN_CPP_DIR}/vending_machine_types.cpp
)

target_include_directories(
	BeveragePreferenceService PRIVATE
)

target_link_libraries(
    BeveragePreferenceService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
)

install(TARGETS BeveragePreferenceService DESTINATION ./)