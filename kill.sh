#!/bin/bash
kill -9 $(pg clock.sh | awk '{print $2}')
kill -9 $(pg redshift | awk '{print $2}')
kill -9 $(pg batsignal | awk '{print $2}')

