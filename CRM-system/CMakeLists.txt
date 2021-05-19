# Minimum CMake required
cmake_minimum_required(VERSION 3.13)

project(CRM-system VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set (proto_name CRM-system)

# Get proto files
get_filename_component(proto "../${proto_name}.proto" ABSOLUTE)
get_filename_component(proto_dir "${proto}" DIRECTORY)

# Generate source files
set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.pb.cc")
set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.grpc.pb.cc")
set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.grpc.pb.h")
add_custom_command(
    OUTPUT "${proto_srcs}" "${proto_hdrs}" "${grpc_srcs}" "${grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
    --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
    -I "${proto_dir}"
    --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
    "${proto}"
    DEPENDS "${proto}"
)

#set(targets "${proto_name}_server" "${proto_name}_client")

# Include generated *.pb.h files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#foreach(target ${targets})
#    include_directories("${target}/include")
#    add_executable(${target} "${target}/${target}.cc" ${proto_srcs} ${grpc_srcs})
#    target_link_libraries(${target} PRIVATE ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
#    # Cannot do this because these directories are not available during CMake "compile time"
#    # target_include_directories(${proto_hdrs} ${grpc_hdrs})
#endforeach()

file(GLOB CPP_SERVER "${proto_name}_server/src_server/*")

#Server
include_directories("${proto_name}_server/include_server")
#add_executable("${proto_name}_server" "${proto_name}_server/${proto_name}_server.cc" ${proto_srcs} ${grpc_srcs})
add_executable("${proto_name}_server" ${CPP_SERVER} ${proto_srcs} ${grpc_srcs})
target_link_libraries("${proto_name}_server" ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
target_link_libraries("${proto_name}_server" LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries("${proto_name}_server" curl mysqlcppconn)
target_compile_features("${proto_name}_server" PRIVATE cxx_range_for)

#file(GLOB CPP "${proto_name}_client/include/*" "${proto_name}_client/src/*" )
file(GLOB CPP "${proto_name}_client/include/*" "${proto_name}_client/src/*" )

#Client
#include_directories("${proto_name}_client/include")
include_directories("CRM-system_client/include")
add_executable("${proto_name}_client" CRM-system_client/include/people.h ${CPP} ${proto_srcs} ${grpc_srcs})
target_link_libraries("${proto_name}_client" PRIVATE ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF} Qt5::Widgets)
