# Makefile to build and send the project using fxsdk

# Default target
all: build send

# Target to build the project
build:
	fxsdk build-cg

# Target to send the project
send:
	fxsdk send-cg

# Phony targets to avoid conflicts with files named 'all', 'build', or 'send'
.PHONY: all build send
