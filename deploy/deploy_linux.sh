#!/usr/bin/env bash

script_dir=$(cd $(dirname $0) || exit 1; pwd)

pushd $script_dir/..
mkdir -p $script_dir/dist
docker build -f ./deploy/Dockerfile-dockcross-manylinux2014 . -t phcerdan/wolfram_model-linux
docker cp $(docker create phcerdan/wolfram_model-linux:latest):/work/dist $script_dir/dist
popd
