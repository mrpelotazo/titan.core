#!/bin/bash
##############################################################################
# Copyright (c) 2000-2018 Ericsson Telecom AB
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v1.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v10.html
#
# Contributors:
##############################################################################
xsd="$(dirname $(readlink -n -f $0))/*.xsd"

xsd2ttcn $xsd
