from __future__ import print_function
from os import sys, path

try:
    from skbuild import setup
except ImportError:
    print('scikit-build is required to build from source.', file=sys.stderr)
    print('Please run:', file=sys.stderr)
    print('', file=sys.stderr)
    print('  python -m pip install scikit-build')
    sys.exit(1)

sys.path.append(path.dirname(path.dirname(path.abspath(__file__))))
from wolfram_model_version import get_versions

long_description= r'wolfram_model is an open-source, cross-platform library for ' \
                   'exploring Set Substitution Systems (Wolfram Models).\n' \
                   'It produces evolving graphs given a set of rules and initial states. '\
                   'It is proposed as a candidate for a unifying theory of physics by '\
                   'Stephan Wolfram et al.\n'\
                   'The original implementation for the wolfram language can be found '\
                   'in https://github.com/maxitg/SetReplace.'
setup(
    name='wolfram_model',
    version=get_versions()['package-version'],
    author='Pablo Hernandez-Cerdan',
    author_email='pablo.hernandez.cerdan@outlook.com',
    packages=['wolfram_model'],
    package_dir={'wolfram_model': 'wolfram_model'},
    cmake_source_dir='../',
    cmake_args=[
        '-DWOLFRAM_MODEL_BUILD_TESTING:BOOL=OFF',
        '-DWOLFRAM_MODEL_WRAP_PYTHON:BOOL=ON'
    ],
    # cmake_target="install-runtime",
    py_modules=[
        'wolfram_model_version',
    ],
    download_url=r'https://github.com/phcerdan/wolfram_model',
    description=r'wolfram_model is a toolkit to explore Set Substitution Systems (Wolfram Models)',
    long_description=long_description,
    long_description_content_type='text/markdown',
    classifiers=[
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python",
        "Programming Language :: C++",
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Physics",
        "Topic :: Scientific/Engineering :: Mathematics",
        "Topic :: Scientific/Engineering :: Information Analysis",
        "Topic :: Software Development :: Libraries",
        "Operating System :: Android",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: POSIX",
        "Operating System :: Unix",
        "Operating System :: MacOS"
        ],
    license='MIT',
    keywords=r'wolfram_model physics graph complex_networks unifying relativity quantum',
    url=r'https://github.com/phcerdan/wolfram_model',
    install_requires=[
    ]
    )
