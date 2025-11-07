# ============================================================================
# Llama Module
# Interacts with llm module
# ============================================================================

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
    LlamaEngine.h
    LlamaEngine.cpp
    LlamaEngine_p.h
    LlamaEngine_p.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/libs/llama.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        llama
)
