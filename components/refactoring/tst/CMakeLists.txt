ADD_EXECUTABLE(refactoring_tst 
    main.cc
    test_refactoring.cc
)

ADD_TEST(NAME refactoring_tst COMMAND refactoring_tst)

#TARGET_INCLUDE_DIRECTORIES(refactoring_tst
#    PUBLIC
#        .
#)

TARGET_LINK_LIBRARIES(refactoring_tst 
    PUBLIC 
        gtest
        gmock
        refactoring
)