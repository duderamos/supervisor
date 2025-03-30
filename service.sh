#!/bin/bash

set -eo pipefail -x

function term() {
  echo "processing term"
  sleep 2
  exit 0
}

function int() {
  while true ; do echo "processing init" ; sleep 1 ; done
  exit 0
}

trap term SIGTERM
trap int SIGINT

while true ; do
  echo "ping."
  sleep 1
done
