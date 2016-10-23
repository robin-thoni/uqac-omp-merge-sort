#! /usr/bin/env sh

cat tests/*.in | ./omp-merge-sort --no-array
