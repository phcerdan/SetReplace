#!/usr/bin/env python

import os
import sys
import argparse

parser = argparse.ArgumentParser(description='Increase version of wolfram_model_version')

parser.add_argument("-c", "--component", dest="version_component",
                    default="extra",
                    help="What version component to update, options: major, minor, patch, extra")
parser.add_argument("-n", "--no-write", dest="no_write",
                    action='store_true',
                    help="Do not perform the write. Useful to check results before.")
args = parser.parse_args()
if args.version_component  == "major":
    version_index = 0
elif args.version_component  == "minor":
    version_index = 1
elif args.version_component  == "patch":
    version_index = 2
elif args.version_component  == "extra":
    version_index = 3
else:
    raise argparse.ArgumentError(args.version_component, "unknown version component")

max_version_index = 3
print("incrementing version component:", args.version_component, "| version_index:", version_index)

this_dir = os.path.dirname(os.path.realpath(__file__))
version_file = os.path.join(this_dir, 'wolfram_model_version.py')

if not os.path.exists(version_file):
    print('Expected file ' + version_file+ ' not found!')
    sys.exit(1)
with open(version_file, 'r') as fp:
    lines = fp.readlines()
    for line in lines:
        if line.startswith('VERSION = '):
            current_version_str = line.split('=')[1].strip().replace("'","")

print("current_version: ", current_version_str)

final_version = [int(comp) for comp in current_version_str.split('.')]

final_version[version_index] = final_version[version_index] + 1
for comp in range(version_index + 1, max_version_index + 1):
    final_version[comp] = 0

final_version_str = ".".join([str(comp) for comp in final_version])
print("final_version: ", final_version_str)

if not final_version_str:
    raise Exception(final_version_str)

if args.no_write:
    print("Not writting to file, remove -n or --no-write argument if wanted.")
    sys.exit()

with open(version_file, 'w') as fp:
    for line in lines:
        if line.startswith('VERSION = '):
            fp.write("VERSION = '")
            fp.write(final_version_str)
            fp.write("'\n")
        else:
            fp.write(line)
