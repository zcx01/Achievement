#!/usr/bin/env python
#-*- coding:utf-8 -*-
import os 
from setuptools import setup, find_packages

MAJOR =1
MINOR =0
PATCH =0
VERSION = f"{MAJOR}.{MINOR}.{PATCH}"

def get_install_requires():
    reqs = [
            'pexpect'
            ]
    return reqs
setup(
	name = "Deployment",
	version = VERSION,
    author ="zcx01",
    author_email = "13509038620@qq.com",
    long_description_content_type="text/markdown",
	url = 'git@github.com:zcx01/Achievement.git',
	long_description = open('README',encoding="utf-8").read(),
    python_requires=">=3.6",
    install_requires=get_install_requires(),
	packages = find_packages(),
 	license = 'Apache',
   	classifiers = [
       'License :: OSI Approved :: Apache Software License',
       'Natural Language :: English',
       'Operating System :: OS Independent',
       'Programming Language :: Python',       
       'Programming Language :: Python :: 3.6',
       'Topic :: Software Development :: Libraries :: Python Modules',
    ],
    package_data={
        '': ['*.csv', '*.txt','.toml','.*json'],
        'config': ['qnx_config']
        }, #这个很重要
    include_package_data=True #也选上

)
