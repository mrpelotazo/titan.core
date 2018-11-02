##############################################################################
# Copyright (c) 2000-2018 Ericsson Telecom AB
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
#
# Contributors:
#   Balasko, Jeno
#   Delic, Adam
#
##############################################################################
import xml.etree.ElementTree as ET
tree = ET.parse('project_hierarchy_graph.xml')
root = tree.getroot()
f = open('project_hierarchy_graph.dot', 'w')
f.write("digraph PROJECT_HIERARCHY_GRAPH {\n")
for project in root:
	for reference in project:
		f.write(project.attrib['name'])
		f.write(" -> ")
		f.write(reference.attrib['name'])
		f.write(";\n")
f.write("}\n")
f.close()

# use this to generate graph:
# > dot -Tpng project_hierarchy_graph.dot -o project_hierarchy_graph.png
