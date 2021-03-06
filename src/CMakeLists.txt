project(src)

set(HEADER_FILES
        filters/CompositeKeyProbabilityFilter.h
        filters/KeyProbabilityFilter.h
        filters/KeyProbabilitySet.h
        filters/MultiKeyProbabilityFilter.h
        filters/SingleKeyProbabilityFilter.h
        filters/SpiralKeyProbabilityFilter.h
        Accuracy.h
        Bpm.h
        DetectedKey.h
        key/Key.h
        key/KeyCode.h
        key/KeyRelation.h
        key/ShiftedKeyNotation.h
        KeyDetectionMatrix.h
        KeyDetector.h
        KeyProbability.h
        RectangularVectors.h
        stringbuilder.h
        util/Semaphore.h
        util/SortObjectWrapper.h
        util/Task.h
        util/TaskProgressListener.h
        audio/WavFile.h
        audio/WavDefinition.h
        audio/ByteToSampleReader.h
        audio/TConversionTool.h
        audio/AudioBuffer.h
        )

set(SOURCE_FILES
        filters/CompositeKeyProbabilityFilter.cpp
        filters/KeyProbabilityFilter.cpp
        filters/KeyProbabilitySet.cpp
        filters/MultiKeyProbabilityFilter.cpp
        filters/SingleKeyProbabilityFilter.cpp
        filters/SpiralKeyProbabilityFilter.cpp
        Accuracy.cpp
        Bpm.cpp
        DetectedKey.cpp
        key/Key.cpp
        key/KeyCode.cpp
        key/KeyRelation.cpp
        key/ShiftedKeyNotation.cpp
        KeyDetectionMatrix.cpp
        KeyDetector.cpp
        KeyProbability.cpp
        util/Semaphore.cpp
        util/SortObjectWrapper.cpp
        util/Task.cpp
        util/TaskProgressListener.cpp
        audio/WavFile.cpp
        audio/ByteToSampleReader.cpp
        audio/TConversionTool.cpp
        audio/AudioBuffer.cpp
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})