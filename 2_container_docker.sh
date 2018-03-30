#!/bin/sh
CONTAINER_NAME=$1
IMAGE_NAME=onion

PORT=

SHARED=

## FINAL VERSION
OPTION="--rm"

sudo docker run --name $CONTAINER_NAME $PORT -i -t -d $SHRED $OPTION $IMAGE_NAME:1.0 /home/jff/onion

sudo docker attach $CONTAINER_NAME
