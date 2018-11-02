/******************************************************************************
 * Copyright (c) 2000-2018 Ericsson Telecom AB
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 *
 * Contributors:
 *   Balasko, Jeno
 *   Kremer, Peter
 *   Szabo, Janos Zoltan – initial implementation
 *
 ******************************************************************************/
#ifndef TTCN3_PREPARSER_H
#define TTCN3_PREPARSER_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int is_ttcn3_module(const char *file_name, FILE *fp, char **module_name);

#ifdef __cplusplus
}
#endif

#endif /* TTCN3_PREPARSER_H */
