#!/usr/bin/env bash

# author     Adrian Antonana
# brief      TITAN package generation with Docker

readonly TARGET_OS="$1"
readonly PROJECT_NAME="titan-build-env"
readonly SCRIPT_FULL_PATH="$(readlink -m $(type -p $0))"
readonly SCRIPT_BASE_DIR="$(dirname ${SCRIPT_FULL_PATH})"
readonly TITAN_SOURCES_DIR="$SCRIPT_BASE_DIR/.."
readonly CONTAINER_BUILD_DIR="/work/build-${TARGET_OS}"

case $TARGET_OS in
    "ubuntu" | "debian" | "opensuse" | "fedora")
        echo "Building docker image ${PROJECT_NAME}:${TARGET_OS}"
        ;;
    *)
        echo "ERROR: Unsupported target OS \"${TARGET_OS}\""
        echo "supported targets are:"
        echo "   ubuntu"
        echo "   debian"
        echo "   opensuse"
        echo "   fedora"
        exit 1
        ;;
esac


docker run -it --rm --user "$(id -u):$(id -g)" -v $TITAN_SOURCES_DIR:/work "${PROJECT_NAME}:${TARGET_OS}" /bin/bash -c "[[ ! -d $CONTAINER_BUILD_DIR ]] && mkdir $CONTAINER_BUILD_DIR; cd $CONTAINER_BUILD_DIR; cmake -DBUILD_DOCS=on .. && make -j $(nproc) package"
