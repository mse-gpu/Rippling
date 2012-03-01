# Version 0.0.2 - 27.01.2012
#
# Cedric.Bilat@he-arc.ch
#
# Contrainte
#
#	Dans les d�finitions de variables ci-dessous, ne laisser jamais d'espace � la fin!!!
#

#########
#Project#
#########

#Name target,without extension
TARGET_NAME:=Ripling

#EXE
#SHARED_LIB
#STATIC_LIB 
TARGET_MODE:=EXE

#Path where target will be build (relative or absolute for a ram disk by example)
#TARGET_PATH:=Q:/${USER}/Targets/${TARGET_NAME}
TARGET_PATH:=/tmp/ramdrive/${USER}/Targets/${TARGET_NAME}
#TARGET_PATH:=target

#Path where the targe will be copied just after building process (usefull for link project's)
#mimimum : nothing
TARGET_DEPLOY_PATH:=#../PRODUCTION/Deploy/bin

#Define variable Compilation
#Same as #define XXX (in .ccp code)
#mimimum : rien
#multiple variable : separateur espace
CODE_DEFINE_VARIABLES+=


#Etend le folder src du projet
#Conseil: Use this to specify .lib or .h in a workspace where projectA use output of ProjectB
#Circular dependancy are not allowed!
#Use space if multiple dependency to separate folder to include
#minimum : rien
SRC_AUX:=  ../cppTestAPI ../Common/src/core

#########
#  End  #
#########