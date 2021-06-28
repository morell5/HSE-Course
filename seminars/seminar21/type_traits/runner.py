"""
CE checker
"""

import os
import subprocess


def main():
    """
    CE checker
    """
    for file_name in os.listdir(os.path.dirname(__file__)):
        if file_name.endswith('cpp'):
            process = subprocess.Popen(['g++', '-o', 'out', file_name], stdin=subprocess.PIPE,
                                       stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            _, err = process.communicate()
            if err.decode('utf-8'):
                print('CE: {}'.format(file_name))


if __name__ == '__main__':
    main()
