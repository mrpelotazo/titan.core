###############################################################################
# Copyright (c) 2000-2018 Ericsson Telecom AB
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
#
# Contributors:
#   Balasko, Jeno
#
###############################################################################
// README to function test
All command shall be started from this folder (function_test)

1. How to start function test?
make

2. Ho to start function test for one subfolder?
Do it with the subfolder name,
e.g:
make Text_EncDec
make Semantic_Analyser

or 

for the subfolders of folder Semantic_Analyser:
make Semantic_Analyser_Csaba

Note: It is not the same as 
>cd Text_EncDec; ./run_test
because the environment is not prepared with the latter method.

3.How to clean all subfolder?
make clean

4. Which scripts will be executed in the function test?

function_test/Tools/SAtester for:
BER_EncDec
RAW_EncDec
Text_EncDec

function_test/Tools/SAtester.pl for:
Config_Parser
Semantic_Analyser
