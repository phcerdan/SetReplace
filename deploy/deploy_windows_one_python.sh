#!/usr/bin/env bash

# Assumes that python points to the python you want to use
# This should be managed from other script, or from CI/CD pipelines

# Be aware of dirname not working in azure pipeline bash v3,
# use inline option instead of filepath in .azure-pipelines
# https://github.com/Microsoft/azure-pipelines-tasks/issues/7934
# script_dir=$(cd $(dirname $0) || exit 1; pwd)
script_dir=$(pwd)/deploy

echo "pwd: $(pwd)"
echo "script_dir: $script_dir"
echo "$(python --version)"

python -m pip install cmake
python -m pip install ninja
python -m pip install -r ${script_dir}/../requirements-dev.txt

pushd ${script_dir}
python setup.py bdist_wheel --build-type Release -G "Visual Studio 16 2019" -- \
  -DCMAKE_CXX_STANDARD=14 \
  -DWOLFRAM_MODEL_BUILD_TESTING:BOOL=OFF \
  -DWOLFRAM_MODEL_WRAP_PYTHON:BOOL=ON \
  || exit 1
  # ${PYBIN}/python setup.py clean
popd
