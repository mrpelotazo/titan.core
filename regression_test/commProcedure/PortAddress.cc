/******************************************************************************
 * Copyright (c) 2000-2018 Ericsson Telecom AB
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 *
 * Contributors:
 *   Balasko, Jeno
 *   Feher, Csaba
 *   Lovassy, Arpad
 *   Raduly, Csaba
 *   Szabo, Janos Zoltan – initial implementation
 *   Tatarka, Gabor
 *
 ******************************************************************************/
// This Test Port skeleton source file was generated by the
// TTCN-3 Compiler of the TTCN-3 Test Executor version 1.4.pl3
// for Gabor Tatarka (tmpgta@pythagoras) on Tue Jul 29 10:50:23 2003


// You may modify this file. Complete the body of empty functions and
// add your member functions here.

#include "PortAddress.hh"

#ifndef OLD_NAMES
namespace ProcPort {
#endif

PortAddress::PortAddress(const char *par_port_name)
	: PortAddress_BASE(par_port_name)
{

}

PortAddress::~PortAddress()
{

}

void PortAddress::set_parameter(const char *parameter_name,
	const char *parameter_value)
{

}

void PortAddress::Handle_Fd_Event(int fd, boolean is_readable,
	boolean is_writable, boolean is_error)
{

}

void PortAddress::user_map(const char *system_port)
{

}

void PortAddress::user_unmap(const char *system_port)
{

}

void PortAddress::user_start()
{

}

void PortAddress::user_stop()
{

}

void PortAddress::outgoing_call(const MyProc_call& call_par,
	const ADDRESS *destination_address)
{
	ADDRESS a;
	if(destination_address==NULL)TTCN_error("Address is a NULL pointer.");
	a.a1()=destination_address->a2();
	a.a2()=destination_address->a1();
	if(a.a1()==67) {
		MyProc_reply tmp;
		tmp.Par2()="CharString";tmp.Par3()=1.41;tmp.return_value()=true;
		incoming_reply(tmp,&a);
	} else if(a.a1()==68) {
		incoming_exception(MyProc_exception(INTEGER(a.a1()+a.a2())),&a);
	} else TTCN_error("Error in address.");
}

void PortAddress::outgoing_call(const s__StopPTC_call& call_par,
	const ADDRESS *destination_address)
{

}

void PortAddress::outgoing_reply(const MyProc_reply& reply_par,
	const ADDRESS *destination_address)
{

}

void PortAddress::outgoing_reply(const s__StopPTC_reply& reply_par,
	const ADDRESS *destination_address)
{

}

void PortAddress::outgoing_reply(const MyProc2_reply& reply_par,
	const ADDRESS *destination_address)
{

}

void PortAddress::outgoing_raise(const MyProc_exception& raise_exception,
	const ADDRESS *destination_address)
{

}

#ifndef OLD_NAMES
} /* end of namespace */
#endif
