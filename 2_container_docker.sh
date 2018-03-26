#!/bin/sh
CONTAINER_NAME=$1
IMAGE_NAME=onion

PORT=
#"-p 20003:22"

SHARED=

## FINAL VERSION
#OPTION="--read-only --rm"

OPTION="--rm"

sudo docker run --name $CONTAINER_NAME $PORT -i -t -d $SHRED $OPTION $IMAGE_NAME:1.0 /bin/sh

sudo docker attach $CONTAINER_NAME
