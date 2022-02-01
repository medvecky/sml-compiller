#!/bin/bash

MOUNT_DIR=$PWD:/home/project
WORKING_DIR=/home/project

docker run -e CPPUTEST_HOME=cpputest -it  -v $MOUNT_DIR -w $WORKING_DIR sc_docker ./make-tests.sh 
