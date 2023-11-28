#!/bin/bash

# This script is used to build a CIA file from a 3DSX file.

META_DIR=meta
PRODUCT_CODE=CTR-P-CFBI
UNIQUE_ID=0xF8001

makerom -f cia -o FBI.cia -elf FBI.elf -rsf "$META_DIR/template.rsf" -target t -exefslogo -icon "$META_DIR/icon.icn" -banner "$META_DIR/banner.bnr" -major "$VERSION_MAJOR" -minor "$VERSION_MINOR" -micro "$VERSION_MICRO" -DAPP_PRODUCT_CODE="$PRODUCT_CODE" -DAPP_UNIQUE_ID="$UNIQUE_ID" -logo "$META_DIR/logo_3ds.bcma.lz" 
