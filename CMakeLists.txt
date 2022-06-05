project(Snake)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 17)

# рекурсивный сбор директорий в список
MACRO(get_directories_recursive return_list from)
    FILE(GLOB_RECURSE new_list ${from})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# рекурсивный сбор файлов из папок в список
MACRO(get_files_from_directories_recursive return_list from)
    FILE(GLOB_RECURSE new_list ${from})
    SET(all_files "")
    FOREACH(file_path ${new_list})
        SET(all_files ${all_files} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES all_files)
    SET(${return_list} ${all_files})
ENDMACRO()

# добавление header файлов рекурсивно
MACRO(include_directories_recursively from)
   get_directories_recursive(return_list "${from}/*.h")
   include_directories(${return_list})
ENDMACRO()

# добавление header файлов рекурсивно
MACRO(include_directories_recursively_hpp from)
   get_directories_recursive(return_list "${from}/*.hpp")
   include_directories(${return_list})
ENDMACRO()

# подключение файлов
include_directories_recursively_hpp("./libs")
include_directories_recursively("./src")
get_files_from_directories_recursive(SOURCE "./src/*.cpp")

# выходной файл
set(APP_FILE Snake)
add_executable(${APP_FILE} ${SOURCE})