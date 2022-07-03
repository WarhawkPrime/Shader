set(GLM_VERSION "0.9.9")
set(GLM_INCLUDE_DIRS "D:/Documents/Uni/Master/SS_22/Shader/Project/Framework/Framework/libs/glm-master")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
