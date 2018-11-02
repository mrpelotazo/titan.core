/******************************************************************************
 * Copyright (c) 2000-2018 Ericsson Telecom AB
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 *
 * Contributors:
 *   Balasko, Jeno
 *   Godar, Marton
 *   Raduly, Csaba
 *   Szabo, Bence Janos
 *
 ******************************************************************************/
#ifndef IMPORTSTATEMENT_HH_
#define IMPORTSTATEMENT_HH_

#include "RootType.hh"

/**
 * Type that contains information coming from XSD import and include tags
 *
 * Source in XSD:
 *
 * 	* <import namespace="..." schemaLocation="..."/>
 * 	* <include schemaLocation="..."/>
 *
 * Result in TTCN-3:
 *
 * 	* TTCN-3 import statement
 * 	* Real inclusion of the referenced datatypes
 *
 */
class ImportStatement : public RootType {
    /// Originally, the "namespace" attribute of the <import>
    Mstring from_namespace;
    /// Originally, the "schemaLocation" attribute of the <import>
    Mstring from_schemaLocation;
    /// Result of the reference resolving function:
    /// The module we want to import from. Not owned.
    TTCN3Module *source_module;

    ImportStatement(const ImportStatement &); // not implemented
    ImportStatement & operator=(const ImportStatement &); // not implemented
    // Default destructor is used
public:
    ImportStatement(XMLParser * a_parser, TTCN3Module * a_module, ConstructType a_construct);

    /** Virtual methods
     *  inherited from the abstract RootType
     */
    void loadWithValues();
    void referenceResolving();

    void validityChecking() {
    }
    void printToFile(FILE * file);
    
    const TTCN3Module* getSourceModule() { return source_module; }

    void dump(unsigned int depth) const;
};

#endif /* IMPORTSTATEMENT_HH_ */
