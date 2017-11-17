#!/usr/bin/env bash

# author     Adrian Antonana
# brief      TITAN package generation with Docker helper script


 TARGET_OS="$1"
 PROJECT_NAME="titan.core"

 case $TARGET_OS in
    "ubuntu" | "debian" | "opensuse" | "centos" | "fedora")
                echo "Building ${PROJECT_NAME}"
                ;;
            *)
                echo "ERROR: Unsupported target OS \"${TARGET_OS}\""
                echo "supported targets are:"
                echo "   ubuntu"
                echo "   debian"
                echo "   opensuse"
                echo "   centos"
                echo "   fedora"
                exit 1
                ;;
 esac

 IMAGE_TAG="${TARGET_OS}:${PROJECT_NAME}"
 IMAGE_PACKAGES_PATH="/work/${PROJECT_NAME}/build/packages/"
 docker build -f Dockerfile.${TARGET_OS} -t ${IMAGE_TAG} .. && \
 CONTAINER_ID=$(docker create ${IMAGE_TAG}) && \
 docker cp ${CONTAINER_ID}:${IMAGE_PACKAGES_PATH} . && \
 docker rm ${CONTAINER_ID}
