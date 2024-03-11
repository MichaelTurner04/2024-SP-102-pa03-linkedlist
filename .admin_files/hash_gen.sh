#!/bin/bash

# this is because '_' sorts differently with different locales
LC_COLLATE=C

# To produce null strings when no match
shopt -s nullglob
# To enable !(nothis)
shopt -s extglob

# To init the file (anew)
sha512sum ../grade.sh >hashes.txt

arr=(
    !(*hashes.txt)
    ../.gitlab-ci.yml
    ../Cargo.toml
    ../Makefile
    ../tests/cfg_tests/goals/*
    ../tests/cfg_tests/goal_cfgs/*
    ../tests/stdio_tests/goals/*
    ../tests/stdio_tests/inputs/*
    ../tests/arg_tests/args/*
    ../tests/arg_tests/goals/*
    ../tests/arg_tests/files/*
    ../tests/unit_tests/*
)

for file_to_hash in "${arr[@]}"; do
    if [ -f "$file_to_hash" ]; then
        sha512sum "$file_to_hash" >>hashes.txt
    fi
done

shopt -u nullglob
shopt -u extglob
