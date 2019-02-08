// This Test Port skeleton header file was generated by the
// TTCN-3 Compiler of the TTCN-3 Test Executor version CRL 113 200/6 R5A
// for ebotbar (ebotbar@ebotbarVB) on Fri Oct 26 17:43:41 2018

// Copyright (c) 2000-2018 Ericsson Telecom AB

// You may modify this file. Add your attributes and prototypes of your
// member functions here.

#ifndef PortMsg_HH
#define PortMsg_HH

#include "realtimeTimestamp.hh"

namespace realtimeTimestamp {

class PortMsg : public PortMsg_BASE {
  friend void ef__incoming__message(PortMsg& p__pt, const INTEGER& p__msg, const BOOLEAN& p__set__timestamp);
public:
	PortMsg(const char *par_port_name = NULL);
	~PortMsg();

	void set_parameter(const char *parameter_name,
		const char *parameter_value);

private:
	/* void Handle_Fd_Event(int fd, boolean is_readable,
		boolean is_writable, boolean is_error); */
	void Handle_Fd_Event_Error(int fd);
	void Handle_Fd_Event_Writable(int fd);
	void Handle_Fd_Event_Readable(int fd);
	/* void Handle_Timeout(double time_since_last_call); */
protected:
	void user_map(const char *system_port);
	void user_unmap(const char *system_port);

	void user_start();
	void user_stop();

	void outgoing_send(const INTEGER& send_par, FLOAT* timestamp_redirect);
};

} /* end of namespace */

#endif
