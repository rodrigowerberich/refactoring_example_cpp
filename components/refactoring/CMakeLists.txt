CMAKE_MINIMUM_REQUIRED(VERSION 3.10)


ADD_LIBRARY(refactoring 
    STATIC
    src/statement.cc
)

TARGET_INCLUDE_DIRECTORIES(refactoring
    PUBLIC
        inc
)

# TARGET_LINK_LIBRARIES(clonable_interface 
#     PUBLIC 
#         ooc_config
#         ooc_base
# )

ADD_SUBDIRECTORY(tst)