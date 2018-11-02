#!/bin/bash
###############################################################################
# Copyright (c) 2000-2018 Ericsson Telecom AB
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
#
# Contributors:
#   Balasko, Jeno
#   Baranyi, Botond
#   Pilisi, Gergely
#
###############################################################################

TPD_DIR="./tpdTest/"
XSD_DIR="$TTCN3_DIR/etc/xsd/"
XSD="TPD.xsd"

find $TPD_DIR -type f -name *.tpd | xargs -I {} xmllint --noout --schema $XSD_DIR/$XSD {}

if [ $? -ne 0 ]; then
  echo "Not every .tpd is valid! Overall verdict: fail"
  exit 1
else
  echo "Every .tpd is valid! Overall verdict: pass"
  exit 0
fi
