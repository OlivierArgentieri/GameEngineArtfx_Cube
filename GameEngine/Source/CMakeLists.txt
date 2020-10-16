# Settings
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Include/GL)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Include/GLFW)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Include/IMGUI)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Include/glm)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/GameEngine/Header)

# Files
FILE(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
FILE(GLOB_RECURSE ENGINE_HEADERS *.h *.hpp *.inl)

# imgui include folder
FILE(GLOB IMGUI ${CMAKE_SOURCE_DIR}/Include/ImGUI/*.*)

# glm
FILE(GLOB GLM ${CMAKE_SOURCE_DIR}/Include/glm/*.*)

# ge_window folder
FILE(GLOB GE_WINDOW ${CMAKE_SOURCE_DIR}/GameEngine/Window/*.*)

# ge_color folder
FILE(GLOB GE_COLOR ${CMAKE_SOURCE_DIR}/GameEngine/Color/*.*)

# ge_renderer folder
FILE(GLOB GE_RENDERER ${CMAKE_SOURCE_DIR}/GameEngine/Renderer/*.*)

# ge_game folder
FILE(GLOB GE_GAME ${CMAKE_SOURCE_DIR}/GameEngine/Game/*.*)

# ge_component folder
FILE(GLOB GE_COMPONENT ${CMAKE_SOURCE_DIR}/GameEngine/Component/*.*)


# ge_CustomObject folder
FILE(GLOB GE_CUSTOM_COMP_ROTATE_CUBE ${CMAKE_SOURCE_DIR}/GameEngine/Component/Custom/RotateCube/*.*)
FILE(GLOB GE_CUSTOM_COMP_QUAD ${CMAKE_SOURCE_DIR}/GameEngine/Component/Custom/Quad/*.*)


# ge_transform folder
FILE(GLOB GE_TRANSFORM ${CMAKE_SOURCE_DIR}/GameEngine/Transform/*.*)

# ge_common folder
FILE(GLOB GE_COMMON ${CMAKE_SOURCE_DIR}/GameEngine/Common/*.*)

# ge_Time folder
FILE(GLOB GE_TIME ${CMAKE_SOURCE_DIR}/GameEngine/Time/*.*)

# ge_Shaders_Files folder
FILE(GLOB GE_SHADERS_FILES ${CMAKE_SOURCE_DIR}/Resources/Shaders/*.*)

# Utils folder
FILE(GLOB UTILS ${CMAKE_SOURCE_DIR}/GameEngine/Utils/*.*)

# Input folder
FILE(GLOB INPUTS ${CMAKE_SOURCE_DIR}/GameEngine/Input/*.*)

ADD_EXECUTABLE(GameEngine
	${ENGINE_SOURCES}
	${ENGINE_HEADERS}
	${IMGUI}
	${GLM}
	${GE_WINDOW}
	${GE_COLOR}
	${GE_RENDERER}
	${GE_GAME}

	${GE_COMPONENT}
	${GE_CUSTOM_COMP_ROTATE_CUBE}
	${GE_CUSTOM_COMP_QUAD}

	${GE_TRANSFORM}
	${GE_COMMON}
	${GE_SHADERS_FILES}
	${GE_TIME}
	${UTILS}
	${INPUTS}
) 
TARGET_LINK_LIBRARIES(GameEngine glfw3 opengl32 User32 Gdi32 Shell32 glew32s)

# Add filters
SOURCE_GROUP(Include\\IMGUI FILES ${IMGUI})
SOURCE_GROUP(GameEngine\\Window FILES ${GE_WINDOW})
SOURCE_GROUP(GameEngine\\Color FILES ${GE_COLOR})
SOURCE_GROUP(GameEngine\\Renderer FILES ${GE_RENDERER})
SOURCE_GROUP(GameEngine\\Game FILES ${GE_GAME})
SOURCE_GROUP(GameEngine\\Component FILES ${GE_COMPONENT})
SOURCE_GROUP(GameEngine\\Component\\Custom\\RotateCube FILES ${GE_CUSTOM_COMP_ROTATE_CUBE})
SOURCE_GROUP(GameEngine\\Component\\Custom\\Quad FILES ${GE_CUSTOM_COMP_QUAD})

SOURCE_GROUP(GameEngine\\Transform FILES ${GE_TRANSFORM})
SOURCE_GROUP(GameEngine\\Common FILES ${GE_COMMON})
SOURCE_GROUP(GameEngine\\Time FILES ${GE_TIME})
SOURCE_GROUP(GameEngine\\Utils FILES ${UTILS})
SOURCE_GROUP(GameEngine\\Inputs FILES ${INPUTS})

SOURCE_GROUP(Resources\\Shaders FILES ${GE_SHADERS_FILES})


# Compile option
TARGET_COMPILE_DEFINITIONS(GameEngine PUBLIC GLEW_STATIC)

# Copy shaders file to Binary_build project
add_custom_command(
   TARGET GameEngine POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Resources/Shaders" "${CMAKE_BINARY_DIR}/GameEngine/Source" 
)