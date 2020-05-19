VERSION = '0.3.0.4'

def get_versions():
    """Returns versions for the wolfram_model Python package.

    from wolfram_model_version import get_versions

    # Returns the wolfram_model repository version
    get_versions()['version']

    # Returns the package version. Since GitHub Releases do not support the '+'
    # character in file names, this does not contain the local version
    # identifier in nightly builds, i.e.
    #
    #  '4.11.0.dev20170208'
    #
    # instead of
    #
    #  '4.11.0.dev20170208+139.g922f2d9'
    get_versions()['package-version']
    """
    versions = {}
    versions['version'] = VERSION
    versions['package-version'] = VERSION.split('+')[0]
    return versions
