#!/usr/bin/env bash

EXPECTED="Hello World!"
OUTPUT=$(../brainfuck test_hello_world.bf)

if [ "$OUTPUT" = "$EXPECTED" ]; then
  echo "test_hello_world.bf: PASSED"
else
  echo "test_hello_world.bf: FAILED"
  echo "Expected: '$EXPECTED'"
  echo "Got:      '$OUTPUT'"
fi
