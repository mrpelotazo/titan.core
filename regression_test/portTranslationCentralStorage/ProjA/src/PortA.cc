// This Test Port skeleton source file was generated by the
// TTCN-3 Compiler of the TTCN-3 Test Executor version CRL 113 200/6 R5A
// for ebotbar (ebotbar@ebotbarVB) on Thu Dec  6 15:58:49 2018

// Copyright (c) 2000-2018 Ericsson Telecom AB

// You may modify this file. Complete the body of empty functions and
// add your member functions here.

#include "PortA.hh"
#include "A.hh"

namespace A {

PortA_PROVIDER::PortA_PROVIDER(const char *par_port_name)
	: PORT(par_port_name)
{

}

PortA_PROVIDER::~PortA_PROVIDER()
{

}

void PortA_PROVIDER::set_parameter(const char * /*parameter_name*/,
	const char * /*parameter_value*/)
{

}

/*void PortA_PROVIDER::Handle_Fd_Event(int fd, boolean is_readable,
	boolean is_writable, boolean is_error) {}*/

void PortA_PROVIDER::Handle_Fd_Event_Error(int /*fd*/)
{

}

void PortA_PROVIDER::Handle_Fd_Event_Writable(int /*fd*/)
{

}

void PortA_PROVIDER::Handle_Fd_Event_Readable(int /*fd*/)
{

}

/*void PortA_PROVIDER::Handle_Timeout(double time_since_last_call) {}*/

void PortA_PROVIDER::user_map(const char * /*system_port*/)
{

}

void PortA_PROVIDER::user_unmap(const char * /*system_port*/)
{

}

void PortA_PROVIDER::user_start()
{

}

void PortA_PROVIDER::user_stop()
{

}

void PortA_PROVIDER::outgoing_send(const INTEGER& send_par)
{
	incoming_message(send_par * 10 + 6);
}

} /* end of namespace */

