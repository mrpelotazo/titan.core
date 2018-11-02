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
package org.eclipse.titan.executorapi.test;

import static org.junit.Assert.assertTrue;

import org.eclipse.titan.executor.jni.McStateEnum;
import org.eclipse.titan.executorapi.JniExecutor;
import org.eclipse.titan.executorapi.util.Log;

/**
 * Utility functions for JniExecutor tests
 */
public class TestUtil {

	/**
	 * @param aAssertedState expected MC state
	 * @throws AssertionError if current MC state is not the expected state
	 */
	public static void assertState( final McStateEnum aAssertedState ) {
		Log.fi(aAssertedState);
		final JniExecutor je = JniExecutor.getInstance();
		assertTrue( je.isConnected() );
		final McStateEnum state = je.getState();
		assertTrue( state == aAssertedState );
		Log.fo();
	}
}
