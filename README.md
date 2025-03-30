# Process supervisor from scratch

This is a tool write for learning purpose only.

## The problem

Some service processes may implement different ways to shut down depending on the signal received.
However, the may not implement internal time-outs to trigger these different ways.

E.g.:

1. Send SIGINT and start graceful shut down of children
2. After 10 secs of grace time
2. Send SIGTERM and terminate the children and do clean up tasks

## Solution

Have a supervisor process to capture SIGINT and SIGTERM, transmit the signals according to the example above.

### How to compile

1. `make`

### How to run

1. `./supervisor`
2. `pkill supervisor`
