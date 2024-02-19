cmake_minimum_required(VERSION 3.16)
project(pipeline)

set(CMAKE_CXX_STANDARD 17)

set(itk_components
        WebAssemblyInterface
        ITKCommon
        ITKImageGrid
)
if (NOT EMSCRIPTEN)
    set(itk_components
            ${itk_components}
            ITKIOMeta
    )
endif()
find_package(ITK REQUIRED
        COMPONENTS ${itk_components}
)
include(${ITK_USE_FILE})

add_executable(pad_bug main.cpp)
target_link_libraries(pad_bug PUBLIC ${ITK_LIBRARIES})

