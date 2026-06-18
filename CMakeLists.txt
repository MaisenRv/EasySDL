cmake_minimum_required(VERSION 3.15)
project(EasySDL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

# Detectar Plataforma
if(EMSCRIPTEN)
    set(IS_WEB TRUE)
else()
    set(IS_WEB FALSE)
endif()


add_subdirectory(third_party/BitMth)
# ---------------------------------------------------------------------------
# Control de Selección de Demo
# ---------------------------------------------------------------------------
# Definimos la variable DEMO. Si no pasas ninguna, por defecto usará "template"
set(DEMO "template" CACHE STRING "Nombre del demo a compilar (ej: interpolation, Pendulum, pruebas)")
message(STATUS ">> Configurando proyecto para compilar el DEMO: ${DEMO} <<")

# ---------------------------------------------------------------------------
# Cabeceras globales del proyecto
# ---------------------------------------------------------------------------
add_library(project_headers INTERFACE)
target_include_directories(project_headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---------------------------------------------------------------------------
# Configuración de Dependencias según Plataforma
# ---------------------------------------------------------------------------
if(NOT IS_WEB)
    # --- Local (g++) ---
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)

    add_library(native_deps INTERFACE)
    target_include_directories(native_deps INTERFACE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
    target_link_libraries(native_deps INTERFACE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
else()
    # --- Web (em++) ---
    add_link_options(
        "-O2" "-sWASM=1" "-sUSE_SDL=2" "-sUSE_SDL_TTF=2" "-sMAX_WEBGL_VERSION=2"
        "-sALLOW_MEMORY_GROWTH=1" "-sUSE_WEBGL2=1" "-sMODULARIZE=1"
        "-sEXPORTED_RUNTIME_METHODS=['cwrap','ccall']"
        "-sEXPORTED_FUNCTIONS=['_main','_registerWindow','_getWindowWidth','_getWindowHeight','_setPositionMouse','_setClick']"
        # Pre-carga de assets
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/vertexShader.glsl@assets/shaders/vertexShader.glsl"
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/fragmentShader.glsl@assets/shaders/fragmentShader.glsl"
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/vertexTextShader.glsl@assets/shaders/vertexTextShader.glsl"
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/fragmentTextShader.glsl@assets/shaders/fragmentTextShader.glsl"
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/Poppins-Regular.ttf@assets/fonts/Poppins-Regular.ttf"
    )
endif()

# ---------------------------------------------------------------------------
# Lógica de Compilación Condicional por Nombre de Demo
# ---------------------------------------------------------------------------
if(NOT IS_WEB)
    # --- COMPILACIÓN LOCAL ---
    
    if(DEMO STREQUAL "interpolation")
        add_executable(app_bin demos/interpolation/main.cpp)
    elseif(DEMO STREQUAL "Pendulum")
        add_executable(app_bin demos/Pendulum/main.cpp)
    elseif(DEMO STREQUAL "pruebas")
        add_executable(app_bin demos/pruebasLocal/main.cpp)
    else()
        # Fallback por si pones un nombre que no tiene versión local directa
        message(WARNING "No se encontró config local exacta para '${DEMO}'. Usando template.")
        add_executable(app_bin demos/template/main.cpp)
    endif()

    target_link_libraries(app_bin PRIVATE project_headers native_deps BitMth)
    set_target_properties(app_bin PROPERTIES 
        OUTPUT_NAME "app" # Para que siempre se llame 'app' en ./bin/
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    )

else()
    # --- COMPILACIÓN WEB ---
    
    if(DEMO STREQUAL "interpolation")
        add_executable(web_bin demos/interpolationWeb/main.cpp)
    elseif(DEMO STREQUAL "Pendulum")
        add_executable(web_bin demos/Pendulum/main.cpp)
    elseif(DEMO STREQUAL "pruebas")
        add_executable(web_bin demos/pruebas/main.cpp)
    else()
        add_executable(web_bin demos/template/main.cpp)
    endif()

    target_link_libraries(web_bin PRIVATE project_headers BitMth)
    set_target_properties(web_bin PROPERTIES 
        OUTPUT_NAME "${DEMO}" # Se llamará como el demo (ej: Pendulum.js)
        SUFFIX ".js"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/web"
    )
endif()