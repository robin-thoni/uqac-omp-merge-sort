#! /usr/bin/env sh

for exe in omp-merge-sort-seq omp-merge-sort-par
do

echo "Running ${exe}"

for tIn in tests/*.in
do
  tOut=$(echo "${tIn}" | sed -re 's/(.+).in/\1/')".out"
  tmpfile=$(mktemp)
  cat "${tIn}" | "./${exe}" > "${tmpfile}"
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

done
