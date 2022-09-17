#!/bin/zsh
kill -9 $(ps -ef | grep  clock.sh | awk '{print $2}')
kill -9 $(ps -ef | grep  redshift | awk '{print $2}')
kill -9 $(ps -ef | grep  batsignal | awk '{print $2}')

