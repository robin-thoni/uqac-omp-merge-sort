#! /usr/bin/env sh

for tIn in tests/*.in
do
  tOut=$(echo "${tIn}" | sed -re 's/(.+).in/\1/')".out"
  tmpfile=$(mktemp)
  cat "${tIn}" | ./omp-merge-sort --test > "${tmpfile}"
  cmp "${tmpfile}" "${tOut}"
  res=$?
  if [ ${res} -ne 0 ]
  then
    echo "${tIn} failed"
  else
    echo "${tIn} succeded"
    rm "${tmpfile}"
  fi
done
