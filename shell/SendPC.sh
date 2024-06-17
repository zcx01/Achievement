#!/bin/bash
mgs=\{\"extension\":\"\",\"relative\":false,\"time\":14603935,\"type\":4194304,\"unit\":\"\",\"valid\":true,\"value\":${2}\} 
mosquitto_pub -t  $1  -m $mgs $3