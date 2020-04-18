#!/usr/bin/env bash

# Assumes that python points to the python you want to use
# This should be managed from other script, or from CI/CD pipelines

script_dir=$(cd $(dirname $0) || exit 1; pwd)

echo ""
echo "$(python --version)"

python -m pip install cmake
python -m pip install ninja
python -m pip install delocate
python -m pip install -r ${script_dir}/../requirements-dev.txt

python setup.py bdist_wheel --build-type Release -G Ninja -- \
  -CMAKE_OSX_DEPLOYMENT_TARGET:STRING=10.9
  -DWOLFRAM_MODEL_BUILD_TESTING:BOOL=OFF \
  -DWOLFRAM_MODEL_WRAP_PYTHON:BOOL=ON \
  || exit 1
  # ${PYBIN}/python setup.py clean

delocate-listdeps $PWD/dist/*.whl # lists library dependencies
delocate-wheel $PWD/dist/*.whl # copies library dependencies into wheel
