/******************************************************************************
 * Copyright (c) 2000-2018 Ericsson Telecom AB
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 *
 * Contributors:
 *   Balasko, Jeno
 *   Lovassy, Arpad
 *
 ******************************************************************************/
package org.eclipse.titan.executor.jni;

/**
 * Transport types for port connections.
 * <p>
 * The original C++ structure can be found at TTCNv3\core\Types.h
 * */
public final class TransportTypeEnum {

	public static final TransportTypeEnum TRANSPORT_LOCAL = new TransportTypeEnum(0);
	public static final TransportTypeEnum TRANSPORT_INET_STREAM = new TransportTypeEnum(1);
	public static final TransportTypeEnum TRANSPORT_UNIX_STREAM = new TransportTypeEnum(2);
	public static final TransportTypeEnum TRANSPORT_NUM = new TransportTypeEnum(3);

	private int enum_value;

	private TransportTypeEnum(final int value) {
		enum_value = value;
	}

	public int getValue() {
		return enum_value;
	}
}
