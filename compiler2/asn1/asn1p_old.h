/******************************************************************************
 * Copyright (c) 2000-2018 Ericsson Telecom AB
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 *
 * Contributors:
 *   Balasko, Jeno
 *   Forstner, Matyas
 *   Kremer, Peter
 *   Szabados, Kristof
 *   Szabo, Janos Zoltan – initial implementation
 *
 ******************************************************************************/
#ifndef _ASN1P_H
#define _ASN1P_H

#include <sys/types.h>

typedef struct {
  const char *dispname; /**< is like "@...foo.bar" */
  size_t parent_level; /**< 0 means outermost. */
  const char *parent_typename;
  const char *type_name;
  char *sourcecode; /**< to access the field */
} AtNotation_t;

typedef struct {
  size_t nElements;
  AtNotation_t *elements;
} AtNotationList_t;

typedef struct {
  const char *alt; /* alternative */
  const char *alt_dispname;
  const char *alt_typename;
  const char *alt_typedescrname;
  const char **valuenames; /* !!! */
  const char **const_valuenames; /** this replaces valuenames in new
                                     BER stuff */
} OpentypeAlternative_t;

typedef struct {
  size_t nElements;
  OpentypeAlternative_t *elements;
} OpentypeAlternativeList_t;

typedef struct {
  AtNotationList_t anl;
  OpentypeAlternativeList_t oal;
} Opentype_t;

#endif /* _ASN1P_H */
