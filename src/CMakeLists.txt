cmake_minimum_required(VERSION 3.6)
project(src_run)

find_package(Boost 1.61.0)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(BoostTest main.cpp)
target_link_libraries(BoostTest ${Boost_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        filters/CompositeKeyProbabilityFilter.cpp
        filters/CompositeKeyProbabilityFilter.h
        filters/KeyProbabilityFilter.cpp
        filters/KeyProbabilityFilter.h
        filters/KeyProbabilitySet.cpp
        filters/KeyProbabilitySet.h
        filters/MultiKeyProbabilityFilter.cpp
        filters/MultiKeyProbabilityFilter.h
        filters/SingleKeyProbabilityFilter.cpp
        filters/SingleKeyProbabilityFilter.h
        filters/SpiralKeyProbabilityFilter.cpp
        filters/SpiralKeyProbabilityFilter.h
        Accuracy.cpp
        Accuracy.h
        Bpm.cpp
        Bpm.h
        DetectedKey.cpp
        DetectedKey.h
        key/Key.cpp
        key/Key.h
        key/KeyCode.cpp
        key/KeyCode.h
        key/KeyRelation.cpp
        key/KeyRelation.h
        key/ShiftedKeyNotation.cpp
        key/ShiftedKeyNotation.h
        KeyDetectionMatrix.cpp
        KeyDetectionMatrix.h
        KeyDetector.cpp
        KeyDetector.h
        KeyProbability.cpp
        KeyProbability.h
        RectangularVectors.h
        stringbuilder.h
        util/Semaphore.h
        util/Semaphore.cpp
        util/SortObjectWrapper.cpp
        util/SortObjectWrapper.h
        util/Task.cpp
        util/Task.h
        util/TaskProgressListener.cpp
        util/TaskProgressListener.h
        audio/WavFile.cpp
        audio/WavFile.h
        audio/WavDefinition.h
        audio/ByteToSampleReader.cpp
        audio/ByteToSampleReader.h
        audio/TConversionTool.cpp
        audio/TConversionTool.h audio/AudioBuffer.cpp audio/AudioBuffer.h)
add_executable(src_run ${SOURCE_FILES})