add_executable(sip SIP.cpp
)

target_link_libraries(sip ${llvm_libs} ${SVF_LIB})