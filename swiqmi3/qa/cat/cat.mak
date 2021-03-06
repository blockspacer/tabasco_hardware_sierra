#-------------------------------------------------------------------------------
#
#  Name:
#    cat.mak
#
#  Description:
#    Makefile to build the pkgs/qa/cat package
#
#   The following make targets are available in this makefile:
#
#     all           - make .o and .a image files (default)
#                     Test programs are also built when present
#     clean         - delete object directory and image files
#
#   The above targets can be made with the following command:
#
# Copyright (c) 2010 by Sierra Wireless, Incorporated.  All Rights Reserved.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Local Settings
#-------------------------------------------------------------------------------
SRCS_CAT = cat/src/qaGobiApiCat.c \
           cat/src/qaCatSendEnvelopeCmd.c \
           cat/src/qaCatSendTerminalResponse.c

#-------------------------------------------------------------------------------
# Split the object files into their respective groups
#-------------------------------------------------------------------------------
CATOBJ   = $(OBJSDIR)/qaGobiApiCat.o \
           $(OBJSDIR)/qaCatSendEnvelopeCmd.o \
           $(OBJSDIR)/qaCatSendTerminalResponse.o

