project(${PROJECT_NAME}-main)

add_executable(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)

add_subdirectory(source)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/source)

target_link_libraries(${PROJECT_NAME}
        HarudioEngine::HarudioEngine
        )

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
