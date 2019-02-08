#!/usr/bin/env bash

# author     Adrian Antonana
# brief      Docker image build helper script


TARGET_OS="$1"
PROJECT_NAME="titan-build-env"

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

docker build -f Dockerfile.${TARGET_OS} -t "${PROJECT_NAME}:${TARGET_OS}" .
