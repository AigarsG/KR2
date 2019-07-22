#!/bin/bash

BASEDIR=$(dirname $BASH_SOURCE)
ERROR_CMD_ARG_NUM="incorrect number of command line arguments"

source "$BASEDIR/common"

OLD_HEADER_GUARD="$(f_get_project_baseguard $1)_HEADER"
NEW_HEADER_GUARD="$(f_get_project_baseguard $2)_HEADER"

function f_usage
{
	echo -e "Usage:\n\t./rename_project.sh PROJECT_DIR NEW_PROJECT_DIR"
	echo -e "Example:\n\t./rename_project.sh exercise5.12 exercise5.13"
}

function f_rename
{
	# 1. if directory contains old project name change that part to new project
	#	directory
	# 2. check each item in directory
	# 	2.1. if item is a directory
	#		2.1.1. goto step 1
	# 	2.2. if item is a file,
	#		2.2.1. change part of its name containing old project name to
	#			new project name
	#		2.2.2. modify its contents by replacing old project name
	#			to new project dir name

	if [ $# -ne 3 ]; then
		echo "${FUNCNAME[0]}: error: ${ERROR_CMD_ARG_NUM}"
		echo -e "Usage:\n\tf_rename OLD_PROJ_NAME NEW_PROJ_NAME DIR"
		exit 1
	fi

	newdir="${3/$1/$2}"
	mv "$3" "$newdir"

	for item in "$newdir"/*; do
		if [ -d "$item" ]; then
			f_rename "$1" "$2" "$item"
		fi
		if [ -f "$item" ]; then
			sed -i -e "s|${1}|${2}|g" "$item"
			sed -i -e "s|${OLD_HEADER_GUARD}|${NEW_HEADER_GUARD}|g" "$item"
			mv "$item" "${item/$1/$2}"
		fi
	done
}

if [ $# -ne 2 ]; then
	echo "Error: ${ERROR_CMD_ARG_NUM}"
	f_usage
	exit 1
fi

# Exit if project directory does not exist
if [ ! -d "$1" ]; then
	echo "Directory '$1' does not exist"
	f_usage
	exit 1
fi

f_rename "$1" "$2" "$1"
