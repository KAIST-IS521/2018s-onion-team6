#!/bin/sh
NAME="onion"

PORT="-p 20000:22"

SHARED=

## FINAL VERSION
#OPTION="--read-only --rm"

OPTION="--rm"

sudo docker run --name $NAME $PORT -i -t -d $SHRED $OPTION $NAME:1.0 /bin/sh

