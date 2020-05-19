#!/bin/bash

pushd library || exit 1
../generate-cmake.pl '${PROJECT_NAME}'
popd || exit 1

pushd main || exit 1
../generate-cmake.pl '${PROJECT_NAME}'
popd || exit 1