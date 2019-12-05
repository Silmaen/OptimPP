#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *
import datetime
os.chdir(buildDir)

Parser = argparse.ArgumentParser()
args = Parser.parse_args()
doxyfile=os.path.join(srcRoot,"doc","Doxyfile")

cc = os.getcwd()
os.chdir(srcRoot)
# TODO: check for doxygen command!
runcommand("doxygen "+doxyfile)

os.chdir(cc)
