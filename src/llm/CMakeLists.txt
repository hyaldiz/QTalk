# ============================================================================
# LLMEngine Module
# Interacts with llm module
# ============================================================================

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        AbstractLLMEngine.h
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
