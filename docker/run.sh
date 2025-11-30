#!/bin/bash

docker rm qtalk-env

docker run -it --name "qtalk-env" -v "$(pwd)/..:/home/builder/project" qtalk-builder