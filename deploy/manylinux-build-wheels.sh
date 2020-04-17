#!/usr/bin/env bash

# -----------------------------------------------------------------------
# These variables are set in common script:
#
ARCH=""
PYBINARIES=""

script_dir=$(cd $(dirname $0) || exit 1; pwd)
source "${script_dir}/manylinux-build-common.sh"
# -----------------------------------------------------------------------

pushd ${script_dir}
# Compile wheels re-using standalone project and archive cache
for PYBIN in "${PYBINARIES[@]}"; do
    Python3_EXECUTABLE=${PYBIN}/python
    Python3_INCLUDE_DIR=$( find -L ${PYBIN}/../include/ -name Python.h -exec dirname {} \; )
    Python3_INCLUDE_DIRS=${Python3_INCLUDE_DIR}

    echo ""
    echo "Python3_EXECUTABLE:${Python3_EXECUTABLE}"
    echo "Python3_INCLUDE_DIR:${Python3_INCLUDE_DIR}"

    # Remove when scikit-build includes cmake_target PR:
    # https://github.com/scikit-build/scikit-build/pull/477
    ${PYBIN}/python -m pip uninstall scikit-build -y
    ${PYBIN}/python -m pip install -r ${script_dir}/../requirements-dev.txt

    if [[ -e /work/requirements-dev.txt ]]; then
      ${PYBIN}/pip install --upgrade -r /work/requirements-dev.txt
    fi

    ${PYBIN}/python setup.py bdist_wheel --build-type Release -G Ninja -- \
      -DCMAKE_CXX_COMPILER_TARGET:STRING=$(uname -p)-linux-gnu \
      -DWOLFRAM_MODEL_BUILD_TESTING:BOOL=OFF \
      -DWOLFRAM_MODEL_WRAP_PYTHON:BOOL=ON \
      -DPython3_EXECUTABLE:FILEPATH=${Python3_EXECUTABLE} \
      -DPython3_INCLUDE_DIRS:PATH=${Python3_INCLUDE_DIRS} \
    || exit 1
    # ${PYBIN}/python setup.py clean
done

# Since there are no external shared libraries to bundle into the wheels
# this step will fixup the wheel switching from 'linux' to 'manylinux2014' tag
for whl in dist/*linux_$(uname -p).whl; do
    auditwheel repair ${whl} -w /work/dist/
    rm ${whl}
done
popd
