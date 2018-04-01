#!/bin/sh
NAME="onion"
if [ $1 ]
then
  cp TEST_KEYS/private$1.key ./private.key
fi
sudo docker build --tag $NAME:1.0 ./
