#!/bin/sh

git clone git@github.com:evolvedlight/pydashie
cd pydashie
python setup.py install
python setup.py develop
