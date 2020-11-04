#!/bin/sh
rm -rf bin/out
gcc -I headers/ lib/log.c lib/arraylist.c sources/models.c sources/admission_manager.c sources/main.c -o bin/out
bin/out