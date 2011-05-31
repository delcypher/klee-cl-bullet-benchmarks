#!/bin/sh

sed -e 's/%fd<2>/%fd<4>/; s/div.full.f32.*\(%f[0-9]\+\), \(%f[0-9]\+\), \(%f[0-9]\+\);/cvt.f64.f32 %fd1, \2; cvt.f64.f32 %fd2, \3; div.rn.f64 %fd3, %fd1, %fd2; cvt.rn.f32.f64 \1, %fd3;/' "$@"
